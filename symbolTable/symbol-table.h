#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_
namespace Symbol {
    class Table {
        public:
            explicit Table() noexcept = default;
            ~Table() noexcept = default;
            static Table get(const char* id);
            static void insert(const char* id, Table symbols);
            static void update(const char* id);
            inline static char* type = nullptr;
            inline static char* value = nullptr; 
        private:
            static void* table;

    };

};

#endif