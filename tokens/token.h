#ifndef _TOKEN_H_
#define _TOKEN_H_
#include <interface.h>
#include <catch.h>
/** --------------------------------------------------------------------------------------
 * @brief This header file holds the declarations of the class called Token which is used a lot throughout this codebase
 * 
 * @details It includes the "interface.h".
 *          It declares crtp classes that are mainly methods that were simply created from inspirations of crafting interpreters
 * @details interface.h includes the definition header which that header includes declarations.h 
 *          interface.h is a package basically and should only be needed if the class that is being declared/defined needs those methods 
 * 
 */
class Token: public MemberConv<Token>, catcher<Token>  {
    public:
        /**
         * @brief default constructor is needed only for initialization, (Instantiation) of the member vairables
         *
        */
        explicit Token() = default;
        ~Token() noexcept = default;
        // Other Constructor
        explicit Token(const TokenType type_, const String lexeme_, const String literal_, const int line_);
        TokenType getType();
        String getTypeStr();
        String getLexeme();
        String getLiteral();
        int getLine();
        inline std::any toString() {
            return std::make_any<String>(tokenTypeToString() + " " + lexeme + " " + literal);
        };
    protected:
        inline String tokenTypeToString() {
            auto it = tokenTypeStrings.find(type);
            if (it != tokenTypeStrings.end()) { return it->second;}
            catcher<Token> cT("Unknown TokenType");
            throw cT;
        };
        inline static const char* what(const char* msg = std::move(getMsg())) throw() { return msg;};
    private:
        TokenType type;
        String lexeme;
        String literal; 
        int line;
    };

#endif
