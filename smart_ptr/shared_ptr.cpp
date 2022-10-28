#include <iostream>

class Item {
 public:
  // Item() { std::cout << "Item()" << std::endl; }
  void Test() {}
  // virtual ~Item() { std::cout << "~Item()" << std::endl; }
};

int main() {
  std::unique_ptr<Item> p1(new Item);
  std::shared_ptr<Item> p2(new Item);
  std::cout << "size of p1: " << sizeof(p1) << std::endl; // 8
  std::cout << "size of p2: " << sizeof(p2) << std::endl; // 16，shared ptr指针固定是两个word的尺寸

  auto begin = std::chrono::system_clock::now();
  for (int i = 0; i < 100000; ++i) {
    std::unique_ptr<Item> p3(new Item);
    p3->Test();
  }
  auto end = std::chrono::system_clock::now();
  std::cout << "unique_ptr: " << (end - begin).count() << "ns" << std::endl;

  // shared_ptr的效率比unique_ptr低，因为shared_ptr需要维护引用计数
  begin = std::chrono::system_clock::now();
  for (int i = 0; i < 100000; ++i) {
    std::shared_ptr<Item> p4(new Item);
    p4->Test();
  }
  end = std::chrono::system_clock::now();
  std::cout << "shared_ptr: " << (end - begin).count() << "ns" << std::endl;

  std::shared_ptr<Item> p5 = p2; // 拷贝构造
  std::cout << (p2.get() != nullptr) << std::endl; // 1
  std::shared_ptr<Item> p6 = std::move(p2); // 移动构造
  std::cout << (p2.get() == nullptr) << std::endl; // 1

  std::shared_ptr<Item> p7 = std::move(p1); // unique_ptr升级为shared_ptr
  std::cout << (p1.get() == nullptr) << std::endl; // 1

  std::shared_ptr<Item> p8 = std::make_shared<Item>(); // 使用make_shared创建shared_ptr，总是创建一个引用计数控制块
  std::shared_ptr<Item> p9(std::make_unique<Item>()); // 使用unique_ptr构造shared_ptr，总是创建一个引用计数控制块
  std::shared_ptr<Item> p10(new Item); // 使用new创建shared_ptr，总是创建一个引用计数控制块

  auto logging_deleter = [](Item *p) {
    std::cout << "delete" << std::endl;
    delete p;
  };
  // 使用自定义的删除器，删除器类型属于unique_ptr的一部分，所以不同的删除器类型会导致不同的unique_ptr类型
  std::unique_ptr<Item, decltype(logging_deleter)> p11(new Item, logging_deleter);
  // 使用自定义的删除器，删除器的类型不属于shared_ptr的一部分，因此可以使用不同的删除器
  std::shared_ptr<Item> p12(new Item, logging_deleter);

  return 0;
}