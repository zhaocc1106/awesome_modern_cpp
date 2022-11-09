#ifndef SMART_PTR__PIMPL_H_
#define SMART_PTR__PIMPL_H_

#include <memory>

class Widget {
 public:
  Widget() noexcept;
  ~Widget() noexcept;
  Widget(Widget&& rhs) noexcept;
  Widget& operator=(Widget&& rhs) noexcept;

  const std::string& name() const;
  const std::vector<double>& data() const;

 private:
  // 在源文件中声明，可以使结构体变化时不用重新编译所有引用了该头文件的源文件
  struct Impl;
  std::unique_ptr<Impl> p_impl_;
};

#endif // SMART_PTR__PIMPL_H_
