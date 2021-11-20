#pragma once
#include "WinElement.h"

enum BtnOnClickEvent
{
	SHOW_DATA,
	CLOSE,
	FILL_ARRAY,
	HANDLE_DATA
};

class Button : public WinElement
{
private:
	BtnOnClickEvent event_;
private:
	bool checkTouch(MOUSE_EVENT_RECORD& mer);
public:
	void writeOutText(HANDLE& hStdout);
	void addTextAttribute(std::list<CHAR*>& text);
	void handleType(WinElementType type);
	void drawElement(HANDLE& hStdout);
	//events
	void onClick(MOUSE_EVENT_RECORD& mer, Window* Sender);
	//constructors
	Button(COORD btnPos, int padding, LPCSTR btnText, BtnOnClickEvent ev);
	Button(int padding, LPCSTR btnText, BtnOnClickEvent ev);
};

