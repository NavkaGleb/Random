# Random Library
### Usage
```cpp
#include <iostream>
#include <Random/Random.hpp>

int main() {
    // Return random integer number from -5 to 5
    std::cout << Ng::Random::Get(-5, 5) << std::endl;

    // Return random floating point number from min to max value of provided type
    std::cout << Ng::Random::Get<float>() << std::endl;

    // Return random boolean number with probability 0.4
    std::cout << Ng::Random::Get<bool>(0.4f) << std::endl;
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