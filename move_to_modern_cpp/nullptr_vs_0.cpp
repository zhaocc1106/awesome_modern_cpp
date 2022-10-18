#include <iostream>

void f(int) {
  std::cout << "int" << std::endl;
}

void f(bool) {
  std::cout << "bool" << std::endl;
}

void f(void*) {
  std::cout << "void*" << std::endl;
}

int main() {
  f(0); // int
  // f(NULL); // 编译报错：call to 'f' is ambiguous
  f(nullptr); // void*
  return 0;
}
