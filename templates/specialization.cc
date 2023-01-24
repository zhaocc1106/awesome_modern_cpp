#include <cassert>

namespace jc {

// 特化基础模板
template<typename T>
class A {
 public:
  int f() { return 1; }
};

// 全特化
template<>
class A<int> {
 public:
  int f() { return 2; }
  int g() { return 3; }
};

}  // namespace jc

int main() {
  jc::A<void> a;
  assert(a.f() == 1);
  jc::A<int> b;
  assert(b.f() == 2);
  assert(b.g() == 3);
}