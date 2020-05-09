
#ifndef __VX_TYPE_H__
#define __VX_TYPE_H__

#include "VxDef.h"

typedef void (*VxFuncPtr)();
typedef void (*VxFuncPtrA)(void *);
typedef int (*VxFuncPtrNA)(void *);
typedef void* (*VxFuncPtrPA)(void *);
typedef void* (*VxFuncPtrPAA)(void*, void*);
typedef void (*VxFuncPtrAA)(void*, void*);
typedef void (*VxFuncPtrAAA)(void*, void*, void*);
typedef bool (*VxFuncPtrBA)(void*);
typedef bool (*VxFuncPtrBAA)(void*, void*);
typedef bool (*VxFuncPtrBAAA)(void*, void*, void*);

class VxMsg;
typedef void (*VxFuncPtrMsgCb)(void*, VxMsg*);

//typedef pthread_t VxThread;

typedef void (*VxSockEventCb)(void* pvArg, int eEventId, void *pvEventArgs);
typedef void (*VxNetEventCb)(void* pvArg, int eEventId, void *pvEventArgs);

typedef int VxTimer;

typedef void (*VxNetSendCb)(void* arg, int eEventId, void *pvEventArgs);



#pragma pack(push, 4)


class VxString
{
public:
	VxString()
		: m_pString(NULL), m_nLength(0)
	{
	}

	VxString(char* pString, int nLength)
		: m_nLength(nLength), m_pString(pString)
	{
	}

	void copy(const std::string& str)
	{
		char* pString = NULL;
		int nLength = (int)(str.length());
		int nRealLength = VXMATH_ALIGMENT4(nLength + 1);
		pString = new char[nRealLength];
		if(pString)
		{
			memcpy(pString, str.c_str(), nLength);
			memset(pString + nLength, 0, nRealLength - nLength);
			m_pString = pString;
			m_nLength = nLength;
		}
	}

	inline bool empty()
	{
		return !m_nLength || !m_pString;
	}

public:
	int m_nLength;
	char* m_pString;
};





/************************************************************************/
/* Key - value pair
/************************************************************************/
template<class K, class V>
class VxKeyValuePair
{
public:
	VxKeyValuePair(K nKey, V nValue)
		: m_nKey(nKey)
		, m_nValue(nValue)
	{
	}
	
public:
	K m_nKey;
	V m_nValue;
};



#pragma pack(pop)

#endif	// __VX_TYPE_H__