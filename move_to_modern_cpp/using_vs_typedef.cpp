#include <iostream>
#include <list>

// using声明可以模板化
template<typename T>
using MyList = std::list<T>;

// typedef需要借助struct来模板化
template<typename T>
struct MyList2 {
  typedef std::list<T> type;
};

struct Item {
  typename MyList2<int>::type list; // typedef定义的是一个带依赖类别，内嵌使用时，需要加typename。
  MyList<int> list2; // 用using声明时不需要加typename
};

int main() {
  Item item;
  item.list.push_back(1);
  item.list2.push_back(2);
  return 0;
}
