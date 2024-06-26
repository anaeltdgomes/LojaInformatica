#pragma once

#define WIN32_LEAN_AND_MEAN             // Excluir itens raramente utilizados dos cabeçalhos do Windows
// Arquivos de Cabeçalho do Windows
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <tchar.h>
#include <chrono>
#include <sstream>
#include <string>
#include <array>
#include "SQL/sqlite3.h"

using namespace std;
using std::stringstream;
using std::string;

#include "Delay.h"
#include "Control/AnyButton.h"
#include "Control/Button.h"
#include "Control/ComboBox.h"
#include "Control/EditBox.h"
#include "Control/ImageListManager.h"
#include "Control/Label.h"
#include "Control/ListView.h"
#include "Control/MonthCalendar.h"
#include "Control/Tab.h"
#include "Control/UpDownControl.h"


#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "Winmm.lib")



// Habilita estilos visuais modernos
#pragma comment(linker, "\"/manifestdependency:type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
