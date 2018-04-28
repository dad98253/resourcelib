/*
 * StdAfx.h
 *
 *  Created on: Jan 17, 2017
 *      Author: dad
 */

#ifndef STDAFX_H_
#define STDAFX_H_


#ifndef WINDOZE
#define _MSC_VER	0
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>

#ifdef WINDOZE
// Windows Header Files:
//#include <windows.h>
// Windows Html Help Header Files:
//#include <htmlhelp.h>
#include <tchar.h>
#define UNUSED(x) x
#define CLEARSCR system ( "cls" )
#else
// Linux Header Files:
//#include "lindows.h"
#define CLEARSCR system ( "reset -m unknown:dumb" )
#endif

#define Stringize( L ) #L
#define MakeString( M, L ) M(L)
#define $Line MakeString( Stringize, __LINE__ )
#define Reminder __FILE__ "(" $Line ") : Reminder: "
#ifdef DEBUG
#ifndef __MYFILE__
#ifdef WINDOZE
#define __MYFILE__  (strrchr ( __FILE__ , '\\' )+1)
#else   // WINDOZE
#define __MYFILE__  (strrchr ( __FILE__ , '/' )+1)
#endif  // WINDOZE
#endif	// __MYFILE__
#endif  // debug
#ifdef WINDOZE
#include <windows.h>
#define JKNULL	NULL
#else
#ifndef JKNULL
#ifdef __cplusplus
#define JKNULL    0
#else
#define JKNULL    ((void *)0)
#endif
#endif
#endif

#ifdef DEBUG
		extern FILE *fp9;
		extern int debugflag;
		extern int FAR cdecl WinFprintf(FILE *hp, const char * fmt,...);
        #define dfprintf if (debugflag) WinFprintf
#else
        #define dfprintf if (0) ((int (*)(const char *, ...)) 0)
#endif



#endif /* STDAFX_H_ */
