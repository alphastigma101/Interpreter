#pragma once
#ifndef _ADDON_H_
#define _ADDON_H_
/** ------------------------------------------------------------------------------------------------------------
 * @brief Enables the custome language tatical nuke to be compiled or not
*/
#ifndef ENABLE_ENV
    #define ENABLE_ENV 0
#endif
/** ----------------------------------------------------------------------------
 * @brief Enables the custom language tatical nuke to be compiled or not in a .o file 
*/
#ifndef ENABLE_TATICAL_NUKE
    #define ENABLE_TATICAL_NUKE 0
#endif
/** ---------------------------------------------------------------------------
 * @brief Enables evaluatedExpressions to be compiled or not in a .o file
*/
#ifndef ENABLE_EVALUATED_EXPRESSIONS
    #define ENABLE_EVALUATED_EXPRESSIONS 0
#endif
/** ----------------------------------------------------------------------------
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

#endif  // End of addon.h 
