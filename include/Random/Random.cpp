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

} // namespace Ng