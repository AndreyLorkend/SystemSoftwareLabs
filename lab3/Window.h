#pragma once
#include <windows.h>
#include <string>

class Window
{
public:
	virtual void printArray(COORD outCoord) = 0;
	virtual void fillArray() = 0;
	virtual HANDLE getHandleStdOut() = 0;
	virtual void setExitFlag(bool flag) = 0;
	virtual void handleArrayData(COORD outCoord) = 0;
	virtual void runProgram(std::string fileName) = 0;
	virtual ~Window();
};

