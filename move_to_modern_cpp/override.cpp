#include <iostream>

class Base {
 public:
  virtual void mf1() const {
    std::cout << "Base::mf1()" << std::endl;
  }
  virtual void mf2(int x) {
    std::cout << "Base::mf2(int x)" << std::endl;
  }
  virtual void mf3()& {
    std::cout << "Base::mf3()&" << std::endl;
  }
  virtual void mf4()&& {
    std::cout << "Base::mf4()&&" << std::endl;
  }
  virtual ~Base() {
    std::cout << "Base::~Base()" << std::endl;
  }
};

class ErrorDerived : public Base {
 public:
  // 重写基类的虚函数
  void mf1() {
    std::cout << "ErrorDerived::mf1()" << std::endl;
  }
  void mf2(unsigned int x) {
    std::cout << "ErrorDerived::mf2()" << std::endl;
  }
  void mf3()&& {
    std::cout << "ErrorDerived::mf3()" << std::endl;
  }
  ~ErrorDerived() override {
    std::cout << "ErrorDerived::~ErrorDerived()" << std::endl;
  }
};

class SuccessDerived : public Base {
 public:
  // 重写基类的虚函数
  void mf1() const override {
    std::cout << "SuccessDerived::mf1()" << std::endl;
  }
  void mf2(int x) override {
    std::cout << "SuccessDerived::mf2()" << std::endl;
  }
  void mf3()& override {
    std::cout << "SuccessDerived::mf3()" << std::endl;
  }
  ~SuccessDerived() override {
    std::cout << "SuccessDerived::~SuccessDerived()" << std::endl;
  }
};

int main() {
  // 错误的重写，因为没有override关键字，所以仍然可以编译通过，并且调用的函数是基类的。
  auto ed = std::make_unique<ErrorDerived>();
  Base* pb = ed.get();
  pb->mf1(); // Base::mf1()
  pb->mf2(1); // Base::mf2()
  pb->mf3(); // Base::mf3()

  // 正确的重写，因为有override关键字，如果错误的重写会编译报错。
  auto sd = std::make_unique<SuccessDerived>();
  pb = sd.get();
  pb->mf1(); // SuccessDerived::mf1()
  pb->mf2(1); // SuccessDerived::mf2()
  pb->mf3(); // SuccessDerived::mf3()
  return 0;
}