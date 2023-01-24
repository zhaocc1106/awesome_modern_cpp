#include <cstddef>
#include <iostream>
#include <tuple>

namespace jc {

// 特化基础模板
template<std::size_t Index, std::size_t N, typename... List>
struct PrintImpl {
  static void impl(const std::tuple<List...>& t) {
    std::cout << std::get<Index>(t) << " ";
    PrintImpl<Index + 1, N, List...>::impl(t);
  }
};

// 偏特化实现tuple遍历的终止
template<std::size_t N, typename... List>
struct PrintImpl<N, N, List...> {
  static void impl(const std::tuple<List...>& t) {}
};

template<typename... List>
void Print(const std::tuple<List...>& t) {
  PrintImpl<0, sizeof...(List), List...>::impl(t);
}

}  // namespace jc

int main() {
  auto t = std::make_tuple(3.14, 42, "hello world");
  jc::Print(t);  // 3.14 42 hello world
}