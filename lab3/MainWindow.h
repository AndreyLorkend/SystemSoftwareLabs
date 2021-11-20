#pragma once
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include "Window.h"
#include "WinBox.h"
#include "Button.h"
#include "TextBox.h"
#include <time.h>
#include <map>

#define ARR_LENGTH 20
#define INPUT_RECORD_BUFFER 128

extern "C" {
	int findNegativeCount(int length, int* array);
	int findPositiveArithmeticMean(int length, int* array);
}

class MainWindow : public Window
{
private:
	std::map<std::string, WinBox*> winBoxes;
	std::map<std::string, DWORD> processMap;
	int arr[ARR_LENGTH];
	HANDLE hStdin;
	HANDLE hStdout;
	DWORD fdwSaveOldMode;
	DWORD fdwMode;
	INPUT_RECORD irInBuf[INPUT_RECORD_BUFFER];
	bool isExitFlagSet;
private:
	void fillArray();
	VOID MouseEventProc(MOUSE_EVENT_RECORD mer);
	VOID SetConsoleAppearance(WORD wAttributes);
	VOID DrawInterface();
	void handleConsole();
	bool SetConsoleParams();
	bool ErrorExit(LPSTR lpszMessage);
	void CreateElements();
	VOID KeyEventProc(KEY_EVENT_RECORD ker);
public:
	HANDLE getHandleStdOut();
	MainWindow();
	void setExitFlag(bool flag);
	void printArray(COORD textCoord);
	void handleArrayData(COORD outCoord);
	void Show();
	void runProgram(std::string fileName, std::string processName);
	bool isProcessExits(std::string processName);
};

