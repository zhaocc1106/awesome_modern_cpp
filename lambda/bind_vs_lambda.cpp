#include <iostream>
#include <thread>

void cur_time(long long time) {
  std::cout << "cur_time: " << time << std::endl;
}

void func() {
  auto time = std::chrono::system_clock::now().time_since_epoch().count();
}

int main() {
  // 使用bind容易出现不容易发现的错误
  auto func_l = []() {
    cur_time(std::chrono::system_clock::now().time_since_epoch().count());
  };
  auto func_b = std::bind(cur_time, std::chrono::system_clock::now().time_since_epoch().count());
  std::this_thread::sleep_for(std::chrono::seconds(1));
  func_l(); // 打印的是当前时间戳
  func_b(); // 打印的其实是创建func_b时的时间戳，因为bind是在创建时就绑定了参数

  // 使用lambda可以触发内联优化，有时性能会更好一些
  auto func_l2 = []() {
    func();
  };
  auto func_b2 = std::bind(func);
  auto begin = std::chrono::system_clock::now().time_since_epoch().count();
  for (int i = 0; i < 10000000; ++i) {
    func_l2();
  }
  auto end = std::chrono::system_clock::now().time_since_epoch().count();
  std::cout << "lambda: " << end - begin << std::endl;
  begin = std::chrono::system_clock::now().time_since_epoch().count();
  for (int i = 0; i < 10000000; ++i) {
    func_b2();
  }
  end = std::chrono::system_clock::now().time_since_epoch().count();
  std::cout << "bind: " << end - begin << std::endl;
}