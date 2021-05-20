#include <iostream>

#include <Random/Random.hpp>

int main() {
    std::cout << Ng::Random::Get<bool>(0.5f) << std::endl;
    std::cout << Ng::Random::Get(-10, 10) << std::endl;
    std::cout << Ng::Random::Get(0.0f, 1.0f) << std::endl;
    std::cout << Ng::Random::Get<float>({ 0.1f, 1.0f, 5.0f }) << std::endl;
}