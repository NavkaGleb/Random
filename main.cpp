#include <iostream>

#include <Random/Random.hpp>

int main() {
    for (int i = 0; i < 10; ++i)
        std::cout << Ng::Random::Get<int>(-5, 5) << std::endl;

    return 0;
}
