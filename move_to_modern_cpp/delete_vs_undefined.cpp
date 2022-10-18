#include <iostream>

class A {
 public:
  A() {
    std::cout << "A()" << std::endl;
  }
  // 使用delete关键字，禁止拷贝构造函数和拷贝赋值函数
  A(const A&) = delete;
  A(A&&) = delete;
  A& operator=(const A&) = delete;
  A& operator=(A&&) = delete;

  template<typename T>
  void processPointer(T* ptr) {
    std::cout << "processPointer(T* ptr)" << std::endl;
  }

  ~A() {
    std::cout << "~A()" << std::endl;
  }

 private:
  // 下面编译无法通过，因为模板特化必须要在名字空间作用域，而不是类作用域（但是mac环境可以编译过，呃...）
  // template<>
  // void processPointer<void>(void* ptr);
};

template<>
void A::processPointer<void>(void* ptr) = delete;

class B {
 public:
  B() {
    std::cout << "B()" << std::endl;
  }
  ~B() {
    std::cout << "~B()" << std::endl;
  }

 private:
  // 使用private关键字，禁止拷贝构造函数和拷贝赋值函数，但是内部和友元类还可以调用，不太好
  B(const B&); // undefined
  B(B&&); // undefined
  B& operator=(const B&); // undefined
  B& operator=(B&&); // undefined
};

bool isLucky(int num) {
  return num == 7;
}

// 类外也可以使用delete防止隐藏转换出现
bool isLucky(double num) = delete;
bool isLucky(char num) = delete;
bool isLucky(bool num) = delete;

int main() {
  return 0;
}