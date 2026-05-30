#include <utility>
#include <concepts>
#include <cstddef>

template <typename... Ts>
struct all_unique;

template <typename FirstType, typename... OtherTypes>
struct all_unique<FirstType, OtherTypes...> {
    static constexpr bool value = (!std::same_as<FirstType, OtherTypes> && ...)
                                    && all_unique<OtherTypes...>::value;
};

template <>
struct all_unique<> {
    static constexpr bool value = true;
};

template <typename... Ts>
static constexpr bool all_unique_v = all_unique<Ts...>::value;


template <typename... Ts>
    requires all_unique_v<Ts...>
class type_set {
    public:

        static constexpr std::size_t size = sizeof...(Ts);
        static constexpr bool empty = false;

        template <typename SearchType>
        static constexpr bool contains = (std::same_as<SearchType, Ts> || ...);
        
        template <typename InsertType>
        using insert = type_set<Ts..., InsertType>;
};

template <>
class type_set<> {
    public:

        static constexpr std::size_t size = 0;
        static constexpr bool empty = true;

        template <typename SearchType>
        static constexpr bool contains = false;

        template <typename InsertType>
        using insert = type_set<InsertType>;
};