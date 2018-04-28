/*
 * UnloadAllResources.cpp
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
#include <stdio.h>

#include "Resources.h"

extern int ReturnAllCFHandles();

void UnloadAllResources(){
	if (NumTempIntResources>0){
		int i;
		for(i=1;i<=NumTempIntResources;i++){
			if (tempIntResource[i] != NULL) {
#ifdef DEBUGUNLOADALLRESOURCES
				dfprintf(fp9,"freeing %i byte tempIntResource[%i] (0x%llx) = %s\n",(int)_msize(tempIntResource[i]),i,(long long unsigned int)tempIntResource[i],tempIntResource[i]);
#endif
				free(tempIntResource[i]);
				tempIntResource[i]=NULL;
			} else {
				printf("UnloadAllResources found NULL pointer at tempIntResource[%i]\n",i);
			}
		}
		if (tempIntResource != NULL) {
#ifdef DEBUGUNLOADALLRESOURCES
			dfprintf(fp9,"freeing %i byte tempIntResource = 0x%llx\n",(int)_msize(tempIntResource),(long long unsigned int)tempIntResource);
#endif
			free(tempIntResource);
			tempIntResource=NULL;
		} else {
			printf("UnloadAllResources found NULL tempIntResource pointer (this error impossible)\n");
		}
		NumTempIntResources=0;
	}
	ReturnAllCFHandles();
	return;
}
