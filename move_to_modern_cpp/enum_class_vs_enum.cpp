#include <iostream>

// c98风格的枚举类型，是不限制作用域的枚举类别
enum Color1 {
  RED,
  BLUE,
  GREEN
};

enum class Color2 {
  RED,
  BLUE,
  GREEN
};

int main() {
  Color1 c1 = RED; // 使用时不需要加作用域
  Color2 c2 = Color2::RED; // 使用时需要带上作用域，可以防止作用域污染
  return 0;
}
