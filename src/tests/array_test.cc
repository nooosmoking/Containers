#include <gtest/gtest.h>

#include "../s21_array.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(5, arr.size());
  for (auto i = arr.begin(); i != arr.end(); ++i) {
    EXPECT_EQ(0, *i);
  }
}

TEST(ArrayTest, ParameterizedConstructor) {
  std::initializer_list<int> items = {1, 2, 3, 4, 5};
  s21::array<int, 10> arr(items);
  EXPECT_EQ(10, arr.max_size());
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(3, arr[2]);
  EXPECT_EQ(4, arr[3]);
  EXPECT_EQ(5, arr[4]);
  for (int i = 5; i < (int)arr.size(); i++) {
    EXPECT_EQ(0, arr[i]);
  }
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<std::string, 3> original;
  original[0] = "Hello";
  original[1] = "World";
  original[2] = "!";
  s21::array<std::string, 3> arr(original);
  EXPECT_EQ(3, arr.size());
  EXPECT_EQ("Hello", arr[0]);
  EXPECT_EQ("World", arr[1]);
  EXPECT_EQ("!", arr[2]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<double, 5> original = {2.4, -46.16, 0.000024, 24683};
  s21::array<double, 5> arr(std::move(original));
  EXPECT_EQ(5, arr.size());
  EXPECT_EQ(2.4, arr[0]);
  EXPECT_EQ(-46.16, arr[1]);
  EXPECT_EQ(0.000024, arr[2]);
  EXPECT_EQ(24683, arr[3]);
  EXPECT_EQ(0, arr[4]);
}

TEST(ArrayTest, CopyAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr2 = arr1;
  EXPECT_EQ(arr1.size(), arr2.size());
  for (std::size_t i = 0; i < arr1.size(); ++i) EXPECT_EQ(arr1[i], arr2[i]);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 5> arr1 = {1, 2, 3, 4, 5};
  s21::array<int, 5> arr2 = {6, 7, 8, 9, 10};
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 5);
  for (std::size_t i = 0; i < arr2.size(); ++i) EXPECT_EQ(arr2[i], i + 1);
}

TEST(ArrayTest, At) {
  s21::array<char, 3> arr1 = {'a', 'b', 'c'};
  std::array<char, 3> arr2 = {'a', 'b', 'c'};
  EXPECT_EQ(arr1.at(0), arr2.at(0));
  EXPECT_EQ(arr1.at(1), arr2.at(1));
  EXPECT_EQ(arr1.at(2), arr2.at(2));
  EXPECT_THROW(arr1.at(5), std::out_of_range);
}

TEST(ArrayTest, OperatorSubscript) {
  s21::array<long double, 5> arr = {1.1, 10e5, -0.0000000041, 4.3, 0};
  EXPECT_EQ(10e5, arr[1]);
  EXPECT_EQ(-0.0000000041, arr[2]);
  EXPECT_EQ(0, arr[4]);
}

TEST(ArrayTest, Front_Back) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(5, arr.back());
}

TEST(ArrayTest, Data) {
  s21::array<char, 2> arr;
  EXPECT_EQ(&arr[0], arr.data());
}

TEST(ArrayTest, BeginEndTest) {
  s21::array<int, 5> arr{0, 1, 2, 3, 4};
  EXPECT_EQ(arr.begin(), &arr[0]);
  EXPECT_EQ(arr.end(), &arr[5]);
}

TEST(ArrayTest, EmptyTest) {
  s21::array<int, 0> arr1;
  EXPECT_TRUE(arr1.empty());
  s21::array<int, 5> arr2;
  EXPECT_FALSE(arr2.empty());
}

TEST(ArrayTest, SizeTest) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_EQ(arr.max_size(), 5);
}

TEST(ArrayTest, SwapTest) {
  s21::array<int, 5> arr1{1, 2, 3, 4, 5};
  s21::array<int, 5> arr2{6, 7, 8, 9, 10};
  arr1.swap(arr2);
  for (int i = 0; i < 5; ++i) {
    EXPECT_EQ(arr1[i], i + 6);
    EXPECT_EQ(arr2[i], i + 1);
  }
}

// const

TEST(ArrayTest, ConstDefaultConstructor) {
  const s21::array<int, 5> arr;
  EXPECT_EQ(5, arr.size());
  for (auto i = arr.cbegin(); i != arr.cend(); ++i) {
    EXPECT_EQ(0, *i);
  }
}

TEST(ArrayTest, ConstParameterizedConstructor) {
  std::initializer_list<int> items = {1, 2, 3, 4, 5};
  const s21::array<int, 10> arr(items);
  EXPECT_EQ(10, arr.max_size());
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(3, arr[2]);
  EXPECT_EQ(4, arr[3]);
  EXPECT_EQ(5, arr[4]);
  for (int i = 5; i < (int)arr.size(); ++i) {
    EXPECT_EQ(0, arr[i]);
  }
}

TEST(ArrayTest, ConstCopyConstructor) {
  const s21::array<std::string, 3> original = {"Hello", "World", "!"};
  const s21::array<std::string, 3> arr(original);
  EXPECT_EQ(3, arr.size());
  EXPECT_EQ("Hello", arr[0]);
  EXPECT_EQ("World", arr[1]);
  EXPECT_EQ("!", arr[2]);
}

TEST(ArrayTest, ConstMoveConstructor) {
  const s21::array<double, 5> original = {2.4, -46.16, 0.000024, 24683};
  const s21::array<double, 5> arr(std::move(original));
  EXPECT_EQ(5, arr.size());
  EXPECT_EQ(2.4, arr[0]);
  EXPECT_EQ(-46.16, arr[1]);
  EXPECT_EQ(0.000024, arr[2]);
  EXPECT_EQ(24683, arr[3]);
  EXPECT_EQ(0, arr[4]);
}

TEST(ArrayTest, ConstAt) {
  const s21::array<char, 3> arr1 = {'a', 'b', 'c'};
  std::array<char, 3> arr2 = {'a', 'b', 'c'};
  EXPECT_EQ(arr1.at(0), arr2.at(0));
  EXPECT_EQ(arr1.at(1), arr2.at(1));
  EXPECT_EQ(arr1.at(2), arr2.at(2));
  EXPECT_THROW(arr1.at(5), std::out_of_range);
}

TEST(ArrayTest, ConstOperatorSubscript) {
  const s21::array<long double, 5> arr = {1.1, 10e5, -0.0000000041, 4.3, 0};
  EXPECT_EQ(10e5, arr[1]);
  EXPECT_EQ(-0.0000000041, arr[2]);
  EXPECT_EQ(0, arr[4]);
}

TEST(ArrayTest, ConstFront_Back) {
  const s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(5, arr.back());
}

TEST(ArrayTest, ConstData) {
  const s21::array<char, 2> arr = {'a', 'b'};
  EXPECT_EQ(&arr[0], arr.data());
}

TEST(ArrayTest, ConstBeginEndTest) {
  const s21::array<int, 5> arr1{0, 1, 2, 3, 4};
  EXPECT_EQ(arr1.cbegin(), &arr1[0]);
  EXPECT_EQ(arr1.cend(), &arr1[5]);
}