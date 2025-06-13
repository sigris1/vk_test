//
// Created by sigris on 11.06.2025.
//

#pragma once
#include "string"
#include "sstream"

template<typename result>
class ResultAnalyzer {
public:
    static std::string results_to_string(result Result) {
        if constexpr (std::is_void_v<result>) {
            return "";
        } else if constexpr (std::is_same_v<result, std::string>) {
            return Result;
        } else if constexpr (has_std_base_to_string<result>::value) {
            return std::to_string(Result);
        } else if constexpr (has_special_to_string<result>::value) {
            return Result.to_string();
        } else if constexpr (is_auto_printable<result>::value){
            std::stringstream now;
            now << Result;
            return now.str();
        } else if constexpr (is_container<result>::value){
            std::string returned;
            for (auto i : Result){
                returned += ResultAnalyzer<decltype(i)>::results_to_string(i) + " ";
            }
            returned.erase(--returned.end());
            return returned;
        } else if constexpr (is_pair<result>::value) {
            return ResultAnalyzer<decltype(Result.first)>::results_to_string(Result.first) + " " + ResultAnalyzer<decltype(Result.second)>::results_to_string(Result.second);
        } else if constexpr (is_tuple<result>::value){
            std::string returned;
            bool first = true;
            std::apply([&](const auto&... elems) {
                ((returned += (first ? "" : " ") + ResultAnalyzer<std::decay_t<decltype(elems)>>::results_to_string(elems), first = false), ...);
            }, Result);

            return returned;
        }
    }

private:
    template<typename value, typename = void>
    struct has_std_base_to_string
            : std::false_type {};

    template<class value>
    struct has_std_base_to_string<value, std::void_t<
            decltype(std::to_string(std::declval<value>()))
    >> : std::true_type {};

    template<typename value, typename = void>
    struct has_special_to_string
            : std::false_type {};

    template<class value>
    struct has_special_to_string<value, std::void_t<
            decltype(std::declval<value>().to_string())
    >> : std::true_type {};

    template<typename value, typename = void>
    struct is_auto_printable
            : std::false_type {};

    template<typename value>
    struct is_auto_printable<value, std::void_t<
            decltype(std::declval<std::stringstream>() << std::declval<value>())
    >> : std::true_type {};

    template<typename value, typename = void>
    struct is_container
            : std::false_type {};

    template<typename value>
    struct is_container<value, std::void_t<
            decltype(std::declval<value>().begin()),
            decltype(std::declval<value>().end()),
            typename value::value_type,
            typename value::iterator,
            typename value::const_iterator
    >> : std::true_type {};

    template<typename T>
    struct is_pair : std::false_type {};

    template<typename T1, typename T2>
    struct is_pair<std::pair<T1, T2>> : std::true_type {};

    template<typename value>
    struct is_tuple : std::false_type {};

    template<typename... Args>
    struct is_tuple<std::tuple<Args...>> : std::true_type {};

};