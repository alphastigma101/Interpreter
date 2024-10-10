#pragma once
#ifndef _ADDON_H_
#define _ADDON_H_
/** ------------------------------------------------------------------------------------------------------------
 * @brief Builds the bits that will prevent undefined reference to cTree 
 */
#ifndef ENABLE_TREE_DEBUGGING
    #define ENABLE_TREE_DEBUGGING 0
#endif
/** ---------------
 * @brief Used in context_free_grammar.cc to enable cTree object to be compuled once 
 * ----------------
*/
#ifndef ENABLE_TREE_BUILD
    #define ENABLE_TREE_BUILD 0
#endif

/** --------------------------------------------------------------------------
 * @brief this macro will be set to one if the executable that start with 'exec_debug_...' during compilation. Otherwise, will remain off
 * 
 * @details Used in abstraction_tree_syntax.h
 *
 * ---------------------------------------------------------------------------
*/
#ifndef ENABLE_TESTING
    #define ENABLE_TESTING 0
#endif
/** --------------------------------------------------------------------------
 * @brief This feature will allow the user to generate random extensions if needed
 *
 * @details Use grep -R 'RANDOM_EXTENSIONS' ../ or ./ to find where it is used
*/
#ifndef RANDOM_EXTENSIONS
    #define RANDOM_EXTENSIONS 0
#endif
/** --------------------------------------------------------------------------
 * @brief this macro will be set to one by default. This avoids re-defining LogEntries multiple times
 *
*/
#ifndef ENABLE_LOGGING_TEST
    #define ENABLE_LOGGING_TEST 0
#endif
/** --------------------------------------------------------------------------
 * @brief This feature will allow the user to disable the interpreter or enable it at compile time 
 *
 * @details Either the compiler flag or interpreter flag must be enabled, not both
 * @details By default the compiler flag is disabled and the interpreter flag is enabled
 * @details Depending on the language the user chooses, the compiler flag or the interpreter flag will be overwritten 
 * @details Use grep -R 'RANDOM_EXTENSIONS' ../ or ./ to find where it is used
 * ---------------------------------------------------------------------------
*/
#ifndef ENABLE_INTERPRETER
    #define ENABLE_INTERPRETER(...) setI(1 __VA_OPT__(,) __VA_ARGS__)
#endif
/** ------------------------------------------------------------------------
 * @brief This feature will allow the user to choose to enable the compiler or disable it at compile time 
 *
 * @details Either the interpreter needs to be enabled or the compiler, not both at the same time
 * @details Use grep -R 'ENABLE_COMPILER' ../ or ./ to find where it is used
*/
#ifndef ENABLE_COMPILER
    #define ENABLE_COMPILER(...) setC(0 __VA_OPT__(,) __VA_ARGS__)
#endif

#endif  // End of addon.h 
