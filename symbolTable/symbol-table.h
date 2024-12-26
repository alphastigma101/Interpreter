#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
#include <map>
#include <string>
namespace Symbol {
    struct Statements {
        ~Statements() noexcept = default;
        struct Parameters {
            std::multimap<std::string, std::string> p_id;
        };
        struct Functions {
            // No need for vectors here 
            // Function name which is f_id will be used as a look up key
            std::string f_type;
            std::string f_id;
        };
        struct Logic {
            // Have no idea how to deal with this yet..
            // It probably needs variables the operands
            const char* l_type;
            const char* l_id;
        };
        struct Variable {
            std::map<const char*, Symbol::Statements> v_id;
        };
        Parameters params;
        Functions functions;
        Logic logic;
        Variable variable;
    };
    class Table {
        public:
            explicit Table() noexcept = default;
            ~Table() noexcept = default;
            static Statements get(const char* id);
            static void insert(const char* id, Symbol::Statements symbols);
            inline static Statements* newSymbols() { return new Symbol::Statements(); };
            static void update(const char* id, const Symbol::Statements symbol); 
        private:
            static void* table;

    };

};

#endif