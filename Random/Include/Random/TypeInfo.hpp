#pragma once

namespace Ng {

    namespace Internal {

        template <typename T, typename = void>
        struct IsIterator {
            static constexpr bool Value = false;
        };

        template<typename T>
        struct IsIterator<T, typename std::enable_if<!std::is_same_v<typename std::iterator_traits<T>::value_type, void>>::type> {
            static constexpr bool Value = true;
        };

    } // namespace Internal

    // Static variables
    template <typename T>
    static inline constexpr bool IsIntegral = std::is_integral_v<T>;

    template <typename T>
    static inline constexpr bool IsFloatingPoint = std::is_floating_point_v<T>;

    template <typename T>
    static inline constexpr bool IsIterator = Internal::IsIterator<T>::Value;

    // Concepts
    template <typename T>
    concept IsIntegralConcept = std::is_integral_v<T>;

    template <typename T>
    concept IsBoolConcept = std::is_same_v<T, bool>;

    template <typename T>
    concept IsFloatingPointConcept = std::is_floating_point_v<T>;

    template <typename T>
    concept IsIteratorConcept = IsIterator<T>;

    template <typename T>
    concept IsRandomAccessIteratorConcept = std::is_same_v<
        typename std::iterator_traits<T>::iterator_category,
        std::random_access_iterator_tag
    >;

    template <typename T>
    concept IsPrimitiveDataTypeConcept = IsIntegral<T> || IsFloatingPoint<T>;

    template <typename T>
    concept IsContainerConcept = requires (T t) {
        { std::begin(t) };
        { std::end(t)   };
    };

    // TODO
//    template <typename T>
//    concept IsStdSequenceContainerConcept = IsContainerConcept<T>;
//
//    template <typename T>
//    concept IsStdContainerAdaptorConcept = IsContainerConcept<T> && requires (T t, typename T::iterator iterator) {
//        { t.insert(iterator, T::value_type()) };
//    };
//
//    template <typename T>
//    concept IsStdAssociativeAdaptorConcept = IsContainerConcept<T> && requires (T t, typename T::iterator iterator) {
//        { t.insert(iterator, T::value_type()) };
//    };
//
//    template <typename T>
//    concept IsStdUnorderedAssociativeConcept = IsContainerConcept<T> && requires (T t, typename T::iterator iterator) {
//        { t.insert(iterator, T::value_type()) };
//    };

} // namespace Ng