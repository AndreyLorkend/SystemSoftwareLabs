#pragma once
#include "WinElement.h"

enum BtnOnClickEvent
{
	C_C,
	C_ASM,
	ASM_C,
	ASM_ASM,
	LAB_2,
	CLOSE
};

enum ButtonKeyboardKey {
	FIRST = 49,
	SECOND,
	THIRD,
	FOURTH,
	FIFTH,
	SIXTH
};

class Button : public WinElement
{
private:
	BtnOnClickEvent event_;
private:
	bool checkTouch(MOUSE_EVENT_RECORD& mer);
	ButtonKeyboardKey key_;
public:
	void writeOutText(HANDLE& hStdout);
	void addTextAttribute(std::list<CHAR*>& text);
	void handleType(WinElementType type);
	void drawElement(HANDLE& hStdout);
	//events
	void onClick(MOUSE_EVENT_RECORD& mer, Window* Sender);
	void onKbClick(KEY_EVENT_RECORD& ker, Window* sender);
	//constructors
	Button(COORD btnPos, int padding, LPCSTR btnText, BtnOnClickEvent ev);
	Button(int padding, LPCSTR btnText, BtnOnClickEvent ev, ButtonKeyboardKey key);
};

