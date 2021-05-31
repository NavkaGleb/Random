# Random Header-Only Library for modern C++
### Usage
```c++
#include <iostream>
#include <Random/Random.hpp>

int main() {
    // Return random integer number from -5 to 5
    std::cout << Ng::Random::Get(-5, 5) << std::endl;

    // Return 'true' value with probability 0.4
    std::cout << Ng::Random::Get<bool>(0.4f) << std::endl;
    
    // Return random value from given std::initializer_list
    std::cout << Ng::Random::Get({ 0, 5, 4, -1, 9 }) << std::endl;

    // Return random floating point number from min to max value of provided type
    std::cout << Ng::Random::GetFromRange<float>() << std::endl;
    
    // Return random value from range defining the common type
    std::cout << Ng::Random::GetFromRange(12, 43u) << std::endl;
    
    // Return random iterator from range
    const std::vector vector = { 12, 43, 32, -21, -4 };
    std::cout << Ng::Random::GetFromRange(vector.begin(), vector.end()) << std::endl;
}
```

# Integration
### CMake
- As subproject

```cmake
add_subdirectory(random)                  # path to the 'random' library root
                                          # create target
target_link_libraries(${TARGET} NgRandom) # add include path to a compiler
```