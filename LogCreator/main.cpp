#include "LogCreator.h"

int main(int argc, char** argv)
{
	LogCreator::createFolder("./Log");
	LogCreator log("./Log/log.log");
	log.WriteLog(NORMAL, "System info");
	log.WriteLog(DEBUG, "Debug info");
	log.WriteLog(FATAL, "Fatal error");
}