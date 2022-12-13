#pragma once
#include "LogCreator.h"

string LogFilePath;
#define MAKE_LOG_FLODER(Path) LogCreator::createFolder(Path)
#define MAKE_LOG_FILE(FilePath){LogFilePath = FilePath}
LogCreator log(LogFilePath);

#define LOG(Level, _Format, ...){}
