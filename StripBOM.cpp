/*
 * StripBOM.cpp
 *
 *  Created on: Jan 17, 2017
 *      Author: dad
 */

#ifdef WINDOZE
#pragma message( "Compiling " __FILE__ " on " __DATE__ " at " __TIME__ )
#pragma message( "File last modified on " __TIMESTAMP__ )
#pragma message( "  ")
#pragma title( "My Secret Box version 2.0" )
#pragma subtitle( "Copyright (c) 2003 - 2015, Nehemiah Ministries, Inc." )
#pragma comment( compiler )
#pragma comment( user, "File: " __FILE__ ". Compiled on " __DATE__ " at " __TIME__ ".  Last modified on " __TIMESTAMP__ )
#endif

#include "StdAfx.h"

#include "Resources.h"

int StripBOM (char* c){
	int i,j;
	int len;
	ResLineNum++;
	if ((len=strlen(c)) == 0) return (0);
	for (i=0;i<(len-2);i++) {
		if(c[i]=='\xef'&&c[i+1]=='\xbb'&&c[i+2]=='\xbf'){
#ifdef DEBUGSTRIPBOM
	WinFprintf(fp9,"BOM found on line %i\n",ResLineNum);
#endif
			for(j=i+3;j<len;j++)c[j-3]=c[j];
			c[len-3]='\000';
			len=strlen(c);
		}
	}
	if (len>0){
		if(c[len-1]=='\x0a'){
			c[len-1]='\000';
			len--;
		}
	}
#ifdef DEBUGSTRIPBOM
	WinFprintf(fp9,"len of line %4i=%3i \"%s\"\n",ResLineNum,len,c);
#endif
	return(len);
}
