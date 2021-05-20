namespace Ng {

    template <BoolConcept T>
    T Random::Get(float probability) {
        return BooleanDist(probability)(GetData().MersenneTwister);
    }

    template <IntegralConcept T>
    T Random::Get(T left, T right) {
        auto& mt = GetData().MersenneTwister;

        return left < right ? IntegralDist<T>(left, right)(mt) : IntegralDist<T>(right, left)(mt);
    }

    template <FloatingPointConcept T>
    T Random::Get(T left, T right) {
        auto& mt = GetData().MersenneTwister;

        return left < right ? FloatingPointDist<T>(left, right)(mt) : FloatingPointDist<T>(right, left)(mt);
    }

    template <typename T>
    T Random::Get(const std::vector<T>& data) {
        return data[Get<std::size_t>(0, data.size() - 1)];
    }

} // namespace Ng