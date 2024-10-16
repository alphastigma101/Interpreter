#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <logging.h>
#include <token.h>
#include <filesystem>
/*
 * A Context Free Grammar consists of a head and a body, which describes what it can generate.
 * The body's purest form will be a list of symbols and these symbols are:
    * (Terminal):
        * letter from the grammar’s alphabet, which you can think of it as a literal value.  They are the endpoints in a sense as you only produce one symbol
        * In a sense, the symbol will represent a token of some sort 
    * (Nonterminal):
        * is a reference of another grammar rule, which allows you to pick any rules for it 
 * The rule is on the very left side of the ->. On the other side of it are: 
    * Quoted strings which represent the "terminal"
    * Lowercase letters that are  "nonterminal"
*/
#if ENABLE_TREE_BUILD
   Set<astTree<int, String, ExprVariant>> cTree;
#endif
namespace ContextFreeGrammar {
    //template<class Derived>
    class Expr /*: public Visitor<Derived>*/ {
        /** ------------------------------------------------------------------------------------------
         * @brief A representation of an abstraction classs which is also considered as a disoriented object
         *
         * @details By creating an abstraction class, and allowing a class to inherit it, you basically are allowing them to communicate with eachother
         *          Which allows it to not be associated with any type of behavior which usually methods/functions etc are what defined the behavior of an object
         * 
         * @details Maning that, it does nothing and the derived classes override the data member function (method).
         *          You make an abstract class, so the derived classes can access different types; 
         *          you basically access the types of the derived class through polymorphism.
         * ------------------------------------------------------------------------------------------
        */
        public:
            virtual ~Expr() noexcept = default;
            /** --------------------------------------------------------
             * @brief left represents the left binary node.
             * ---------------------------------------------------------
            */
            Expr* left = nullptr;
            /** --------------------------------------------------------
             * @brief right represents the left binary node.
             * ---------------------------------------------------------
            */
            Expr* right = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Token op;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* expression = nullptr;
            virtual String accept(Expr* visitor, bool tree = true) = 0;
            // TODO: Uncomment after you get your ast printer fully working
            //inline String accept(Expr* visitor) { return static_cast<Derived*>(this)->visit(*static_cast<Derived*>(this)); };
            virtual String visit(Expr* visitor, bool tree = true) = 0;
            //inline String visit(Expr* visitor) { return static_cast<Derived*>(this)->parenthesize(*static_cast<Derived*>(this)); };
        protected:
            int idx = 0;
    };
    class Binary: public Expr, public catcher<Binary> {
        /** --------------------------------------------------------------------
             * @brief A class that represents a binary abstraction syntax tree
             * 
             * @details The 'visiting design pattern' is crucial for the abstraction syntax tree to work as it will visit the nodes
             *          It relies on recrusion to visit every node in a graph or tree 
             *          ---------------(Example of Ast Tree)--------------
                                              *
                                             / \
                                            /   \
                                            -   ()
                                           /      \
                                          123      45.67
             *          Would print out this: (* (- 123) (group 45.67)) Note: Parathesis are always included 
         */
        public:
            friend class catcher<Binary>; // Use to output a message
            explicit Binary(Expr* left_, const Token& op_, Expr* right_);
            ~Binary() noexcept = default;
            String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override { 
                String result;
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr->left, expr->right);
                else {
                    // TODO: This needs to be stored in a if block, because >, >=, !=, etc can be compared other representations that are not integer or double
                    // Need to make a method that will store all this code and get called if expr->left or expr->right actually contain a integer or double
                    String leftResult = expr->left->accept(this, tree);
                    String rightResult = expr->right->accept(this, tree);
        
                    // Convert string results to numbers
                    double leftValue = std::stoi(leftResult);
                    double rightValue = std::stoi(rightResult);
                    switch (expr->op.getType()) {
                        case TokenType::PLUS:
                            result = std::to_string(leftValue + rightValue);
                            break;
                        case TokenType::MINUS:
                            result = std::to_string(leftValue - rightValue);
                            break;
                        case TokenType::STAR:
                            result = std::to_string(leftValue * rightValue);
                            break;
                        case TokenType::SLASH:
                            result = std::to_string(leftValue / rightValue);
                            break;
                        // Add other cases as needed
                        default:
                            throw new catcher<Binary>("Unknown operator");
                    }
                }
                return result;
            };
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Binary>::getMsg()) throw() { return msg;};
            String parenthesize(String name, Expr* left, Expr* right);
    };
    class Unary: public Expr, public catcher<Unary> {
        public:
            friend class catcher<Unary>; // Use to output a message
            explicit Unary(Expr* right_, const Token& op_);
            ~Unary() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Unary>::getMsg()) throw() { return msg;};
            String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override { 
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr->right); 
                else
                    return accept(this, tree);
            };
    };
    class Grouping: public Expr, public catcher<Grouping> {
        public:
            friend class catcher<Grouping>; // Use to output a message
            friend class Visitor<Grouping>;
            /** ----------------------------------------------------------------------------------------------------------
             * @brief constructor for creating the memory addresses that will later on be accessed by a vector 
             *
             * @param expression is an rvalue that will get destroyed once it leaves the scope
             *
             * 
             * @details expression is used to represent grouping class. 
             *          It points to the left and right binary node trees
            */
            explicit Grouping(Expr* expression);
            ~Grouping() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Grouping>::getMsg()) throw() { return msg;};
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true)
                    return parenthesize("group", expr->expression);
                else {
                    return expr->expression->accept(this, false);
                }
            };
            String parenthesize(String name, Expr* expr);
    };
    class Literal: public Expr, public catcher<Literal> {
        public:
            friend class catcher<Literal>; // Use to output a message
            friend class Visitor<Literal>;
            explicit Literal(const Token&& oP);
            ~Literal() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true) {
                    if (expr->op.getTypeStr() == "NULL" || expr->op.getTypeStr() == "NIL") return "null";
                    return " " + expr->op.getLiteral();
                }
                else
                    return expr->op.getLexeme();
            };
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Literal>::getMsg()) throw() { return msg;};
        protected:
            Literal() = default; 
    };
    class Variable: public Expr, public catcher<Variable> {
        public:
            friend class catcher<Variable>; // Use to output a message
            friend class Visitor<Variable>;
            Variable(const Token&& oP);
            ~Variable() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override { 
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr->left, expr->right); 
                else
                    return accept(this, tree);
            };
        protected:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Variable>::getMsg()) throw() { return msg;};
            String parenthesize(String name, Expr* left, Expr* right);
        private:
            //
    };
    class Statement: public Expr, public catcher<Statement> {
        public:
            friend class catcher<Statement>; // Use to output a message
            friend class Visitor<Statement>;
            Statement(Expr* initalizer, const Token&& oP);
            ~Statement() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true) {
                    if (expr->op.getTypeStr() == "NULL" || expr->op.getTypeStr() == "NIL") return "null";
                    return " " + expr->op.getLiteral();
                }
                else
                    return accept(this, tree);
            };
        protected:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Statement>::getMsg()) throw() { return msg;};
        private:
            //
    };
    class Methods: public Expr, public catcher<Methods> {
        public:
            friend class catcher<Methods>; // Use to output a message
            explicit Methods(Expr* meth, const Token& op_);
            ~Methods() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override {return visit(this, tree); };
        protected:
            Methods() = default;
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Methods>::getMsg()) throw() { return msg;};
            static String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr);
                else
                    return accept(this, tree);
            };
    };
    class Arguments: public Expr, public catcher<Arguments> {
        public:
            friend class catcher<Arguments>; // Use to output a message
            friend class Visitor<Arguments>;
            explicit Arguments(Expr* left, const Token& op_, Expr* right);
            ~Arguments() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        //protected:
            //Arguments() noexcept = default;
        private:
            inline static logTable<Map<String, Vector<String>>> logs_{};
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<Arguments>::getMsg()) throw() { return msg;};
            static String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr); 
                else
                    return accept(this, tree);
            };
           
        protected:
            Arguments() = default;
    };
    class EcoSystem: public Expr, public catcher<EcoSystem> {
        public:
            friend class catcher<EcoSystem>; // Use to output a message
            friend class Visitor<EcoSystem>;
            explicit EcoSystem(Expr* ecoSystem, const Token& op_);
            ~EcoSystem() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static logTable<Map<String, Vector<String>>> logs_;
            /** --------------------------------------
             * @brief A method that is overloaded by this class 
             * 
             * @details It is a method that is defined here which gets called by the definition method inside catcher 
             * 
             * @param msg A default argument that calls in a statically inlined method to output the error message
             * 
             * @return a string literal. Usually will be ub. Something that you do not want to get
             * 
             * ---------------------------------------
            */
            inline static const char* what(const char* msg = catcher<EcoSystem>::getMsg()) throw() { return msg;};
            static String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override { 
                if (tree == true) 
                    return parenthesize(expr->op.getLexeme(), expr);
                else
                    return accept(this, tree);
            };
        protected:
            EcoSystem() = default;
    };
};
using namespace ContextFreeGrammar;
#endif 
