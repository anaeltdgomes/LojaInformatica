#pragma once
#include "framework.h"

extern RECT mainWindowRec;  // Possibilita a variável ser usada em outros arquivos
extern int contadorVendas;

// Protótipo das funções
void __stdcall hideWindow(HWND hwnd);

void __stdcall translate(HWND window, int moveX, int moveY, int widthPlus, int heightPlus);

void __stdcall centralize(HWND window);

int __stdcall returnWidth(HWND window);

int __stdcall returnHeight(HWND window);

int __stdcall returnPosX(HWND window);

int __stdcall returnPosY(HWND window);

void __stdcall showEmployee(ListView& lisViewObj, int numActive);

char __stdcall addEmployeeFunction(HWND hwnd, string textEmployeeEdit, string textEmployeeSexEdit, string textEmployeeAgeEdit,
    string textEmployeeJobEdit, string textEmployeeSalaryEdit, string textEmployeeAdmissionEdit);

void __stdcall showProduct(ListView& listViewObj, const char* brand);

void __stdcall showVendas(ListView& listViewObj);

int __stdcall showVendas(int num, Label& labelObj1, Label& labelObj2, Label& labelObj3, Label& labelObj4, Label& labelObj5, Label& labelObj6, Label& labelObj7);