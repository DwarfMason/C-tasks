#include <vector>
#include <algorithm>

class Set {
 private:
  std::vector<int64_t> set_;

  void MakeSet() {
    sort(set_.begin(), set_.end());
    set_.resize(unique(set_.begin(), set_.end()) - set_.begin());
  }

 public:
  explicit Set(const std::vector<int64_t> &set) : set_(set) {
    sort(set_.begin(), set_.end());
    set_.resize(unique(set_.begin(), set_.end()) - set_.begin());
  }

  explicit Set() {}

  Set Union(const Set &set) {
    std::vector<int64_t> buff;
    buff = set_;
    for (int i = 0; i < set.set_.size(); i++)
      buff.push_back(set.set_[i]);
    return Set(buff);
  }

  Set Intersection(const Set &set) {
    std::vector<int64_t> buff;
    for (int i = 0; i < set.set_.size(); i++)
      if (Set(set_).Contains(set.set_[i]))
        buff.push_back(set.set_[i]);
    return Set(buff);
  }

  Set Difference(const Set &set) {
    std::vector<int64_t> buff;
    for (int i = 0; i < set_.size(); i++)
      if (!Set(set.set_).Contains(set_[i]))
        buff.push_back(set_[i]);
    return Set(buff);
  }

  Set SymmetricDifference(const Set &set) {
    return Set(set_).Union(set).Difference(Set(set_).Intersection(set));
  }

  bool Contains(int64_t value) {
    for (int i = 0; i < set_.size(); i++)
      if (set_[i] == value)
        return true;
    return false;
  }

  void Add(int64_t value) {
    set_.push_back(value);
    MakeSet();
  }

  void Remove(int64_t value) {
    if (Set(set_).Contains(value))
      for (int i = 0; i < set_.size(); i++) {
        if (set_[i] == value) {
          set_.erase(set_.begin() + i);
          break;
        }
      }
  }

  std::vector<int64_t> Data() {
    return set_;
  }
};
