/*
 * LoadResources.cpp
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
#include <errno.h>

#include "Resources.h"

#define GetLineType(x) ((ParseLineRCfmtItem[x] == 1 ) ? (ParseLineRCItems[x]) : (ParseLineRCItems[x+1]))
#define BOOL bool
#ifndef WINDOZE
#define TRUE true
#define FALSE false
#endif

extern void SetParseFmt(int fmt, int numdelim, ...);
extern int StripBOM (char* c);
extern int ParseLineRC(char* ctemp);

BOOL LoadResources()
{
	int lenline;
	int numStringItemsOut = 0;
	char ctemp[1202];
	int nParse;
	FILE *fVersionInfoFile;
	FILE *fExtRefFile;
	FILE *fStringResourceFile;
	FILE *fResourceFile;
	int level = 0;
	  enum STATE {
		  INITIAL,
		  MENU1,
		  MENU2,
		  DIALOG1,
		  DIALOG2,
		  STRINGTAB1,
		  STRINGTAB2,
		  ACCEL1,
		  ACCEL2,
		  VERS1,
		  VERS2
	  } state = INITIAL;

	fResourceFile = fopen ("passwintestnew.rc","rt");
	if (fResourceFile == NULL)
	  {
		int myerr = errno;
		perror("LoadResources failed to open resource file");
	    printf("LoadResources failed to open resource file, system error number = %i\n",myerr);
	    return(TRUE);
	  }
#ifdef DEBUG
	WinFprintf(fp9,"Loading resource file passwintestnew.rc\n");
#endif
	fExtRefFile = fopen ("extwindata.h","w");
	if (fExtRefFile == NULL)
	  {
	    printf("LoadResources failed to open extwindata output file\n");
	    return(TRUE);
	  }
	fprintf(fExtRefFile,"extern int numStringItems;\n\n");
	fprintf(fExtRefFile,"typedef struct WindowsStringData {\n  int id;\n  const char *string;\n} WindowsStringDataTYPE;\n\nextern WindowsStringDataTYPE StringResourceData[];\n\n");
	fVersionInfoFile = fopen ("versioninfo.h","w");
	if (fVersionInfoFile == NULL)
	  {
	    printf("LoadResources failed to open versioninfo output file\n");
	    return(TRUE);
	  }
	fStringResourceFile = fopen ("stringresources.h","w");
	if (fStringResourceFile == NULL)
	  {
	    printf("LoadResources failed to open stringresources output file\n");
	    return(TRUE);
	  }
	fprintf(fStringResourceFile,"typedef struct WindowsStringData {\n  int id;\n  const char *string;\n} WindowsStringData;\n\nWindowsStringData StringResourceData[]={\n");
	SetParseFmt(1,2," ",",");
	while (fgets ( ctemp, 1200, fResourceFile) != NULL) {
#ifdef DEBUGLOADRESOURCES
		WinFprintf(fp9,"in LoadResources ctemp=%s\n",ctemp);
#endif
		if ((LengthOfInputLine = lenline = StripBOM(ctemp))==0)continue;
#ifdef DEBUGLOADRESOURCES
			  WinFprintf(fp9,"nParse = %i\n",nParse);
#endif
		if ((nParse=ParseLineRC(ctemp))<1)continue;
#if defined(DEBUGLOADRESOURCES) || defined(DEBUGPARSE)
		int i;
#endif
#ifdef DEBUGLOADRESOURCES
		WinFprintf(fp9,"found %i items\n",nParse);
		for (i=0;i<nParse;i++){
			WinFprintf(fp9,"item[%i] (fmt %i) = %s\n",i,ParseLineRCfmtItem[i],ParseLineRCItems[i]);
		}
#endif
#ifdef DEBUGPARSE
		WinFprintf(fp9,"%i fields(fmt) = ",nParse);
		for (i=0;i<nParse;i++){
			WinFprintf(fp9,"%s(%i); ",ParseLineRCItems[i],ParseLineRCfmtItem[i]);
		}
		WinFprintf(fp9,"\n");
#endif
// parse the line
        switch (state)
        {
        case INITIAL:
        	if (strcmp(GetLineType(0), "LANGUAGE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"LANGUAGE type found in INITIAL mode\n");
#endif
        	}
        	else if (strcmp(GetLineType(0), "TEXTFILE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"TEXTFILE type found in INITIAL mode\n");
#endif
        	}
        	else if (strcmp(GetLineType(0), "BITMAP") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"BITMAP type found in INITIAL mode\n");
#endif
        	}
        	else if (strcmp(GetLineType(0), "MENU") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"MENU type found in INITIAL mode\n");
#endif
        		state = MENU1;
        	}
        	else if (strcmp(GetLineType(0), "DIALOGEX") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"DIALOGEX type found in INITIAL mode\n");
#endif
        		state = DIALOG1;
        	}
        	else if (strcmp(GetLineType(0), "STRINGTABLE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"STRINGTABLE type found in INITIAL mode\n");
#endif
        		state = STRINGTAB1;
       	}
        	else if (strcmp(GetLineType(0), "ACCELERATORS") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"ACCELERATORS type found in INITIAL mode\n");
#endif
        		state = ACCEL1;
        	}
        	else if (strcmp(GetLineType(0), "RCDATA") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"RCDATA type found in INITIAL mode\n");
#endif
        	}
        	else if (strcmp(GetLineType(0), "ICON") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"ICON type found in INITIAL mode\n");
#endif
        	}
        	else if (strcmp(GetLineType(0), "VERSIONINFO") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"VERSIONINFO type found in INITIAL mode\n");
#endif
        		state = VERS1;
        	}
        	else if (strcmp(GetLineType(0), "240") == 0) {
#ifdef DEBUGPARSERCDATA
		WinFprintf(fp9,"240 type found in INITIAL mode\n");
#endif
        	} else {
#ifdef DEBUGPARSERCDATA
		WinFprintf(fp9,"unknown type found in INITIAL mode = %s\n",GetLineType(0));
#endif
        		return(TRUE);
        	}
        	break;


// MENU1
        case MENU1:
        	if (strcmp(ParseLineRCItems[0], "LANGUAGE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"LANGUAGE type found in MENU1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in MENU1 mode\n");
#endif
        		state = MENU2;
        		level = 1;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in MENU1 mode = %s\n",ParseLineRCItems[0]);
#endif
        		return(TRUE);
        	}
        	break;

        case MENU2:
        	if (strcmp(ParseLineRCItems[0], "}") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"} type found in MENU2 mode\n");
#endif
        		level--;
        		if (level == 0) state = INITIAL;
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in MENU2 mode\n");
#endif
        		level++;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in MENU2 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
       	break;

        case DIALOG1:
        	if (strcmp(ParseLineRCItems[0], "STYLE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"STYLE type found in DIALOG1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "EXSTYLE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"EXSTYLE type found in DIALOG1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "CAPTION") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"CAPTION type found in DIALOG1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "LANGUAGE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"LANGUAGE type found in DIALOG1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "FONT") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"FONT type found in DIALOG1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in DIALOG1 mode\n");
#endif
        		state = DIALOG2;
        		level = 1;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in DIALOG1 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
       	break;

        case DIALOG2:
        	if (strcmp(ParseLineRCItems[0], "}") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"} type found in DIALOG2 mode\n");
#endif
        		level--;
        		if (level == 0) state = INITIAL;
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in DIALOG2 mode\n");
#endif
        		level++;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in DIALOG2 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
        break;

        case STRINGTAB1:
        	if (strcmp(ParseLineRCItems[0], "LANGUAGE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"LANGUAGE type found in STRINGTAB1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in STRINGTAB1 mode\n");
#endif
        		state = STRINGTAB2;
        		level = 1;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in STRINGTAB1 mode = %s\n",ParseLineRCItems[0]);
#endif
        		return(TRUE);
        	}
       	break;

        case STRINGTAB2:
        	if ( ParseLineRCfmtItem[0] == 2 && ParseLineRCfmtItem[1] == 3 && ParseLineRCNumItems == 2) {
#ifdef DEBUGPARSERCDATA
           		WinFprintf(fp9,"string data found in STRINGTAB2 mode\n");
       			WinFprintf(fp9," %s , \"%s\"\n",ParseLineRCItems[0],ParseLineRCItems[1]);
#endif
       			fprintf(fStringResourceFile,"{ %s , \"%s\\0\" },\n",ParseLineRCItems[0],ParseLineRCItems[1]);
       			numStringItemsOut++;
        	}
        	else if (strcmp(ParseLineRCItems[0], "}") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"} type found in STRINGTAB2 mode\n");
#endif
        		level--;
        		if (level == 0) state = INITIAL;
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in STRINGTAB2 mode\n");
#endif
        		level++;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in STRINGTAB2 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
       	break;

        case ACCEL1:
        	if (strcmp(ParseLineRCItems[0], "LANGUAGE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"LANGUAGE type found in ACCEL1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in ACCEL1 mode\n");
#endif
        		state = ACCEL2;
        		level = 1;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in ACCEL1 mode = %s\n",ParseLineRCItems[0]);
#endif
        		return(TRUE);
        	}
        	break;

        case ACCEL2:
        	if (strcmp(ParseLineRCItems[0], "}") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"} type found in ACCEL2 mode\n");
#endif
        		level--;
        		if (level == 0) state = INITIAL;
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in ACCEL2 mode\n");
#endif
        		level++;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in ACCEL2 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
       	break;

        case VERS1:
        	if (strcmp(ParseLineRCItems[0], "FILEVERSION") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"FILEVERSION type found in VERS1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "PRODUCTVERSION") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"PRODUCTVERSION type found in VERS1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "FILEOS") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"FILEOS type found in VERS1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "FILETYPE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"FILETYPE type found in VERS1 mode\n");
#endif
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in VERS1 mode\n");
#endif
        		state = VERS2;
        		level = 1;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in VERS1 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
        	break;

        case VERS2:
        	if (strcmp(ParseLineRCItems[0], "}") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"} type found in VERS2 mode\n");
#endif
        		level--;
        		if (level == 0) state = INITIAL;
        	}
        	else if (strcmp(ParseLineRCItems[0], "VALUE") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"VALUE type found in VERS2 mode\n");
#endif
        		fprintf(fVersionInfoFile,"char %s[] = {\"%s\\0\"};\n",ParseLineRCItems[1],ParseLineRCItems[2]);
        		fprintf(fExtRefFile,"extern char %s[];\n",ParseLineRCItems[1]);
        	}
        	else if (strcmp(ParseLineRCItems[0], "{") == 0) {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"{ type found in VERS2 mode\n");
#endif
        		level++;
        	} else {
#ifdef DEBUGPARSERCDATA
        		WinFprintf(fp9,"unknown type found in VERS2 mode = %s\n",ParseLineRCItems[0]);
#endif
//        		return(TRUE);
        	}
        	break;

		default:
#ifdef DEBUGPARSERCDATA
		WinFprintf(fp9,"unknown state in LoadResources, state = %s\n",state);
#endif
		break;
        }
// end of while on reading in data
	}
	fclose (fResourceFile);
	fclose (fVersionInfoFile);
	fclose (fExtRefFile);
	fprintf(fStringResourceFile,"{ %i , \"%s\\0\" }\n };\n\n int numStringItems = %i;\n",0,"dummy",numStringItemsOut);  // note that numStringItems excludes the dummy line
	fclose (fStringResourceFile);
	SetParseFmt(0,0);
	ctemp[0] = '\000';
	ParseLineRC(ctemp);
	return (FALSE);
}
