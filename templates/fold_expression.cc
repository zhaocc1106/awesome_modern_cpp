#include <iostream>
#include <tuple>
#include <utility>

namespace jc {

// c17引入了fold expression，可以用来简化递归模板的实现
template <typename... Args>
auto sum(Args&&... args) {
  auto a = (... + std::forward<Args>(args));      // (((1 + 2) + 3) + 4)，一元左折叠
  auto b = (std::forward<Args>(args) + ...);      // (1 + (2 + (3 + 4)))，一元右折叠
  auto c = (5 + ... + std::forward<Args>(args));  // ((((5 + 1) + 2) + 3) + 4) 二元左折叠
  auto d = (std::forward<Args>(args) + ... + 5);  // (1 + (2 + (3 + (4 + 5)))) 二元有折叠
  return std::make_tuple(a, b, c, d);
}

auto print1 = [](auto&&... args) {
  // operator<< 二元左折叠，std::cout为左折叠的初始值，((((std::cout << 10) << 10) << 15) << 15)
  (std::cout << ... << std::forward<decltype(args)>(args));
};

auto print2 = [](auto&&... args) {
  // operator, 左折叠
  (..., (std::cout << std::forward<decltype(args)>(args) << ","));
};

}  // namespace jc

int main() {
  auto [a, b, c, d] = jc::sum(1, 2, 3, 4); // 10 10 15 15
  jc::print1(a, b, c, d);  // 10101515
  std::cout << std::endl;
  jc::print2(a, b, c, d);  // 10,10,15,15,
}