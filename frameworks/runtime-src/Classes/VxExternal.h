
#ifndef __VX_EXTERNAL_H__
#define __VX_EXTERNAL_H__

#define CC_PLATFORM_WIN32 1

#define  CC_TARGET_PLATFORM  CC_PLATFORM_WIN32

#include <ctime>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string.h>


#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <regex>
#endif

#include <sys/stat.h>

/************************************************************************/
/* Error
/************************************************************************/
#if CC_TARGET_PLATFORM != CC_PLATFORM_WIN32
#include <errno.h>
#endif

/************************************************************************/
/* File
/************************************************************************/
#if CC_TARGET_PLATFORM == CC_PLATFORM_WIN32
#include <direct.h>
#include <io.h>
#else
#include <unistd.h>
#endif



#endif	// __VX_EXTERNAL_H__
