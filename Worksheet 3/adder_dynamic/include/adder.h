#pragma once

//The following two lines prevent adder.h from being included
//more than once in any source (.cpp) file. If this were to happen
//it would cause problems in the compile process but it is difficult to 
//prevent manually in large projects. These #indef, #define and #endif 
//commands for an "include guard" and are types of compiler directive. 
//The include guard contains an ID for this file "MATHSLIB_ADDER_H", this
//is arbitrary but must be unique within the project.

#ifndef MATHSLIB_ADDER_H
#define MATHSLIB_ADDER_H


#if defined(WIN32)|defined(_WIN32)
	#ifdef maths_STATIC
	
		#define MATHSLIB_API
	#else
		#ifdef maths_EXPORTS
			#define MATHSLIB_API  __declspec(dllexport)
		#else
			#define MATHSLIB_API __declspec(dllimport)
		#endif
	#endif
#else
	#define MATHSLIB_API
#endif

	MATHSLIB_API int add(int a, int b);

#endif
//end -adder.h