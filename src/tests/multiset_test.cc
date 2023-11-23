#include <gtest/gtest.h>

#include <functional>
#include <set>
#include <string>
#include <utility>

#include "../s21_multiset.h"

class NoDefaultM {
 public:
  NoDefaultM() = delete;
  explicit NoDefaultM(char ch) : ch_(ch) {}
  NoDefaultM(const NoDefaultM &x) : ch_(x.ch_) {}
  NoDefaultM(NoDefaultM &&x) { *this = std::move(x); }
  NoDefaultM &operator=(const NoDefaultM &x) {
    ch_ = x.ch_;
    return *this;
  }
  NoDefaultM &operator=(NoDefaultM &&x) {
    if (this != &x) {
      ch_ = std::move(x.ch_);
    }
    return *this;
  }
  bool operator==(const NoDefaultM &x) { return ch_ == x.ch_; }
  char ch() const { return ch_; }
  void set_ch(const char ch) { ch_ = ch; }

 private:
  char ch_;
};

bool operator==(const NoDefaultM &x, const NoDefaultM &y) {
  return x.ch() == y.ch();
}

struct CompareNoDef {
  bool operator()(const NoDefaultM &n1, const NoDefaultM &n2) const {
    return n1.ch() > n2.ch();
  }
};

template <typename Key, typename Comparator = std::less<Key>,
          typename Allocator = std::allocator<Key>>
