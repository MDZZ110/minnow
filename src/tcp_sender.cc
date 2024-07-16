#include "tcp_sender.hh"
#include "tcp_config.hh"
#include <iostream>
using namespace std;

uint64_t TCPSender::sequence_numbers_in_flight() const
{
  // Your code here.
  return seqs_in_flight_;
}

uint64_t TCPSender::consecutive_retransmissions() const
{
  // Your code here.
  return retransmission_nums_;
}

// chenzheng
// mock pushing data from user space to kernel space
void TCPSender::push( const TransmitFunction& transmit )
{
  // Your code here

  uint64_t available_window = receiver_window_ - seqs_in_flight_;
  if (receiver_window_ == 0) {
    available_window = 1;
  }


  while((available_window > 0) && (!is_fin_sent_)) {
    uint64_t max_payload_length = min(TCPConfig::MAX_PAYLOAD_SIZE, available_window);
    std::cout<< "max length before handling: " << max_payload_length << std::endl;
    TCPSenderMessage message;
    if (current_abs_seq_ == 0) {
      message.SYN = true;
      max_payload_length--;
    }

    if (input_.reader().has_error()) {
      message.RST = true;
    }

    while ((message.payload.size() < max_payload_length) && (input_.reader().bytes_buffered() > 0) ){
      string_view front_view = input_.reader().peek();
      uint64_t bytes_to_read = min(front_view.size(), max_payload_length - message.payload.size());
      message.payload += front_view.substr(0, bytes_to_read);
      input_.reader().pop(bytes_to_read);
      max_payload_length--;
    }

    if (input_.reader().is_finished() && (max_payload_length >= 1)) {
      message.FIN = true;
      is_fin_sent_ = true;
    }

    std::cout<< "window size: "<< receiver_window_ << "  payload size: "<< message.payload.size() << ", max length: " << max_payload_length << " messge seq length: "<< message.sequence_length() << std::endl;
    if (message.sequence_length() == 0) {
      return;
    }



    message.seqno = Wrap32::wrap(current_abs_seq_, isn_);
    current_abs_seq_ += message.sequence_length();

    transmit(message);
    seqs_in_flight_ += message.sequence_length();
    segment_inflight_queue.push(message);
    available_window -= message.sequence_length();

    if (expire_time_ms_ == UINT64_MAX) {
      expire_time_ms_ = current_time_ms_ + rto_;
    }
  }
}

TCPSenderMessage TCPSender::make_empty_message() const
{
  // Your code here.
  TCPSenderMessage message;
  message.SYN = false;
  message.FIN = false;
  message.RST = false;
  message.payload = "";
  message.seqno = Wrap32::wrap(current_abs_seq_, isn_);
  return message;
}

void TCPSender::receive( const TCPReceiverMessage& msg )
{
  // Your code here.
  if (msg.ackno.has_value()) {
    uint64_t recv_ack_abs_seq = msg.ackno.value().unwrap(isn_, abs_ack_);
    while(!segment_inflight_queue.empty()) {
      TCPSenderMessage msg_in_flight = segment_inflight_queue.front();
      uint64_t in_flight_abs_seq = msg_in_flight.seqno.unwrap(isn_, abs_ack_);
      if (recv_ack_abs_seq >= (in_flight_abs_seq + msg_in_flight.sequence_length())) {
        abs_ack_ = in_flight_abs_seq + msg_in_flight.sequence_length();
        segment_inflight_queue.pop();
        retransmission_nums_ = 0;
        rto_ = initial_RTO_ms_;
        expire_time_ms_ = current_time_ms_ + rto_;
        seqs_in_flight_ -= msg_in_flight.sequence_length();
      } else {
        break;
      }
    }

    if (segment_inflight_queue.empty()) {
      expire_time_ms_ = UINT64_MAX;
    }

  }

  if (msg.RST) {
    input_.reader().set_error();
  }

  receiver_window_ = msg.window_size;

}

void TCPSender::tick( uint64_t ms_since_last_tick, const TransmitFunction& transmit )
{
  // Your code here.
  current_time_ms_ += ms_since_last_tick;
  if (!segment_inflight_queue.empty() && (current_time_ms_ >= expire_time_ms_)) {
    rto_ *= 2;
    expire_time_ms_ = current_time_ms_ + rto_;

//    if (retransmission_nums_++ > TCPConfig::MAX_RETX_ATTEMPTS) {
//      input_.reader().set_error();
//      return;
//    }
    retransmission_nums_++ ;
    transmit(segment_inflight_queue.front());
  }
}
