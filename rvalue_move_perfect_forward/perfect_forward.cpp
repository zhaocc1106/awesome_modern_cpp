#include <iostream>
#include <set>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_T_TYPE(T) std::cout << #T << ": " << type_id_with_cvr<T>().pretty_name() << std::endl
#define PRINT_PARAM_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

std::multiset<std::string> names;

void log_and_add(const std::string& name) {
  std::cout << "Adding " << name << std::endl;
  names.insert(name);
}

// 使用万能引用和完美转发可以防止不必要的临时变量产生以及不必要的拷贝
template<typename T>
void log_and_add2(T&& name) {
  std::cout << "Adding " << name << std::endl;
  names.insert(std::forward<T>(name));
}

class Item {
 public:
  Item() {
    std::cout << "default constructor" << std::endl;
  }

  Item(const Item& other) {
    std::cout << "copy constructor" << std::endl;
  }

  Item(Item&& other) noexcept {
    std::cout << "move constructor" << std::endl;
  }

  Item& operator=(const Item& other) {
    std::cout << "copy assignment" << std::endl;
    return *this;
  }

  Item& operator=(Item&& other) noexcept {
    std::cout << "move assignment" << std::endl;
    return *this;
  }

  ~Item() {
    std::cout << "destructor" << std::endl;
  }
};

Item reduce_and_copy(const Item& item) {
  std::cout << "reduce_and_copy" << std::endl;
  return item;
}

// 某些场景下使用完美转发返回值，可以避免不必要的拷贝
template<typename T>
T&& reduce_and_copy2(T&& item) {
  PRINT_T_TYPE(T);
  PRINT_PARAM_TYPE(item);
  std::cout << "reduce_and_copy2" << std::endl;
  return std::forward<T>(item);
}

int main() {
  std::string new_name("James");
  log_and_add(new_name); // 传递左值，一次拷贝
  log_and_add(std::string("Sarah")); // 传递右值，一次拷贝而不是一次移动
  log_and_add("Mike"); // 传递字符串字面值，产生一个临时的std::string对象，一次拷贝

  log_and_add2(new_name); // 传递左值，一次拷贝
  log_and_add2(std::string("Sarah")); // 传递右值，一次移动
  log_and_add2("Mike"); // 传递字符串字面值，在插入到set时才产生一个std::string对象

  Item item;
  reduce_and_copy(item); // 传递左值，函数返回产生一次拷贝
  std::cout << "-----" << std::endl;
  reduce_and_copy(Item()); // 传递右值，函数返回依然产生一次拷贝
  std::cout << "-----" << std::endl;
  reduce_and_copy2(item); // 传递左值，不产生拷贝，直接返回左值引用
  std::cout << "-----" << std::endl;
  reduce_and_copy2(Item()); // 传递右值，不产生拷贝，直接返回右值引用
}
