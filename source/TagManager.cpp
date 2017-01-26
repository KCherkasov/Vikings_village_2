#include "TagManager.h"

size_t TagManager::find_tag(const size_t& tag_id, const size_t& start_pos, const std::string& source) const {
  size_t tag_pos = source.size();
  if (tag_id < _tag_list.size() && start_pos < source.size()) {
    for (size_t i = start_pos; i < source.size(); ++i) {
      size_t k = 0;
      for (size_t j = i; _tag_list[tag_id][k] == source[j] && j < source.size() && k < _tag_list[tag_id].size(); ++j, ++k);
      if (k == _tag_list[tag_id].size()) {
      	tag_pos = i;
      	break;
      }
    }
  }
  return tag_pos;
}

size_t TagManager::add_tag(const std::string& new_tag) {
  if (!new_tag.empty()) {
    _tag_list.push_back(new_tag);
    return MR_OK;
  } else {
    return MR_BAD_INPUT;
  }
}

size_t TagManager::add_tag(const char* new_tag) {
  if (new_tag == NULL) {
  	return MR_BAD_INPUT;
  }
  std::string to_add(new_tag);
  _tag_list.push_back(to_add);
  return MR_OK;
}

size_t TagManager::remove_tag(const size_t& tag_id) {
  if (tag_id < _tag_list.size()) {
    _tag_list.erase(_tag_list.begin() + tag_id);
    return MR_OK;
  } else {
    return MR_BAD_INDEX;
  }
}

size_t TagManager::remove_tag(const std::string& tag) {
  for (size_t i = 0; i < _tag_list.size(); ++i) {
    if (tag == _tag_list[i]) {
      _tag_list.erase(_tag_list.begin() + i);
      return MR_OK;
    }
  }
  return MR_NOT_FOUND;
}

size_t TagManager::get_by_tag(const size_t& tag_id, const size_t& start_pos, const std::string& source, std::string& result) const {
  result.clear();
  size_t tag_start = find_tag(tag_id, start_pos, source);
  if (tag_start == source.size()) {
    return tag_start;
  }
  tag_start += _tag_list[tag_id].size();
  tag_start = std::min(source.size(), tag_start);
  size_t tag_end = find_tag(tag_id, tag_start, source);
  if (tag_end == source.size()) {
  	--tag_end;
  }
  for (size_t i = tag_start; i < tag_end; ++i) {
    result.push_back(source[i]);
  }
  return std::min(tag_end, source.size());
}

size_t TagManager::replace_tag(const size_t& tag_id, const size_t& start_pos, std::string& source, const std::string& replacement) const {
  size_t replacement_pos = source.size();
  if (start_pos < source.size() && tag_id < _tag_list.size()) {
    replacement_pos = find_tag(tag_id, start_pos, source);
    if (replacement_pos < source.size()) {
      std::string pre_source;
      std::string post_source;
      for (size_t i = 0; i < replacement_pos; ++i) {
        pre_source.push_back(source[i]);
      }
      for (size_t i = replacement_pos + _tag_list[tag_id].size(); i < source.size(); ++i) {
        post_source.push_back(source[i]);
      }
      pre_source += replacement;
      pre_source += post_source;
      source.clear();
      post_source.clear();
      source = pre_source;
      pre_source.clear();
    }
  }
  return replacement_pos + replacement.size();
}
