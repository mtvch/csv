#ifndef TUPLE_HELPER_H
#define TUPLE_HELPER_H

#include <tuple>
#include <utility>
#include <ostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <typeinfo>
#include <sstream>

//https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple

template <typename T>
inline typename std::enable_if<std::is_integral<T>::value, bool>::type is_correct_string(std::string &string) {
    for (auto now : string) {
        if (now > '9' || now < '0') {
            return false;
        }
    }

    return true;
}

template <typename T>
inline typename std::enable_if<std::is_floating_point<T>::value, bool>::type is_correct_string(std::string & string) {
    int dots_counter = 0;

    for (auto now : string) {
        if (now == '.') {
            dots_counter++;
        }
        else if (now > '9' || now < '0') {
            return false;
        }
        if (dots_counter > 1) {
            return false;
        }
    }

    return true;
}

template <typename T>
inline void from_string(std::string &string, T &elem);

template <>
inline void from_string(std::string &string, std::string &elem) {
    elem = string;
}

template <typename T>
inline void from_string(std::string &string, T &elem) {
    if (!is_correct_string<T>(string)) {
        throw(std::string("Can't convert '") + string + "'");
    }
    std::stringstream convert(string);
    convert >> elem;
}

template <size_t I = 0, class Ch, class Tr, typename... Args>
inline typename std::enable_if<I == sizeof...(Args), void>::type add_each_to_ostream(std::tuple<Args...> const&, std::basic_ostream<Ch, Tr>&) {

}

template <size_t I = 0, class Ch, class Tr, typename... Args>
inline typename std::enable_if<I < sizeof...(Args), void>::type add_each_to_ostream(std::tuple<Args...> const& t, std::basic_ostream<Ch, Tr>& os) {
    os << std::get<I>(t) << " ";
    add_each_to_ostream<I + 1, Ch, Tr, Args...>(t, os);
}

template <class Ch, class Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, std::tuple<Args...> const& t) {
    add_each_to_ostream(t, os);
    return os;
}

template <size_t I = 0, typename... Args>
inline typename std::enable_if<I == sizeof...(Args), void>::type add_each_to_tuple(std::tuple<Args...> &t, std::vector<std::string> &v) {
    
}

template <size_t I = 0, typename... Args>
inline typename std::enable_if<I < sizeof...(Args), void>::type add_each_to_tuple(std::tuple<Args...> &t, std::vector<std::string> &v) {
    from_string(v[I], std::get<I>(t));
    add_each_to_tuple<I + 1, Args...>(t, v);
}

#endif