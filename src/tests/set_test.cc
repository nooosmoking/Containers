#include <gtest/gtest.h>

#include <functional>
#include <set>
#include <string>
#include <utility>

#include "../s21_set.h"

class NoDefault {
 public:
  NoDefault() = delete;
  explicit NoDefault(char ch) : ch_(ch) {}
  NoDefault(const NoDefault &x) : ch_(x.ch_) {}
  NoDefault(NoDefault &&x) { *this = std::move(x); }
  NoDefault &operator=(const NoDefault &x) {
    ch_ = x.ch_;
    return *this;
  }
  NoDefault &operator=(NoDefault &&x) {
    if (this != &x) {
      ch_ = std::move(x.ch_);
    }
    return *this;
  }
  bool operator==(const NoDefault &x) { return ch_ == x.ch_; }
  char ch() const { return ch_; }
  void set_ch(const char ch) { ch_ = ch; }

 private:
  char ch_;
};

bool operator==(const NoDefault &x, const NoDefault &y) {
  return x.ch() == y.ch();
}

struct CompareNoDef {
  bool operator()(const NoDefault &n1, const NoDefault &n2) const {
    return n1.ch() > n2.ch();
  }
};

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
bool compare_sets(const s21::set<Key, Comparator, Allocator> &my_set,
                  const std::set<Key, Comparator, Allocator> &std_set) {
  bool result = my_set.size() == std_set.size();
  if (result) {
    auto my_it = my_set.begin();
    auto std_it = std_set.begin();
    for (size_t i = 0; i != my_set.size() && result; ++i) {
      result = *my_it == *std_it;
      ++my_it;
      ++std_it;
    }
  }
  return result;
}

