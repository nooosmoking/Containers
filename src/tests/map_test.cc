#include "../map/map.h"

#include <gtest/gtest.h>

TEST(mapTest, InsertAndFind) {
  s21::map<int, int, std::less<int>> map;
  map.insert(1, 10);
  map.insert(2, 20);
  map.insert(3, 30);

  auto iter = map.find(2);
  ASSERT_TRUE(iter != map.end());
  EXPECT_EQ(iter->second, 20);
}

TEST(mapTest, Erase) {
  s21::map<int, int, std::less<int>> map;
  map.insert(1, 10);
  map.insert(2, 20);
  map.insert(3, 30);

  auto iter = map.find(2);
  ASSERT_TRUE(iter != map.end());

  map.erase(iter);

  iter = map.find(2);
  ASSERT_TRUE(iter == map.end());
}

TEST(mapTest, Clear) {
  s21::map<int, int, std::less<int>> map;
  map.insert(1, 10);
  map.insert(2, 20);
  map.insert(3, 30);

  ASSERT_FALSE(map.empty());

  map.clear();

  ASSERT_TRUE(map.empty());
}

TEST(mapTest, Iterator) {
  s21::map<int, int> m;
  for (int i = -1000; i <= 1000; i++) {
    m.insert(i, i * 10);
  }

  auto iter = m.begin();
  iter++;
  iter--;
  ASSERT_TRUE(iter == m.begin());
}

TEST(mapTest, Iterator2) {
  s21::map<int, int> m;
  for (int i = 1000; i >= -1000; i--) {
    m.insert(i, i * 10);
  }

  auto iter = m.begin();
  iter++;
  iter--;
  ASSERT_TRUE(iter == m.begin());
}

TEST(mapTest, OperatorI) {
  s21::map<int, int> m;
  for (int i = -1000; i <= 1000; i++) {
    m.insert(i, i * 10);
  }
  auto iter = m.begin();
  iter++;
  iter--;
  ASSERT_TRUE(iter == m.begin());
}

TEST(mapTest, DeepTree) {
  s21::map<int, int> m;
  for (int i = -1000; i <= 1000; ++i) {
    m.insert(i, i * 10);
  }

  for (auto i = -1000; i <= 100; ++i) {
    m.erase(i);
  }

  m.clear();
}

TEST(MapTest, Merge) {
  // Arrange
  s21::map<int, std::string> m1({{1, "one"}, {2, "two"}, {3, "three"}});
  s21::map<int, std::string> m2({
      {1, "one"},
      {2, "two"},
  });

  // Act
  m2.merge(m1);

  // Assert
  ASSERT_EQ(m1.size(), m2.size());
  ASSERT_EQ(m1.at(1), m2.at(1));
  ASSERT_EQ(m1.at(2), m2.at(2));
  ASSERT_EQ(m1.at(2), m2.at(2));
}

// Тест на создание пустой карты
TEST(mapTest, DefaultConstructor) {
  std::map<int, int> stdMap;
  s21::map<int, int> myMap;
  EXPECT_EQ(stdMap.size(), myMap.size());
}

// Тест на создание карты из списка инициализации
TEST(mapTest, InitializerListConstructor) {
  std::initializer_list<std::pair<int, int>> initList = {
      {1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> myMap(initList);
  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap[1], 10);
  EXPECT_EQ(myMap[2], 20);
  EXPECT_EQ(myMap[3], 30);
}

// Тест на создание карты из другой карты
TEST(mapTest, CopyConstructor) {
  s21::map<int, int> myMap1({{1, 10}, {2, 20}, {3, 30}});
  s21::map<int, int> myMap2(myMap1);
  EXPECT_EQ(myMap1.size(), myMap2.size());
  EXPECT_EQ(myMap2[1], myMap1[1]);
  EXPECT_EQ(myMap2[2], myMap1[2]);
  EXPECT_EQ(myMap2[3], myMap1[3]);
}

// Тест функции at()
TEST(mapTest, AtTest) {
  s21::map<int, std::string> m({{1, "one"}, {2, "two"}, {3, "three"}});

  // Проверка существующего элемента
  EXPECT_EQ(m.at(1), "one");

  // Проверка несуществующего элемента
  EXPECT_THROW(m.at(4), std::out_of_range);
}

// Тест функции operator[]
TEST(mapTest, OperatorBracketTest) {
  s21::map<int, std::string> m({{1, "one"}, {2, "two"}, {3, "three"}});

  // Проверка существующего элемента
  EXPECT_EQ(m[1], "one");

  // Проверка несуществующего элемента
  EXPECT_DEATH(m[4], "");
}

// Тест функции const at()
TEST(mapTest, ConstAtTest) {
  const s21::map<int, std::string> m({{1, "one"}, {2, "two"}, {3, "three"}});

  // Проверка существующего элемента
  EXPECT_EQ(m.at(1), "one");

  // Проверка несуществующего элемента
  EXPECT_THROW(m.at(4), std::out_of_range);
}

// Тесты для метода swap
TEST(mapTest, SwapTest) {
  s21::map<int, int> map1, map2;
  map1.insert(1, 10);
  map1.insert(2, 20);

  map1.swap(map2);
  EXPECT_THROW(map1.at(1), std::out_of_range);

  EXPECT_EQ(map2[1], 10);
}

// Тесты для метода contains
TEST(mapTest, ContainsTest) {
  s21::map<int, int> map1;
  map1.insert(1, 10);

  EXPECT_TRUE(map1.contains(1));
  EXPECT_FALSE(map1.contains(2));
}
