#include "Button.h"

bool Button::checkTouch(MOUSE_EVENT_RECORD& mer)
{
	SHORT mX = mer.dwMousePosition.X;
	SHORT mY = mer.dwMousePosition.Y;
	bool isTouched = false;
	if ( (mX >= getElementBox().Left && mX <= getElementBox().Right-1) &&
		(mY >= getElementBox().Top && mY <= getElementBox().Bottom-1) )
	{
		isTouched = true;
	}
	return isTouched;
}

void Button::onClick(MOUSE_EVENT_RECORD& mer, Window* sender)
{
	if (checkTouch(mer)) {
		switch (event_)
		{
		case C_C:
			if (!sender->isProcessExits("C-C")) {
				sender->runProgram("../C_to_C/lab1.exe", "C-C");
			}
			break;
		case C_ASM:
			if (!sender->isProcessExits("C-ASM")) {
				sender->runProgram("../C_to_Asm/lab1.exe", "C-ASM");
			}
			break;
		case ASM_C:
			sender->runProgram("../Asm_to_C/lab1.exe", "ASM-C");
			break;
		case ASM_ASM:
			sender->runProgram("../Asm_to_Asm/lab1.exe", "ASM-ASM");
			break;
		case LAB_2:
			sender->runProgram("../Release/lab2.exe", "LAB-2");
			break;
		case CLOSE:
			sender->setExitFlag(true);
			break;
		default:
			break;
		}
	}
}

void Button::onKbClick(KEY_EVENT_RECORD& ker, Window* sender)
{
	//if (ker.wVirtualKeyCode == key_) {
	//	switch (ker.wVirtualKeyCode)
	//	{
	//	case FIRST:
	//		sender->runProgram("../C_to_C/lab1.exe");
	//		break;
	//	case SECOND:
	//		sender->runProgram("../C_to_Asm/lab1.exe");
	//		break;
	//	case THIRD:
	//		sender->runProgram("../Asm_to_C/lab1.exe");
	//		break;
	//	case FOURTH:
	//		sender->runProgram("../Asm_to_Asm/lab1.exe");
	//		break;
	//	case FIFTH:
	//		sender->runProgram("../Release/lab2.exe");
	//		break;
	//	case SIXTH:
	//		sender->setExitFlag(true);
	//	default:
	//		break;
	//	}
	//}
}

void Button::writeOutText(HANDLE& hStdout)
{
}

void Button::addTextAttribute(std::list<CHAR*>& text)
{
}

void Button::handleType(WinElementType type)
{
}

void Button::drawElement(HANDLE& hStdout)
{
	DWORD cWritten;
	SMALL_RECT btnBox(getElementBox().Left, getElementBox().Top, getElementBox().Right, getElementBox().Bottom);
	COORD curCoord(btnBox.Left, btnBox.Top);
	WORD textColor = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
	WORD bgColor = BACKGROUND_RED | BACKGROUND_INTENSITY;
	for (int i = btnBox.Top; i < btnBox.Bottom; i++) {
		FillConsoleOutputCharacterA(hStdout, ' ', btnBox.Right-btnBox.Left, curCoord, &cWritten);
		FillConsoleOutputAttribute(hStdout, textColor | bgColor, btnBox.Right-btnBox.Left, curCoord, &cWritten);
		curCoord.Y++;
	}
	COORD textCoord(btnBox.Left + getPadding(), (btnBox.Top + btnBox.Bottom) / 2);
	WriteConsoleOutputCharacterA(hStdout, getElementText(), lstrlenA(getElementText()), textCoord, &cWritten);
}

Button::Button(COORD btnPos, int padding, LPCSTR btnText, BtnOnClickEvent ev) : 
	WinElement(btnPos, padding, btnText, BUTTON_ELEMENT)
{
	event_ = ev;
}

Button::Button(int padding, LPCSTR btnText, BtnOnClickEvent ev, ButtonKeyboardKey key) : 
	WinElement(btnText, padding, BUTTON_ELEMENT)
{
	event_ = ev;
	key_ = key;
}
