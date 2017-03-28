#ifndef SYMBOLS_HPP
#define SYMBOLS_HPP

#include <string>
#include <unordered_map>

class Symbol_table {
    std::unordered_map<std::string, void*> symbols;

    public:
    const std::string* ins(const std::string& s) {
        auto res = symbols.insert({s, nullptr});
        return &res.first->first;
    }

    const std::string* find(const std::string& s) {
        auto i = symbols.find(s);
        return &i->first;
    }
};

#endif // symbols
