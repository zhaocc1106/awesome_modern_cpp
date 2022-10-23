#include <iostream>
#include <array>

// c11的constexpr函数只能有一行语句
constexpr int pow1(int base, int exp) {
  return exp == 0 ? 1 : base * pow1(base, exp - 1);
}

// c14的constexpr函数可以有多行语句
constexpr int pow2(int base, int exp) {
  auto result = 1;
  for (auto i = 0; i < exp; ++i) {
    result *= base;
  }
  return result;
}

class Point {
 public:
  constexpr Point() : x_(0), y_(0) {}
  constexpr Point(int x, int y) : x_(x), y_(y) {}

  constexpr int x() const { return x_; }
  constexpr int y() const { return y_; }

  constexpr void set_x(int x) noexcept { x_ = x; }  // c14可以使用constexpr修饰set函数
  constexpr void set_y(int y) noexcept { y_ = y; }

 private:
  int x_;
  int y_;
};

constexpr Point midpoint(const Point& p1, const Point& p2) {
  return {(p1.x() + p2.x()) / 2, (p1.y() + p2.y()) / 2};
}

constexpr Point reflect(const Point& p) noexcept {
  Point result;
  result.set_x(-p.x());
  result.set_y(-p.y());
  return result;
}

int main() {
  int sz; // 非constexpr变量
  // constexpr auto array_size = sz; // 错误，sz的值在编译期不可知
  // std::array<int, array_size> array; // 错误，array_size的值在编译期不可知
  constexpr auto array_size2 = 10;
  std::array<int, array_size2> array2{}; // 正确，array_size2的值在编译期可知

  sz = 10;
  const auto array_size3 = sz; // 10， 仅是sz的一个const副本
  std::cout << "array_size3: " << array_size3 << std::endl;
  // std::array<int, array_size3> array3; // 错误，array_size3的值在编译期不可知

  constexpr auto array_size4 = pow1(2, 3); // 8，编译期计算
  std::cout << "array_size4: " << array_size4 << std::endl;

  constexpr Point p1(1, 2); // 编译期构造，因为Point的构造函数和成员函数都是constexpr的
  constexpr Point p2(3, 4); // 编译期构造，因为Point的构造函数和成员函数都是constexpr的
  constexpr auto p3 = midpoint(p1, p2); // 编译期计算
  std::cout << "p3: (" << p3.x() << ", " << p3.y() << ")" << std::endl;
  constexpr auto p4 = reflect(p3); // 编译期计算
  std::cout << "p4: (" << p4.x() << ", " << p4.y() << ")" << std::endl;
}