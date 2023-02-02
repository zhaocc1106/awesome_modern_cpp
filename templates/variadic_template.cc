#include <iostream>
#include <string>
#include <tuple>
#include <utility>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_T_TYPE(T) std::cout << #T << ": " << type_id_with_cvr<T>().pretty_name() << std::endl
#define PRINT_PARAM_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

namespace jc {

void print() {}  // 递归终止

template<typename T, typename... Args>
void print(const T& t, Args&& ... args) {
  std::cout << t << ",";
  print(std::forward<Args>(args)...);
}

template<int... Index>
struct A {};

// 变参模板，用省略号表示一个参数包，类型名后接省略号表示任意数量给定类型的参数。在表达式后跟省略号，如果表达式中有参数包，就会把表达式
// 应用到参数包中的每个参数。如果表达式中出现两次参数包，对整个表达式扩展，而不会做笛卡尔积计算
template<typename... List, int... Index>
void test1(const std::tuple<List...>& t, A<Index...>) {
  print(std::get<Index>(t)...);  // print(std::get<2>(t), std::get<3>(t));
}

template<typename... List, int... Index>
void test2(const std::tuple<List...>& t, A<Index...>) {
  print((std::get<Index>(t) + std::get<Index>(t))...);
}

// 可以直接用逗号运算符做参数包扩展，逗号左侧是对参数包每个元素做的操作，右侧是一个无关紧要的值，这样展开后对每个元素都做了操作，并形成了
// 一个以无关值为元素的数组，这个数组无作用，只是为了满足扩展时省略号不能为表达式最后的 token 而引入
template<typename... Args>
void print2(Args&& ... args) {
  auto a = {(std::cout << std::forward<Args>(args) << std::endl, 0)...};
  PRINT_PARAM_TYPE(a); // std::initializer_list<int>
}

// 可以使用编译期条件判断实现递归终止
template<typename T, typename... Args>
void print3(const T& t, Args&& ... args) {
  std::cout << t << std::endl;
  // sizeof...可以在编译期间判断参数包的大小
  if constexpr (sizeof...(args) > 0) {  // 不能用 if，因为零长包也会实例化代码，if constexpr（c17以上） 判断编译期值，编译期结果为 true 才会实例化代码
    print(std::forward<Args>(args)...);  // 当条件满足时才实例化
  }
}

}  // namespace jc

namespace jc2 {

// c11可以通过偏特化实现达到if constexpr的效果
template<bool b>
struct A;

template<typename T, typename... Args>
void print(const T& t, Args&& ... args) {
  std::cout << t << std::endl;
  A<(sizeof...(args) > 0)>::f(std::forward<Args>(args)...);
}

template<bool b>
struct A {
  template<typename... Args>
  static void f(Args&& ... args) {
    print(std::forward<Args>(args)...);
  }
};

template<>
struct A<false> {
  static void f(...) {}
};

}

int main() {
  auto t = std::make_tuple(3.14, 42, std::string{"hello"}, "world");
  jc::test1(t, jc::A<2, 3>{});     // hello,world
  jc::test2(t, jc::A<0, 1, 2>{});  // 6.28,84,hellohello,
  jc::print2(3.14, 42, std::string{"hello"}, "world");
  jc::print3(3.14, 42, std::string{"hello"}, "world");
  jc2::print(3.14, 42, std::string{"hello"}, "world");
}