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

	m_Buffer[ret] = '\n';
	if (ret <= LOG_BUFFER_SIZE - 2)
		m_Buffer[ret + 1] = '\0';
	else
	{
		m_strBuffer.clear();
		m_strBuffer = m_Buffer + '\0';
		return const_cast<char*>(m_strBuffer.c_str());
	}
	return m_Buffer;
}

void LogCreator::CreateFile(IN const string& FilePath)
{
	char* pcSubDir = NULL;
	char* pcLast = NULL;
	char szSeps[] = "\\/";    /* Ŀ¼�ָ��� */
	std::string strCurrDir;   /* ���浱ǰ�贴��Ŀ¼��ȫ·������ */
	struct _stat stStat = { 0 };

	/* strtok����������Ϊ const CHAR* ���ͣ��������������Ŀ¼ */
	unsigned long ulLen = FilePath.length() + 1;
	char* pcFullDir = (char*)malloc(ulLen);
	if (NULL == pcFullDir)
	{
		return;
	}
	memset((void*)pcFullDir, 0, ulLen);
	strncpy_s(pcFullDir, ulLen, FilePath.c_str(), ulLen - 1);

	/* ������Ŀ¼���� */
	pcSubDir = strtok_s(pcFullDir, szSeps, &pcLast);
	while (NULL != pcSubDir)
	{
		strCurrDir += pcSubDir;

		/* Windowsϵͳ�̷�����Ϊ��C:\����ʽ����stat�����ɹ���linuxĿ¼�����������֡�:�� */
		std::string strTmpDir = strCurrDir;
		if (':' == strTmpDir[strTmpDir.length() - 1])
		{
			strTmpDir += "/";
		}

		/* ��ü�Ŀ¼�Ѵ��ڣ�����д�����һ��Ŀ¼ */
		memset((void*)&stStat, 0, sizeof(struct _stat));
		if ((0 == _stat(strTmpDir.c_str(), &stStat)) &&
			(stStat.st_mode & S_IFDIR))
		{
			strCurrDir += "/";
			pcSubDir = strtok_s(NULL, szSeps, &pcLast);
			continue;
		}

		/* ������Ŀ¼ */
		if (0 != _mkdir(strCurrDir.c_str()))
		{
			free((void*)pcFullDir);
			return;
		}

		/* ����������һ��Ŀ¼���� */
		strCurrDir += "/";
		pcSubDir = strtok_s(NULL, szSeps, &pcLast);
	}

	free((void*)pcFullDir);
	return;
}

void LogCreator::CreateFile(IN const char* _FilePath)
{
	string FilePath = _FilePath;
	char* pcSubDir = NULL;
	char* pcLast = NULL;
	char szSeps[] = "\\/";    /* Ŀ¼�ָ��� */
	std::string strCurrDir;   /* ���浱ǰ�贴��Ŀ¼��ȫ·������ */
	struct _stat stStat = { 0 };

	/* strtok����������Ϊ const CHAR* ���ͣ��������������Ŀ¼ */
	unsigned long ulLen = FilePath.length() + 1;
	char* pcFullDir = (char*)malloc(ulLen);
	if (NULL == pcFullDir)
	{
		return;
	}
	memset((void*)pcFullDir, 0, ulLen);
	strncpy_s(pcFullDir, ulLen, FilePath.c_str(), ulLen - 1);

	/* ������Ŀ¼���� */
	pcSubDir = strtok_s(pcFullDir, szSeps, &pcLast);
	while (NULL != pcSubDir)
	{
		strCurrDir += pcSubDir;

		/* Windowsϵͳ�̷�����Ϊ��C:\����ʽ����stat�����ɹ���linuxĿ¼�����������֡�:�� */
		std::string strTmpDir = strCurrDir;
		if (':' == strTmpDir[strTmpDir.length() - 1])
		{
			strTmpDir += "/";
		}

		/* ��ü�Ŀ¼�Ѵ��ڣ�����д�����һ��Ŀ¼ */
		memset((void*)&stStat, 0, sizeof(struct _stat));
		if ((0 == _stat(strTmpDir.c_str(), &stStat)) &&
			(stStat.st_mode & S_IFDIR))
		{
			strCurrDir += "/";
			pcSubDir = strtok_s(NULL, szSeps, &pcLast);
			continue;
		}

		/* ������Ŀ¼ */
		if (0 != _mkdir(strCurrDir.c_str()))
		{
			free((void*)pcFullDir);
			return;
		}

		/* ����������һ��Ŀ¼���� */
		strCurrDir += "/";
		pcSubDir = strtok_s(NULL, szSeps, &pcLast);
	}

	free((void*)pcFullDir);
	return;
}