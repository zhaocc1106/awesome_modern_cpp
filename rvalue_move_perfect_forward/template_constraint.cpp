#include <iostream>
#include <vector>

std::vector<std::string> names = {"tom", "jerry", "jack"};

class Person {
 public:
  template<typename T>
  explicit Person(T&& name) : name_(std::forward<T>(name)) { // 想通过接受可以转换为string类型的所有类型的构造函数，但是和其他的构造函数冲突了
    std::cout << "Person(T&&)" << std::endl;
  }

  explicit Person(int idx) : name_(names[idx]) { // 接受整形实参的构造函数
    std::cout << "Person constructor" << std::endl;
  }

  Person(const Person& other) : name_(other.name_) { // 拷贝构造函数
    std::cout << "Person copy constructor" << std::endl;
  }

  Person(Person&& other) noexcept: name_(std::move(other.name_)) { // 移动构造函数
    std::cout << "Person move constructor" << std::endl;
  }

 private:
  std::string name_;
};

class TruePerson {
 public:
  template<
      typename T,
      typename = std::enable_if_t<
          !std::is_base_of_v<Person, std::decay_t<T>> && // 不是Person的派生类，防止子类以及本类调用构造函数时调用到万能引用构造函数
              !std::is_integral_v<std::remove_reference_t<T>> // 不是整形，防止整形调用到万能引用构造函数
      >
  >
  explicit TruePerson(T&& name) : name_(std::forward<T>(name)) { // 通过模板约束，解决构造函数冲突问题
    std::cout << "TruePerson(T&&)" << std::endl;
  }

  explicit TruePerson(int idx) : name_(names[idx]) { // 接受整形实参的构造函数
    std::cout << "TruePerson constructor" << std::endl;
  }

  TruePerson(const TruePerson& other) : name_(other.name_) { // 拷贝构造函数
    std::cout << "TruePerson copy constructor" << std::endl;
  }

  TruePerson(TruePerson&& other) noexcept: name_(std::move(other.name_)) { // 移动构造函数
    std::cout << "TruePerson move constructor" << std::endl;
  }

 private:
  std::string name_;
};

class Student : public TruePerson {
 public:
  explicit Student(const std::string& name) : TruePerson(name) {
    std::cout << "Student constructor" << std::endl;
  }
};

int main() {
  Person p1("tom");
  short idx = 1;
  // Person p2(idx); // 编译失败，构造函数冲突

  TruePerson tp1("tom");
  TruePerson tp2(idx); // 通过模板约束后，编译成功

  Student s1("tom");
  return 0;
}
