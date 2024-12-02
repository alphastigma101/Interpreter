#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <definitions.h>
// These interfaces should be used for when the Derived class does not directly implement the methods that they offer
// Note that some interfaces do not use the -> and define the methods
template<class Type>
class Conv {
    // An abstract class is used to convert types of a class object into a string 
    public:
        ~Conv() noexcept = default;
        template<typename Sig>
        inline Sig toString() { return static_cast<Type*>(this)->toString();};
        inline Any toNumeric(Any& value) { return static_cast<Type*>(this)->toNumeric(value);};
        inline Any toOther(Any& lhs, Any& rhs) { return static_cast<Type*>(this)->toOther(lhs, rhs); };
};
template<class Type>
class Check {
    // An abstract class that checks the instance of an object
    public:
        ~Check() noexcept = default;
        template<typename T>
        inline bool isNumeric(const Any value) { return static_cast<Type*>(this)->isNumeric(value);};
        inline bool isString(const Any value) {return static_cast<Type*>(this)->isString(value);};
        template<typename T>
        inline bool isOther(const Any value) { return static_cast<Type*>(this)->isOther(value);};
        template<typename T>
        inline bool instanceof(const Any& object) { return static_cast<Type*>(this)->template instanceof<T>(object);};
};

template <typename Derived>
class Visitor {
    public:
        // Visit Binary Expression
        inline Any visitBinaryExpr(ContextFreeGrammar::Binary* expr) { return static_cast<Derived*>(this)->visitBinaryExpr(expr); };
        // Visit Block Statement
        inline void visitBlockStmt(ContextFreeGrammar::Block* stmt) { return static_cast<Derived*>(this)->visitBlockStmt(stmt); };
        inline Any visitExpressionStmt(ContextFreeGrammar::Expression* stmt) { return static_cast<Derived*>(this)->visitExpressionStmt(stmt); };
        inline Any visitPrintStmt(ContextFreeGrammar::Print* stmt) { return static_cast<Derived*>(this)->visitPrintStmt(stmt); };
        inline Any visitVariableExpr(ContextFreeGrammar::Variable* expr) { return static_cast<Derived*>(this)->visitVariableExpr(expr); };
        inline void visitVarStmt(ContextFreeGrammar::Var* stmt) { return static_cast<Derived*>(this)->visitVarStmt(stmt); };
        inline Any visitAssignExpr(ContextFreeGrammar::Assign* expr) { return static_cast<Derived*>(this)->visitAssignExpr(expr); };
};
#endif 
