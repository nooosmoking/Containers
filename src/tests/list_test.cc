#include <gtest/gtest.h>

#include <list>
#include <string>

#include "../s21_list.h"

template <typename value_type>
bool compare_lists(s21::list<value_type> my_list,
                   std::list<value_type> std_list) {
  bool result = my_list.size() == std_list.size();
  if (result) {
    auto my_it = my_list.begin();
    auto std_it = std_list.begin();
    for (size_t i = 0; i != my_list.size() && result; ++i) {
      result = *my_it == *std_it;
      ++my_it;
      ++std_it;
    }
  }
  return result;
}

TEST(ListConstructor, DefaultConstructor1) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_TRUE(my_list.empty());
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, DefaultConstructor2) {
  s21::list<char> my_list;
  std::list<char> std_list;
  EXPECT_TRUE(my_list.empty());
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, DefaultConstructor3) {
  s21::list<std::string> my_list2;
  std::list<std::string> std_list2;
  EXPECT_TRUE(my_list2.empty());
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListConstructor, SizeConstructor1) {
  s21::list<int> my_list(100);
  std::list<int> std_list(100);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, SizeConstructor2) {
  s21::list<char> my_list(100);
  std::list<char> std_list(100);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, SizeConstructor3) {
  s21::list<std::string> my_list2(100);
  std::list<std::string> std_list2(100);
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListConstructor, InitializerListConstructor1) {
  s21::list<int> my_list{1, 2, 3, 7, 9};
  std::list<int> std_list{1, 2, 3, 7, 9};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, InitializerListConstructor2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, InitializerListConstructor3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListConstructor, CopyConstructor1) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListConstructor, CopyConstructor2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  s21::list<char> my_list_copy1(my_list);
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list_copy1(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy1, std_list_copy1));
}

TEST(ListConstructor, CopyConstructor3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  s21::list<std::string> my_list_copy2(my_list2);
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list_copy2(std_list2);
  EXPECT_TRUE(compare_lists(my_list_copy2, std_list_copy2));
}

TEST(ListConstructor, CopyConstructor4) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_copy = my_list;
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_copy = std_list;
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListConstructor, CopyConstructor5) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  s21::list<char> my_list_copy1 = my_list;
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list_copy1 = std_list;
  EXPECT_TRUE(compare_lists(my_list_copy1, std_list_copy1));
}

TEST(ListConstructor, CopyConstructor6) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  s21::list<std::string> my_list_copy2 = my_list2;
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list_copy2 = std_list2;
  EXPECT_TRUE(compare_lists(my_list_copy2, std_list_copy2));
}

TEST(ListConstructor, CopyConstructorEmpty1) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy(my_list);
  std::list<int> std_list;
  std::list<int> std_list_copy(std_list);
  EXPECT_TRUE(compare_lists(my_list_copy, std_list_copy));
}

TEST(ListConstructor, CopyConstructorEmpty2) {
  s21::list<int> my_list;
  s21::list<int> my_list_copy1 = my_list;
  std::list<int> std_list;
  std::list<int> std_list_copy1 = std_list;
  EXPECT_TRUE(compare_lists(my_list_copy1, std_list_copy1));
}

TEST(ListConstructor, MoveConstructor1) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, MoveConstructor2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  s21::list<char> my_list_move1(std::move(my_list));
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list_move1(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_move1, std_list_move1));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListConstructor, MoveConstructor3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  s21::list<std::string> my_list_move2(std::move(my_list2));
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list_move2(std::move(std_list2));
  EXPECT_TRUE(compare_lists(my_list_move2, std_list_move2));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListConstructor, MoveConstructorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_move(std::move(my_list));
  std::list<int> std_list;
  std::list<int> std_list_move(std::move(std_list));
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, MoveAssignmentOperator1) {
  s21::list<int> my_list{1, 2, 3};
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list{1, 2, 3};
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, MoveAssignmentOperator2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  s21::list<char> my_list_move1 = std::move(my_list);
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list_move1 = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move1, std_list_move1));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListTest, MoveAssignmentOperator3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  s21::list<std::string> my_list_move2 = std::move(my_list2);
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list_move2 = std::move(std_list2);
  EXPECT_TRUE(compare_lists(my_list_move2, std_list_move2));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListTest, MoveAssignmentOperatorEmpty) {
  s21::list<int> my_list;
  s21::list<int> my_list_move = std::move(my_list);
  std::list<int> std_list;
  std::list<int> std_list_move = std::move(std_list);
  EXPECT_TRUE(compare_lists(my_list_move, std_list_move));
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListAccess, Front1) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListAccess, Front2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  EXPECT_EQ(my_list.front(), std_list.front());
}

