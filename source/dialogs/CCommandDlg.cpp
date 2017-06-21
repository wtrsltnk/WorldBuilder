#include "CCommandDlg.h"

bool CCommandDlg::nieuw = true;
string CCommandDlg::m_sgr;
string CCommandDlg::m_stl;
string CCommandDlg::m_scmd;
CCommand *CCommandDlg::m_cmd = new CCommand();
CGroupManager *CCommandDlg::m_pGroupManager = NULL;

/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////

CCommandDlg::CCommandDlg( HINSTANCE hInstance, HWND hOwner, CGroupManager *pGroupManager )
{
	this->m_hOwner		= hOwner;
	this->m_hInstance	= hInstance;
	this->m_pGroupManager = pGroupManager;


	m_hWnd = CreateDialog( m_hInstance, MAKEINTRESOURCE( IDD_COMMAND ), m_hOwner, (DLGPROC)DlgProc );
}

CCommandDlg::~CCommandDlg( void )
{
	DestroyWindow( m_hWnd );
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

BOOL CCommandDlg::DlgProc( HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
		case WM_COMMAND:
			switch( LOWORD(wParam) )
			{
  			case IDOK:
				if ( nieuw )
				{
					savedata( hDlg );
					if ( strcmp(m_stl.c_str(), "") != 0 )
					{
						m_pGroupManager->addTlCommand( m_sgr, m_stl, m_cmd );
					}
					else
					{
						m_pGroupManager->addGrGameCommand( m_sgr, m_cmd );
					}
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

void CCommandDlg::show( string group, string tool, string command, bool nieuw )
{
	this->m_sgr = group;
	this->m_stl = tool;
	this->m_scmd = command;
	this->nieuw = nieuw;

	ShowWindow( m_hWnd, SW_SHOWNORMAL );
	SendMessage( GetDlgItem( m_hWnd, IDC_EDIT_NAME ), EM_SETREADONLY, !nieuw, 0 );

	clearData();
	if ( nieuw )
	{
		m_cmd = new CCommand();
	}
	else
	{
		if ( strcmp(tool.c_str(), "") == 0 )
		{
			m_cmd = m_pGroupManager->getGrGameCommand( group, command );
		}
		else
		{
			m_cmd = m_pGroupManager->getTlCommand( group, tool, command );
		}
		showdata();
	}
}

void CCommandDlg::clearData( void )
{
	SetDlgItemText( m_hWnd, IDC_EDIT_NAME, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_CALL, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_VALUE, "" );
	SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, "" );
	SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_TEXT ), BM_SETCHECK, BST_CHECKED, 0 );
	SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_INT ), BM_SETCHECK, BST_UNCHECKED, 0 );
	SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_BOOL ), BM_SETCHECK, BST_UNCHECKED, 0 );
}

void CCommandDlg::showdata( void )
{
	if ( m_cmd != NULL )
	{
		SetDlgItemText( m_hWnd, IDC_EDIT_NAME, m_cmd->getName().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_CALL, m_cmd->getCall().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_VALUE, m_cmd->getValue().c_str() );
		SetDlgItemText( m_hWnd, IDC_EDIT_DESCRIPTION, m_cmd->getDescription().c_str() );
		switch ( m_cmd->getType() )
		{
		case 0:
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_TEXT ), BM_SETCHECK, BST_CHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_INT ), BM_SETCHECK, BST_UNCHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_BOOL ), BM_SETCHECK, BST_UNCHECKED, 0 );
			break;
		case 1:
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_TEXT ), BM_SETCHECK, BST_UNCHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_INT ), BM_SETCHECK, BST_CHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_BOOL ), BM_SETCHECK, BST_UNCHECKED, 0 );
			break;
		case 2:
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_TEXT ), BM_SETCHECK, BST_UNCHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_INT ), BM_SETCHECK, BST_UNCHECKED, 0 );
			SendMessage( GetDlgItem( m_hWnd, IDC_RADIO_BOOL ), BM_SETCHECK, BST_CHECKED, 0 );
			break;
		}
	}
}

void CCommandDlg::savedata( HWND hDlg )
{
	char szBuff[255];
	
	if ( m_cmd != NULL )
	{
		GetDlgItemText( hDlg, IDC_EDIT_NAME, szBuff, 255 );
		m_cmd->setName( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_CALL, szBuff, 255 );
		m_cmd->setCall( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_VALUE, szBuff, 255 );
		m_cmd->setValue( szBuff );

		GetDlgItemText( hDlg, IDC_EDIT_DESCRIPTION, szBuff, 255 );
		m_cmd->setDescription( szBuff );

		if ( SendMessage( GetDlgItem( hDlg, IDC_RADIO_TEXT ), BM_GETCHECK, 0, 0 ) == BST_CHECKED )
		{
			m_cmd->setType( 0 );
		}
		else if ( SendMessage( GetDlgItem( hDlg, IDC_RADIO_INT ), BM_GETCHECK, 0, 0 ) == BST_CHECKED )
		{
			m_cmd->setType( 1 );
		}
		else if ( SendMessage( GetDlgItem( hDlg, IDC_RADIO_BOOL ), BM_GETCHECK, 0, 0 ) == BST_CHECKED )
		{
			m_cmd->setType( 2 );
		}
	}
}

bool CCommandDlg::isDlg( void )
{
	if ( IsWindowVisible( m_hWnd ) == 1 )
		return true;
	return false;
}
