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
        // aliases
        template <typename T> using IntegerDistribution = std::uniform_int_distribution<T>;
        template <typename T> using RealDistribution    = std::uniform_real_distribution<T>;
        template <typename T> using Limit               = std::numeric_limits<T>;

        // constructor / destructor
        Random(const Random& other) = delete;
        ~Random() = default;

        // static public methods
        template <typename T>
        static T Get(T left = Limit<T>::min(), T right = Limit<T>::max());

        // operators
        Random operator=(const Random& other) = delete;

    private:
        // member constructor
        Random();

        // member static methods
        static Random& GetInstance();

        // member methods
        template <typename T>
        typename std::enable_if<std::is_integral<T>::value, T>::type GetImpl(T left, T right);

        template <typename T>
        typename std::enable_if<std::is_floating_point<T>::value, T>::type GetImpl(T left, T right);

        // member data
        std::random_device m_RandomDevice;
        std::seed_seq      m_SeedSequence;
        std::mt19937       m_MersenneTwister;

    }; // class Random

    //////////////////////////////////////////////////////////////////////////////
    /// Source
    //////////////////////////////////////////////////////////////////////////////
    // static public methods
    template <typename T>
    T Random::Get(T left, T right) {
        return GetInstance().GetImpl<T>(left, right);
    }

    // member constructor
    Random::Random() :
        m_SeedSequence({
           m_RandomDevice(),
           static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
        }),
        m_MersenneTwister(m_SeedSequence) { }

    // member static methods
    Random& Random::GetInstance() {
        static Random instance;
        return instance;
    }

    // member methods
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