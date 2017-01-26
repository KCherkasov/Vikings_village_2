#ifndef TAG_MANAGER_H
#define TAG_MANAGER_H

#include <iostream>
#include <string>
#include <vector>

enum ManagerResponse { MR_OK, MR_NOT_FOUND, MR_BAD_INDEX, MR_BAD_INPUT, MR_SIZE };

class TagManager {
  public:
    TagManager() {}
    TagManager(const std::vector<std::string>& tag_list): _tag_list(tag_list) {}
    ~TagManager() {}
    size_t tags_count() const { return _tag_list.size(); }
    std::string tag(const size_t& id) const { std::string result; if (id < _tag_list.size()) { result = _tag_list[id]; } return result; }
    size_t add_tag(const std::string& new_tag);
    size_t add_tag(const char* new_tag);
    size_t remove_tag(const size_t& tag_id);
    size_t remove_tag(const std::string& tag);
    size_t get_by_tag(const size_t& tag_id, const size_t& start_pos, const std::string& source, std::string& result) const;
    size_t replace_tag(const size_t& tag_id, const size_t& start_pos, std::string& source, const std::string& replacement) const;
  private:
    size_t find_tag(const size_t& tag_id, const size_t& start_pos, const std::string& source) const;

    std::vector<std::string> _tag_list;
};

#endif
