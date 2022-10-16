#include <iostream>
#include <vector>
#include <unordered_map>
#include <boost/type_index.hpp>

using boost::typeindex::type_id_with_cvr;

#define GET_TIME() std::chrono::system_clock::now().time_since_epoch().count()
#define PRINT_TYPE(x) std::cout << #x << ": " << type_id_with_cvr<decltype(x)>().pretty_name() << std::endl

int main() {
  // 1. 使用auto可以简化闭包的表示，同时避免产生不必要的对象std::function，提高性能
  std::function<int(int)> f1 = [](int x) { return x * x; };
  auto f2 = [](int x) { return x * x; };
  auto beg_time = GET_TIME();
  for (int i = 0; i < 10000; ++i) {
    f1(i);
  }
  auto end_time = GET_TIME();
  std::cout << "f1 cost time: " << end_time - beg_time << " ns" << std::endl; // 700+ ns

  beg_time = GET_TIME();
  for (int i = 0; i < 10000; ++i) {
    f2(i);
  }
  end_time = GET_TIME();
  std::cout << "f2 cost time: " << end_time - beg_time << " ns" << std::endl; // 70+ ns

  // 2. 使用auto可以避免一些无心的错误
  std::unordered_map<std::string, int> m;
  m["a"] = 1;
  m["b"] = 2;
  m["c"] = 3;
  beg_time = GET_TIME();
  for (int i = 0; i < 10000; ++i) {
    for (const std::pair<std::string, int>
          & it : m) { // 其实unordered_map保存的pair是std::pair<const std::string, int>，这里会产生一个临时对象
    }
  }
  end_time = GET_TIME();
  std::cout << "not use auto to iterate, cost time: " << end_time - beg_time << " ns" << std::endl; // 4000+ ns

  beg_time = GET_TIME();
  for (int i = 0; i < 10000; ++i) {
    for (const auto& it : m) {
    }
  }
  end_time = GET_TIME();
  std::cout << "use auto to iterate, cost time: " << end_time - beg_time << " ns" << std::endl; // 2000+ ns

  // 3. 使用auto可以更方便的进行平台迁移
  auto s = sizeof(long); // 32位机器上为4，64位机器上为8
  std::cout << "sizeof(long): " << s << std::endl;

  // 4. 使用auto注意不要和隐形代理表达式合用
  std::vector<bool> v{false, true, false, true};
  bool b = v[0];
  auto b2 = v[0]; // b2的类型是std::vector<bool>::reference，而不是bool，可能会产生未定义行为!
  PRINT_TYPE(b2);
  std::cout << "b: " << b << ", b2: " << b2 << std::endl;

  return 0;
}
