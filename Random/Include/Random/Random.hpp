//////////////////////////////////////////////////////////////////////////////
/// ####   ##   ##   # ####   ###  ##   ##
/// #  #  #  #  # #  # #   # #   # # # # #
/// ###   ####  # #  # #   # #   # #  #  #
/// # #  ##  ## #  # # #   # #   # #     #
/// #  # #    # #   ## ####   ###  #     #
///
/// Version 2.2
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <random>
#include <chrono>
#include <numeric>
#include <vector>
#include <type_traits>
#include <iterator>

#include "TypeInfo.hpp"

namespace Ng {

    class Random {
    public:
                              using BooleanDistribution       = std::bernoulli_distribution;
        template <typename T> using IntegralDistribution      = std::uniform_int_distribution<T>;
        template <typename T> using FloatingPointDistribution = std::uniform_real_distribution<T>;
        template <typename T> using Limit                     = std::numeric_limits<T>;

    public:
        Random() = delete;
        Random(const Random& other) = delete;
        Random(Random&& other) = delete;
        ~Random() = default;

    public:
        template <typename T> requires (!IsIntegralConcept<T> && !IsFloatingPoint<T>)
        static T Get();

        template <typename T> requires IsIntegralConcept<T> || IsFloatingPointConcept<T>
        static T Get();

        template <IsBoolConcept T>
        static T Get(float probability = 0.5f);

        template <typename T>
        static T Get(std::initializer_list<T> list);

        template <typename T> requires (!IsIntegralConcept<T> && !IsFloatingPoint<T> && !IsIteratorConcept<T>)
        static T GetFromRange(const T& min, const T& max);

        template <IsIntegralConcept T>
        static T GetFromRange(T min, T max);

        template <IsFloatingPointConcept T>
        static T GetFromRange(T min, T max);

        // Rely to standard common_type detection
        template <IsPrimitiveDataTypeConcept T, IsPrimitiveDataTypeConcept U>
        static std::common_type_t<T, U> GetFromRange(T min, U max);

        template <IsIteratorConcept T>
        static T GetFromRange(T begin, T end);

        static std::string GetString(std::size_t size, char min = 33, char max = 126);

        template <IsRandomAccessIteratorConcept Iterator>
        static void Fill(Iterator begin, Iterator end);

        template <IsRandomAccessIteratorConcept Iterator, typename T>
        static void Fill(Iterator begin, Iterator end, const T& min, const T& max);

        template <IsRandomAccessIteratorConcept Iterator>
        static void Shuffle(Iterator begin, Iterator end);

    public:
        Random& operator =(const Random& other) = delete;
        Random& operator =(Random&& other) = delete;

    private:
        struct Data {
            std::random_device RandomDevice;
            std::seed_seq      SeedSequence;
            std::mt19937       MersenneTwister;
        };

    private:
        static Data& GetData();

    }; // class Random

} // namespace Ng

#include "Random.inl"