TEST(ListAccess, Front3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  EXPECT_EQ(my_list2.front(), std_list2.front());
}

TEST(ListAccess, Back1) {
  s21::list<int> my_list{99, 2, 3, 4, 5};
  std::list<int> std_list{99, 2, 3, 4, 5};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListAccess, Back2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  EXPECT_EQ(my_list.back(), std_list.back());
}

TEST(ListAccess, Back3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  EXPECT_EQ(my_list2.back(), std_list2.back());
}

TEST(ListCapacity, Empty1) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_TRUE(my_list.empty());
  my_list.push_back(10);
  std_list.push_back(10);
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListCapacity, Empty2) {
  s21::list<char> my_list;
  std::list<char> std_list;
  EXPECT_TRUE(my_list.empty());
  my_list.push_back('a');
  std_list.push_back('a');
  EXPECT_EQ(my_list.empty(), std_list.empty());
}

TEST(ListCapacity, Empty3) {
  s21::list<std::string> my_list2;
  std::list<std::string> std_list2;
  my_list2.push_back("a");
  std_list2.push_back("a");
  EXPECT_EQ(my_list2.empty(), std_list2.empty());
}

TEST(ListCapacity, Size1) {
  s21::list<int> my_list{1, 2, 3, 4, 5, 6, 7, 8};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListCapacity, Size2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListCapacity, Size3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  EXPECT_EQ(my_list2.size(), std_list2.size());
}

TEST(ListCapacity, SizeEmpty) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(my_list.size(), std_list.size());
}

TEST(ListCapacity, MaxSize) {
  s21::list<size_t> my_list_empty;
  std::list<size_t> std_list_empty;
  EXPECT_EQ(my_list_empty.max_size(), std_list_empty.max_size());
}

