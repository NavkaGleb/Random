#include <iostream>

#include <Random/Random.hpp>

struct Foo {
    int   A;
    float B;
};

// Overload for custom type!
namespace Ng {

    template <>
    Foo Random::Get<Foo>() {
        return { Random::Get<int>(), Random::Get<float>(1.0f, 5.0f) };
    }

} // namespace Ng

int main() {
    std::cout << Ng::Random::Get<int>() << std::endl;

    std::cout << Ng::Random::Get<bool>(0.5f) << std::endl;
    std::cout << Ng::Random::Get(-10, 10) << std::endl;
    std::cout << Ng::Random::Get(0.0f, 1.0f) << std::endl;
    std::cout << Ng::Random::Get<float>({ 0.1f, 1.0f, 5.0f }) << std::endl;

    auto [a, b] = Ng::Random::Get<Foo>();

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;
}