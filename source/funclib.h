#ifndef FUNCLIB_H
#define FUNCLIB_H

#include <windows.h>
#include <string>
using namespace std;

string trim( string );
void msgError( string, HWND );
UINT msgConfirm( string, HWND );
void msgNotify( string, HWND );

#endif