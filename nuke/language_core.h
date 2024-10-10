#pragma once
#ifndef _LANGUAGE_TYPES_H_
#define _LANGUAGE_TYPES_H_
#include <declarations.h>
/** ---------------------------------------------------------------------------------------------------------------------------------------------------------------------
 * @details This header file is designed to be used in conjunction with `enum_types.h` at the end. This separation helps to better organize the code and its definitions.
 *
 * ----------------------------------------------------------------------------------------------------------------------------------------------------------------------
*/
namespace Nuke {
    struct core {
        // alias templates
        template<typename...> using Object = void;
        using numeric = Object<int, double, float>;
        using tokens = Object<char, std::string>;
        using list = Object<std::vector<std::any>>;
        using dict = Object<std::map<std::any,std::any>>;
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
