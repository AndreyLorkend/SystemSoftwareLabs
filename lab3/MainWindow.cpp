#include "MainWindow.h"

void MainWindow::fillArray()
{
    srand(time(0));
    for (int i = 0; i < ARR_LENGTH; i++) {
        arr[i] = rand() % 21 - 10;
    }
}

MainWindow::MainWindow()
{
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    isExitFlagSet = false;
    fdwMode = 0;
}

void MainWindow::printArray(COORD outCoord)
{
    DWORD cWritten = 0;
    std::string outText;
    std::list<CHAR*>textLines;
    char txt[10];
    for (int i = 0; i < ARR_LENGTH; i++) {
        wsprintf(txt, "  %d", arr[i]);
        outText.append(txt);
    }

    textLines.push_back(outText.data());

    for (auto& [key, value] : winBoxes) {
        value->handleWinElement("INITIAL_DATA", TEXT_BOX_ELEMENT, textLines, hStdout);
    }
}

VOID MainWindow::MouseEventProc(MOUSE_EVENT_RECORD mer)
{
    switch (mer.dwEventFlags)
    {
    case 0:
        if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
        {
            for (auto &[key, value] : winBoxes) {
                value->checkClick(mer, this);
            }
        }
        break;
    default:
        break;
    }
}

VOID MainWindow::SetConsoleAppearance(WORD wAttributes)
{
    CONSOLE_SCREEN_BUFFER_INFO csbiScreenInfo;
    COORD coordStart = { 0, 0 };
    DWORD dwNumWritten = 0;
    DWORD dwScrSize;

    if (!GetConsoleScreenBufferInfo(hStdout, &csbiScreenInfo))
        ErrorExit((LPSTR)"GetConsoleScreenBufferInfo");
    dwScrSize = csbiScreenInfo.dwMaximumWindowSize.X * csbiScreenInfo.dwMaximumWindowSize.Y;
    FillConsoleOutputAttribute(hStdout, wAttributes, dwScrSize, coordStart, &dwNumWritten);
    SetConsoleTextAttribute(hStdout, wAttributes);
}

VOID MainWindow::DrawInterface()
{
    // Adding LEGEND
    std::list<CHAR*> textLines;
    CHAR outText1[64];

    wsprintf(outText1, "Program by Andrew Derendyaev");
    textLines.push_back(outText1);

    // Drawing another elements
    for (auto& [key, value] : winBoxes) {
        value->drawElements(hStdout);
    }

    for (auto& [key, value] : winBoxes) {
        value->handleWinElement("LEGEND", TEXT_BOX_ELEMENT, textLines, hStdout);
    }

    textLines.clear();
}

void MainWindow::handleConsole()
{
    DWORD cNumRead = 0;
    while (!isExitFlagSet) {
        if (!ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead)) {
            ErrorExit((LPSTR)"ReadConsoleInput");
        }

        for (int i = 0; i < cNumRead; i++)
        {
            switch (irInBuf[i].EventType)
            {
            case MOUSE_EVENT: // mouse input
                MouseEventProc(irInBuf[i].Event.MouseEvent);
                break;
            case KEY_EVENT: // keyboard input
                KeyEventProc(irInBuf[i].Event.KeyEvent);
                break;
            default:
                break;
            }
        }
    }
}

bool MainWindow::SetConsoleParams()
{
    bool errorFlag = false;
    WORD attr = BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;
    SetConsoleAppearance(attr);

    if (hStdin == INVALID_HANDLE_VALUE) {
        errorFlag = ErrorExit((LPSTR)"GetStdHandle");
    }

    if (!GetConsoleMode(hStdin, &fdwSaveOldMode)) {
        errorFlag = ErrorExit((LPSTR)"GetConsoleMode");
    }

    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode)) {
        errorFlag = ErrorExit((LPSTR)"SetConsoleMode");
    }

    return errorFlag;
}

bool MainWindow::ErrorExit(LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);
    SetConsoleMode(hStdin, fdwSaveOldMode);
    return true;
}

void MainWindow::handleArrayData(COORD outCoord)
{
    std::list<CHAR*> textLines;
    CHAR outText1[32];
    CHAR outText2[32];

    wsprintf(outText1, "Negative numbers count: %d", findNegativeCount(ARR_LENGTH, arr));
    textLines.push_back(outText1);

    wsprintf(outText2, "Positive avrage arithmetic: %d", findPositiveArithmeticMean(ARR_LENGTH, arr));
    textLines.push_back(outText2);


    WinElement* element;
    for (auto& [key, value] : winBoxes) {
        value->handleWinElement("HANDLED_DATA", TEXT_BOX_ELEMENT, textLines, hStdout);
    }
    textLines.clear();
}

void MainWindow::Show()
{
    if (!SetConsoleParams()) {
        CreateElements();
        DrawInterface();
        handleConsole();
    }

    SetConsoleMode(hStdin, fdwSaveOldMode);
    system("cls");
}

void MainWindow::runProgram(std::string fileName)
{
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    PROCESS_INFORMATION pi;

    if (!CreateProcess(
        NULL,   // No module name (use command line)
        (LPSTR)fileName.data(),        // Command line
        NULL,           // Process handle not inheritable
        NULL,           // Thread handle not inheritable
        FALSE,          // Set handle inheritance to FALSE
        CREATE_NEW_CONSOLE,              // No creation flags
        NULL,           // Use parent's environment block
        NULL,           // Use parent's starting directory 
        &si,            // Pointer to STARTUPINFO structure. Стиль окна
        &pi)           // Pointer to PROCESS_INFORMATION structure. 
        )
    {
        printf("CreateProcess failed (%d).\n", GetLastError());
        return;
    }
    printf("s");
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

VOID MainWindow::KeyEventProc(KEY_EVENT_RECORD ker)
{
    for (auto& [key, value] : winBoxes) {
        value->checkKbHit(ker, this);
    }
}

HANDLE MainWindow::getHandleStdOut()
{
    return hStdout;
}

void MainWindow::setExitFlag(bool flag)
{
    isExitFlagSet = flag;
}

void MainWindow::CreateElements()
{
    //TEXT_BOX_1
    winBoxes.insert(std::pair<std::string, WinBox*>("TEXT_BOX_1", new WinBox(COORD(1, 1))));
    winBoxes["TEXT_BOX_1"]->addElementWidthVerticalAlignment(new TextBox(4, 117, "|Legend|", LEGEND));
    //TEXT_BOX_2
    winBoxes.insert(std::pair<std::string, WinBox*>("TEXT_BOX_2", new WinBox(COORD(1, 1))));
    winBoxes["TEXT_BOX_1"]->addElementWidthVerticalAlignment(new TextBox(4, 117, "|Process status|", INITIAL_DATA));
    //BUTTON_BOX_1
    winBoxes.insert(std::pair<std::string, WinBox*>("BUTTON_BOX_1", new WinBox(COORD(1, 1))));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "C-C", C_C, FIRST));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "C-Asm", C_ASM, SECOND));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "Asm-C", ASM_C, THIRD));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "Asm-Asm", ASM_ASM, FOURTH));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "Lab2", LAB_2, FIFTH));
    winBoxes["BUTTON_BOX_1"]->addElementWidthHorizontalAlignment(new Button(1, "Close", CLOSE, SIXTH));
}
