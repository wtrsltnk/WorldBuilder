#include "CNewNameDlg.h"

string CNewNameDlg::result = "";

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CNewNameDlg::CNewNameDlg( HINSTANCE hInstance, HWND hWnd )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;

}

CNewNameDlg::~CNewNameDlg( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CNewNameDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	char *szBuff;
	switch(uMsg)
	{
		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
  			case IDOK:
				szBuff = new char;
				GetDlgItemText( hDlg, IDC_EDIT_NAME, szBuff, 255 );
				result = szBuff;
  			case IDCANCEL:
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;
	}
	return FALSE;
}

string CNewNameDlg::show( void )
{
	DialogBox( m_hInstance, MAKEINTRESOURCE( IDD_NEWNAME ), m_hOwner, (DLGPROC)DlgProc );

	ShowWindow( m_hWnd, SW_SHOWNORMAL );

	return result;
}

bool CNewNameDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
