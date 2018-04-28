/*
 * ReturnAllCFHandles.cpp
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


int ReturnAllCFHandles()
{
	int i;
	for (i=0;i<NUMCFHANDLES;i++) {
		if(CFileHandles[i] != NULL) {
#ifdef DEBUG
			dfprintf(fp9,"freeing handle %i (for %s)\n",i+1,CFileHandles[i]);
#endif
			free(CFileHandles[i]);
		}
	}
	return(1);
}
