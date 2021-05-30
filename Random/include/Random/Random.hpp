//////////////////////////////////////////////////////////////////////////////
/// ####   ##   ##   # ####   ###  ##   ##
/// #  #  #  #  # #  # #   # #   # # # # #
/// ###   ####  # #  # #   # #   # #  #  #
/// # #  ##  ## #  # # #   # #   # #     #
/// #  # #    # #   ## ####   ###  #     #
///
/// Version 2.1
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <random>
#include <chrono>
#include <numeric>
#include <vector>

namespace Ng {

    template <typename T>
    concept BoolConcept = std::is_same_v<T, bool>;

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
        template <typename T>
        static T Get();

        template <typename T>
        static T GetFromRange(const T& min, const T& max);

        template <BoolConcept T>
        static T Get(float probability = 0.5f);

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