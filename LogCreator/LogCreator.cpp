#include "LogCreator.h"

LogCreator::LogCreator(IN string FilePath, IN int Mode)
{
	m_LogFile.open(FilePath, Mode);
	if (!m_LogFile.is_open())
		fprintf_s(stderr, "<<< [ %s %s ] Create log file failed.\n", __DATE__, __TIME__);

	m_LogFile << "************************************** " << __DATE__ << __TIME__ << " Log file start here **************************************" << endl;
	m_LogFile << "********************************************************************************************************************************" << endl << endl;
}

LogCreator::LogCreator(IN const char* FilePath, IN int Mode)
{
	m_LogFile.open(FilePath, Mode);
	if (!m_LogFile.is_open())
		fprintf_s(stderr, "<<< [ %s %s ] Create log file failed.\n", __DATE__, __TIME__);

	m_LogFile << "****************************************** " << __DATE__ << __TIME__ << " Log file start here *******************************************" << endl;
	m_LogFile << "********************************************************************************************************************************" << endl << endl;
}

LogCreator::~LogCreator()
{
	m_LogFile << "\n\n****************************************** " << __DATE__ << __TIME__ << " Log file end here *******************************************" << endl;
	m_LogFile << "********************************************************************************************************************************" << endl << endl;
}

size_t LogCreator::StyledWriteLog(IN const char* _Format, ...)
{
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return 0;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
	return StyledLog.length();
}

size_t LogCreator::WriteLog(IN const char* _Format, ...)
{
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return 0;

	m_LogFile << res;
	return strlen(res);
}

char* LogCreator::_writeLog(IN const char* _Format, IN va_list ap)
{
	memset(m_Buffer, 0, LOG_BUFFER_SIZE);
	int ret = vsprintf_s(m_Buffer, _Format, ap);
	if (ret < 0 || ret >= LOG_BUFFER_SIZE)
	{
		return nullptr;
	}

	return m_Buffer;
}

void LogCreator::createFile(IN const string& FilePath)
{
	char* pcSubDir = NULL;
	char* pcLast = NULL;
	char szSeps[] = "\\/";    /* 目录分隔符 */
	std::string strCurrDir;   /* 保存当前需创建目录的全路径名称 */
	struct _stat stStat = { 0 };

	/* strtok操作对象不能为 const CHAR* 类型，因此需另存输入目录 */
	unsigned long ulLen = FilePath.length() + 1;
	char* pcFullDir = (char*)malloc(ulLen);
	if (NULL == pcFullDir)
	{
		return;
	}
	memset((void*)pcFullDir, 0, ulLen);
	strncpy_s(pcFullDir, ulLen, FilePath.c_str(), ulLen - 1);

	/* 逐层解析目录名称 */
	pcSubDir = strtok_s(pcFullDir, szSeps, &pcLast);
	while (NULL != pcSubDir)
	{
		strCurrDir += pcSubDir;

		/* Windows系统盘符必须为“C:\”形式才能stat操作成功。linux目录名称允许出现“:” */
		std::string strTmpDir = strCurrDir;
		if (':' == strTmpDir[strTmpDir.length() - 1])
		{
			strTmpDir += "/";
		}

		/* 如该级目录已存在，则进行创建下一级目录 */
		memset((void*)&stStat, 0, sizeof(struct _stat));
		if ((0 == _stat(strTmpDir.c_str(), &stStat)) &&
			(stStat.st_mode & S_IFDIR))
		{
			strCurrDir += "/";
			pcSubDir = strtok_s(NULL, szSeps, &pcLast);
			continue;
		}

		/* 创建子目录 */
		if (0 != _mkdir(strCurrDir.c_str()))
		{
			free((void*)pcFullDir);
			return;
		}

		/* 继续解析下一级目录名称 */
		strCurrDir += "/";
		pcSubDir = strtok_s(NULL, szSeps, &pcLast);
	}

	free((void*)pcFullDir);
	return;
}

void LogCreator::createFile(IN const char* _FilePath)
{
	string FilePath = _FilePath;
	char* pcSubDir = NULL;
	char* pcLast = NULL;
	char szSeps[] = "\\/";    /* 目录分隔符 */
	std::string strCurrDir;   /* 保存当前需创建目录的全路径名称 */
	struct _stat stStat = { 0 };

	/* strtok操作对象不能为 const CHAR* 类型，因此需另存输入目录 */
	unsigned long ulLen = FilePath.length() + 1;
	char* pcFullDir = (char*)malloc(ulLen);
	if (NULL == pcFullDir)
	{
		return;
	}
	memset((void*)pcFullDir, 0, ulLen);
	strncpy_s(pcFullDir, ulLen, FilePath.c_str(), ulLen - 1);

	/* 逐层解析目录名称 */
	pcSubDir = strtok_s(pcFullDir, szSeps, &pcLast);
	while (NULL != pcSubDir)
	{
		strCurrDir += pcSubDir;

		/* Windows系统盘符必须为“C:\”形式才能stat操作成功。linux目录名称允许出现“:” */
		std::string strTmpDir = strCurrDir;
		if (':' == strTmpDir[strTmpDir.length() - 1])
		{
			strTmpDir += "/";
		}

		/* 如该级目录已存在，则进行创建下一级目录 */
		memset((void*)&stStat, 0, sizeof(struct _stat));
		if ((0 == _stat(strTmpDir.c_str(), &stStat)) &&
			(stStat.st_mode & S_IFDIR))
		{
			strCurrDir += "/";
			pcSubDir = strtok_s(NULL, szSeps, &pcLast);
			continue;
		}

		/* 创建子目录 */
		if (0 != _mkdir(strCurrDir.c_str()))
		{
			free((void*)pcFullDir);
			return;
		}

		/* 继续解析下一级目录名称 */
		strCurrDir += "/";
		pcSubDir = strtok_s(NULL, szSeps, &pcLast);
	}

	free((void*)pcFullDir);
	return;
}

void LogCreator::FatalLog(const char* _Format, ...)
{
	LogLevel level = LogLevel::FATAL;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ FATAL ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::ErrorLog(const char* _Format, ...)
{
	LogLevel level = (LogLevel)1;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ ERROR ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::WarnLog(const char* _Format, ...)
{
	LogLevel level = LogLevel::WARN;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ WARN ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::InfoLog(const char* _Format, ...)
{
	LogLevel level = LogLevel::INFO;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ INFO ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::DebugLog(const char* _Format, ...)
{
	LogLevel level = LogLevel::DEBUG;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ DEBUG ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::AllLog(const char* _Format, ...)
{
	LogLevel level = LogLevel::ALL;
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ ALL ] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}

void LogCreator::CustomLog(IN const char* _Format, IN CustLog customLog, ...)
{
	va_list ap;
	char* res = nullptr;
	va_start(ap, _Format);
	res = _writeLog(_Format, ap);
	va_end(ap);

	if (res == nullptr)
		return;

	string _str1 = "<<< [ ";
	string _date = __DATE__;
	string _time = __TIME__;
	string _str2 = " ] [ " + customLog.level + "] ";
	string _str3 = res;

	string StyledLog = _str1 + _date + " " + _time + _str2 + _str3;
	m_LogFile << StyledLog;
}