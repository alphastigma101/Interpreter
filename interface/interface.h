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
        template<typename Sig>
        inline Sig toNumeric(Sig& value) { return static_cast<Type*>(this)->toNumeric(value);};
        template<typename Sig>
        inline Sig toOther(Sig& lhs, Sig& rhs) { return static_cast<Type*>(this)->toOther(lhs, rhs); };
};
template<class Type>
class Check {
    // An abstract class that checks the instance of an object
    public:
        ~Check() noexcept = default;
        template<typename T>
        inline T isNumeric(const T value) { return static_cast<Type*>(this)->isNumeric(value);};
        template<typename T>
        inline T isString(const T value) {return static_cast<Type*>(this)->isString(value);};
        template<typename T>
        inline T isOther(const T value) { return static_cast<Type*>(this)->isOther(value);};
        template<typename T>
        inline T instanceof(const T& object) { return static_cast<Type*>(this)->template instanceof<T>(object);};
};

template <typename Derived>
class Visitor {
    public:
        template<typename T>
        inline auto visitBinaryExpr(T* expr) { return static_cast<Derived*>(this)->visitBinaryExpr(expr); };
        template<typename T>
        inline auto visitUnaryExpr(T* expr) { return static_cast<Derived*>(this)->visitUnaryExpr(expr); };
        template<typename T>
        inline void visitBlockStmt(T* stmt) { return static_cast<Derived*>(this)->visitBlockStmt(stmt); };
        template<typename T>
        inline auto visitExpressionStmt(T* stmt) { return static_cast<Derived*>(this)->visitExpressionStmt(stmt); };
        template<typename T>
        inline auto visitPrintStmt(T* stmt) { return static_cast<Derived*>(this)->visitPrintStmt(stmt); };
        template<typename T>
        inline auto visitVariableExpr(T* expr) { return static_cast<Derived*>(this)->visitVariableExpr(expr); };
        template<typename T>
        inline void visitVarStmt(T* stmt) { return static_cast<Derived*>(this)->visitVarStmt(stmt); };
        template<typename T>
        inline auto visitAssignExpr(T* expr) { return static_cast<Derived*>(this)->visitAssignExpr(expr); };
};
#endif 
