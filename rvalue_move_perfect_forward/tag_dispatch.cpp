#include <iostream>
#include <set>
#include <unordered_map>

std::multiset<std::string> names;
template<typename T>
void log_and_add(T&& name) {
  std::cout << "log_and_add(T&& name) " << name << std::endl;
  names.insert(std::forward<T>(name));
}

std::unordered_map<int, std::string> name_map = {
    {0, "tony"},
    {1, "haha"},
    {2, "hehe"},
    {3, "xixi"},
    {4, "hoho"},
    {5, "lala"},
    {6, "lili"},
    {7, "lulu"},
    {8, "lolo"},
    {9, "lili"},
};
void log_and_add(int idx) {
  std::cout << "log_and_add(int idx) " << name_map[idx] << std::endl;
  names.insert(name_map[idx]);
}

void log_and_add_impl(int idx, std::true_type) {
  std::cout << "log_and_add_impl(int idx, std::true_type) " << name_map[idx] << std::endl;
  names.insert(name_map[idx]);
}

template<typename T>
void log_and_add_impl(T&& name, std::false_type) {
  std::cout << "log_and_add_impl(T&& name, std::false_type) " << name << std::endl;
  names.insert(std::forward<T>(name));
}

template<typename T>
void log_and_add2(T&& name) {
  // std::cout << "log_and_add2(T&& name) " << name << std::endl;
  log_and_add_impl(std::forward<T>(name),
                   std::is_integral<typename std::remove_reference_t<T>>()); // 如果是整数类型，就调用调用log_and_add_impl(int idx, std::true_type)函数
}

int main() {
  std::string new_name("James");
  log_and_add(new_name); // 调用模板函数
  log_and_add("John"); // 调用模板函数
  log_and_add(std::string("Frank")); // 调用模板函数
  log_and_add(0); // 调用重载函数log_and_add(int idx)
  log_and_add(1); // 调用重载函数log_and_add(int idx)

  short idx = 2;
  // log_and_add(idx); // 编译不通过，因为模板函数优先匹配

  // 使用标签分派解决上述万能引用模板函数与重载函数冲突的问题
  log_and_add2(new_name); // 调用log_and_add_impl(T&& name, std::false_type)
  log_and_add2("John"); // 调用log_and_add_impl(T&& name, std::false_type)
  log_and_add2(std::string("Frank")); // 调用log_and_add_impl(T&& name, std::false_type)
  log_and_add2(0); // 调用log_and_add_impl(int idx, std::true_type)
  log_and_add2(1); // 调用log_and_add_impl(int idx, std::true_type)
  log_and_add2(idx); // 调用log_and_add_impl(int idx, std::true_type)
  return 0;
}
