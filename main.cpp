#include <iostream>

#include <Random/Random.hpp>

int main() {
    for (int i = 0; i < 10; ++i)
        std::cout << Ng::Random::Get<bool>(0.5f) << std::endl;

    return 0;
}
