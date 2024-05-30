#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream( uint64_t capacity ) :
  capacity_( capacity ),
  push_bytes_(0),
  pop_bytes_(0),
  closed(false),
  buffer_(),
  error_( false)
{
}

bool Writer::is_closed() const
{
  return closed;
}

void Writer::push( string data )
{
  if (data.empty() || is_closed() || has_error()) {
    return;
  }

  uint64_t allowed_size = min(available_capacity(), data.size());
  data = data.substr(0, allowed_size);


  for (char i : data){
    buffer_.push_back(i);
  }

  push_bytes_ += allowed_size;
}

void Writer::close()
{
  closed = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  // Your code here.
  return push_bytes_;
}

bool Reader::is_finished() const
{
  // Your code here.
  return closed && buffer_.empty();
}

uint64_t Reader::bytes_popped() const
{
  // Your code here.
  return pop_bytes_;
}

string_view Reader::peek() const
{
  return {&buffer_.front(), 1};
}

void Reader::pop( uint64_t len )
{
  // Your code here.
  const uint64_t length = min(len, buffer_.size());
  uint64_t _size = length;
  while(_size-- > 0) {
    buffer_.pop_front();
  }
  pop_bytes_ += length;

}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}
