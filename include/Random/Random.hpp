//////////////////////////////////////////////////////////////////////////////
/// ####   ##   ##   # ####   ###  ##   ##
/// #  #  #  #  # #  # #   # #   # # # # #
/// ###   ####  # #  # #   # #   # #  #  #
/// # #  ##  ## #  # # #   # #   # #     #
/// #  # #    # #   ## ####   ###  #     #
///
/// Version 1.1
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include <random>
#include <chrono>
#include <numeric>
#include <vector>

namespace Ng {

    //////////////////////////////////////////////////////////////////////////////
    /// Header
    //////////////////////////////////////////////////////////////////////////////
    class Random {
    public:
                              using BooleanDistribution = std::bernoulli_distribution;
        template <typename T> using IntegerDistribution = std::uniform_int_distribution<T>;
        template <typename T> using RealDistribution    = std::uniform_real_distribution<T>;
        template <typename T> using Limit               = std::numeric_limits<T>;

        Random(const Random& other) = delete;
        Random(Random&& other) = delete;
        ~Random() = default;

        template <typename T>
        static T Get(float probability);

        template <typename T>
        static T Get(T left = Limit<T>::min(), T right = Limit<T>::max());

        template <typename T>
        static T Get(const std::initializer_list<T>& list);

        template <typename T>
        static T Get(const std::vector<T>& data);

        static std::string GetString(int size, int left = 33, int right = 126);

        Random& operator =(const Random& other) = delete;
        Random& operator =(Random&& other) = delete;

    private:
        Random();

        static Random& GetInstance();

        // Member methods
        template <typename T>
        typename std::enable_if<std::is_same<T, bool>::value, bool>::type GetImpl(float probability);

        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, T>::type GetImpl(T left, T right);

        template <typename T>
        typename std::enable_if<std::is_floating_point<T>::value, T>::type GetImpl(T left, T right);

        template <typename T>
        T GetImpl(const std::initializer_list<T>& list);

        template <typename T>
        T GetImpl(const std::vector<T>& data);

        std::string GetStringImpl(int size, int left, int right);

    private:
        std::random_device m_RandomDevice;
        std::seed_seq      m_SeedSequence;
        std::mt19937       m_MersenneTwister;

    }; // class Random

    //////////////////////////////////////////////////////////////////////////////
    /// Source
    //////////////////////////////////////////////////////////////////////////////
    template <typename T>
    T Random::Get(float probability) {
        return GetInstance().GetImpl<T>(probability);
    }

    template <typename T>
    T Random::Get(T left, T right) {
        return GetInstance().GetImpl<T>(left, right);
    }

    template <typename T>
    T Random::Get(const std::initializer_list<T>& list) {
        return GetInstance().GetImpl(list);
    }

    template <typename T>
    T Random::Get(const std::vector<T>& data) {
        return GetInstance().GetImpl(data);
    }

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

    template <typename T>
    T Random::GetImpl(const std::initializer_list<T>& list) {
        std::vector<T> data(list.begin(), list.end());

        return data[GetImpl<std::size_t>(0, data.size() - 1)];
    }

    template <typename T>
    T Random::GetImpl(const std::vector<T>& data) {
        return data[GetImpl<std::size_t>(0, data.size() - 1)];
    }

} // namespace Ng