#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <token.h>
//#include <filesystem>
#include <run_time_error.h>
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
namespace ContextFreeGrammar {
    //template<class Derived>
    class Expr {
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
            Visitor<Interpreter::interpreter>* interp;
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
             * @brief represents the callee node.
             * ---------------------------------------------------------
            */
            Expr* callee = nullptr;
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
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Expr* paren = nullptr;
            /** --------------------------------------------------------
             * @brief expression represents the left/right binary nodes.
             *        It does not represent its own nodes. Used with Grouping class
             * ---------------------------------------------------------
            */
            Vector<Any> arguments{};
            virtual Any accept(Expr* visitor, bool tree = true) = 0;
            // TODO: Uncomment after you get your ast printer fully working
            //inline String accept(Expr* visitor) { return static_cast<Derived*>(this)->visit(*static_cast<Derived*>(this)); };
            virtual String visit(Expr* visitor, bool tree = true) = 0;
            //inline String visit(Expr* visitor) { return static_cast<Derived*>(this)->parenthesize(*static_cast<Derived*>(this)); };
    };
    class Binary: public Expr, public catcher<Binary>, protected runtimeerror<Binary> {
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
            friend class runtimeerror<Binary>;
            explicit Binary(Expr* left_, const Token& op_, Expr* right_);
            ~Binary() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline String visit(Expr* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), expr->left, expr->right); };
        protected:
            explicit Binary() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Binary>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Binary>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Binary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Binary> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* left, Expr* right);     
    };
    class Logical: public Expr, public catcher<Logical>, protected runtimeerror<Logical> {
        public:
            friend class catcher<Logical>; // Use to output a message
            friend class runtimeerror<Logical>;
            explicit Logical(Expr* left_, const Token& op_, Expr* right_);
            ~Logical() noexcept = default;
            Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline String visit(Expr* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), expr->left, expr->right); };
        protected:
            explicit Logical() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Logical>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Logical>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Logical>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Binary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Binary> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* left, Expr* right);     
    };
    class Unary: public Expr, public catcher<Unary>, public logging<Unary>, protected runtimeerror<Unary> {
        public:
            friend class catcher<Unary>; // Use to output a message
            friend class runtimeerror<Unary>;
            explicit Unary(Expr* right_, const Token& op_);
            ~Unary() noexcept = default;
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
        protected:
            explicit Unary() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Unary>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Unary>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Unary>(
                                String(String("From Unary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Unary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Unary> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), expr->right); };
    };
    class Grouping: public Expr, public catcher<Grouping> {
        public:
            friend class catcher<Grouping>; // Use to output a message
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
            inline Any accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static Map<String, Vector<String>> logs_{};
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
                if (tree == true) return parenthesize("group", expr->expression);
                else return std::any_cast<String>(expr->expression->accept(this, false));
            };
            String parenthesize(String name, Expr* expr);
    };
    class Literal: public Expr, public catcher<Literal> {
        public:
            friend class catcher<Literal>; // Use to output a message
            explicit Literal(const Token&& oP);
            ~Literal() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override {
                if (tree == true) {
                    if (expr->op.getTypeStr() == "NULL" || expr->op.getTypeStr() == "NIL") return "null";
                    return " " + expr->op.getLiteral();
                }
                else
                    return expr->op.getLexeme();
            };
        private:
            inline static Map<String, Vector<String>> logs_{};
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
    class Assign: public Expr, public catcher<Assign>, protected runtimeerror<Assign> {
        public:
            friend class catcher<Assign>; // Use to output a message
            friend class runtimeerror<Assign>;
            explicit Assign(const Token &op, Expr* expr);
            ~Assign() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline String visit(Expr* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), expr); };
        protected:
            explicit Assign() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Assign>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Assign>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Assign>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Assign>(
                                String(String("From Assign what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Assign>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Assign> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* left);    
    };
    class Variable: public Expr, public catcher<Variable> {
        public:
            friend class catcher<Variable>; // Use to output a message
            friend class Visitor<Variable>;
            Variable(const Token&& oP);
            ~Variable() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline String visit(Expr* expr, bool tree = true) override { 
                if (expr->op.getTypeStr() == "NULL" || expr->op.getTypeStr() == "NIL") return "null";
                return " " + expr->op.getTypeStr() + "(" + expr->op.getLexeme() + ")"; 
            };
        protected:
            explicit Variable() = default;
            inline static Map<String, Vector<String>> logs_{};
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
    };
    class Call: public Expr, public catcher<Call>, protected runtimeerror<Call> {
        public:
            friend class catcher<Call>; // Use to output a message
            friend class runtimeerror<Call>;
            explicit Call(Expr* callee, Token& paren, Vector<Expr*> arguments);
            ~Call() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Expr* visitor, bool tree = true);
            inline String visit(Expr* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), expr->left, expr->right); };
        protected:
            explicit Call() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Call>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Call>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Call>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Call>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Functions> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* left, Expr* right);
    };
    //template<class Derived>
    class Statement {
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
            Visitor<Interpreter::interpreter>* interp;
            virtual ~Statement() noexcept = default;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* initializer = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* condition = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Token op;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Vector<ContextFreeGrammar::Statement*> statements{};
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Statement* thenBranch = nullptr;
            /** --------------------------------------------------------
             * @brief A token class instance wrapped in a unique_ptr. 
             *        It is included with the node that was created
             * ---------------------------------------------------------
            */
            Statement* elseBranch = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Statement* body = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Expr* value = nullptr;
            /** --------------------------------------------------------
             * @brief initializer represents the value.
             * ---------------------------------------------------------
            */
            Vector<Token> params{};
            virtual Any accept(Statement* visitor, bool tree = true) = 0;
            // TODO: Uncomment after you get your ast printer fully working
            //inline String accept(Expr* visitor) { return static_cast<Derived*>(this)->visit(*static_cast<Derived*>(this)); };
            virtual String visit(Statement* visitor, bool tree = true) = 0;
            //inline String visit(Expr* visitor) { return static_cast<Derived*>(this)->parenthesize(*static_cast<Derived*>(this)); };
    };
    class Print: public Statement, public catcher<Print> {
        public:
            friend class catcher<Print>; // Use to output a message
            friend class Visitor<Print>;
            Print(Expr* initalizer);
            ~Print() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize("Print", stmt); };
            String parenthesize(String name, Statement* stmt);
        protected:
            Print() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Print>::getMsg()) throw() { return msg;};
    };
    class Return: public Statement, public catcher<Return> {
        public:
            friend class catcher<Return>; // Use to output a message
            Return(const Token& keyword, Expr* value);
            ~Return() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize("Return", stmt); };
            String parenthesize(String name, Statement* left);
        protected:
            explicit Return() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Return>::getMsg()) throw() { return msg;};
    };
    class Var: public Statement, public catcher<Var> {
        public:
            friend class catcher<Var>; // Use to output a message
            Var(const Token& op, Expr* initalizer);
            ~Var() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize("Var", stmt); };
            String parenthesize(String name, Statement* left);
        protected:
            explicit Var() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Var>::getMsg()) throw() { return msg;};
    };
    class While: public Statement, public catcher<While> {
        public:
            friend class catcher<While>; // Use to output a message
            While(Expr* condition, Statement* body);
            ~While() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize("While", stmt); };
            String parenthesize(String name, Statement* left);
        protected:
            explicit While() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<While>::getMsg()) throw() { return msg;};
    };
    class Expression: public Statement, public catcher<Expression> {
        public:
            friend class catcher<Expression>; // Use to output a message
            Expression(Expr* initalizer);
            ~Expression() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize(stmt->op.getLexeme(), stmt); };
            String parenthesize(String name, Statement* stmt);
        protected:
            explicit Expression() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Expression>::getMsg()) throw() { return msg;};
    };
    class Block: public Statement, public catcher<Block>, protected runtimeerror<Block> {
        public:
            friend class catcher<Block>; // Use to output a message
            friend class runtimeerror<Block>;
            explicit Block(Vector<ContextFreeGrammar::Statement*>&& statements);
            ~Block() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override {  return parenthesize(std::move(stmt->statements)); };
        protected:
            explicit Block() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Block>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Block>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Block>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Block>(
                                String(String("From Block what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Block>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Block> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(Vector<ContextFreeGrammar::Statement*>&& expr);  
    };
    class If: public Statement, public catcher<Print> {
        public:
            friend class catcher<If>; // Use to output a message
            explicit If(Expr* cond, Statement* thenbranch, Statement* elsebranch);
            ~If() noexcept = default;
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            inline String visit(Statement* stmt, bool tree = true) override { return parenthesize("If", stmt); };
            String parenthesize(String name, Statement* stmt);
        protected:
            If() = default;
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<If>::getMsg()) throw() { return msg;};
    };
    class Functions: public Statement, public catcher<Functions>, protected runtimeerror<Functions> {
        public:
            friend class catcher<Functions>; // Use to output a message
            friend class runtimeerror<Functions>;
            explicit Functions(Token& name, Vector<Token> params, Vector<Statement*>& body);
            ~Functions() noexcept = default;
            inline Any accept(Statement* visitor, bool tree = true) override { return acceptHelper(this, tree); };
            Any acceptHelper(Statement* visitor, bool tree = true);
            inline String visit(Statement* expr, bool tree = true) override { return parenthesize(expr->op.getLexeme(), nullptr, nullptr); };
        protected:
            explicit Functions() = default;
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Functions>::type));};
            inline static Map<String, Vector<String>> logs_{};
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
            inline static const char* what(const char* msg = catcher<Functions>::getMsg()) throw() { return msg;};
            /** --------------------------------------
             * @brief A method that is overloaded here from this class 
             * 
             * @details The runtimeerror class will call this method and it will output something to the temrinal
             * 
             * @param msg A default argument that calls in a statically inlined method to output error message
             * @param type A temp object that will eventually be destroyed once it leaves the scope. 
             *             It also calls in a statically inlined method to get the TokenType
             * 
             * @return a concated string back to the caller method
             * 
             * ---------------------------------------
            */
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Functions>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        /*auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }*/
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Functions>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Functions> logs(e.what());
                    logs_ = logs.getLogs();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Statement* left, Statement* right);
    };
    class Methods: public Expr, public catcher<Methods> {
        public:
            friend class catcher<Methods>; // Use to output a message
            explicit Methods(Expr* meth, const Token& op_);
            ~Methods() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override {return visit(this, tree); };
        protected:
            Methods() = default;
        private:
            inline static Map<String, Vector<String>> logs_{};
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
                return "\0";
            };
    };
    class EcoSystem: public Expr, public catcher<EcoSystem> {
        public:
            friend class catcher<EcoSystem>; // Use to output a message
            friend class Visitor<EcoSystem>;
            explicit EcoSystem(Expr* ecoSystem, const Token& op_);
            ~EcoSystem() noexcept = default;
            inline Any accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static Map<String, Vector<String>> logs_{};
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
                return "\0";
            };
        protected:
            EcoSystem() = default;
    };
};
using namespace ContextFreeGrammar;
#endif 
