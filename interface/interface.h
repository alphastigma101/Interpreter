#ifndef _INTERFACE_H_
#define _INTERFACE_H_
#include <definitions.h>
template<class Type>
class Visitor {
    public:
    template<typename... Args>
    inline String visit(Args&&... args) {  return static_cast<Type*>(this)->visit(std::forward<Args>(args)...); };
    template<typename... Args>
    inline String accept(Args&&... args) {  return static_cast<Type*>(this)->accept(std::forward<Args>(args)...);  };
};
#endif 
