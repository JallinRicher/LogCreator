/*****************************************************************//**
 * \file   LogCreator.h
 * \brief  Chinese: 日志系统类，负责输出和保存系统日志。
 * \brief  English: Log system class, responsible for outputting and saving system logs.
 * 
 * \author JallinRichel(Rundong Li)
 * \date   November 2022
 *********************************************************************/

#pragma once
#include <cstdio>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <stdarg.h>
#include <string>
#include "Defines.h"

using namespace std;

class LogCreator
{
public:
	LogCreator(IN string FilePath, IN int Mode = ios_base::in | ios_base::out | ios_base::app | ios_base::ate);
	LogCreator(IN const char* FilePath, IN int Mode = ios_base::in | ios_base::out | ios_base::app | ios_base::ate);
	~LogCreator();

	/**
	* 打印日志，打印出的日志长度不能超过 1024Bytes
	* \param Level 日志等级
	* \param _Format 格式化日志
	* \param ... 变长参数列表
	* \return size_t 写入的日志长度
	*/
	size_t CLASS_API PUBLIC_FUNCTION WriteLog(IN const char* Level, IN const char* _Format, ...);

public:
	static void createFolder(IN const char* FilePath);

private:
	char* CLASS_API PRIVATE_FUNCTION _writeLog(IN const char* _Format, IN va_list ap);

private:
	fstream m_LogFile;
	char m_Buffer[LOG_BUFFER_SIZE]{ 0 };
	string m_strBuffer;
};