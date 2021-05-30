#include <stdexcept>
#include <iostream>

namespace Ng {

    template <typename T>
    T Random::Get() {
        if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
            return GetFromRange(Limit<T>::min(), Limit<T>::max());

        throw std::runtime_error("Ng::Random::Get: Called for an unknown type!");
    }

    template <typename T>
    T Random::GetFromRange(const T& min, const T& max) {
        auto& mt = GetData().MersenneTwister;

        if constexpr (std::is_integral_v<T>)
            return min < max ? IntegralDist<T>(min, max)(mt) : IntegralDist<T>(max, min)(mt);

        if constexpr (std::is_floating_point_v<T>)
            return min < max ? FloatingPointDist<T>(min, max)(mt) : FloatingPointDist<T>(min, max)(mt);

        throw std::runtime_error("Ng::Random::GetFromRange: Called for an unknown type!");
    }

    template <BoolConcept T>
    T Random::Get(float probability) {
        return BooleanDist(probability)(GetData().MersenneTwister);
    }

} // namespace Ng