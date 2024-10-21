#pragma once
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_
#include <experimental/random>
#include <declarations.h>
// These are macros that are enabled or disabled by the compiler 
#if ENABLE_LOGGING_TEST
    logTable<Map<String, Vector<String>>> logEntries;
#endif

#if ENABLE_TREE_BUILD
   Vector<astTree<int, String, ExprVariant>> cTree;
#endif

#if ENABLE_EVALUATED_EXPRESSIONS
    Vector<String> evaluatedExpressions;
#endif 
#if ENABLE_TESTING
    String file_name, user_choice;
    int settings;
#endif
#if ENABLE_TATICAL_NUKE
    //Nuke::core tatical_nuke;
    int currentEnvEle = 0;
#endif
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
};
/** ---------------------------------------------------------------------------
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
namespace Nuke {
    struct core {
        // alias templates
        template<typename...> using Object = void;
        using numeric = Object<int, double, float>;
        using tokens = Object<char, String>;
        using list = List<Any>;
        using dict = Map<Any,Any>;
        template<typename...> using Ptr = void*;
        template<typename...> using Ref = void;
        using ptr = Ptr<numeric, tokens>;
        using ref = Ref<std::reference_wrapper<numeric>, std::reference_wrapper<tokens>>;
        struct hasSpecialRules {
            // implement the rules here
            // Example: If the language is NUKE. That means if any kind of syntax error occurs, it will spout random ASCII values and display TATICAL NUKE AT THE END 
            // And destory itself. 
            // Otherwise make the source code use the generic rules for a custom language
            // TODO: Search and see if there are theories on generic rules when it comes to creating a custom language if not, make one 
            // Phonetics and Phonology:
            // - Decide on the sound inventory (consonants, vowels).
            // - Establish phonotactic rules (how sounds can combine).

            // Morphology:
            // - Determine how words are formed (prefixes, suffixes, infixes).
            // - Choose between isolating (few affixes) vs. agglutinative (many affixes) vs. fusional (affixes merge with roots).

            // Syntax:
            // - Define sentence structure (e.g., Subject-Verb-Object vs. Subject-Object-Verb).
            // - Establish rules for question formation, negation, etc.

            // Semantics:
            // - Create a vocabulary and decide on word meanings.
            // - Develop rules for word formation and compounding.

            // Pragmatics:
            // - Consider how context affects meaning.
            // - Decide on politeness strategies and speech acts.

            // Orthography:
            // - Design a writing system (alphabetic, syllabic, logographic).
        };
    };
};
#endif