TEST(SetTest, DefaultConstructorInt) {
  s21::set<int> my_set;
  std::set<int> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, DefaultConstructorString) {
  s21::set<std::string> my_set;
  std::set<std::string> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, DefaultConstructorNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set;
  std::set<NoDefault, CompareNoDef> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InitConstructorConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, CopyConstructorInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, CopyConstructorConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, MoveConstructorInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, MoveConstructorString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, MoveConstructorNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, AssignCopyInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  s21::set<int> my_set_copy{-1, -2, -300, -4, -5, 7, 7, 800};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set_copy{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, AssignCopyString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  s21::set<std::string> my_set_copy{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  std::set<std::string> std_set_copy{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, AssignCopyNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_set_copy{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set_copy{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(SetTest, AssignMoveInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  s21::set<int> my_set_move{-1, -2, -300, -4, -5, 7, 7, 800};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set_move{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, AssignMoveString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  s21::set<std::string> my_set_move{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  std::set<std::string> std_set_move{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, AssignMoveNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_set_move{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set_move{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(SetTest, BeginInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, BeginConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, BeginString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, BeginConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, BeginNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, BeginConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EndConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(SetTest, EmptyInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  s21::set<int> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, EmptyConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const s21::set<int> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, EmptyString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  s21::set<std::string> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, EmptyConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const s21::set<std::string> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, EmptyNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, EmptyConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const s21::set<NoDefault, CompareNoDef> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(SetTest, SizeInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, SizeConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeInt) {
  s21::set<int> my_set;
  std::set<int> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeConstInt) {
  const s21::set<int> my_set;
  const std::set<int> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeString) {
  s21::set<std::string> my_set;
  std::set<std::string> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeConstString) {
  const s21::set<std::string> my_set;
  const std::set<std::string> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set;
  std::set<NoDefault, CompareNoDef> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, MaxSizeConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set;
  const std::set<NoDefault, CompareNoDef> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(SetTest, ContainsInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(my_set.contains(4));
  EXPECT_TRUE(my_set.contains(8));
  EXPECT_TRUE(my_set.contains(7));
  EXPECT_TRUE(my_set.contains(6));
  EXPECT_TRUE(my_set.contains(10));
  EXPECT_FALSE(my_set.contains(9));
}

TEST(SetTest, ContainsConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(my_set.contains(4));
  EXPECT_TRUE(my_set.contains(8));
  EXPECT_TRUE(my_set.contains(7));
  EXPECT_TRUE(my_set.contains(6));
  EXPECT_TRUE(my_set.contains(10));
  EXPECT_FALSE(my_set.contains(9));
}

TEST(SetTest, ContainsString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  EXPECT_TRUE(my_set.contains("art"));
  EXPECT_TRUE(my_set.contains("ask me"));
  EXPECT_TRUE(my_set.contains("code"));
  EXPECT_TRUE(my_set.contains("boolean"));
  EXPECT_TRUE(my_set.contains("true or false"));
  EXPECT_FALSE(my_set.contains("don't ask me"));
}

TEST(SetTest, ContainsConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_TRUE(my_set.contains("art"));
  EXPECT_TRUE(my_set.contains("ask me"));
  EXPECT_TRUE(my_set.contains("code"));
  EXPECT_TRUE(my_set.contains("boolean"));
  EXPECT_TRUE(my_set.contains("true or false"));
  EXPECT_FALSE(my_set.contains("don't ask me"));
}

TEST(SetTest, ContainsNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_TRUE(my_set.contains(NoDefault('x')));
  EXPECT_TRUE(my_set.contains(NoDefault('a')));
  EXPECT_TRUE(my_set.contains(NoDefault('z')));
  EXPECT_TRUE(my_set.contains(NoDefault('d')));
  EXPECT_TRUE(my_set.contains(NoDefault('t')));
  EXPECT_FALSE(my_set.contains(NoDefault('y')));
}

TEST(SetTest, FindInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto it = my_set.find(4);
  auto std_it = std_set.find(4);
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(9);
  std_it = std_set.find(9);
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, FindConstInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  const std::set<int> std_set{4, 8, 7, 6, 4, 10};
  auto it = my_set.find(4);
  auto std_it = std_set.find(4);
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(9);
  std_it = std_set.find(9);
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, FindString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  auto it = my_set.find("art");
  auto std_it = std_set.find("art");
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find("dont ask me");
  std_it = std_set.find("dont ask me");
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, FindConstString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  const std::set<std::string> std_set{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  auto it = my_set.find("true or false");
  auto std_it = std_set.find("true or false");
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find("dont ask me");
  std_it = std_set.find("dont ask me");
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, FindNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto it = my_set.find(NoDefault('t'));
  auto std_it = std_set.find(NoDefault('t'));
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(NoDefault('.'));
  std_it = std_set.find(NoDefault('.'));
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, FindConstNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  const std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto it = my_set.find(NoDefault('t'));
  auto std_it = std_set.find(NoDefault('t'));
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(NoDefault('.'));
  std_it = std_set.find(NoDefault('.'));
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(SetTest, ClearInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(SetTest, ClearString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(SetTest, ClearNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(SetTest, InsertInt) {
  s21::set<int> my_set;
  std::set<int> std_set;
  bool inserted = false;
  auto it = my_set.begin();
  std_set.insert(100);
  std::tie(it, inserted) = my_set.insert(100);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 100);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(50);
  std::tie(it, inserted) = my_set.insert(50);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 50);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(25);
  std::tie(it, inserted) = my_set.insert(25);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 25);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(25);
  std::tie(it, inserted) = my_set.insert(25);
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, 25);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(150);
  std::tie(it, inserted) = my_set.insert(150);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 150);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(250);
  std::tie(it, inserted) = my_set.insert(250);
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, 250);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(150);
  std::tie(it, inserted) = my_set.insert(150);
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, 150);
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, InsertString) {
  s21::set<std::string> my_set;
  std::set<std::string> std_set;
  bool inserted = false;
  auto it = my_set.begin();
  std_set.insert("Hey Jude");
  std::tie(it, inserted) = my_set.insert("Hey Jude");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "Hey Jude");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("don't make it bad");
  std::tie(it, inserted) = my_set.insert("don't make it bad");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "don't make it bad");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Take a sad song and make it better");
  std::tie(it, inserted) = my_set.insert("Take a sad song and make it better");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "Take a sad song and make it better");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Remember to let her into your heart");
  std::tie(it, inserted) = my_set.insert("Remember to let her into your heart");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "Remember to let her into your heart");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Then you can start to make it better");
  std::tie(it, inserted) =
      my_set.insert("Then you can start to make it better");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "Then you can start to make it better");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  std::tie(it, inserted) = my_set.insert("na na na");
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  std::tie(it, inserted) = my_set.insert("na na na");
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  std::tie(it, inserted) = my_set.insert("na na na");
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Hey Jude");
  std::tie(it, inserted) = my_set.insert("Hey Jude");
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, "Hey Jude");
}

TEST(SetTest, InsertNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set;
  std::set<NoDefault, CompareNoDef> std_set;
  bool inserted = false;
  auto it = my_set.begin();
  std_set.insert(NoDefault('S'));
  std::tie(it, inserted) = my_set.insert(NoDefault('S'));
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, NoDefault('S'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('O'));
  std::tie(it, inserted) = my_set.insert(NoDefault('O'));
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, NoDefault('O'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('S'));
  std::tie(it, inserted) = my_set.insert(NoDefault('S'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('S'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('-'));
  std::tie(it, inserted) = my_set.insert(NoDefault('-'));
  EXPECT_TRUE(inserted);
  EXPECT_EQ(*it, NoDefault('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('-'));
  std::tie(it, inserted) = my_set.insert(NoDefault('-'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('-'));
  std::tie(it, inserted) = my_set.insert(NoDefault('-'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefault('.'));
  std::tie(it, inserted) = my_set.insert(NoDefault('.'));
  EXPECT_FALSE(inserted);
  EXPECT_EQ(*it, NoDefault('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, EraseInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  my_set.erase(my_set.find(8));
  std_set.erase(std_set.find(8));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(4));
  std_set.erase(std_set.find(4));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(10));
  std_set.erase(std_set.find(10));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(6));
  std_set.erase(std_set.find(6));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(7));
  std_set.erase(std_set.find(7));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, EraseString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  my_set.erase(my_set.find("art"));
  std_set.erase(std_set.find("art"));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find("true or false"));
  std_set.erase(std_set.find("true or false"));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find("ask me"));
  std_set.erase(std_set.find("ask me"));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find("code"));
  std_set.erase(std_set.find("code"));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find("boolean"));
  std_set.erase(std_set.find("boolean"));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, EraseNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  my_set.erase(my_set.find(NoDefault('t')));
  std_set.erase(std_set.find(NoDefault('t')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefault('a')));
  std_set.erase(std_set.find(NoDefault('a')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefault('z')));
  std_set.erase(std_set.find(NoDefault('z')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefault('d')));
  std_set.erase(std_set.find(NoDefault('d')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefault('x')));
  std_set.erase(std_set.find(NoDefault('x')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(SetTest, SwapInt) {
  s21::set<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::set<int> my_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  std::set<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::set<int> std_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, SwapString) {
  s21::set<std::string> my_set_1{"art",     "ask me",        "code",
                                 "boolean", "true or false", "ask me"};
  s21::set<std::string> my_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::set<std::string> std_set_1{"art",     "ask me",        "code",
                                  "boolean", "true or false", "ask me"};
  std::set<std::string> std_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, SwapNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_set_2{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  std::set<NoDefault, CompareNoDef> std_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set_2{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, MergeIntDifferent) {
  s21::set<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::set<int> my_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  std::set<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::set<int> std_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, MergeIntIntersection) {
  s21::set<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::set<int> my_set_2{-1, -2, -300, 4, -5, 7, 10, 800};
  std::set<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::set<int> std_set_2{-1, -2, -300, 4, -5, 7, 10, 800};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, MergeStringDifferent) {
  s21::set<std::string> my_set_1{"art",     "ask me",        "code",
                                 "boolean", "true or false", "ask me"};
  s21::set<std::string> my_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::set<std::string> std_set_1{"art",     "ask me",        "code",
                                  "boolean", "true or false", "ask me"};
  std::set<std::string> std_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, MergeStringIntersection) {
  s21::set<std::string> my_set_1{"art",     "ask me",        "code",
                                 "boolean", "true or false", "ask me"};
  s21::set<std::string> my_set_2{"code",   "paste",        "copy, paste, done",
                                 "done",   "Oh, my God",   "copy",
                                 "ask me", "true or false"};
  std::set<std::string> std_set_1{"art",     "ask me",        "code",
                                  "boolean", "true or false", "ask me"};
  std::set<std::string> std_set_2{"code",   "paste",        "copy, paste, done",
                                  "done",   "Oh, my God",   "copy",
                                  "ask me", "true or false"};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}
TEST(SetTest, MergeNoDefaultDifferent) {
  s21::set<NoDefault, CompareNoDef> my_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_set_2{
      NoDefault('w'), NoDefault('7'), NoDefault('c'), NoDefault(';'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  std::set<NoDefault, CompareNoDef> std_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set_2{
      NoDefault('w'), NoDefault('7'), NoDefault('c'), NoDefault(';'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, MergeNoDefaultIntersection) {
  s21::set<NoDefault, CompareNoDef> my_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  s21::set<NoDefault, CompareNoDef> my_set_2{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  std::set<NoDefault, CompareNoDef> std_set_1{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set_2{
      NoDefault('w'), NoDefault('x'), NoDefault('c'), NoDefault('t'),
      NoDefault('q'), NoDefault('q'), NoDefault('r')};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(SetTest, InsertManyInt) {
  s21::set<int> my_set;
  auto many = my_set.insert_many(4, 8, 7, 6, 4, 10);
  int check_data[6] = {4, 8, 7, 6, 4, 10};
  std::set<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i) {
    if (i == 4) {
      EXPECT_FALSE(many[i].second);
    } else {
      EXPECT_TRUE(many[i].second);
    }
    EXPECT_TRUE(*many[i].first == check_data[i]);
  }
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(SetTest, InsertManyString) {
  s21::set<std::string> my_set;
  auto many = my_set.insert_many("art", "ask me", "code", "boolean",
                                 "true or false", "ask me");
  std::string check_data[6] = {"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::set<std::string> std_set{"art",     "ask me",        "code",
                                "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i) {
    if (i == 5) {
      EXPECT_FALSE(many[i].second);
    } else {
      EXPECT_TRUE(many[i].second);
    }
    EXPECT_TRUE(*many[i].first == check_data[i]);
  }
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(SetTest, InsertManyNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set;
  auto many = my_set.insert_many(NoDefault('x'), NoDefault('x'), NoDefault('x'),
                                 NoDefault('a'), NoDefault('z'), NoDefault('d'),
                                 NoDefault('t'));
  NoDefault check_data[7] = {NoDefault('x'), NoDefault('x'), NoDefault('x'),
                             NoDefault('a'), NoDefault('z'), NoDefault('d'),
                             NoDefault('t')};
  std::set<NoDefault, CompareNoDef> std_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i) {
    if (i == 1 || i == 2) {
      EXPECT_FALSE(many[i].second);
    } else {
      EXPECT_TRUE(many[i].second);
    }
    EXPECT_TRUE(*many[i].first == check_data[i]);
  }
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(SetTest, IteratorInt) {
  s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  int check_data[5] = {4, 6, 7, 8, 10};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(SetTest, ConstIteratorInt) {
  const s21::set<int> my_set{4, 8, 7, 6, 4, 10};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  int check_data[5] = {4, 6, 7, 8, 10};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(SetTest, IteratorString) {
  s21::set<std::string> my_set{"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  std::string check_data[5] = {"art", "ask me", "boolean", "code",
                               "true or false"};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(SetTest, ConstIteratorString) {
  const s21::set<std::string> my_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  std::string check_data[5] = {"art", "ask me", "boolean", "code",
                               "true or false"};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(SetTest, IteratorNoDefault) {
  s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  NoDefault check_data[5] = {NoDefault('z'), NoDefault('x'), NoDefault('t'),
                             NoDefault('d'), NoDefault('a')};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(SetTest, ConstIteratorNoDefault) {
  const s21::set<NoDefault, CompareNoDef> my_set{
      NoDefault('x'), NoDefault('x'), NoDefault('x'), NoDefault('a'),
      NoDefault('z'), NoDefault('d'), NoDefault('t')};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  NoDefault check_data[5] = {NoDefault('z'), NoDefault('x'), NoDefault('t'),
                             NoDefault('d'), NoDefault('a')};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[4]);
  EXPECT_EQ(*(++it_end), check_data[4]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
