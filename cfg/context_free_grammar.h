#ifndef _CONTEXT_FREE_GRAMMAR_H_
#define _CONTEXT_FREE_GRAMMAR_H_
#include <logging.h>
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
    template<class Derived>
    class Evaluation: public Conv<Derived>, public Check<Derived> {
        // An abstract class that is used for converting strings into targeted types during interpretation
        // This class offers methods that should not be directly implemented into the Derived class, but are still needed
        public:
            ~Evaluation() = default;
            inline Any compute(Any& a, Any& b, auto& expr) { return static_cast<Derived*>(this)->compute(a, b, expr);};
    };
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
    class Binary: public Expr, public catcher<Binary>, public Evaluation<Binary>, protected runtimeerror<Binary> {
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
            friend class Visitor<Binary>;
            friend class Check<Binary>;
            friend class Conv<Binary>;
            friend class Evaluation<Binary>;
            explicit Binary(Expr* left_, const Token& op_, Expr* right_);
            ~Binary() noexcept = default;
            String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override { 
                String result;
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr->left, expr->right);
                else {
                    try {
                        // Check and see if leftResult and rightResult are binary
                        Any leftResult = std::make_any<String>(expr->left->accept(this, tree));
                        Any rightResult = std::make_any<String>(expr->right->accept(this, tree));
                        Any res = eval.compute(leftResult, rightResult, expr);
                        if (!res.has_value()) 
                            throw new runtimeerror<Binary>(expr->op.getType(), String("Failed to compute this object:" + expr->op.getLexeme()).c_str());
                        else
                            result = std::any_cast<String>(res);
                    }
                    catch(...) {
                        try {
                            Any leftResult = std::make_any<String>(expr->left->accept(this, tree));
                            Any rightResult = std::make_any<String>(expr->right->accept(this, tree));
                            return std::any_cast<String>(eval.toOther(leftResult, rightResult));
                        }
                        catch(...) {
                            std::cout << "Invalid Type!" << std::endl;
                        }
                    }
                }
                return result;
            };
        private:
            inline static Evaluation<Binary> eval{};
            static Any compute(Any& a, Any& b, auto& expr);
            /** --------------------------------------------
             * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
             * 
             * @param value Is an any container that will always have a string value inside of it
             * 
             * @cond If lhs and rhs are either a list or map, it will be stored in one any container.
             * 
             * @details ...
             * 
             * @return Returns a complex any container that will hold two values 
             * 
            */
            template<typename T>
            inline static bool isOther(const Any value) {
                return false;
            };
            template<class T>
            static bool instanceof(const Any& object);
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
            template<class T>
            static bool isNumeric(const Any value);
            static Any toNumeric(Any& value);
            static Any toOther(Any& lhs, Any& rhs);
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Binary>::type));};
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
                        auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Binary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Binary> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* left, Expr* right);
       
           
    };
    class Unary: public Expr, public catcher<Unary>, public logging<Unary>, public Evaluation<Unary>, protected runtimeerror<Unary> {
        public:
            friend class catcher<Unary>; // Use to output a message
            friend class runtimeerror<Unary>;
            friend class Visitor<Unary>;
            friend class Check<Unary>;
            friend class Conv<Unary>;
            friend class Evaluation<Unary>;
            explicit Unary(Expr* right_, const Token& op_);
            ~Unary() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static Evaluation<Unary> eval{};
            static Any compute(Any& a, Any& b, auto& expr);
            /** --------------------------------------------
             * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
             * 
             * @param value Is an any container that will always have a string value inside of it
             * 
             * @cond If lhs and rhs are either a list or map, it will be stored in one any container.
             * 
             * @details ...
             * 
             * @return Returns a complex any container that will hold two values 
             * 
            */
            template<typename T>
            inline static bool isOther(const Any value) {
                // TODO: This needs to be implemented when creating the environment later on
                return false;
            };
            template<typename T>
            static bool instanceof(const Any& object);
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
            template<typename T>
            static bool isNumeric(const Any value);
            static Any toNumeric(Any& value);
            static Any toOther(Any& lhs, Any& rhs);
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Unary>::type));};
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
                        auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Unary>(
                                String(String("From Unary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Unary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Unary> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override {
                String result; 
                if (tree == true)
                    return parenthesize(expr->op.getLexeme(), expr->right); 
                else {
                    try {
                        Any right = std::make_any<String>(expr->right->accept(this, tree));
                        auto temp = std::make_any<String>("\0");
                        Any res = eval.compute(temp, right, expr);
                        if (!res.has_value()) 
                            throw new runtimeerror<Unary>(expr->op.getType(), String("Failed to compute this object:" + expr->op.getLexeme()).c_str());
                        else
                            result = std::any_cast<String>(res);
                    }
                    catch(...) {
                        std::cout << "Invalid Type!" << std::endl;
                    }
                }
                return result;
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
                if (tree == true) return parenthesize("group", expr->expression);
                else  return expr->expression->accept(this, false);
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
     class Identifier: public Expr, public catcher<Identifier>, public logging<Identifier>, public Evaluation<Identifier>, protected runtimeerror<Identifier> {
        public:
            friend class catcher<Identifier>; // Use to output a message
            friend class runtimeerror<Identifier>;
            friend class Visitor<Identifier>;
            friend class Check<Identifier>;
            friend class Conv<Identifier>;
            friend class Evaluation<Identifier>;
            explicit Identifier(Expr* right_, const Token& op_);
            ~Identifier() noexcept = default;
            inline String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
        private:
            inline static Evaluation<Identifier> eval{};
            //static Any compute(Any& a, Any& b, auto& expr);
            /** --------------------------------------------
             * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
             * 
             * @param value Is an any container that will always have a string value inside of it
             * 
             * @cond If lhs and rhs are either a list or map, it will be stored in one any container.
             * 
             * @details ...
             * 
             * @return Returns a complex any container that will hold two values 
             * 
            */
            template<typename T>
            inline static bool isOther(const Any value) {
                // TODO: This needs to be implemented when creating the environment later on
                return false;
            };
            /*template<typename T>
            static bool instanceof(const Any& object);
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
            template<typename T>
            static bool isNumeric(const Any value);
            static Any toNumeric(Any& value);
            static Any toOther(Any& lhs, Any& rhs);*/
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Identifier>::type));};
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
            inline static const char* what(const TokenType& type = getType(), const char* msg = runtimeerror<Identifier>::getMsg()) throw() {
                static String output;
                try {
                    if (auto search = tokenTypeStrings.find(type); search != tokenTypeStrings.end()) {
                        output = search->second.c_str() + String(msg);
                        return output.c_str();
                    }
                    else {
                        auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Unary>(
                                String(String("From Unary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Unary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Unary> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
                return output.c_str();
            };
            String parenthesize(String name, Expr* expr);
            inline String visit(Expr* expr, bool tree = true) override {
                String result; 
                if (tree == true)
                    //return parenthesize(expr->op.getLexeme(), expr->right); 
                    return "\0";
                else {
                    try {
                        /*Any right = std::make_any<String>(expr->right->accept(this, tree));
                        auto temp = std::make_any<String>("\0");
                        Any res = eval.compute(temp, right, expr);
                        if (!res.has_value()) 
                            throw new runtimeerror<Unary>(expr->op.getType(), String("Failed to compute this object:" + expr->op.getLexeme()).c_str());
                        else
                            result = std::any_cast<String>(res);*/
                    }
                    catch(...) {
                        std::cout << "Invalid Type!" << std::endl;
                    }
                }
                return result;
            };
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
     class Functions: public Expr, public catcher<Functions>, public Evaluation<Functions>, protected runtimeerror<Functions> {
        public:
            friend class catcher<Functions>; // Use to output a message
            friend class runtimeerror<Functions>;
            friend class Visitor<Functions>;
            friend class Check<Functions>;
            friend class Conv<Functions>;
            friend class Evaluation<Functions>;
            explicit Functions(Expr* left_, const Token& op_, Expr* right_);
            ~Functions() noexcept = default;
            String accept(Expr* visitor, bool tree = true) override { return visit(this, tree); };
            inline String visit(Expr* expr, bool tree = true) override { 
                String result;
                if (tree == true)
                    //return parenthesize(expr->op.getLexeme(), expr->left, expr->right);
                    return "\0";
                else {
                    try {
                        // Check and see if leftResult and rightResult are binary
                        //Any leftResult = std::make_any<String>(expr->left->accept(this, tree));
                        //Any rightResult = std::make_any<String>(expr->right->accept(this, tree));
                        //Any res = eval.compute(leftResult, rightResult, expr);
                        //if (!res.has_value()) 
                            //throw new runtimeerror<Binary>(expr->op.getType(), String("Failed to compute this object:" + expr->op.getLexeme()).c_str());
                        //else
                            //result = std::any_cast<String>(res);
                    }
                    catch(...) {
                        try {
                            //Any leftResult = std::make_any<String>(expr->left->accept(this, tree));
                            //Any rightResult = std::make_any<String>(expr->right->accept(this, tree));
                            //return std::any_cast<String>(eval.toOther(leftResult, rightResult));
                        }
                        catch(...) {
                            std::cout << "Invalid Type!" << std::endl;
                        }
                    }
                }
                return result;
            };
        private:
            inline static Evaluation<Functions> eval{};
            //static Any compute(Any& a, Any& b, auto& expr);
            /** --------------------------------------------
             * @brief A simple but yet, complex method that accesses Tatical Nuke's struct for conversion
             * 
             * @param value Is an any container that will always have a string value inside of it
             * 
             * @cond If lhs and rhs are either a list or map, it will be stored in one any container.
             * 
             * @details ...
             * 
             * @return Returns a complex any container that will hold two values 
             * 
            */
            template<typename T>
            inline static bool isOther(const Any value) {
                return false;
            };
            /*template<class T>
            static bool instanceof(const Any& object);
            inline static bool isString(const Any value) { return value.type() == typeid(String);};
            template<class T>
            static bool isNumeric(const Any value);
            static Any toNumeric(Any& value);
            static Any toOther(Any& lhs, Any& rhs);*/
        private:
            inline static const TokenType& getType() { return *static_cast<const TokenType*>(std::move(runtimeerror<Functions>::type));};
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
                        auto& [intVal, pairVal] = cTree.at(currentEnvEle);
                        if (std::holds_alternative<Expr*>(pairVal.second)) {
                            auto& conv = std::get<Expr*>(pairVal.second);
                            throw new catcher<Binary>(
                                String(String("From Binary what() method, TokenType is not supported!")+ String("\n\t") + 
                                String("Could not find targeted type in map: ")  +   String("\n\t") + String(conv->op.getLexeme())).c_str()
                            );
                        }
                        // TODO: Eventually, an if statement will be going down here to support a smart pointer of some sort
                    }
                }
                catch(catcher<Binary>& e) {
                    std::cout << "Logs have been updated!" << std::endl;
                    logging<Binary> logs(logs_, e.what());
                    logs.update();
                    logs.rotate();
                }
                return output.c_str();
            };
            //String parenthesize(String name, Expr* left, Expr* right);
       
           
    };
    class EcoSystem: public Expr, public catcher<EcoSystem> {
        public:
            friend class catcher<EcoSystem>; // Use to output a message
            friend class Visitor<EcoSystem>;
            explicit EcoSystem(Expr* ecoSystem, const Token& op_);
            ~EcoSystem() noexcept = default;
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
