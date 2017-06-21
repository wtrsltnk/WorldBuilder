#include "funclib.h"

string trim( string input )
{
	string result;
	int i = 0;
	while ( input[ i ] == '\"' )
	{
		i++;
	}

	while ( input[ i ] != '\"' )
	{
		result += input[ i ];
		i++;
	}
	return result;
}

void msgError( string text, HWND hParent )
{
	MessageBox( hParent, text.c_str(), "Error:", MB_OK |MB_ICONEXCLAMATION );
}

UINT msgConfirm( string text, HWND hParent )
{
	return MessageBox( hParent, text.c_str(), "Confirm:", MB_YESNOCANCEL | MB_ICONEXCLAMATION );
}

void msgNotify( string text, HWND hParent )
{
	MessageBox( hParent, text.c_str(), "Notify:", MB_OK | MB_ICONINFORMATION );
}
