#ifndef SCOPE_HPP
#define SCOPE_HPP

#include "symbols.hpp"
#include "stmt.hpp"

#include <unordered_map>

class Scope {
    std::unordered_map<symbol*, Decl*> Declaration_table;

    public:
    bool insert(symbol* s, Decl* d) {
        return Declaration_table.insert({s, d}).second;
    }
};

#endif
