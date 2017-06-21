#include "COpenSaveDlg.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

COpenSaveDlg::COpenSaveDlg( HINSTANCE hInstance, HWND hWnd )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;
}

COpenSaveDlg::~COpenSaveDlg( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

string COpenSaveDlg::open( char *title, char *szFilter, char *szDefExt )
{
	string result;
	string bla;
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = title;
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	//open de dialoog
	if( GetOpenFileName( &ofn ) != 0 )
	{
		for ( int i = 0; i < strlen(ofn.lpstrFile); i++ )
			result += ofn.lpstrFile[i];
		return result;
	}

	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}

string COpenSaveDlg::save( char *title, char *szFilter, char *szDefExt )
{
	OPENFILENAME ofn = {0};
	char szFile[MAX_PATH+1] =	{0};
	
	//specificeer de dialog box zo volledig mogelijk
	ofn.Flags             = OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT;
	ofn.hwndOwner         = m_hOwner;
	ofn.lpstrCustomFilter = 0;
	ofn.lpstrFile         = szFile;
	ofn.lpstrFileTitle    = 0;
	ofn.lpstrFilter       = szFilter;
	ofn.lpstrDefExt		  = szDefExt;
	ofn.lpstrInitialDir   = 0;
	ofn.lpstrTitle        = title;
	ofn.lStructSize       = sizeof( OPENFILENAME );
	ofn.nMaxFile          = MAX_PATH;


	//open de dialoog
	if( GetSaveFileName( &ofn ) != 0 )
		return ofn.lpstrFile;

	//als het openen van de dialoog niet gelukt is, geeft een lege string terug
	return "";
}
