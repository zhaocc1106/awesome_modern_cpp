#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

void SomeFunc(int, double) {
}

int main() {
  // auto类别推导本质上和模板类型推导相同
  auto x = 27;
  PRINT_TYPE(x); // int
  const auto cx = x;
  PRINT_TYPE(cx); // const int
  const auto& rx = x;
  PRINT_TYPE(rx); // const int&

  auto&& uref1 = x; // int&
  PRINT_TYPE(uref1);
  auto&& uref2 = cx; // const int&
  PRINT_TYPE(uref2);
  auto&& uref3 = 27; // int&&
  PRINT_TYPE(uref3);

  const char name[] = "R. N. Briggs";
  auto arr1 = name; // const char*
  PRINT_TYPE(arr1);
  auto& arr2 = name; // const char(&)[13]
  PRINT_TYPE(arr2);
  auto func1 = SomeFunc; // void(*)(int, double)
  PRINT_TYPE(func1);
  auto& func2 = SomeFunc; // void(&)(int, double)
  PRINT_TYPE(func2);

  // auto和模板类别推导不同之处：auto会假定 = {}初始化代表一个std::initializer_list
  auto x3 = {27}; // std::initializer_list<int>,
  PRINT_TYPE(x3);
  auto x4{27}; // int
  PRINT_TYPE(x4);
  return 0;
}