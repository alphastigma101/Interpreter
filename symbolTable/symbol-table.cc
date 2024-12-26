#include <declarations.h>
#include <symbol-table.h>
#include <run_time_error.h>
void* Symbol::Table::table = new Map<String, Symbol::Statements>();

Symbol::Statements Symbol::Table::get(const char *id) {
    if (table != nullptr)  { 
        auto& map = *reinterpret_cast<Map<String, Symbol::Statements>*>(table);
        for (auto it = map.begin(); it != map.end(); it++) {
            if (it->first == String(id)) return it->second; // return the whole statement struct 
        }
    }
    else 
        throw runtimeerror<Symbol::Table>();
    throw ;
}

void Symbol::Table::insert(const char *id, Symbol::Statements symbols) {
    auto& map = *reinterpret_cast<Map<String, Symbol::Statements>*>(table);
    map.insert({String(id), symbols});
    table = new Map<String, Symbol::Statements>(std::move(map));
    return;
}


void Symbol::Table::update(const char* id, const Symbol::Statements symbol) {
    if (table != nullptr)  { 
        auto& map = *reinterpret_cast<Map<String, Symbol::Statements>*>(table);
        for (auto it = map.begin(); it != map.end(); it++) { 
            if (it->first == String(id)) {
                map.insert_or_assign(String(id), symbol);
                return;
            } 
        }
    }
    else 
        throw runtimeerror<Symbol::Table>();
    throw "Error" ;
}
