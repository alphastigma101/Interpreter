#include <declarations.h>
#include <symbol-table.h>
#include <run_time_error.h>
void* Symbol::Table::table = new Map<String, Symbol::Table>();

Symbol::Table Symbol::Table::get(const char *id) {
    if (table != nullptr)  { 
        auto& map = *reinterpret_cast<Map<String, Symbol::Table>*>(table);
        for (auto it = map.begin(); it != map.end(); it++) {
            if (it->first == String(id)) return it->second; // return the whole statement struct 
        }
    }
    else 
        throw runtimeerror<Symbol::Table>();
    throw ;
}
/** -------------------------------
 * @brief insert the class called Tables into a multi-map 
 * 
 * @param id is a const char* type that should hold the identifier 
 * @param symbols the Table class instance that holds the properties of that id
 * 
 *
 * -------------------------------- 
*/
void Symbol::Table::insert(const char *id, Symbol::Table symbols) {
    auto& map = *reinterpret_cast<Map<String, Symbol::Table>*>(table);
    map.insert({String(id), symbols});
    table = new Map<String, Symbol::Table>(std::move(map));
    return;
}


void Symbol::Table::update(const char* id) {
    if (table != nullptr)  { 
        auto& map = *reinterpret_cast<Map<String, Symbol::Table>*>(table);
        for (auto it = map.begin(); it != map.end(); it++) { 
            if (it->first == String(id)) {
                //map.insert_or_assign(String(id), symbol);
                return;
            } 
        }
    }
    else 
        throw runtimeerror<Symbol::Table>();
}
