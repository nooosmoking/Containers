#include <gtest/gtest.h>

#include "../s21_vector.h"
using namespace s21;
TEST(vectorTest, Createvector) {
  vector<int> v;
  std::vector<int> stdv;
  EXPECT_EQ(v.size(), stdv.size());
  EXPECT_EQ(v.capacity(), stdv.capacity());
}

TEST(vectorTest, InsertElements) {
  vector<int> v;
  std::vector<int> stdv;
  v.insert(v.end(), 1);
  stdv.insert(stdv.begin(), 1);
  v.insert(v.end(), 2);
  stdv.insert(stdv.begin() + 1, 2);
  v.insert(v.end(), 3);
  stdv.insert(stdv.begin() + 2, 3);
  EXPECT_EQ(v.size(), stdv.size());
  EXPECT_EQ(v.capacity(), stdv.capacity());
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], stdv[i]);
  }
}

TEST(vectorTest, AccessElements) {
  vector<int> v;
  std::vector<int> stdv;
  v.push_back(1);
  stdv.push_back(1);
  v.push_back(2);
  stdv.push_back(2);
  v.push_back(3);
  stdv.push_back(3);
  EXPECT_EQ(v.size(), stdv.size());
  EXPECT_EQ(v.capacity(), stdv.capacity());
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], stdv[i]);
  }
}

TEST(vectorTest, RemoveElements) {
  vector<int> v;
  std::vector<int> stdv;
  v.push_back(1);
  stdv.push_back(1);
  v.push_back(2);
  stdv.push_back(2);
  v.push_back(3);
  stdv.push_back(3);
  v.erase(v.begin() + 1);
  stdv.erase(stdv.begin() + 1);
  EXPECT_EQ(v.size(), stdv.size());
  EXPECT_EQ(v.capacity(), stdv.capacity());
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], stdv[i]);
  }
}

TEST(vectorTest, PushPopElements) {
  vector<int> v;
  std::vector<int> stdv;
  v.push_back(1);
  stdv.push_back(1);
  v.push_back(2);
  stdv.push_back(2);
  v.push_back(3);
  stdv.push_back(3);
  v.pop_back();
  stdv.pop_back();
  EXPECT_EQ(v.size(), stdv.size());
  EXPECT_EQ(v.capacity(), stdv.capacity());
  for (size_t i = 0; i < v.size(); i++) {
    EXPECT_EQ(v[i], stdv[i]);
  }
}

TEST(vectorTest, Swapvectors) {
  vector<int> v1;
  vector<int> v2;
  std::vector<int> stdv1;
  std::vector<int> stdv2;
  v1.push_back(1);
  stdv1.push_back(1);
  v2.push_back(2);
  stdv2.push_back(2);
  v1.swap(v2);
  std::swap(stdv1, stdv2);
  EXPECT_EQ(v1.size(), stdv1.size());
  EXPECT_EQ(v1.capacity(), stdv1.capacity());
  for (size_t i = 0; i < v1.size(); i++) {
    EXPECT_EQ(v1[i], stdv1[i]);
  }
}

TEST(vectorTest, CreatevectorStd) {
  auto v = new vector<int>;
  // EXPECT_EQ(v.size(), 0);
  // EXPECT_EQ(v.capacity(), 0);
  delete v;
}

TEST(vectorTest, InsertElementsStd) {
  vector<int> v;

  v.insert(v.end(), 1);
  v.insert(v.end(), 2);
  v.insert(v.end(), 3);
  EXPECT_EQ(v.size(), 3);
  EXPECT_EQ(v.capacity(), 4);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(vectorTest, AccessElementsStd) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
  EXPECT_EQ(v[2], 3);
}

TEST(vectorTest, RemoveElementsStd) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.erase(v.begin() + 1);
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 3);
}

TEST(vectorTest, PushPopElementsStd) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.push_back(3);
  v.pop_back();
  EXPECT_EQ(v.size(), 2);
  EXPECT_EQ(v[0], 1);
  EXPECT_EQ(v[1], 2);
}

TEST(vectorTest, SwapvectorsStd) {
  vector<int> v1;
  vector<int> v2;
  v1.push_back(1);
  v2.push_back(2);
  v1.swap(v2);
  EXPECT_EQ(v1.size(), 1);
  EXPECT_EQ(v2.size(), 1);
  EXPECT_EQ(v1[0], 2);
  EXPECT_EQ(v2[0], 1);
}

TEST(vectorTest, Clearvector) {
  vector<int> v;
  v.push_back(1);
  v.push_back(2);
  v.clear();
  EXPECT_EQ(v.size(), 0);
}

TEST(vectorTest, ShrinkToFit) {
  vector<int> v;
  v.reserve(100);
  v.push_back(1);
  v.shrink_to_fit();
  EXPECT_EQ(v.capacity(), v.size());
}