#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst {
        /** ---------------------------------------------------------------------
            * @brief A disorienated class object isolating its behavior. It will write data to a file by getting the literals from each expression it visits. 
            * ---------------------------------------------------------------------
        */
        public:
            ~generateAst() noexcept = default;
            inline void streamOutAst(String res) { return static_cast<Type*>(this)->streamOutAst(res); };
            inline void formatAst(String res) { return static_cast<Type*>(this)->formatAst(res);};
            inline String buildTree(Vector<ContextFreeGrammar::Statement*> stmt) { return static_cast<Type*>(this)->buildTree(stmt);};     
        protected:
            String outputDir_;
            static String ext;
    };
    class ast: protected generateAst<ast> {
        /** ---------------------------------------------------------------------
            * @brief This class creates an abstraction syntax tree by storing each expression instance inside a vector. 
            *        for the intepreter class to evaulaute each instance using the visitor technique
            * ---------------------------------------------------------------------
        */
        public:
            friend class generateAst<ast>;
            ast(Vector<ContextFreeGrammar::Statement*> stmt) noexcept;
            ~ast() noexcept = default;
        protected:
            String buildTree(Vector<ContextFreeGrammar::Statement*> stmt);
            static void streamOutAst(String res);
            inline static void formatAst(String res) { return streamOutAst(res); };
        private:
            generateAst<ast> gA;
    };
};
#endif
