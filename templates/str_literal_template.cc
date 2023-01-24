#include <cassert>
#include <cstddef>
#include <iostream>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_T_TYPE(T) std::cout << #T << ": " << type_id_with_cvr<T>().pretty_name() << std::endl
#define PRINT_PARAM_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

namespace jc {

template<typename T, typename U>
constexpr bool less(const T& a, const U& b) {
  return a < b;
}

// 字符串字面值传引用会推断为字符数组，为此需要为原始数组和字符串字面值提供特定处理的模板
template<typename T, std::size_t M, std::size_t N>
constexpr bool less(T (& a)[M], T (& b)[N]) {
  // PRINT_T_TYPE(T);
  // PRINT_PARAM_TYPE(a);
  // PRINT_PARAM_TYPE(b);
  for (std::size_t i = 0; i < M && i < N; ++i) {
    if (a[i] < b[i]) {
      return true;
    }
    if (b[i] < a[i]) {
      return false;
    }
  }
  return M < N;
}

}  // namespace jc

static_assert(jc::less(0, 42));
static_assert(!jc::less("down", "demo"));
static_assert(jc::less("demo", "down"));

int main() {
  jc::less("demo", "down");
}