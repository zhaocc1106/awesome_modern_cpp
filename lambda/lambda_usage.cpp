#include <iostream>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_T_TYPE(T) std::cout << #T << ": " << type_id_with_cvr<T>().pretty_name() << std::endl
#define PRINT_PARAM_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

template<typename T>
void func(T&& t) {
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(t);
}

int main() {
  int i = 0;
  auto func1 = [=] { std::cout << "func1: " << i << std::endl; }; // 默认按值捕获
  func1();
  auto func2 = [&] { std::cout << "func2: " << i << std::endl; }; // 默认引用捕获
  func2();
  auto func3 = [i] { std::cout << "func3: " << i << std::endl; }; // 按值捕获
  func3();
  auto func4 = [&i] { std::cout << "func4: " << i << std::endl; }; // 引用捕获
  func4();
  auto func5 = [i]() mutable {
    std::cout << "func5: " << i << std::endl;
    i++;
  }; // 按值捕获，但是可以修改
  func5(); // 0
  func5(); // 1

  std::string test = "test";
  auto func6 = [test]() mutable {
    std::cout << "func6: " << test << std::endl;
    test = "mutable";
  }; // 按值捕获
  func6(); // test
  std::cout << "test: " << test << std::endl; // test

  auto func7 = [test = std::move(test)]() { // 通过初始化捕获可以进行移动捕获，需要c14以上
    std::cout << "func7: " << test << std::endl;
  };
  func7(); // test
  std::cout << "test: " << test << std::endl; // 空，因为已经被移动了

  // 使用auto&&在lambda中实现万能引用，需要c14以上
  auto func8 = [](auto&& params) {
    return func(std::forward<decltype(params)>(params));
  };
  int& j = i;
  func8(i); // T为int&, ParamType为int&
  func8(j); // T为int&, ParamType为int&
  func8(42); // T为int, ParamType为int&&
  return 0;
}
