#include <gtest/gtest.h>

#include <list>
#include <string>
#include <vector>

#include "../s21_stack.h"

TEST(StackTest, Constructor) {
  s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s21::stack<int> s2{1, 2, 3};
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, ConstructorWithContainer) {
  s21::stack<int, std::list<int>> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  s21::stack<int, std::vector<int>> s2{1, 2, 3};
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, CopyConstructor) {
  s21::stack<double> s1{1.3, 0.00001, 12345.0};
  s21::stack<double> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 12345);
  s2.pop();
  EXPECT_EQ(s2.top(), 0.00001);
}

TEST(StackTest, CopyConstructorWithContainer) {
  s21::stack<double, std::list<double>> s1{0.014352};
  s21::stack<double, std::list<double>> s2(s1);
  EXPECT_EQ(s2.size(), 1);
  EXPECT_EQ(s2.top(), 0.014352);
}

TEST(StackTest, MoveConstructor) {
  s21::stack<std::string> s1{"Hello", "World", "!"};
  s21::stack<std::string> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), "!");
}

TEST(StackTest, MoveConstructorWithContainer) {
  s21::stack<std::string, std::list<std::string>> s1{"!"};
  s21::stack<std::string, std::list<std::string>> s2(std::move(s1));
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 1);
  EXPECT_EQ(s2.top(), "!");
}

TEST(StackTest, CopyAssignmentOperator) {
  s21::stack<int> s1;
  s1.push(1), s1.push(2), s1.push(3);
  s21::stack<int> s2;
  s2.push(4), s2.push(5), s2.push(6);
  s2 = s1;
  EXPECT_EQ(s1.size(), s2.size());
  while (!s1.empty() && !s2.empty()) {
    EXPECT_EQ(s1.top(), s2.top());
    s1.pop(), s2.pop();
  }
  EXPECT_TRUE(s1.empty());
  EXPECT_TRUE(s2.empty());
}

TEST(StackTest, MoveAssignmentOperator) {
  s21::stack<int> s1{1, 2, 3};
  s21::stack<int> s2;
  s2 = std::move(s1);
  EXPECT_TRUE(s1.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
  s21::stack<int> s3{4, 5};
  s2 = std::move(s3);
  EXPECT_TRUE(s3.empty());
  EXPECT_EQ(s2.size(), 2);
  EXPECT_EQ(s2.top(), 5);
}

TEST(StackTest, Empty) {
  s21::stack<int> s2{1, 2};
  EXPECT_FALSE(s2.empty());
  s2.pop();
  EXPECT_FALSE(s2.empty());
  s2.pop();
  EXPECT_TRUE(s2.empty());
}

TEST(StackTest, Size) {
  s21::stack<std::string, std::list<std::string>> s1;
  EXPECT_EQ(s1.size(), 0);
  s21::stack<std::string, std::list<std::string>> s2{"abc", "def"};
  EXPECT_EQ(s2.size(), 2);
  s2.pop();
  s2.pop();
  EXPECT_EQ(s2.size(), 0);
}

TEST(StackTest, PushAndPop) {
  s21::stack<char, std::vector<char>> s;
  s.push('a');
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 1);
  EXPECT_EQ(s.top(), 'a');
  s.push('b');
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(s.top(), 'b');
  s.pop();
  EXPECT_EQ(s.top(), 'a');
}

TEST(StackTest, Swap) {
  s21::stack<double> s1{1.1, 2.2, 3.3};
  s21::stack<double> s2{4.4, 5.5, 6.6};
  s1.swap(s2);
  EXPECT_EQ(s1.top(), 6.6);
  EXPECT_EQ(s2.top(), 3.3);
}

//   const

TEST(StackTest, ConstConstructor) {
  const s21::stack<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);

  const s21::stack<int> s2{1, 2, 3};
  EXPECT_FALSE(s2.empty());
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 3);
}

TEST(StackTest, ConstCopyConstructor) {
  const s21::stack<double> s1{1.3, 0.00001, 12345.0};
  const s21::stack<double> s2(s1);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), 12345);
}

TEST(StackTest, ConstMoveConstructor) {
  const s21::stack<std::string> s1{"Hello", "World", "!"};
  const s21::stack<std::string> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_EQ(s2.top(), "!");
}

TEST(StackTest, ConstEmpty) {
  const s21::stack<int> s2{1, 2};
  EXPECT_FALSE(s2.empty());
}

TEST(StackTest, ConstSize) {
  const s21::stack<std::string, std::list<std::string>> s1;
  EXPECT_EQ(s1.size(), 0);
  const s21::stack<std::string, std::list<std::string>> s2{"abc", "def"};
  EXPECT_EQ(s2.size(), 2);
}

TEST(StackTest, ConstTop) {
  const s21::stack<char, std::vector<char>> s{'a', 'b', 'c'};
  EXPECT_EQ(s.top(), 'c');
}

TEST(StackTest, InsertManyFront) {
  s21::stack<int> s;
  s.insert_many_front(1, 2, 3, 4, 5);
  EXPECT_EQ(s.size(), 5);
  EXPECT_EQ(s.top(), 5);
}