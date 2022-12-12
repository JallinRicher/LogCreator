/*****************************************************************//**
 * \file   MacroDefines.h
 * \brief  Chinese: 宏定义
 * \brief  English: Macro defines.
 * 
 * \author JallinRichel(Rundong Li)
 * \date   November 2022
 *********************************************************************/

#pragma once

#define IN
#define OUT
#define CLASS_API

#define BASE_CLASS
#define INTERFACE_CLASS
#define INHERITED_CLASS
#define ABSTRACT_CLASS

#define PUBLIC_FUNCTION
#define PRIVATE_FUNCTION
#define OPERATOR_OVERRIDE
#define INLINE_FUNCTION
#define STATIC_FUNCTION
#define STATIC_MEMBER_FUNCTION
#define OVERRIDE_FUNCTION
#define CONST_FUNCTION
#define CONST_MEMBER_FUNCTION
#define EXPLICIT_FUNCTION
#define VIRTUAL_FUNCTION
#define PURE_VIRTUAL_FUNCTION
#define MEMBER_FUNCTION
#define GLOBAL_FUNCTION

#define MAX_LINE_LENGTH		1024
#define LOG_BUFFER_SIZE		1024

#define FATAL		"FATAL"		// 致命错误，可能导致程序运行终止
#define ERROR		"ERROR"		// 致命错误，程序可能可以继续运行
#define WARN		"WARN"		// 警告，存在潜在危险
#define INFO		"INFO"		// 程序运行过程信息
#define DEBUG		"DEBUG"		// 调试信息
#define NORMAL		"NORMAL"	// 一般信息