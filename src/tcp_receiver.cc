#include "tcp_receiver.hh"

using namespace std;

void TCPReceiver::receive( TCPSenderMessage message )
{
  if (message.RST) {
    reader().set_error();
    return;
  }


  if (message.SYN) {
//    if (zero_point_.has_value() || ackno_.has_value()) {
//      return;
//    }

    zero_point_ = Wrap32(message.seqno);
  }

  if (zero_point_.has_value()) {
    uint64_t first_abs_index = message.seqno.unwrap(zero_point_.value(), get_checkpoint_abs_seqno()+1);
    if (!message.SYN) {
      if (first_abs_index == 0) {
        return;
      }
      first_abs_index--;
    }
    reassembler_.insert(first_abs_index, std::move(message.payload), message.FIN);

    uint64_t byte_pushed = reassembler_.writer().bytes_pushed();
    ackno_ = zero_point_.value() + static_cast<uint32_t>(1+byte_pushed+reassembler_.writer().is_closed());
  }

  return;
}

TCPReceiverMessage TCPReceiver::send() const
{
  uint16_t window_size = UINT16_MAX;
  if(writer().available_capacity() < window_size) {
    window_size = static_cast<uint16_t>(writer().available_capacity());
  }
  // Your code here.
  return {
    ackno_, window_size, reader().has_error()
  };
}
