#include "pimpl.h"
#include <string>
#include <vector>
#include <iostream>

struct Widget::Impl {
  std::string name;
  std::vector<double> data;
};

Widget::Widget() noexcept: p_impl_(new Impl{"default", {1, 2, 3}}) {
  std::cout << "Widget()" << std::endl;
}

Widget::~Widget() noexcept {
  std::cout << "~Widget()" << std::endl;
}

Widget::Widget(Widget&& rhs) noexcept {
  std::cout << "Widget(Widget&& rhs)" << std::endl;
  p_impl_ = std::move(rhs.p_impl_);
}
Widget& Widget::operator=(Widget&& rhs) noexcept {
  std::cout << "Widget& operator=(Widget&& rhs)" << std::endl;
  p_impl_ = std::move(rhs.p_impl_);
  return *this;
}

const std::string& Widget::name() const {
  return p_impl_->name;
}

const std::vector<double>& Widget::data() const {
  return p_impl_->data;
}