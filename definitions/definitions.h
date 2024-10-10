#pragma once
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_
#include <experimental/random>
#include <declarations.h>
#include <enum_types.h>
/** -------------------------------------------------------
 * 
 * @brief Gernic structs that perform deepy copying and shallow copying
 * 
 * @details Deep copying is useful when you're allocating memory dynamically.
 *          There are multiple cases as to why deep copying is needed.
 * 
 * @details Is friends with certain classes that need to deep copy a unique data structure.
 * 
 * @details Pass in an object that isn't a smart pointer or a raw pointer and it could convert it into a unique_ptr.
 *          
*/
template<typename T>
struct deepCopy {
    // In order to use this struct, classes or other structs must be friends
    // Because the default constructor is inside the private interface
    friend class ::Parser::parseError<Parser::parser>;
    friend class ::Parser::parser;
    deepCopy(const deepCopy&) noexcept = default;
    deepCopy(deepCopy&&) noexcept = default;
    deepCopy& operator=(const deepCopy&) = default;
    deepCopy& operator=(deepCopy&&) noexcept = default;
    explicit deepCopy(const T& other) 
            : data(other) 
        {}
    /** --------------------------------------------- 
     * @brief  Method that will set the data from an rvalue reference
     * 
    */
    inline void setData(T&& other) {
        data = std::move(other);
    };
    /** ----------------------------------------------------
     * @brief Method to get a const reference to the data
     * 
     * -----------------------------------------------------
    */
    inline const T& getData() const {
        if (!data) {
            throw std::runtime_error("Accessing uninitialized data");
        }
        return *data;
    };
    /** -------------------------------------------------
     * @brief Method to get a mutable reference to the data
     * 
     * 
     * --------------------------------------------------
    */
    inline T& getData() {
        if (!data) {
            throw std::runtime_error("Accessing uninitialized data");
        }
        return *data;
    };
    private:
        T data;
        deepCopy() = default;
};
/** ---------------------------------------------------------------------------
 * @brief Custom function that creates a tuple for later use.
 * ----------------Generic Arguments------------------------------------------
 * @param T: Is a type int to indicate the position of the tree (first)
 * @param U: The name of the node which is paired with a initializer_list (second)
 * @param V: Object type variants  (third)
 * --------------------Detials-------------------------------------------------
 * @details The arguments are generic, therefore they can be reused with other types. Templates are more flexible than any
 *
 * @return tuple(int, string, shared_ptr(initializer_list(variant)))
 *
 * ---------------------------------------------------------------------------
*/
template<typename T, typename U, typename V>
inline astTree<T, U, V> compressedAstTree(T first, U second, V third) {
    return std::make_tuple(
        std::move(first),
        std::make_pair(
            std::move(second),
            std::forward<V>(third)
        )
    );
}

/**---------------------------------------------------------------------------
 * @brief Uses atomic to prevent 'data races'/sync. It also uses threading.
 *
 *
 * @details Makes a copy of languageExtension and downloads and places it into it's own table
 * @details The asympotic notation will be at least O(n^2)
 *
 * @return Returns a table that has extensions for a language and the links
 *
 * ---------------------------------------------------------------------------
*/
Table initTable(const Unordered<String, Vector<String>> languageExtensions_, const Unordered<String, String> downloads_) {
    std::vector<std::pair<std::string, std::vector<std::string>>> languageExt(languageExtensions_.begin(), languageExtensions_.end());
    Unique<Atomic<const char*>> atomicExtChar;
    Unique<Atomic<const char*>> atomicKeyChar;
    Table languageTable;
    std::thread build_;
    auto build = [downloads_, &languageTable](Unique<Atomic<const char*>> key, Unique<Atomic<const char*>> value) -> void {
        std::string loadedKey = key.get()->load(std::memory_order_relaxed);
        if (auto search = downloads_.find(loadedKey); search != downloads_.end()) { 
            std::string dVal = search->second;
            std::string loadedValue = value.get()->load(std::memory_order_relaxed);
            languageTable[loadedKey] = std::make_pair(loadedValue, dVal); // Update the Table
        }
        return;
    };
    const char* extension;
    for (int i = 0; i < languageExt.size(); i++) {
        const char* key = languageExt[i].first.c_str();
        #if RANDOM_EXTENSIONS
            int random_number = std::experimental::randint(0, static_cast<int>(languageExt[i].second.size()));
            extension = languageExt[i].second.at(random_number).c_str();
        #else  
            extension = languageExt[i].second.at(0).c_str();
        #endif
        Unique<Atomic<const char*>> atomicExtChar = std::make_unique<Atomic<const char*>>(extension);
        Unique<Atomic<const char*>> atomicKeyChar = std::make_unique<Atomic<const char*>>(key);
        if (build_.joinable()) {
            build_.join(); // terminate the thread
            build_ = std::thread (build, std::move(atomicKeyChar), std::move(atomicExtChar)); // Initialize the thread
        }
        else {
            build_ = std::thread (build, std::move(atomicKeyChar), std::move(atomicExtChar)); // Initialize the thread
        }
    }
    return languageTable;
};
/** ------------------------------------------------------------------------
 * @brief This function is apart of the preproccessor ENABLE_INTERPRETER. default is 1
 *
 * @details It will overwrite ENABLE_INTERPRETER to 0 or one depending on the user programming language choice
 *
 * -------------------------------------------------------------------------
*/
int setI(const int val...) {
    int result = 0;
    std::va_list args;
    va_start(args, val);
    for (int i = 0; i < val; ++i) {
        if (va_arg(args, int) != 0) {
            result = va_arg(args, int);
            break;
        }
        va_end(args);
    }
    return result;
};
/** ------------------------------------------------------------------------
 * @brief This function is apart of the preproccessor ENABLE_COMPILER. default is 0
 *
 * @details It will overwrite ENABLE_COMPILER to 0 or 1 depending on the user programming language choice
 *
 * -------------------------------------------------------------------------
*/
int setC(const int val...) {
    int result = 0;
    std::va_list args;
    va_start(args, val);
    for (int i = 0; i < val; ++i) {
        if (va_arg(args, int) != 0) {
            result = va_arg(args, int);
            break;
        }
        va_end(args);
    }
    return result;
};
#endif
