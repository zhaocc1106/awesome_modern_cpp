namespace jc {

template<typename T, typename U>
struct A;  // primary template

template<typename T>
struct A<T, T> {
  static constexpr int i = 1;
};

template<typename T>
struct A<T, int> {
  static constexpr int j = 2;
};

template<typename T, typename U>
struct A<T*, U*> {
  static constexpr int k = 3;
};

}  // namespace jc

using namespace jc;

static_assert(A<double, double>::i == 1);
static_assert(A<double, int>::j == 2);
static_assert(A<int*, double*>::k == 3);

int main() {
  //   A<int, int>{};    // 编译错误，匹配A<T, T> 和 A<T, int>
  //   A<int*, int*>{};  // 编译错误，匹配A<T, T> 和 A<T*, U*>
}