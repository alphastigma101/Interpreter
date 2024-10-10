#ifndef _CATCH_H_
#define _CATCH_H_
template<class Type>
class catcher {
    public:
        explicit catcher() = default;
        inline static char* getMsg() { return message_; };
        explicit catcher(const char* message) { message_ = const_cast<char*>(message); };
        inline const char* what(const char* msg = getMsg()) throw() { return static_cast<Type*>(this)->what(msg); };
        virtual ~catcher() = default;
    private:
        static char* message_;
};
template<class T>
char* catcher<T>::message_;
#endif
