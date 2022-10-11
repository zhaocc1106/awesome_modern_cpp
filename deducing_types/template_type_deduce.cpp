#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_T_TYPE(T) std::cout << #T << ": " << type_id_with_cvr<T>().pretty_name() << std::endl
#define PRINT_PARAM_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

// 如下描述T和ParamType
// template<typename T>
// void f(ParamType param);

// 1. ParamType为T的引用
template<typename T>
void f(T& param) {
  std::cout << "T&" << std::endl;
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(param);
}

// 2. ParamType为T的指针
template<typename T>
void f2(T* param) {
  std::cout << "T*" << std::endl;
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(param);
}

// 3. ParamType为T的万能引用
template<typename T>
void f3(T&& param) {
  std::cout << "T&&" << std::endl;
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(param);
}

// 4. ParamType为T
template<typename T>
void f4(T param) {
  std::cout << "T" << std::endl;
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(param);
}

int main() {
  int x = 27;
  const int cx = x;
  const int& rx = x;

  // 1. T为int, ParamType为int&
  f(x); // T为int, ParamType为int&
  f(cx); // t为const int, paramtype为const int&
  f(rx); // T为const int, ParamType为const int&

  // 2. T为int, ParamType为int*
  const int* px = &x;
  f2(px); // T为const int, ParamType为const int*
  f2(&x); // T为int, ParamType为int*

  // 3. T为int, ParamType为int&&
  f3(std::move(x)); // T为int, ParamType为int&&
  f3(rx); // T为const int&, ParamType为const int&

  // 4. T为int, ParamType为int
  f4(x); // T为int, ParamType为int
  f4(cx); // T为int, ParamType为int
  f4(rx); // T为int, ParamType为int
  f4(px); // T为const int*, ParamType为const int*
  const char* const ptr = "Fun with pointers";
  f4(ptr); // T为const char*, ParamType为const char*
  char* ptr2 = nullptr;
  f4(ptr2); // T为char*, ParamType为char*
  return 0;
}
