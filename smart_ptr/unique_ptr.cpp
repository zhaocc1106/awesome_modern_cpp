#include <iostream>

class Investment {
 public:
  Investment() { std::cout << "Investment()" << std::endl; }
  virtual ~Investment() { std::cout << "~Investment()" << std::endl; }
};

class Stock : public Investment {
 public:
  Stock() { std::cout << "Stock()" << std::endl; }
  ~Stock() override { std::cout << "~Stock()" << std::endl; }
};

class Bond : public Investment {
 public:
  Bond() { std::cout << "Bond()" << std::endl; }
  ~Bond() override { std::cout << "~Bond()" << std::endl; }
};

class RealEstate : public Investment {
 public:
  RealEstate() { std::cout << "RealEstate()" << std::endl; }
  ~RealEstate() override { std::cout << "~RealEstate()" << std::endl; }
};

enum class InvestmentType { Stock, Bond, RealEstate };

// 使用lambda自定义指针清理过程
auto del_inv = [](Investment *p) {
  std::cout << "Calling delete for Investment" << std::endl;
  delete p;
};

class InvestmentFactory {
 public:

  // 返回值是一个unique_ptr，指向Investment的派生类
  template<typename... Ts>
  auto Create(InvestmentType type, Ts &&... params) {
    std::unique_ptr<Investment, decltype(del_inv)> p_inv(nullptr, del_inv);
    if (type == InvestmentType::Stock) {
      p_inv.reset(new Stock(std::forward<Ts>(params)...));
    } else if (type == InvestmentType::Bond) {
      p_inv.reset(new Bond(std::forward<Ts>(params)...));
    } else if (type == InvestmentType::RealEstate) {
      p_inv.reset(new RealEstate(std::forward<Ts>(params)...));
    } else {
      throw std::runtime_error("Unknown investment type");
    }
    return p_inv;
  }

  static InvestmentFactory &Instance() {
    static InvestmentFactory instance;
    return instance;
  }

  InvestmentFactory(const InvestmentFactory &) = delete;
  InvestmentFactory &operator=(const InvestmentFactory &) = delete;
  InvestmentFactory(InvestmentFactory &&) = delete;
  InvestmentFactory &operator=(InvestmentFactory &&) = delete;

  ~InvestmentFactory() = default;

 private:
  InvestmentFactory() = default;
};

// 自定义指针清理过程函数
void del_inv2(Investment *p) {
  std::cout << "Calling delete for Investment" << std::endl;
  delete p;
}

class InvestmentFactory2 {
 public:

  // 返回值是一个unique_ptr，指向Investment的派生类
  template<typename... Ts>
  auto Create(InvestmentType type, Ts &&... params) {
    std::unique_ptr<Investment, void (*)(Investment *)> p_inv(nullptr, del_inv2);
    if (type == InvestmentType::Stock) {
      p_inv.reset(new Stock(std::forward<Ts>(params)...));
    } else if (type == InvestmentType::Bond) {
      p_inv.reset(new Bond(std::forward<Ts>(params)...));
    } else if (type == InvestmentType::RealEstate) {
      p_inv.reset(new RealEstate(std::forward<Ts>(params)...));
    } else {
      throw std::runtime_error("Unknown investment type");
    }
    return p_inv;
  }

  static InvestmentFactory2 &Instance() {
    static InvestmentFactory2 instance;
    return instance;
  }

  InvestmentFactory2(const InvestmentFactory2 &) = delete;
  InvestmentFactory2 &operator=(const InvestmentFactory2 &) = delete;
  InvestmentFactory2(InvestmentFactory2 &&) = delete;
  InvestmentFactory2 &operator=(InvestmentFactory2 &&) = delete;

  ~InvestmentFactory2() = default;

 private:
  InvestmentFactory2() = default;
};

int main() {
  auto &factory = InvestmentFactory::Instance();
  auto p_inv = factory.Create(InvestmentType::Stock);
  std::cout << "size of p_inv: " << sizeof(p_inv) << std::endl; // 8，使用无状态的lambda定义删除器不会增加指针尺寸
  // auto p_inv3 = p_inv; // 编译不通过，因为unique_ptr是不可拷贝的
  auto p_inv3 = std::move(p_inv); // 将指针所有权转移

  auto &factory2 = InvestmentFactory2::Instance();
  auto p_inv2 = factory2.Create(InvestmentType::Stock);
  std::cout << "size of p_inv2: " << sizeof(p_inv2) << std::endl; // 16，使用有状态的函数定义删除器会增加指针尺寸，至少增加一个指针的尺寸

  int* p = new int(10);
  p[0] = 1;
  std::unique_ptr<int[]> p_arr(p);
  std::cout << "p_arr[0]: " << p_arr[0] << std::endl; // unique_ptr可以像数组一样使用，但是不建议这样使用
  return 0;
}
