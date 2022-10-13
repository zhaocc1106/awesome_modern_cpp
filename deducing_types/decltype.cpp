#include <iostream>
#include <vector>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

// c11以上版本可以正常工作
template<typename Container, typename Index>
auto Access(Container& c, Index i) -> decltype(c[i]) {
  return c[i];
}

// c14以上版本可以正常工作，返回值不带引用特性
template<typename Container, typename Index>
auto Access2(Container& c, Index i) {
  return c[i];
}

// c14以上版本可以正常工作，返回值带引用特性
template<typename Container, typename Index>
decltype(auto) Access3(Container& c, Index i) {
  return c[i];
}

// c14版本以上可以正常工作，使用万能引用和完美转发实现返回原本的类型
template<typename Container, typename Index>
decltype(auto) Access4(Container&& c, Index i) {
  return std::forward<Container>(c)[i];
}

// c11版本以上可以正常工作，使用万能引用和完美转发实现返回原本的类型
template<typename Container, typename Index>
auto Access5(Container&& c, Index i) -> decltype(std::forward<Container>(c)[i]) {
  return std::forward<Container>(c)[i];
}

int main() {
  int x = 1;
  decltype(x) x2 = x;
  PRINT_TYPE(x2); // int
  decltype((x)) x3 = x; // 注意如果decltype一个左值表达式，则返回的总是引用类型
  PRINT_TYPE(x3); // int&

  std::vector<int> v{1, 2, 3, 4, 5};
  Access(v, 2) = 100; // 可以正常赋值
  // Access2(v, 2) = 100; // 编译不通过，因为返回类型不带有引用特性
  Access3(v, 2) = 100; // 可以正常赋值
  Access4(v, 2) = 100; // 可以正常赋值
  Access5(v, 2) = 100; // 可以正常赋值
}