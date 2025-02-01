#ifndef _CATCH_H_
#define _CATCH_H_
template<class Type>
class catcher {
    public:
        explicit catcher() = default;
        explicit catcher(const char* message) { message_ = const_cast<char*>(message); };
        inline static const char* what() { return message_; };
        ~catcher() = default;
    protected:
        static char* message_;
};
template<class T>
char* catcher<T>::message_;
#endif
