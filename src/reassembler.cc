#include "reassembler.hh"
#include "vector"
#include <sstream>

using namespace std;

void Reassembler::insert( uint64_t first_index, string data, bool is_last_substring )
{
  // Your code here.
  std::vector<uint64_t> related_cache_indexes;

  for (auto & itr : cache) {
    uint64_t item_left = itr.first;
    uint64_t item_right = itr.first + itr.second.size();
    uint64_t data_left = first_index;
    uint64_t data_right = first_index + data.size();
    // overlapping or duplicated
    if ((data_left <= item_right) and (data_right >= item_left)) {
      related_cache_indexes.push_back(itr.first);
    }
  }

  std::map<uint64_t, std::string> new_cache;
  stringstream concat_stream;
  uint64_t curr_index = first_index;
  string curr_merged = data;

  for(uint64_t index: related_cache_indexes) {
    curr_merged = merge_string(index, curr_index, move(cache[index]), move(curr_merged));
    curr_index = index <= curr_index? index:curr_index;
    cache.erase(index);
  }

  if (next_index == curr_index) {
    output_.writer().push(curr_merged);
    next_index += curr_merged.size();
  } else {
    cache[curr_index] = curr_merged;
  }


  if (is_last_substring) {
    output_.writer().close();
  }

}


uint64_t Reassembler::bytes_pending() const
{
  uint64_t pending;
  for(auto& itr: cache) {
    pending += itr.second.size();
  }
  return pending;
}

string  Reassembler::merge_string(uint64_t index_a, uint64_t index_b, string&& string_a, string&& string_b) {
  uint64_t front_index = index_a<=index_b?index_a:index_b;
  uint64_t behind_index = index_a<=index_b?index_b:index_a;;
  string&& front = move(front_index==index_a?string_a:string_b);
  string&& behind = move(behind_index==index_a?string_a:string_b);
  if (front_index + front.size() >= behind_index + behind.size()) {
    return front;
  }

  stringstream ss;
  ss << front;
  uint64_t  behind_trim_prefix_length = front.size() - behind_index + front_index;
  if (behind.size() > behind_trim_prefix_length) {
    ss << behind.substr(behind_trim_prefix_length);
  }

  return ss.str();
}
