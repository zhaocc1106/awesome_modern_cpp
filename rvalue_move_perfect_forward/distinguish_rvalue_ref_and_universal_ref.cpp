#include <iostream>

#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define PRINT_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

class Item {
 public:
  Item() = default;
  Item(const Item& other) {
    std::cout << "copy constructor" << std::endl;
  }
  Item(Item&& other) noexcept {
    std::cout << "move constructor" << std::endl;
  }
};

void f1(Item&& item) { // rvalue reference
  std::cout << "f1(Item&&)" << std::endl;
  PRINT_TYPE(item); // item: Item&&
}

template<typename T>
void f2(T&& item) { // universal reference
  std::cout << "f2(T&&)" << std::endl;
  PRINT_TYPE(item); // item: Item&
}

template<typename T>
void f3(std::vector<T>&& item) { // rvalue reference，类别推导和引用无关，所以不是万能引用
  std::cout << "f3(std::vector<T> &&)" << std::endl;
  PRINT_TYPE(item); // item: std::__1::vector<Item, std::__1::allocator<Item> >&&
}

int main() {
  Item&& item = Item(); // rvalue reference，右值引用本身是左值不是右值，因为右值是没有名字的
  PRINT_TYPE(item); // item: Item&&
  auto&& item2 = item; // universal reference，发生类别推导的是万能引用
  PRINT_TYPE(item2); // item2: Item&，万能引用会保持变量本身特性，本身是左值那就是左值引用，本身是右值，那就是右值引用
  f1(std::move(item));
  f2(item);
  f3(std::vector<Item>{{}, {}, {}});
}