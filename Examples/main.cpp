#include <iostream>

#include <Random/Random.hpp>

struct Foo {
    int   A;
    float B;
};

// Overload for custom type!
namespace Ng {

    template <>
    Foo Random::Get() {
        return { Random::Get<int>(), Random::GetFromRange<float>(1.0f, 5.0f) };
    }

    template <>
    Foo Random::GetFromRange(const Foo& min, const Foo& max) {
        return { Random::GetFromRange(min.A, max.A), Random::GetFromRange(min.B, max.B) };
    }

} // namespace Ng

int main() {
    std::cout << Ng::Random::Get<int>() << std::endl;

    std::cout << Ng::Random::Get<bool>(0.5f) << std::endl;
    std::cout << Ng::Random::GetFromRange(-10, 10) << std::endl;
    std::cout << Ng::Random::GetFromRange(0.0f, 1.0f) << std::endl;

    auto [a, b] = Ng::Random::Get<Foo>();

    std::cout << "a: " << a << std::endl;
    std::cout << "b: " << b << std::endl;

    auto foo = Ng::Random::GetFromRange<Foo>({ 0, 1.0f }, { 100, 2.0f });

    std::cout << "a from range: " << foo.A << std::endl;
    std::cout << "b from range: " << foo.B << std::endl;
}