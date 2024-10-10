#ifndef _ABSTRACTION_TREE_SYNTAX_H_
#define _ABSTRACTION_TREE_SYNTAX_H_
#include <context_free_grammar.h>
#include <threading.h>
#if ENABLE_TESTING
    String file_name, user_choice;
    int settings;
#endif
namespace AbstractionTreeSyntax {
    template<class Type>
    class generateAst: public catcher<Type>, public runtimeerror<Type> {
        /** ---------------------------------------------------------------------
            * @brief A disorienated class object isolating its behavior. It will write data to a file by getting the literals from each expression it visits. 
            * ---------------------------------------------------------------------
        */
        public:
            friend class catcher<Type>;
            friend class runtimeerror<Type>;
            ~generateAst<Type>() noexcept = default;
            inline void streamOutAst(String res) { return static_cast<Type*>(this)->streamOutAst(res); }; // could change the parameter so it uses Type* and use this
            inline void formatAst(String res) { return static_cast<Type*>(this)->formatAst(res);};
            inline String buildTree() { return static_cast<Type*>(this)->buildTree();};
            inline void writeFile(std::string& ext) { return static_cast<Type*>(this)->writeFile(ext);};
            inline void tree_(const generateAst<Type>& gA) { return static_cast<Type*>(this)->tree_(gA);};
            inline static const char* what(const char* msg = catcher<Type>::getMsg()) throw() { return msg;};
            inline static const char* what(TokenType&& type = runtimeerror<Type>::getType(), const char* msg = runtimeerror<Type>::getMsg()) throw() { return msg;};          
        protected:
            String outputDir_;
            static Unique<Atomic<const char*>> accessCodeStr;
            static String codeStr;
            String compactedTreeStr;
            inline static logTable<Map<String, Vector<String>>> logs_;
            Set<astTree<int, String, ExprVariant>> compactedTreeNodes;
            static String ext;
            Visitor<Binary> visitBinary;
            Visitor<Unary> visitUnary;
            Visitor<Grouping> visitGrouping;
            Visitor<Literal> visitLiteral;
            Visitor<Methods> visitMethods;
            Visitor<Arguments> visitArguments;
            Visitor<EcoSystem> visitEcoSystem;
            inline static std::string nameOfFile = std::move(file_name);
           
    };
    class ast: protected generateAst<ast> {
        /** ---------------------------------------------------------------------
            * @brief This class creates an abstraction syntax tree by storing each expression instance inside a vector. 
            *        for the intepreter class to evaulaute each instance using the visitor technique
            * ---------------------------------------------------------------------
        */
        public:
            friend class generateAst<ast>;
            ast() noexcept;
            ~ast() noexcept = default; // TODO: This is virtual for some reason, and it needs to be not virtual
            inline static Table getTable() { return table; };
            inline static Unique<Atomic<const char*>> getCode() { return std::move(accessCodeStr); };
        protected:
            String buildTree();
            void streamOutAst(String res);
            void formatAst(String res);
        private:
            static void tree_(const generateAst<ast>& gA);
            static void writeFile(std::string& ext);
            static Table table;
            generateAst<ast> gA;
    };
    class analyzeSemantics: public catcher<analyzeSemantics>, public ThreadTracker<analyzeSemantics> {
        /** ------------------------------------------------------------------
            * @brief A class that inherits a crtp threading class that has mutex embeded into it
            *
            * @details It makes a copy of the ast class which it will access a certain object using atomic, and builds a map.
            *          This map will be used by the intermediateRepresentation class which strictly only be used with the compiler
        */
        public: 
            friend class catcher<analyzeSemantics>;
            analyzeSemantics(Shared<ast> Ast_);
            ~analyzeSemantics() noexcept = default;
            inline static Map<int, String> getAnalyzedCodeMap() { return std::move(analyzeCode); };
        protected:
            inline static const char* what(const char* msg = catcher<analyzeSemantics>::getMsg()) throw() { return msg; };
            /** ----------------------------------------------------------------
                * @brief A method that creates a thread for the class analyzeSemantics.
                * 
                * @details Spawns in the thread. Main thread will allow this thread to access it.
                *          It uses a getter method to get an atomic object wrapped in a unique_ptr and loads gets the value
                * @details The average/worse case for this method would be O(n)
                * --------------------------------------------------------------
            */
            inline static void run(Shared<ast> Ast) {
                // Want this: memory_order_release or memory_order_relaxed
                if (auto thread_id = strToId.find("treeThread"); thread_id != strToId.end()) {
                    int node = 0;
                    // Expression that indexes at the specific thread 
                    // Once removed this expression should break out
                    std::thread::id default_id; // default constructor id 
                    while (thread_id->second != default_id) {
                        //Symbol resolution: Linking identifiers to their declarations
                        //Type checking: Verifying and inferring types of expressions
                        //Scope analysis: Ensuring variables are used in the correct scope
                        //Checking language-specific semantic rules: e.g., ensuring break is only used inside loops

                        // Might have to check and see if it is not null
                        // Or make the this thread wait until the atomic value is a new one
                        //String stringLiteral = Ast.get()->getCode()->load(std::memory_order_release);
                        //analyzeCode[node] = stringLiteral;
                        //node++;
                    }
                }
            };
        private:
            inline static Map<int, String> analyzeCode;
    };
    class intermediateRepresentation: public catcher<intermediateRepresentation>, public ThreadTracker<intermediateRepresentation> {
        /** ------------------------------------------------------------------
            * @brief A class that takes analyzeSemantics semantic map and converts it into a undirected graph.
            *
            * @details Using a undirected graph will be very benefitical for supporting multitple modern programming languages
            *
            * -------------------------------------------------------------------
        */
        public:
            friend class catcher<intermediateRepresentation>;
            explicit intermediateRepresentation(Weak<analyzeSemantics> as_);
            ~intermediateRepresentation() noexcept = default;
            static void generate();
        protected:
            inline static const char* what(const char* msg = catcher<intermediateRepresentation>::getMsg()) throw() { return msg; };
            inline static void run(Weak<analyzeSemantics> as_weak) { 
                if (auto thread_id = strToId.find("semanticThread"); thread_id != strToId.end()) {
                    int node = 0;
                    // Expression that indexes at the specific thread 
                    // Once removed this expression should break out
                    std::thread::id default_id;
                    while (thread_id->second != default_id) {
                        if (auto aSLocked = as_weak.lock()) {
                            // Might have to check and see if it is not null
                            //String stringLiteral = Ast.get()->getCode()->load(std::memory_order_release);
                            //analyzeCode[node] = stringLiteral;
                            node++;
                        } else {
                            // If the analyzeSemantic thread dies before this is done 
                            // Move the map over and continue creating the graph
                        }
                    }
                }
            };
        private:
            static void adjacent(auto& G, int x, int y);
            static void neighbors(auto& G, int x);
            static void add_vertex(auto& G, int x);
            static void remove_vertex(auto& G, int x);
            static void add_edge(auto& G, int x, int y, int z);
            static void remove_edge(auto& G, int x, int y);
            static void get_vertex_value(auto& G, int x);
            static void set_vertex_value(auto& G, int x, int v);
    };
};
using namespace AbstractionTreeSyntax;
#endif
