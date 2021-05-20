//////////////////////////////////////////////////////////////////////////////
/// ####   ##   ##   # ####   ###  ##   ##
/// #  #  #  #  # #  # #   # #   # # # # #
/// ###   ####  # #  # #   # #   # #  #  #
/// # #  ##  ## #  # # #   # #   # #     #
/// #  # #    # #   ## ####   ###  #     #
///
/// Version 2.0
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <random>
#include <chrono>
#include <numeric>
#include <vector>

namespace Ng {

    template <typename T>
    concept IntegralConcept = std::is_integral_v<T>;

    template <typename T>
    concept BoolConcept = std::is_same_v<T, bool>;

    template <typename T>
    concept FloatingPointConcept = std::is_floating_point_v<T>;

    class Random {
    public:
                              using BooleanDist       = std::bernoulli_distribution;
        template <typename T> using IntegralDist      = std::uniform_int_distribution<T>;
        template <typename T> using FloatingPointDist = std::uniform_real_distribution<T>;
        template <typename T> using Limit             = std::numeric_limits<T>;

    public:
        Random() = delete;
        Random(const Random& other) = delete;
        Random(Random&& other) = delete;
        ~Random() = default;

    public:
        template <BoolConcept T>
        static T Get(float probability);

        template <IntegralConcept T>
        static T Get(T left = Limit<T>::min(), T right = Limit<T>::max());

        template <FloatingPointConcept T>
        static T Get(T left = Limit<T>::min(), T right = Limit<T>::max());

        template <typename T>
        static T Get(const std::vector<T>& data);

        static std::string GetString(std::size_t size, char left = 33, char right = 126);

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