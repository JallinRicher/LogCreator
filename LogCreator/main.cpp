#include "LogCreator.h"

int main(int argc, char** argv)
{
	LogCreator::CreateFile("./Log");
	LogCreator log("./Log/log.txt");
	log.StyledWriteLog("This is Styled Log: Today is %s %s.\n", __DATE__, __TIME__);
	log.WriteLog("This is Generally Log: Today is %s %s.\n", __DATE__, __TIME__);
	log.WriteLog("This is Generally Log: Today is %s %s.This is Generally Log, This is Generally Log, This is Generally Log, This is Generally Log"
		"This is Generally Log, This is Generally Log, This is Generally Log, This is Generally Log, This is Generally Log", __DATE__, __TIME__);
}