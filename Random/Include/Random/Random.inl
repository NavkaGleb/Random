#include <stdexcept>
#include <iostream>

namespace Ng {

    template <typename T> requires (!IsIntegralConcept<T> && !IsFloatingPoint<T>)
    T Random::Get() {
        throw std::runtime_error("Ng::Random::Get: Called for an unknown type!");
    }

    template <typename T> requires IsIntegralConcept<T> || IsFloatingPointConcept<T>
    T Random::Get() {
        return GetFromRange(Limit<T>::min(), Limit<T>::max());
    }

    template <IsBoolConcept T>
    T Random::Get(float probability) {
        return BooleanDistribution(std::max(0.0f, std::min(1.0f, probability)))(GetData().MersenneTwister);
    }

    template <typename T>
    T Random::Get(std::initializer_list<T> list) {
        return *GetFromRange(list.begin(), list.end());
    }

    template <typename T> requires (!IsIntegralConcept<T> && !IsFloatingPoint<T> && !IsIteratorConcept<T>)
    T Random::GetFromRange(const T& min, const T& max) {
        throw std::runtime_error("Ng::Random::GetFromRange: Called for an unknown type!");
    }

    template <IsIntegralConcept T>
    T Random::GetFromRange(T min, T max) {
        return IntegralDistribution<T>(std::min(min, max), std::max(min, max))(GetData().MersenneTwister);
    }

    template <IsFloatingPointConcept T>
    T Random::GetFromRange(T min, T max) {
        return FloatingPointDistribution<T>(std::min(min, max), std::max(min, max))(GetData().MersenneTwister);
    }

    template <IsPrimitiveDataTypeConcept T, IsPrimitiveDataTypeConcept U>
    std::common_type_t<T, U> Random::GetFromRange(T min, U max) {
        return GetFromRange<std::common_type_t<T, U>>(min, max);
    }

    template <IsIteratorConcept T>
    T Random::GetFromRange(T begin, T end) {
        using DifferenceType = typename std::iterator_traits<T>::difference_type;

        return std::next(begin, GetFromRange<DifferenceType>(0, std::distance(begin, end) - 1));
    }

    template <IsRandomAccessIteratorConcept Iterator>
    void Random::Fill(Iterator begin, Iterator end) {
        using ValueType = typename std::iterator_traits<Iterator>::value_type;

        for (auto i = begin; i != end; ++i)
            *i = Get<ValueType>();
    }

    template <IsRandomAccessIteratorConcept Iterator, typename T>
    void Random::Fill(Iterator begin, Iterator end, const T& min, const T& max) {
        for (auto i = begin; i != end; ++i)
            *i = GetFromRange(min, max);
    }

    template <IsRandomAccessIteratorConcept Iterator>
    void Random::Shuffle(Iterator begin, Iterator end) {
        std::shuffle(begin, end, GetData().MersenneTwister);
    }

} // namespace Ng