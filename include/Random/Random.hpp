//////////////////////////////////////////////////////////////////////////////
/// ####   ##   ##   # ####   ###  ##   ##
/// #  #  #  #  # #  # #   # #   # # # # #
/// ###   ####  # #  # #   # #   # #  #  #
/// # #  ##  ## #  # # #   # #   # #     #
/// #  # #    # #   ## ####   ###  #     #
///
/// Version 1.0
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <random>
#include <chrono>
#include <numeric>

namespace Ng {

    //////////////////////////////////////////////////////////////////////////////
    /// Header
    //////////////////////////////////////////////////////////////////////////////
    class Random {
    public:
        // Aliases
                              using BooleanDistribution = std::bernoulli_distribution;
        template <typename T> using IntegerDistribution = std::uniform_int_distribution<T>;
        template <typename T> using RealDistribution    = std::uniform_real_distribution<T>;
        template <typename T> using Limit               = std::numeric_limits<T>;

        // Constructor / Destructor
        Random(const Random& other) = delete;
        ~Random() = default;

        // Public static methods
        template <typename T>
        static T Get(float probability);

        template <typename T>
        static T Get(T left = Limit<T>::min(), T right = Limit<T>::max());

        // Operators
        Random& operator=(const Random& other) = delete;

    private:
        // Member constructor
        Random();

        // Member static methods
        static Random& GetInstance();

        // Member methods
        template <typename T>
        typename std::enable_if<std::is_same<T, bool>::value, bool>::type GetImpl(float probability);

        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, T>::type GetImpl(T left, T right);

        template <typename T>
        typename std::enable_if<std::is_floating_point<T>::value, T>::type GetImpl(T left, T right);

        // Member data
        std::random_device m_RandomDevice;
        std::seed_seq      m_SeedSequence;
        std::mt19937       m_MersenneTwister;

    }; // class Random

    //////////////////////////////////////////////////////////////////////////////
    /// Source
    //////////////////////////////////////////////////////////////////////////////
    // Static public methods
    template <typename T>
    T Random::Get(float probability) {
        return GetInstance().GetImpl<T>(probability);
    }

    template <typename T>
    T Random::Get(T left, T right) {
        return GetInstance().GetImpl<T>(left, right);
    }

    // Member methods
    template <typename T>
    typename std::enable_if<std::is_same<T, bool>::value, bool>::type Random::GetImpl(float probability) {
        return BooleanDistribution(probability)(m_MersenneTwister);
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value, T>::type Random::GetImpl(T left, T right) {
        return left < right ?
               IntegerDistribution<T>(left, right)(m_MersenneTwister) :
               IntegerDistribution<T>(right, left)(m_MersenneTwister);
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type Random::GetImpl(T left, T right) {
        return left < right ?
               RealDistribution<T>(left, right)(m_MersenneTwister) :
               RealDistribution<T>(right, left)(m_MersenneTwister);
    }

} // namespace Ng