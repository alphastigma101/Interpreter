#pragma once
#ifndef _DEFINITIONS_H_
#define _DEFINITIONS_H_
#include <declarations.h>
// These are macros that are enabled or disabled by the compiler 
#if ENABLE_ENV
    Map<Map<Any,String>, Vector<Any>> env;
#endif

#if ENABLE_TESTING
    String file_name, user_choice;
#endif


#endif
