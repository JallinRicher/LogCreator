/*****************************************************************//**
 * \file   LogCreator.h
 * \brief  Chinese: ��־ϵͳ�࣬��������ͱ���ϵͳ��־��
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
	* ��ӡ��־����ӡ������־���Ȳ��ܳ��� 1024Bytes
	* \param Level ��־�ȼ�
	* \param _Format ��ʽ����־
	* \param ... �䳤�����б�
	* \return size_t д�����־����
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