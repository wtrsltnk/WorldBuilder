#include "CNewDlg.h"

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CNewDlg::CNewDlg( HINSTANCE hInstance, HWND hWnd )
{
	this->m_hOwner		= hWnd;
	this->m_hInstance	= hInstance;

	m_hWnd = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_NEW ), m_hOwner, (DLGPROC)DlgProc );

	SendMessage( GetDlgItem( m_hWnd, IDC_LIST_TYPE), LB_ADDSTRING, 0, LPARAM("Group..."));
	SendMessage( GetDlgItem( m_hWnd, IDC_LIST_TYPE), LB_ADDSTRING, 1, LPARAM("Tool..."));
	SendMessage( GetDlgItem( m_hWnd, IDC_LIST_TYPE), LB_ADDSTRING, 2, LPARAM("Command..."));
}

CNewDlg::~CNewDlg( void )
{
	DestroyWindow( m_hWnd );
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CNewDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	char szBuffer[255];

	switch( uMsg )
	{
		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
  			case IDOK:
				switch ( SendMessage( GetDlgItem( hDlg, IDC_LIST_TYPE ), LB_GETCURSEL , 0, 0 ) )
				{
				case 0:
					EndDialog( hDlg, IDCANCEL );
					SendMessage( GetParent( hDlg ), WM_NEW_ITEM, (WPARAM)NEW_TYPE_GR, 0 );
					break;
				case 1:
					EndDialog( hDlg, IDCANCEL );
					SendMessage( GetParent( hDlg ), WM_NEW_ITEM, (WPARAM)NEW_TYPE_TL, 0 );
					break;
				case 2:
					EndDialog( hDlg, IDCANCEL );
					SendMessage( GetParent( hDlg ), WM_NEW_ITEM, (WPARAM)NEW_TYPE_CMD, 0 );
					break;
				default:
					LoadString( GetModuleHandle(NULL), IDS_DLG_NOSELECT, szBuffer, 255 );
					MessageBox( hDlg, szBuffer, "Error:", MB_OK | MB_ICONEXCLAMATION );
					break;
				}
				break;
  			case IDCANCEL:
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;
	}
	return FALSE;
}

void CNewDlg::show( void )
{
	ShowWindow( m_hWnd, SW_SHOWNORMAL );
}

bool CNewDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
