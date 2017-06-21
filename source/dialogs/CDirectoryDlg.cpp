#include "CDirectoryDlg.h"
#include <tchar.h>

string CDirectoryDlg::result = "";

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CDirectoryDlg::CDirectoryDlg( HINSTANCE hInstance, HWND hWnd )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;

}

CDirectoryDlg::~CDirectoryDlg( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CDirectoryDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	char *szBuff;
	DWORD cchCurDir; 
    LPTSTR lpszCurDir; 
    TCHAR tchBuffer[BUFFER]; 
 

	switch(uMsg)
	{
	case WM_INITDIALOG: 

		// Initialize the list box by filling it with files from 
		// the current directory. 

		lpszCurDir = tchBuffer; 
		GetCurrentDirectory(cchCurDir, lpszCurDir); 
		DlgDirList(hDlg, lpszCurDir, IDC_LIST_DIR, IDS_PATHTOFILL, 0); 
		SetFocus(GetDlgItem(hDlg, IDC_LIST_DIR)); 
		break;
	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
  		case IDOK:
			szBuff = new char;
			//GetDlgItemText( hDlg, IDC_EDIT_NAME, szBuff, 255 );
			result = szBuff;
  		case IDCANCEL:
			EndDialog( hDlg, IDCANCEL );
			break;
		}
		break;
	}
	return FALSE;
}

string CDirectoryDlg::show( void )
{
	DialogBox( m_hInstance, MAKEINTRESOURCE( IDD_DIRECTORY ), m_hOwner, (DLGPROC)DlgProc );

	ShowWindow( m_hWnd, SW_SHOWNORMAL );

	return result;
}

bool CDirectoryDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
