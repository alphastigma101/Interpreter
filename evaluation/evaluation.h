#include <interface>
namespace Computation {
    template<class Derived>
class Computation: public Conv<Computation<Derived>> {
    // An abstract class that is used for converting strings into targeted types during interpretation
    // This class offers methods that should not be directly implemented into the Derived class, but are still needed
    public:
        ~Computation() = default;
        /** --------------------------
         * @brief Used for evaluating nested expressions 
         * 
         * @param a Can be an object that represents the left side of the expression
         * @param b Can be an object that represents the right side of the expression
         *
         * @details Returns a implicity converted object 
        */
        inline static Any compute(Any& a, Any& b, auto& expr) { 
            switch (expr->op.getType()) {
                case TokenType::GREATER:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) > std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) > std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<String>(a) && Computation<Derived>::instanceof<String>(b))
                        return std::any_cast<String>(a) > std::any_cast<String>(b);
                    return nullptr;
                case TokenType::GREATER_EQUAL:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) >= std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) >= std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<String>(a) && Computation<Derived>::instanceof<String>(b)) 
                        return std::any_cast<String>(a) >= std::any_cast<String>(b);
                    return nullptr;
                case TokenType::LESS:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) < std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) < std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<String>(a) && Computation<Derived>::instanceof<String>(b)) 
                        return std::any_cast<String>(a) < std::any_cast<String>(b);
                    return nullptr;
                case TokenType::LESS_EQUAL:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) <= std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) <= std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<String>(a) && Computation<Derived>::instanceof<String>(b)) 
                        return std::any_cast<String>(a) <= std::any_cast<String>(b);
                    return nullptr;
                case TokenType::MINUS:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) - std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) - std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    return nullptr;
                case PLUS:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) + std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) + std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<String>(a) && Computation<Derived>::instanceof<String>(b)) 
                        return std::any_cast<String>(a) + std::any_cast<String>(b);
                    return nullptr;
                case TokenType::SLASH:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) / std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) / std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    return nullptr;
                case TokenType::STAR:
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) * std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) * std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    return nullptr;
                case TokenType::BANG_EQUAL: 
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) != std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) != std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    return nullptr;
                case TokenType::EQUAL_EQUAL: 
                    if (Computation<Derived>::instanceof<double>(a) && Computation<Derived>::instanceof<double>(b))  
                        return std::to_string(std::any_cast<double>(Computation<Derived>::toNumeric(a)) == std::any_cast<double>(Computation<Derived>::toNumeric(b)));
                    if (Computation<Derived>::instanceof<int>(a) && Computation<Derived>::instanceof<int>(b))
                        return std::to_string(std::any_cast<int>(Computation<Derived>::toNumeric(a)) == std::any_cast<int>(Computation<Derived>::toNumeric(b)));
                    return nullptr;

            }
            return nullptr;
        };
        inline static bool isOther(const Any value) {
            
            return false;
        };
        /** ---------------------------------------------------------------
         * @brief ...
         *
         * @param object ...
         *
         * @details .....
         * ----------------------------------------------------------------
        */
        template<typename T>
        inline static bool instanceof(const Any& object) {
            try {
                if (isNumeric<T>(object)) return true;
                else if (isOther(object)) return true;
            } catch (...) {
                return false;
            }
            return false;
        };
        inline static bool isString(const Any value) { return value.type() == typeid(String);};
        template<typename T>
        inline static bool isNumeric(const Any value) {
            try {
                String temp = std::move(std::any_cast<String>(value));
                for (int i = 0; i < temp.length() - 1; i++) {
                    if (temp[i] == '.') {
                        try {
                            if (typeid(std::stod(temp)) == typeid(T)) return true;
                            return false;
                        }
                        catch(...) { return false; }
                        return true;
                    }
                }
                try {
                    if (typeid(std::stoi(temp)) == typeid(T)) return true;
                    return false;
                }
                catch(...) { return false; }
            } catch (...) { return false; }
            return false;    
        };
        /** ---------------------------------------------------------------
         * @brief A simple method that converts the parameter object into a supported type
         *
         * @param value Some kind of value that must be a supported type
         *
         * @details The supported types are double for more precision and integer. 
         * ----------------------------------------------------------------
        */
        inline static Any toNumeric(Any& value) {
            try {
                String temp = std::any_cast<String>(value);
                for (int i = 0; i < temp.length() - 1; i++) {
                    if (temp[i] == '.') {
                        try {
                            return std::stod(temp);
                        }
                        catch(...) { return nullptr; }
                    }
                }
                try {
                    return std::stoi(temp);
                }
                catch(...) { return nullptr; }
            } catch (...) { return nullptr; }
            return nullptr;
        };
        inline static Any toOther(Any& lhs, Any& rhs) {
            /*auto toList = [](String& temp) -> Any {
                try {
                    if (temp.front() == '[' && temp.back() == ']') {
                        // Remove brackets and trim whitespace
                        String content = temp.substr(1, temp.length() - 2);
                        content.erase(0, content.find_first_not_of(" \t\n\r"));
                        content.erase(content.find_last_not_of(" \t\n\r") + 1);
                    
                        // Remove quotes from content if they exist
                        if (content.front() == '"' && content.back() == '"') {
                            content = content.substr(1, content.length() - 2);
                        }
                    
                        // Dynamically allocate new list with the processed content
                        return new Nuke::core::list{content};
                    }
                    else 
                        return nullptr;
                }
                catch(...) { return nullptr; }
                return nullptr; 
            };
            try {
                Any res = std::make_any<String>(std::any_cast<String>(toList(lhs)), std::any_cast<String>(toList(rhs)));
                if (res.has_value()) return std::any_cast<String>(res);
                return nullptr; 
            }
            catch(...) { return nullptr; }
            auto toMap = [](String& temp) -> Any {
                try {
                    if (temp.front() == '{' && temp.back() == '}') {
                        // Remove brackets and trim whitespace
                        String content = temp.substr(1, temp.length() - 2);
                        content.erase(0, content.find_first_not_of(" \t\n\r"));
                        content.erase(content.find_last_not_of(" \t\n\r") + 1);
                    
                        // Remove quotes from content if they exist
                        if (content.front() == '"' && content.back() == '"') {
                            content = content.substr(1, content.length() - 2);
                        }
                    
                        // Dynamically allocate new list with the processed content
                        return new Nuke::core::dict{content};
                    }
                    else 
                        return nullptr;
                }
                catch(...) { return nullptr; }
                return nullptr; 
            };
            try {  
                Any res = std::make_any<String>(std::any_cast<String>(toMap(lhs)), std::any_cast<String>(toMap(rhs)));
                if (res.has_value()) return std::any_cast<String>(res);
                return nullptr; 
            }
            catch(...) { return nullptr; }*/
            return nullptr;
        };
};