#ifndef ASSEMBLY_VISITOR_ACCESS_H
#define ASSEMBLY_VISITOR_ACCESS_H

#include <cstdint>

extern "C" {
    extern void* _ZN12BinaryVisitorE;
    extern void* _ZN11UnaryVisitorE;
    extern void* _ZN14GroupingVisitorE;
    extern void* _ZN13LiteralVisitorE;
}

template<typename T>
T* getVisitor(void* symbol) {
    T* result;
    __asm__ (
        "movq %1, %0"
        : "=r" (result)
        : "m" (symbol)
    );
    return result;
}

template<typename T>
T& getBinaryVisitor() {
    return *getVisitor<T>(_ZN12BinaryVisitorE);
}

template<typename T>
T& getUnaryVisitor() {
    return *getVisitor<T>(_ZN11UnaryVisitorE);
}

template<typename T>
T& getGroupingVisitor() {
    return *getVisitor<T>(_ZN14GroupingVisitorE);
}

template<typename T>
T& getLiteralVisitor() {
    return *getVisitor<T>(_ZN13LiteralVisitorE);
}

#endif // ASSEMBLY_VISITOR_ACCESS_H
