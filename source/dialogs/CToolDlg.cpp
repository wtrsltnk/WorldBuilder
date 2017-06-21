#include "CToolDlg.h"

bool CToolDlg::nieuw = true;
string  CToolDlg::m_sgr;
string CToolDlg::m_stl;
CTool *CToolDlg::m_tl = NULL;
CGroupManager *CToolDlg::m_pGroupManager = NULL;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CToolDlg::CToolDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager )
{
	this->m_hOwner		= hOwner;
	this->m_hInstance	= hInstance;
	this->m_pGroupManager = pGroupManager;

	m_hWnd = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_TOOL ), m_hOwner, (DLGPROC)DlgProc );
}

CToolDlg::~CToolDlg( void )
{
	DestroyWindow( m_hWnd );
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CToolDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch(uMsg)
	{
		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
  			case IDOK:
				if ( nieuw )
				{
					savedata( hDlg );
					m_pGroupManager->addGrTool( m_sgr, m_tl );
				}
				else
				{
					savedata( hDlg );
				}
				SendMessage( GetParent( hDlg ), WM_UPDATE, 0, 0 );
  			case IDCANCEL:
				EndDialog( hDlg, IDCANCEL );
				break;
			}
			break;
	}
	return FALSE;
}

void CToolDlg::show( string group,string tool, bool nieuw )
{
	this->m_sgr = group;
	this->m_stl = tool;
	this->nieuw = nieuw;

	ShowWindow( m_hWnd, SW_SHOWNORMAL );
	SendMessage( GetDlgItem( m_hWnd, IDC_EDIT_NAME ), EM_SETREADONLY, !nieuw, 0 );

	clearData();
	if ( nieuw )
	{
		m_tl = new CTool();
	}
	else
	{
		m_tl = m_pGroupManager->getGrTool( group, tool );
		showdata();
	}

}

void CToolDlg::clearData( void )
{
	SetDlgItemText( m_hWnd, IDC_EDIT_NAME, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_CALL, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, "" );
	SendMessage( GetDlgItem( m_hWnd, IDC_CHECK_RUN ), BM_SETCHECK, BST_UNCHECKED, 0 );
}

void CToolDlg::showdata( void )
{
	if ( m_tl != NULL )
	{
		SetDlgItemText( m_hWnd, IDC_EDIT_NAME, m_tl->getName().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_CALL, m_tl->getCall().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, m_tl->getDescription().c_str() );

		if ( m_tl->isRun() )
		{
			SendMessage( GetDlgItem( m_hWnd, IDC_CHECK_RUN ), BM_SETCHECK, BST_CHECKED, 0 );
		}
		else
		{
			SendMessage( GetDlgItem( m_hWnd, IDC_CHECK_RUN ), BM_SETCHECK, BST_UNCHECKED, 0 );
		}
	}
}

void CToolDlg::savedata( HWND hDlg )
{
	char szBuff[255];

	if ( m_tl != NULL )
	{
		GetDlgItemText( hDlg, IDC_EDIT_NAME, szBuff, 255 );
		m_tl->setName( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_CALL, szBuff, 255 );
		m_tl->setCall( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_DESCRIPTION, szBuff, 255 );
		m_tl->setDescription( szBuff );

		m_tl->setRun( SendMessage( GetDlgItem( hDlg, IDC_CHECK_RUN ), BM_GETCHECK, 0, 0 ) == BST_CHECKED );
	}
}

bool CToolDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
