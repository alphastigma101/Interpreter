#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <definitions.h>
template<class Type>
class NonMemberConv {
    // An abstract class used for converting object types that are not a member object of the class 
    public:
        ~NonMemberConv() noexcept = default;
        template<typename T>
        inline T toNumeric(Any& value) { return static_cast<Type*>(this)->toNumeric(value); };
        inline char* toString(Any& left, Any& right) { return static_cast<Type*>(this)->toString(left, right); };
};
template<class Type>
class Check {
    public:
        ~Check() noexcept = default;
        inline bool isNumeric(const Any value) { return static_cast<Type*>(this)->isNumeric(value); };
        inline bool isString(const Any value) {return static_cast<Type*>(this)->isString(value); };
        inline bool bothEqual(const Any a, const Any b) {return static_cast<Type*>(this)->bothEqual(a,b);};
        template<typename T>
        inline bool instanceof(const Any& object) { return static_cast<Type*>(this)->instanceof(object);};
};
template<class Type>
class MemberConv {
    // An abstract class is used to convert member types of a class object into a string 
    public:
        ~MemberConv() noexcept = default;
        inline std::any toString() { return static_cast<Type*>(this)->toString(); };
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
