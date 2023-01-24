namespace jc {

// 变量模板，C++14，设置模板参数的默认值
template<typename T = double>
constexpr T pi{static_cast<T>(3.1415926535897932385)};

static_assert(pi<bool> == true);
static_assert(pi<int> == 3);
static_assert(pi<double> == 3.1415926535897932385);
static_assert(pi<> == 3.1415926535897932385);

}  // namespace jc

int main() {}