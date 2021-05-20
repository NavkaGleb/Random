#include <stdexcept>

namespace Ng {

    template <typename T>
    T Random::Get() {
        throw std::runtime_error("Ng::Random::Get: Called for an unknown type!");
    }

    template <typename T>
    T Random::Get(const T& min, const T& max) {
        throw std::runtime_error("Ng::Random::Get: Called for an unknown type!");
    }

    template <BoolConcept T>
    T Random::Get(float probability) {
        return BooleanDist(probability)(GetData().MersenneTwister);
    }

    template <IntegralConcept T>
    T Random::Get() {
        return Get<T>(Limit<T>::min(), Limit<T>::max());
    }

    template <IntegralConcept T>
    T Random::Get(const T& left, const T& right) {
        auto& mt = GetData().MersenneTwister;

        return left < right ? IntegralDist<T>(left, right)(mt) : IntegralDist<T>(right, left)(mt);
    }

    template <FloatingPointConcept T>
    T Random::Get() {
        return Get<T>(Limit<T>::min(), Limit<T>::max());
    }

    template <FloatingPointConcept T>
    T Random::Get(const T& left, const T& right) {
        auto& mt = GetData().MersenneTwister;

        return left < right ? FloatingPointDist<T>(left, right)(mt) : FloatingPointDist<T>(right, left)(mt);
    }

    template <typename T>
    T Random::Get(const std::vector<T>& data) {
        return data[Get<std::size_t>(0, data.size() - 1)];
    }

} // namespace Ng