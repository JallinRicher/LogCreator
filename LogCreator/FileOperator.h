#pragma once

#include <iostream>
#include <fstream>
#include <direct.h>
#include <string>

#include "MacroDefines.h"

using namespace std;

class INTERFACE_CLASS BASE_CLASS FileOperator
{
public:
	FileOperator(IN string FilePath, IN int Mode = ios_base::in | ios_base::out | ios_base::app | ios_base::ate);
	FileOperator(IN const char* FilePath, IN int Mode = ios_base::in | ios_base::out | ios_base::app | ios_base::ate);
	~FileOperator();

	virtual void CLASS_API VIRTUAL_FUNCTION CloseFile();
	
	virtual int  CLASS_API VIRTUAL_FUNCTION Write(IN string _Str, IN unsigned long long StrLen);
	virtual int  CLASS_API VIRTUAL_FUNCTION Write(IN const char* _Str, IN unsigned long long StrLen);
	virtual int  CLASS_API VIRTUAL_FUNCTION Write(IN const char* _Format, ...);
	
	virtual int  CLASS_API VIRTUAL_FUNCTION Read(IN void* Buffer, IN unsigned long long BufferSize);
	virtual int  CLASS_API VIRTUAL_FUNCTION GetOneLine(IN void* Buffer, IN unsigned long long BufferSize);

	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const char*);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const string&);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const int);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const unsigned int);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const short);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const unsigned short);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const long);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const unsigned long);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const long long);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const unsigned long long);
	virtual FileOperator& OPERATOR_OVERRIDE VIRTUAL_FUNCTION operator << (const void*);

	FileOperator& OPERATOR_OVERRIDE operator >> (void* _buffer);

public:
	static bool STATIC_FUNCTION CreateFile(IN string FilePath);

public:
	inline INLINE_FUNCTION bool IsOpenFile() const
	{ return m_IsOpenFile; }

private:
	bool m_IsOpenFile{ false };
	char* m_Buffer[1024];
};