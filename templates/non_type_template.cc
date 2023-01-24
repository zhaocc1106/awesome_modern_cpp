#include <bitset>
#include <cassert>

namespace jc {

// 非类型模板参数代表一个值，而不是类型，表示在编译期或链接期可以确定的常量值
template<bool IsSet = true, std::size_t N>
std::size_t find_next(const std::bitset<N>& b, std::size_t cur) {
  for (std::size_t i = cur + 1; i < N; ++i) {
    if (!(b.test(i) ^ IsSet)) {
      return i;
    }
  }
  return N;
}

// C++17 允许将非类型模板参数定义为 auto 或 decltype(auto)
template<auto N, typename T = decltype(N)>
constexpr T add(T n) {
  return n + N;
}

template<typename T, T N = T{}>
constexpr T add(T n) {
  return n + N;
}


// template <double N>  // 错误：非类型模板参数不能是浮点数
// double f(double n) {
//   return n * N;
// }
//
// template <std::string s>  // 错误：非类型模板参数不能是类
// struct A {};

template<const char* s>
struct A {};

}  // namespace jc

void test_find_next() {
  std::bitset<8> b{"10010111"};
  static constexpr int _next_set[] = {1, 2, 4, 4, 7, 7, 7, 8, 8, 8};
  static constexpr int _next_unset[] = {3, 3, 3, 5, 5, 6, 8, 8, 8, 8};

  for (std::size_t i = 0; i < std::size(_next_set); ++i) {
    assert(jc::find_next<true>(b, i) == _next_set[i]);
    assert(jc::find_next<false>(b, i) == _next_unset[i]);
  }
}

static_assert(jc::add<2>(3) == 5);
static_assert(jc::add<int>(3) == 3);

constexpr const char* s1 = "hello";  // 内链接对象的指针
extern const char s2[] = "world";    // 外链接
const char s3[] = "down";            // 内链接

int main() {
  test_find_next();

  static const char s4[] = "demo";  // 无链接
  // jc::A<"downdemo">{};              // 错误，非类型模板参数不能是字符串字面量
  // jc::A<s1>{};                      // 错误，非类型模板参数不能是内链接对象的指针
  jc::A<s2>{};                      // C++11 仅允许外链接（external linkage，不定义于单一的文件作用域，链接到全局符号表
  jc::A<s3>{};                      // C++14 允许外链接或内链接（internal linkage，只能在单个文件内部看到，不能被其他文件访问，不暴露给链接器）
  jc::A<s4>{};                      // C++17 不要求链接
}