TEST(ListModifiers, Clear1) {
  s21::list<int> my_list{1, 2, 3, 4};
  std::list<int> std_list{1, 2, 5, 4, 3};
  my_list.clear();
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Clear2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  my_list.clear();
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Clear3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  my_list2.clear();
  std_list2.clear();
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, ClearEmpty) {
  s21::list<int> my_list;
  my_list.clear();
  std::list<int> std_list;
  std_list.clear();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushBack1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_back(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushBack2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  my_list.push_back('a');
  std_list.push_back('a');
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushBack3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  my_list2.push_back("a");
  std_list2.push_back("a");
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, PushBack4) {
  s21::list<int> my_list;
  my_list.push_back(6);
  std::list<int> std_list;
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushBack5) {
  s21::list<int> my_list{1};
  my_list.push_back(6);
  std::list<int> std_list{1};
  std_list.push_back(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopBack1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_back();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopBack2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  my_list.pop_back();
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopBack3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  my_list2.pop_back();
  std_list2.pop_back();
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, PopBack5) {
  s21::list<int> my_list{1};
  my_list.pop_back();
  std::list<int> std_list{1};
  std_list.pop_back();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopBack6) {
  s21::list<int> my_list{1, 2};
  my_list.pop_back();
  ;
  std::list<int> std_list{1, 2};
  std_list.pop_back();
  ;
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushFront1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.push_front(6);
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.push_front(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushFront2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  my_list.push_front('a');
  std_list.push_front('a');
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushFront3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  my_list2.push_front("a");
  std_list2.push_front("a");
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, PushFront4) {
  s21::list<int> my_list;
  my_list.push_front(6);
  std::list<int> std_list;
  std_list.push_front(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PushFront5) {
  s21::list<int> my_list{1};
  my_list.push_front(6);
  std::list<int> std_list{1};
  std_list.push_front(6);
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopFront1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  my_list.pop_front();
  std::list<int> std_list{1, 2, 3, 4, 5};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopFront2) {
  s21::list<char> my_list{'a', 'b', 'c', 'd'};
  std::list<char> std_list{'a', 'b', 'c', 'd'};
  my_list.pop_front();
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopFront3) {
  s21::list<std::string> my_list2{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "b", "c", "d"};
  my_list2.pop_front();
  std_list2.pop_front();
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, PopFront5) {
  s21::list<int> my_list{1};
  my_list.pop_front();
  std::list<int> std_list{1};
  std_list.pop_front();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, PopFront6) {
  s21::list<int> my_list{1, 2};
  my_list.pop_front();
  ;
  std::list<int> std_list{1, 2};
  std_list.pop_front();
  ;
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Swap1) {
  s21::list<int> my_list1{1, 2, 3, 4, 5};
  s21::list<int> my_list2{6, 7, 8, 9, 10, 11};
  my_list1.swap(my_list2);

  std::list<int> std_list1{1, 2, 3, 4, 5};
  std::list<int> std_list2{6, 7, 8, 9, 10, 11};
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListModifiers, Swap2) {
  s21::list<std::string> my_list1{"a", "b", "c", "d"};
  s21::list<std::string> my_list2;
  my_list1.swap(my_list2);

  std::list<std::string> std_list1{"a", "b", "c", "d"};
  std::list<std::string> std_list2;
  std_list1.swap(std_list2);

  EXPECT_TRUE(compare_lists(my_list1, std_list1));
  EXPECT_TRUE(compare_lists(my_list2, std_list2));
}

TEST(ListIterators, Begin1) {
  s21::list<int> my_list{500, 15000, 30000};
  std::list<int> std_list{500, 15000, 30000};
  EXPECT_EQ(*my_list.begin(), *std_list.begin());
}

TEST(ListIterators, Begin2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  EXPECT_EQ(*my_list.begin(), *std_list.begin());
}

TEST(ListIterators, Begin3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(*my_list.begin(), *std_list.begin());
}

TEST(ListIterators, End1) {
  s21::list<int> my_list{500, 15000, 30000};
  std::list<int> std_list{500, 15000, 30000};
  EXPECT_EQ(*my_list.begin(), *std_list.begin());
}

TEST(ListIterators, End2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  EXPECT_EQ(*my_list.end(), *std_list.end());
}

TEST(ListIterators, End3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  EXPECT_EQ(*my_list.end(), *std_list.end());
}

TEST(ListModifiers, Merge1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge2) {
  s21::list<int> my_list1{20000, 15000, 154, 124, 30000};
  s21::list<int> my_list2{1, 20000, 20000, 666};
  my_list1.merge(my_list2);

  std::list<int> std_list1{20000, 15000, 154, 124, 30000};
  std::list<int> std_list2{1, 20000, 20000, 666};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge3) {
  s21::list<int> my_list1{1, 20000, 20000, 666};
  s21::list<int> my_list2{20000, 15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 20000, 666};
  std::list<int> std_list2{20000, 15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{15000, 154, 124, 30000};
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{15000, 154, 124, 30000};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge5) {
  s21::list<int> my_list1{1, 20000, 666};
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1{1, 20000, 666};
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge6) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.merge(my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Merge7) {
  s21::list<std::string> my_list1{"a", "b", "c", "d"};
  s21::list<std::string> my_list2{"a", "d", "b", "c"};
  my_list1.merge(my_list2);

  std::list<std::string> std_list1{"a", "b", "c", "d"};
  std::list<std::string> std_list2{"a", "d", "b", "c"};
  std_list1.merge(std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Reverse1) {
  s21::list<int> my_list{1, 2, 3, 4, 5};
  std::list<int> std_list{1, 2, 3, 4, 5};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Reverse2) {
  s21::list<int> my_list(4);
  std::list<int> std_list(4);
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Reverse3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Reverse4) {
  s21::list<std::string> my_list{"a", "b", "c", "d"};
  std::list<std::string> std_list{"a", "b", "c", "d"};
  my_list.reverse();
  std_list.reverse();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Unique1) {
  s21::list<int> my_list{90, 90, 90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  std::list<int> std_list{90, 90, 90, 10, 3, 40, 30, 20, 10, 10, 90, 90, 90};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Unique2) {
  s21::list<int> my_list(3);
  std::list<int> std_list(3);
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Unique3) {
  s21::list<int> my_list;
  std::list<int> std_list;
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Unique4) {
  s21::list<std::string> my_list{"a", "a", "b", "b", "c", "d", "d"};
  std::list<std::string> std_list{"a", "a", "b", "b", "c", "d", "d"};
  my_list.unique();
  std_list.unique();
  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Splice1) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Splice2) {
  s21::list<int> my_list1;
  s21::list<int> my_list2{500, 15000, 30000};
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2{500, 15000, 30000};
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Splice3) {
  s21::list<int> my_list1{1, 9999, 20000};
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1{1, 9999, 20000};
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Splice4) {
  s21::list<int> my_list1;
  s21::list<int> my_list2;
  my_list1.splice(my_list1.begin(), my_list2);

  std::list<int> std_list1;
  std::list<int> std_list2;
  std_list1.splice(std_list1.begin(), std_list2);
  EXPECT_TRUE(compare_lists(my_list1, std_list1));
}

TEST(ListModifiers, Insert1) {
  s21::list<int> my_list{1, 9999, 20000};
  my_list.insert(my_list.begin(), 5);

  std::list<int> std_list{1, 9999, 20000};
  std_list.insert(std_list.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert2) {
  s21::list<int> my_list{1, 9999, 20000};
  my_list.insert(my_list.end(), 5);

  std::list<int> std_list{1, 9999, 20000};
  std_list.insert(std_list.end(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert3) {
  s21::list<int> my_list;
  my_list.insert(my_list.begin(), 5);

  std::list<int> std_list;
  std_list.insert(std_list.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert4) {
  s21::list<int> my_list;
  my_list.insert(my_list.end(), 5);

  std::list<int> std_list;
  std_list.insert(std_list.end(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert5) {
  s21::list<int> my_list(4);
  my_list.insert(my_list.begin(), 5);

  std::list<int> std_list(4);
  std_list.insert(std_list.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert6) {
  s21::list<int> my_list(4);
  my_list.insert(my_list.end(), 5);

  std::list<int> std_list(4);
  std_list.insert(std_list.end(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Insert7) {
  s21::list<std::string> s21_list = {"a", "c", "d"};
  auto it1 = s21_list.begin();
  ++it1;
  s21_list.insert(it1, "b");

  std::list<std::string> std_list = {"a", "c", "d"};
  auto it2 = std_list.begin();
  ++it2;
  std_list.insert(it2, "b");

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Insert8) {
  s21::list<int> my_list{1};
  my_list.insert(my_list.begin(), 5);

  std::list<int> std_list{1};
  std_list.insert(std_list.begin(), 5);

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase1) {
  s21::list<int> my_list{1, 9999, 20000};
  my_list.erase(my_list.begin());

  std::list<int> std_list{1, 9999, 20000};
  std_list.erase(std_list.begin());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase2) {
  s21::list<std::string> s21_list = {"a", "c", "d"};
  auto it1 = s21_list.begin();
  ++it1;
  s21_list.erase(it1);
  std::list<std::string> std_list = {"a", "c", "d"};
  auto it2 = std_list.begin();
  ++it2;
  std_list.erase(it2);

  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Erase3) {
  s21::list<int> my_list{1, 9999, 20000};
  my_list.erase(--my_list.end());

  std::list<int> std_list{1, 9999, 20000};
  std_list.erase(std_list.end().operator--());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase4) {
  s21::list<int> my_list(5);
  my_list.erase(--my_list.end());

  std::list<int> std_list(5);
  std_list.erase(std_list.end().operator--());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase5) {
  s21::list<int> my_list{1};
  my_list.erase(my_list.begin());

  std::list<int> std_list{1};
  std_list.erase(std_list.begin());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Erase6) {
  s21::list<int> my_list{1, 2};
  my_list.erase(my_list.begin());

  std::list<int> std_list{1, 2};
  std_list.erase(std_list.begin());

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

TEST(ListModifiers, Sort1) {
  s21::list<int> s21_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  std::list<int> std_list{1, -1, -23, 4, 1, 5, 6, 4, -1, -1};
  s21_list.sort();
  std_list.sort();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Sort2) {
  s21::list<int> s21_list{1};
  std::list<int> std_list{1};
  s21_list.sort();
  std_list.sort();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Sort3) {
  s21::list<int> s21_list{};
  std::list<int> std_list{};
  s21_list.sort();
  std_list.sort();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Sort4) {
  s21::list<std::string> s21_list{"abcd", "abcdef", "abc"};
  std::list<std::string> std_list{"abcd", "abcdef", "abc"};
  s21_list.sort();
  std_list.sort();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListModifiers, Sort5) {
  s21::list<int> s21_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::list<int> std_list{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  s21_list.sort();
  std_list.sort();
  EXPECT_TRUE(compare_lists(s21_list, std_list));
}

TEST(ListHard, Hard) {
  s21::list<std::string> my_list;
  std::list<std::string> std_list;
  my_list.push_back("a");
  std_list.push_back("a");
  my_list.clear();
  std_list.clear();

  my_list.push_back("a");
  std_list.push_back("a");
  my_list.push_back("a");
  std_list.push_back("a");

  my_list.pop_back();
  std_list.pop_back();

  EXPECT_TRUE(compare_lists(my_list, std_list));
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
