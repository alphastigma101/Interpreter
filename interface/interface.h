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
        inline Any toString() { return static_cast<Type*>(this)->toString();};
        inline Any toNumeric(Any& value) { return static_cast<Type*>(this)->toNumeric(value); };
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

template<class Type>
class Visitor {
    public:
        template<typename... Args>
        inline String visit(Args&&... args) {  return static_cast<Type*>(this)->visit(std::forward<Args>(args)...); };
        template<typename... Args>
        inline String accept(Args&&... args) {  return static_cast<Type*>(this)->accept(std::forward<Args>(args)...);  };
};
      

#endif 