bool compare_sets(const s21::multiset<Key, Comparator, Allocator> &my_set,
                  const std::multiset<Key, Comparator, Allocator> &std_set) {
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

TEST(MultisetTest, DefaultConstructorInt) {
  s21::multiset<int> my_set;
  std::multiset<int> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, DefaultConstructorString) {
  s21::multiset<std::string> my_set;
  std::multiset<std::string> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, DefaultConstructorNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set;
  std::multiset<NoDefaultM, CompareNoDef> std_set;
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InitConstructorConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, CopyConstructorInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, CopyConstructorConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, CopyConstructorString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, CopyConstructorConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, CopyConstructorNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, CopyConstructorConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_set_copy = my_set;
  auto std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, MoveConstructorInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, MoveConstructorString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, MoveConstructorNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_set_move = std::move(my_set);
  auto std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, AssignCopyInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_set_copy{-1, -2, -300, -4, -5, 7, 7, 800};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set_copy{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, AssignCopyString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_set_copy{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set_copy{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, AssignCopyNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_set_copy{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_copy{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  my_set_copy = my_set;
  std_set_copy = std_set;
  EXPECT_TRUE(compare_sets(my_set_copy, std_set_copy));
}

TEST(MultisetTest, AssignMoveInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_set_move{-1, -2, -300, -4, -5, 7, 7, 800};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set_move{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, AssignMoveString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_set_move{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set_move{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, AssignMoveNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_set_move{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_move{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  my_set_move = std::move(my_set);
  std_set_move = std::move(std_set);
  EXPECT_TRUE(compare_sets(my_set_move, std_set_move));
}

TEST(MultisetTest, BeginInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, BeginConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, BeginString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, BeginConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, BeginNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, BeginConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_it = my_set.begin();
  auto std_it = std_set.begin();
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EndConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto my_it = my_set.end();
  auto std_it = std_set.end();
  ++my_it;
  ++std_it;
  EXPECT_TRUE(*my_it == *std_it);
}

TEST(MultisetTest, EmptyInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, EmptyConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const s21::multiset<int> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, EmptyString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, EmptyConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const s21::multiset<std::string> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, EmptyNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, EmptyConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const s21::multiset<NoDefaultM, CompareNoDef> my_empty_set;
  EXPECT_FALSE(my_set.empty());
  EXPECT_TRUE(my_empty_set.empty());
}

TEST(MultisetTest, SizeInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, SizeConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, SizeString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, SizeConstString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, SizeNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, SizeConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeInt) {
  s21::multiset<int> my_set;
  std::multiset<int> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeConstInt) {
  const s21::multiset<int> my_set;
  const std::multiset<int> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeString) {
  s21::multiset<std::string> my_set;
  std::multiset<std::string> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeConstString) {
  const s21::multiset<std::string> my_set;
  const std::multiset<std::string> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set;
  std::multiset<NoDefaultM, CompareNoDef> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, MaxSizeConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set;
  const std::multiset<NoDefaultM, CompareNoDef> std_set;
  EXPECT_EQ(my_set.size(), std_set.size());
}

TEST(MultisetTest, ContainsInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(my_set.contains(4));
  EXPECT_TRUE(my_set.contains(8));
  EXPECT_TRUE(my_set.contains(7));
  EXPECT_TRUE(my_set.contains(6));
  EXPECT_TRUE(my_set.contains(10));
  EXPECT_FALSE(my_set.contains(9));
}

TEST(MultisetTest, ContainsConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(my_set.contains(4));
  EXPECT_TRUE(my_set.contains(8));
  EXPECT_TRUE(my_set.contains(7));
  EXPECT_TRUE(my_set.contains(6));
  EXPECT_TRUE(my_set.contains(10));
  EXPECT_FALSE(my_set.contains(9));
}

TEST(MultisetTest, ContainsString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  EXPECT_TRUE(my_set.contains("art"));
  EXPECT_TRUE(my_set.contains("ask me"));
  EXPECT_TRUE(my_set.contains("code"));
  EXPECT_TRUE(my_set.contains("boolean"));
  EXPECT_TRUE(my_set.contains("true or false"));
  EXPECT_FALSE(my_set.contains("don't ask me"));
}

TEST(MultisetTest, ContainsConstString) {
  const s21::multiset<std::string> my_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me "};
  EXPECT_TRUE(my_set.contains("art"));
  EXPECT_TRUE(my_set.contains("ask me"));
  EXPECT_TRUE(my_set.contains("code"));
  EXPECT_TRUE(my_set.contains("boolean"));
  EXPECT_TRUE(my_set.contains("true or false"));
  EXPECT_FALSE(my_set.contains("don't ask me"));
}

TEST(MultisetTest, ContainsNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_TRUE(my_set.contains(NoDefaultM('x')));
  EXPECT_TRUE(my_set.contains(NoDefaultM('a')));
  EXPECT_TRUE(my_set.contains(NoDefaultM('z')));
  EXPECT_TRUE(my_set.contains(NoDefaultM('d')));
  EXPECT_TRUE(my_set.contains(NoDefaultM('t')));
  EXPECT_FALSE(my_set.contains(NoDefaultM('y')));
}

TEST(MultisetTest, FindInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto it = my_set.find(4);
  auto std_it = std_set.find(4);
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(9);
  std_it = std_set.find(9);
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, FindConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto it = my_set.find(4);
  auto std_it = std_set.find(4);
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(9);
  std_it = std_set.find(9);
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, FindString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto it = my_set.find("art");
  auto std_it = std_set.find("art");
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find("dont ask me");
  std_it = std_set.find("dont ask me");
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, FindConstString) {
  const s21::multiset<std::string> my_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me "};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  auto it = my_set.find("true or false");
  auto std_it = std_set.find("true or false");
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find("dont ask me");
  std_it = std_set.find("dont ask me");
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, FindNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it = my_set.find(NoDefaultM('t'));
  auto std_it = std_set.find(NoDefaultM('t'));
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(NoDefaultM('.'));
  std_it = std_set.find(NoDefaultM('.'));
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, FindConstNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it = my_set.find(NoDefaultM('t'));
  auto std_it = std_set.find(NoDefaultM('t'));
  EXPECT_TRUE(*it == *std_it);
  it = my_set.find(NoDefaultM('.'));
  std_it = std_set.find(NoDefaultM('.'));
  EXPECT_TRUE(it == my_set.end());
  EXPECT_TRUE(std_it == std_set.end());
}

TEST(MultisetTest, CountInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 4};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 4};
  EXPECT_EQ(my_set.count(4), std_set.count(4));
  EXPECT_EQ(my_set.count(8), std_set.count(8));
  EXPECT_EQ(my_set.count(9), std_set.count(9));
}

TEST(MultisetTest, CountConstInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 4};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 4};
  EXPECT_EQ(my_set.count(4), std_set.count(4));
  EXPECT_EQ(my_set.count(8), std_set.count(8));
  EXPECT_EQ(my_set.count(9), std_set.count(9));
}

TEST(MultisetTest, CountString) {
  s21::multiset<std::string> my_set{"art",    "ask me",        "code",
                                    "ask me", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",    "ask me",        "code",
                                     "ask me", "true or false", "ask me"};
  EXPECT_EQ(my_set.count("art"), std_set.count("art"));
  EXPECT_EQ(my_set.count("ask me"), std_set.count("ask me"));
  EXPECT_EQ(my_set.count("boolean"), std_set.count("boolean"));
}

TEST(MultisetTest, CountConstString) {
  s21::multiset<std::string> my_set{"art",    "ask me",        "code",
                                    "ask me", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",    "ask me",        "code",
                                     "ask me", "true or false", "ask me"};
  EXPECT_EQ(my_set.count("art"), std_set.count("art"));
  EXPECT_EQ(my_set.count("ask me"), std_set.count("ask me"));
  EXPECT_EQ(my_set.count("boolean"), std_set.count("boolean"));
}

TEST(MultisetTest, CountNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(my_set.count(NoDefaultM('x')), std_set.count(NoDefaultM('x')));
  EXPECT_EQ(my_set.count(NoDefaultM('a')), std_set.count(NoDefaultM('a')));
  EXPECT_EQ(my_set.count(NoDefaultM('.')), std_set.count(NoDefaultM('.')));
}

TEST(MultisetTest, CountConstNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(my_set.count(NoDefaultM('x')), std_set.count(NoDefaultM('x')));
  EXPECT_EQ(my_set.count(NoDefaultM('a')), std_set.count(NoDefaultM('a')));
  EXPECT_EQ(my_set.count(NoDefaultM('.')), std_set.count(NoDefaultM('.')));
}

TEST(MultisetTest, ClearInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(MultisetTest, ClearString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(MultisetTest, ClearNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  my_set.clear();
  std_set.clear();
  EXPECT_TRUE(my_set.empty());
  EXPECT_TRUE(std_set.empty());
}

TEST(MultisetTest, InsertInt) {
  s21::multiset<int> my_set;
  std::multiset<int> std_set;
  auto it = my_set.begin();
  std_set.insert(100);
  it = my_set.insert(100);
  EXPECT_EQ(*it, 100);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(50);
  it = my_set.insert(50);
  EXPECT_EQ(*it, 50);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(25);
  it = my_set.insert(25);
  EXPECT_EQ(*it, 25);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(25);
  it = my_set.insert(25);
  // std::cout << *it << ' ' << (it == my_set.end()) << std::endl;
  EXPECT_EQ(*it, 25);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(150);
  it = my_set.insert(150);
  EXPECT_EQ(*it, 150);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(250);
  it = my_set.insert(250);
  EXPECT_EQ(*it, 250);
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(150);
  it = my_set.insert(150);
  EXPECT_EQ(*it, 150);
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, InsertString) {
  s21::multiset<std::string> my_set;
  std::multiset<std::string> std_set;
  auto it = my_set.begin();
  std_set.insert("Hey Jude");
  it = my_set.insert("Hey Jude");
  EXPECT_EQ(*it, "Hey Jude");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("don't make it bad");
  it = my_set.insert("don't make it bad");
  EXPECT_EQ(*it, "don't make it bad");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Take a sad song and make it better");
  it = my_set.insert("Take a sad song and make it better");
  EXPECT_EQ(*it, "Take a sad song and make it better");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Remember to let her into your heart");
  it = my_set.insert("Remember to let her into your heart");
  EXPECT_EQ(*it, "Remember to let her into your heart");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Then you can start to make it better");
  it = my_set.insert("Then you can start to make it better");
  EXPECT_EQ(*it, "Then you can start to make it better");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  it = my_set.insert("na na na");
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  it = my_set.insert("na na na");
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("na na na");
  it = my_set.insert("na na na");
  EXPECT_EQ(*it, "na na na");
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert("Hey Jude");
  it = my_set.insert("Hey Jude");
  EXPECT_EQ(*it, "Hey Jude");
}

TEST(MultisetTest, InsertNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set;
  std::multiset<NoDefaultM, CompareNoDef> std_set;
  auto it = my_set.begin();
  std_set.insert(NoDefaultM('S'));
  it = my_set.insert(NoDefaultM('S'));
  EXPECT_EQ(*it, NoDefaultM('S'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('O'));
  it = my_set.insert(NoDefaultM('O'));
  EXPECT_EQ(*it, NoDefaultM('O'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('S'));
  it = my_set.insert(NoDefaultM('S'));
  EXPECT_EQ(*it, NoDefaultM('S'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('-'));
  it = my_set.insert(NoDefaultM('-'));
  EXPECT_EQ(*it, NoDefaultM('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('-'));
  it = my_set.insert(NoDefaultM('-'));
  EXPECT_EQ(*it, NoDefaultM('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('-'));
  it = my_set.insert(NoDefaultM('-'));
  EXPECT_EQ(*it, NoDefaultM('-'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  std_set.insert(NoDefaultM('.'));
  it = my_set.insert(NoDefaultM('.'));
  EXPECT_EQ(*it, NoDefaultM('.'));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, EraseInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
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

TEST(MultisetTest, EraseString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
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

TEST(MultisetTest, EraseNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  my_set.erase(my_set.find(NoDefaultM('t')));
  std_set.erase(std_set.find(NoDefaultM('t')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefaultM('a')));
  std_set.erase(std_set.find(NoDefaultM('a')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefaultM('z')));
  std_set.erase(std_set.find(NoDefaultM('z')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefaultM('d')));
  std_set.erase(std_set.find(NoDefaultM('d')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
  my_set.erase(my_set.find(NoDefaultM('x')));
  std_set.erase(std_set.find(NoDefaultM('x')));
  EXPECT_TRUE(compare_sets(my_set, std_set));
}

TEST(MultisetTest, SwapInt) {
  s21::multiset<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  std::multiset<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, SwapString) {
  s21::multiset<std::string> my_set_1{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::multiset<std::string> std_set_1{"art",     "ask me",        "code",
                                       "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, SwapNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_set_2{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_2{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  my_set_1.swap(my_set_2);
  std_set_1.swap(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, MergeIntDifferent) {
  s21::multiset<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  std::multiset<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set_2{-1, -2, -300, -4, -5, 7, 7, 800};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, MergeIntIntersection) {
  s21::multiset<int> my_set_1{4, 8, 7, 6, 4, 10};
  s21::multiset<int> my_set_2{-1, -2, -300, 4, -5, 7, 10, 800};
  std::multiset<int> std_set_1{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set_2{-1, -2, -300, 4, -5, 7, 10, 800};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, MergeStringDifferent) {
  s21::multiset<std::string> my_set_1{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  std::multiset<std::string> std_set_1{"art",     "ask me",        "code",
                                       "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set_2{
      "copy",       "paste", "copy, paste, done", "done",
      "Oh, my God", "copy",  "don't ask me",      "false or true"};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, MergeStringIntersection) {
  s21::multiset<std::string> my_set_1{"art",     "ask me",        "code",
                                      "boolean", "true or false", "ask me"};
  s21::multiset<std::string> my_set_2{
      "code", "paste",  "copy, paste, done", "done", "Oh, my God",
      "copy", "ask me", "true or false"};
  std::multiset<std::string> std_set_1{"art",     "ask me",        "code",
                                       "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set_2{
      "code", "paste",  "copy, paste, done", "done", "Oh, my God",
      "copy", "ask me", "true or false"};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}
TEST(MultisetTest, MergeNoDefaultMDifferent) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_set_2{
      NoDefaultM('w'), NoDefaultM('7'), NoDefaultM('c'), NoDefaultM(';'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_2{
      NoDefaultM('w'), NoDefaultM('7'), NoDefaultM('c'), NoDefaultM(';'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, MergeNoDefaultMIntersection) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  s21::multiset<NoDefaultM, CompareNoDef> my_set_2{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_1{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set_2{
      NoDefaultM('w'), NoDefaultM('x'), NoDefaultM('c'), NoDefaultM('t'),
      NoDefaultM('q'), NoDefaultM('q'), NoDefaultM('r')};
  my_set_1.merge(my_set_2);
  std_set_1.merge(std_set_2);
  EXPECT_TRUE(compare_sets(my_set_1, std_set_1));
  EXPECT_TRUE(compare_sets(my_set_2, std_set_2));
}

TEST(MultisetTest, InsertManyInt) {
  s21::multiset<int> my_set;
  auto many = my_set.insert_many(4, 8, 7, 6, 4, 10);
  int check_data[6] = {4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i)
    EXPECT_TRUE(*many[i] == check_data[i]);
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(MultisetTest, InsertManyString) {
  s21::multiset<std::string> my_set;
  auto many = my_set.insert_many("art", "ask me", "code", "boolean",
                                 "true or false", "ask me");
  std::string check_data[6] = {"art",     "ask me",        "code",
                               "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i)
    EXPECT_TRUE(*many[i] == check_data[i]);
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(MultisetTest, InsertManyNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set;
  auto many = my_set.insert_many(
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t'));
  NoDefaultM check_data[7] = {NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'),
                              NoDefaultM('a'), NoDefaultM('z'), NoDefaultM('d'),
                              NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_TRUE(compare_sets(my_set, std_set));
  for (size_t i = 0; i < many.size(); ++i)
    EXPECT_TRUE(*many[i] == check_data[i]);
  many = my_set.insert_many();
  EXPECT_EQ(many.size(), 0);
}

TEST(MultisetTest, IteratorInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  int check_data[6] = {4, 4, 6, 7, 8, 10};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[5]);
  EXPECT_EQ(*(++it_end), check_data[5]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, ConstIteratorInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  int check_data[6] = {4, 4, 6, 7, 8, 10};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[5]);
  EXPECT_EQ(*(++it_end), check_data[5]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, IteratorString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  std::string check_data[6] = {"art",     "ask me", "ask me",
                               "boolean", "code",   "true or false"};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[5]);
  EXPECT_EQ(*(++it_end), check_data[5]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, ConstIteratorString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  std::string check_data[6] = {"art",     "ask me", "ask me",
                               "boolean", "code",   "true or false"};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[5]);
  EXPECT_EQ(*(++it_end), check_data[5]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, IteratorNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  NoDefaultM check_data[7] = {NoDefaultM('z'), NoDefaultM('x'), NoDefaultM('x'),
                              NoDefaultM('x'), NoDefaultM('t'), NoDefaultM('d'),
                              NoDefaultM('a')};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[6]);
  EXPECT_EQ(*(++it_end), check_data[6]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, ConstIteratorNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it_begin = my_set.begin();
  auto it = it_begin;
  auto it_end = my_set.end();
  NoDefaultM check_data[7] = {NoDefaultM('z'), NoDefaultM('x'), NoDefaultM('x'),
                              NoDefaultM('x'), NoDefaultM('t'), NoDefaultM('d'),
                              NoDefaultM('a')};
  for (size_t i = 0; i < my_set.size(); ++i) {
    EXPECT_TRUE(*it == check_data[i]);
    ++it;
  }
  EXPECT_EQ(--it_begin, it_end);
  EXPECT_EQ(*(++it), check_data[6]);
  EXPECT_EQ(*(++it_end), check_data[6]);
  EXPECT_TRUE(it_end == it);
  EXPECT_TRUE(it_begin != it_end);
  const auto it_const_begin = my_set.begin();
  EXPECT_TRUE(it_const_begin != it_begin);
  EXPECT_FALSE(it_const_begin == it_end);
}

TEST(MultisetTest, LowerInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(*my_set.lower_bound(2), *std_set.lower_bound(2));
  EXPECT_EQ(*my_set.lower_bound(7), *std_set.lower_bound(7));
  EXPECT_EQ(*my_set.lower_bound(9), *std_set.lower_bound(9));
  EXPECT_EQ(*my_set.lower_bound(10), *std_set.lower_bound(10));
  EXPECT_TRUE(my_set.lower_bound(11) == my_set.end());
  EXPECT_TRUE(std_set.lower_bound(11) == std_set.end());
}

TEST(MultisetTest, ConstLowerInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(*my_set.lower_bound(2), *std_set.lower_bound(2));
  EXPECT_EQ(*my_set.lower_bound(7), *std_set.lower_bound(7));
  EXPECT_EQ(*my_set.lower_bound(9), *std_set.lower_bound(9));
  EXPECT_EQ(*my_set.lower_bound(10), *std_set.lower_bound(10));
  EXPECT_TRUE(my_set.lower_bound(11) == my_set.end());
  EXPECT_TRUE(std_set.lower_bound(11) == std_set.end());
}

TEST(MultisetTest, LowerString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_EQ(*my_set.lower_bound("a b c d"), *std_set.lower_bound("a b c d"));
  EXPECT_EQ(*my_set.lower_bound("ask me"), *std_set.lower_bound("ask me"));
  EXPECT_EQ(*my_set.lower_bound("game over"),
            *std_set.lower_bound("game over"));
  EXPECT_EQ(*my_set.lower_bound("true or false"),
            *std_set.lower_bound("true or false"));
  EXPECT_TRUE(my_set.lower_bound("zero one two") == my_set.end());
  EXPECT_TRUE(std_set.lower_bound("zero one two") == std_set.end());
}

TEST(MultisetTest, ConstLowerString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  EXPECT_EQ(*my_set.lower_bound("a b c d"), *std_set.lower_bound("a b c d"));
  EXPECT_EQ(*my_set.lower_bound("ask me"), *std_set.lower_bound("ask me"));
  EXPECT_EQ(*my_set.lower_bound("game over"),
            *std_set.lower_bound("game over"));
  EXPECT_EQ(*my_set.lower_bound("true or false"),
            *std_set.lower_bound("true or false"));
  EXPECT_TRUE(my_set.lower_bound("zero one two") == my_set.end());
  EXPECT_TRUE(std_set.lower_bound("zero one two") == std_set.end());
}

TEST(MultisetTest, LowerNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('|')),
            *std_set.lower_bound(NoDefaultM('|')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('a')),
            *std_set.lower_bound(NoDefaultM('a')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('r')),
            *std_set.lower_bound(NoDefaultM('r')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('z')),
            *std_set.lower_bound(NoDefaultM('z')));
  EXPECT_TRUE(my_set.lower_bound(NoDefaultM('A')) == my_set.end());
  EXPECT_TRUE(std_set.lower_bound(NoDefaultM('A')) == std_set.end());
}

TEST(MultisetTest, ConstLowerNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('|')),
            *std_set.lower_bound(NoDefaultM('|')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('a')),
            *std_set.lower_bound(NoDefaultM('a')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('r')),
            *std_set.lower_bound(NoDefaultM('r')));
  EXPECT_EQ(*my_set.lower_bound(NoDefaultM('z')),
            *std_set.lower_bound(NoDefaultM('z')));
  EXPECT_TRUE(my_set.lower_bound(NoDefaultM('A')) == my_set.end());
  EXPECT_TRUE(std_set.lower_bound(NoDefaultM('A')) == std_set.end());
}

TEST(MultisetTest, UpperInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(*my_set.upper_bound(2), *std_set.upper_bound(2));
  EXPECT_EQ(*my_set.upper_bound(7), *std_set.upper_bound(7));
  EXPECT_EQ(*my_set.upper_bound(9), *std_set.upper_bound(9));
  EXPECT_TRUE(my_set.upper_bound(10) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(10) == std_set.end());
  EXPECT_TRUE(my_set.upper_bound(11) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(11) == std_set.end());
}

TEST(MultisetTest, ConstUpperInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  EXPECT_EQ(*my_set.upper_bound(2), *std_set.upper_bound(2));
  EXPECT_EQ(*my_set.upper_bound(7), *std_set.upper_bound(7));
  EXPECT_EQ(*my_set.upper_bound(9), *std_set.upper_bound(9));
  EXPECT_TRUE(my_set.upper_bound(10) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(10) == std_set.end());
  EXPECT_TRUE(my_set.upper_bound(11) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(11) == std_set.end());
}

TEST(MultisetTest, UpperString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  EXPECT_EQ(*my_set.upper_bound("a b c d"), *std_set.upper_bound("a b c d"));
  EXPECT_EQ(*my_set.upper_bound("ask me"), *std_set.upper_bound("ask me"));
  EXPECT_EQ(*my_set.upper_bound("game over"),
            *std_set.upper_bound("game over"));
  EXPECT_TRUE(my_set.upper_bound("true or false") == my_set.end());
  EXPECT_TRUE(std_set.upper_bound("true or false") == std_set.end());
  EXPECT_TRUE(my_set.upper_bound("zero one two") == my_set.end());
  EXPECT_TRUE(std_set.upper_bound("zero one two") == std_set.end());
}

TEST(MultisetTest, ConstUpperString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  EXPECT_EQ(*my_set.upper_bound("a b c d"), *std_set.upper_bound("a b c d"));
  EXPECT_EQ(*my_set.upper_bound("ask me"), *std_set.upper_bound("ask me"));
  EXPECT_EQ(*my_set.upper_bound("game over"),
            *std_set.upper_bound("game over"));
  EXPECT_TRUE(my_set.upper_bound("true or false") == my_set.end());
  EXPECT_TRUE(std_set.upper_bound("true or false") == std_set.end());
  EXPECT_TRUE(my_set.upper_bound("zero one two") == my_set.end());
  EXPECT_TRUE(std_set.upper_bound("zero one two") == std_set.end());
}

TEST(MultisetTest, UpperNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('|')),
            *std_set.upper_bound(NoDefaultM('|')));
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('r')),
            *std_set.upper_bound(NoDefaultM('r')));
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('z')),
            *std_set.upper_bound(NoDefaultM('z')));
  EXPECT_TRUE(my_set.upper_bound(NoDefaultM('a')) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(NoDefaultM('a')) == std_set.end());
  EXPECT_TRUE(my_set.upper_bound(NoDefaultM('A')) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(NoDefaultM('A')) == std_set.end());
}

TEST(MultisetTest, ConstUpperNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('|')),
            *std_set.upper_bound(NoDefaultM('|')));
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('r')),
            *std_set.upper_bound(NoDefaultM('r')));
  EXPECT_EQ(*my_set.upper_bound(NoDefaultM('z')),
            *std_set.upper_bound(NoDefaultM('z')));
  EXPECT_TRUE(my_set.upper_bound(NoDefaultM('a')) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(NoDefaultM('a')) == std_set.end());
  EXPECT_TRUE(my_set.upper_bound(NoDefaultM('A')) == my_set.end());
  EXPECT_TRUE(std_set.upper_bound(NoDefaultM('A')) == std_set.end());
}

TEST(MultisetTest, EqRangeInt) {
  s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(2);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(2);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(4);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(4);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(7);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(7);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(5);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(5);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(10);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(10);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(11);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(11);
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

TEST(MultisetTest, ConstEqRangeInt) {
  const s21::multiset<int> my_set{4, 8, 7, 6, 4, 10};
  const std::multiset<int> std_set{4, 8, 7, 6, 4, 10};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(2);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(2);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(4);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(4);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(7);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(7);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(5);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(5);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(10);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(10);
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(11);
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(11);
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

TEST(MultisetTest, EqRangeString) {
  s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                    "boolean", "true or false", "ask me"};
  std::multiset<std::string> std_set{"art",     "ask me",        "code",
                                     "boolean", "true or false", "ask me"};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("a b c d");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("a b c d");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("ask me");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("ask me");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("boolean");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("boolean");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("game over");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("game over");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("true or false");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("true or false");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("zero one two");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("zero one two");
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

TEST(MultisetTest, ConstEqRangeString) {
  const s21::multiset<std::string> my_set{"art",     "ask me",        "code",
                                          "boolean", "true or false", "ask me"};
  const std::multiset<std::string> std_set{
      "art", "ask me", "code", "boolean", "true or false", "ask me"};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("a b c d");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("a b c d");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("ask me");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("ask me");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("boolean");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("boolean");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("game over");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("game over");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("true or false");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("true or false");
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range("zero one two");
  std::tie(it_std_begin, it_std_end) = std_set.equal_range("zero one two");
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

TEST(MultisetTest, EqRangeNoDefaultM) {
  s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('|'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('|'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('r'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('r'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('t'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('t'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('x'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('x'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('a'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('a'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('A'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('A'));
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

TEST(MultisetTest, ConstEqRangeNoDefaultM) {
  const s21::multiset<NoDefaultM, CompareNoDef> my_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  const std::multiset<NoDefaultM, CompareNoDef> std_set{
      NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('x'), NoDefaultM('a'),
      NoDefaultM('z'), NoDefaultM('d'), NoDefaultM('t')};
  auto it_my_begin = my_set.begin();
  auto it_my_end = my_set.end();
  auto it_std_begin = std_set.begin();
  auto it_std_end = std_set.end();
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('|'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('|'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('r'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('r'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('t'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('t'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('x'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('x'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_EQ(*it_my_end, *it_std_end);
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('a'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('a'));
  EXPECT_EQ(*it_my_begin, *it_std_begin);
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
  std::tie(it_my_begin, it_my_end) = my_set.equal_range(NoDefaultM('A'));
  std::tie(it_std_begin, it_std_end) = std_set.equal_range(NoDefaultM('A'));
  EXPECT_TRUE(it_my_begin == my_set.end());
  EXPECT_TRUE(it_my_end == my_set.end());
  EXPECT_TRUE(it_std_begin == std_set.end());
  EXPECT_TRUE(it_std_end == std_set.end());
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
