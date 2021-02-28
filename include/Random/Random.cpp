#include "Random.hpp"

namespace Ng {

    // Member constructor
    Random::Random() :
        m_SeedSequence({
            m_RandomDevice(),
            static_cast<unsigned int>(std::chrono::steady_clock::now().time_since_epoch().count())
        }),
        m_MersenneTwister(m_SeedSequence) { }

    // Member static methods
    Random& Random::GetInstance() {
        static Random instance;
        return instance;
    }

    std::string Random::GetString(int size, int left, int right) {
        return GetInstance().GetStringImpl(size, left, right);
    }

    std::string Random::GetStringImpl(int size, int left, int right) {
        std::string result;

        result.resize(size);

        for (auto& ch : result)
            ch = GetImpl<char>(left, right);

        return result;
    }

} // namespace Ng