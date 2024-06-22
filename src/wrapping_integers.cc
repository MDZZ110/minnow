#include "wrapping_integers.hh"

using namespace std;

Wrap32 Wrap32::wrap( uint64_t n, Wrap32 zero_point )
{
  uint64_t left_half_abs_seqno = n % (1LL << 32);
  return zero_point + static_cast<uint32_t>(left_half_abs_seqno);
}

uint64_t Wrap32::unwrap( Wrap32 zero_point, uint64_t checkpoint ) const
{
  // Your code here.
  uint64_t right_half_abs_seqno;
  if (zero_point.raw_value_ > raw_value_) {
    right_half_abs_seqno = static_cast<uint64_t>(raw_value_) + static_cast<uint64_t> (1UL << 32) - static_cast<uint64_t>(zero_point.raw_value_);
  } else {
    right_half_abs_seqno = static_cast<uint64_t>(raw_value_) - static_cast<uint64_t>(zero_point.raw_value_);
  }

  uint64_t right_half_checkpoint_seqno = checkpoint % (1UL << 32);
  uint64_t left_half_checkpoint_seqno = checkpoint - right_half_checkpoint_seqno;
  uint64_t converted;
  if (right_half_checkpoint_seqno > right_half_abs_seqno) {
    if (right_half_checkpoint_seqno - right_half_abs_seqno >= (1UL << 31)) {
      converted = static_cast<uint64_t>(1UL << 32) + left_half_checkpoint_seqno + right_half_abs_seqno;
    } else {
      converted = left_half_checkpoint_seqno + right_half_abs_seqno;
    }
  } else {
    converted = left_half_checkpoint_seqno + right_half_abs_seqno;
    if (( right_half_abs_seqno - right_half_checkpoint_seqno >= 1UL << 31) && (left_half_checkpoint_seqno >= 1UL << 32)){
      converted = left_half_checkpoint_seqno + right_half_abs_seqno - (1UL << 32);
    }
  }
  return converted;
}
