#include "CCompileManager.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CCompileManager::CCompileManager( HINSTANCE hInstance, 
								   HWND hParent )
{
	this->m_hInstance = hInstance;
	this->m_hParent = hParent;
}

CCompileManager::~CCompileManager( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

bool CCompileManager::buildBatch( string filename, CGroup *gr ) throw()
{
	ofstream output;

	if ( gr != NULL )
	{
// CONTROLE
		if ( stricmp(filename.c_str(), "") == 0 )
		{
			throw( "No file name specified !\n" );
			return false;
		}

		output.open((const char *)filename.c_str());
		if (output.fail())
		{
			throw( "Couldn't open this file\n" );
			return false;
		}

// SCHRIJVEN
		output << "echo off\ncls\n";
		output << gr->getWadDrive().c_str() << "\n";

		for ( int i = 0; i < gr->getToolCount(); i++ )
		{
			output << "\"";
			output << gr->getBaseDir().c_str();
			output << "\\";
			output << gr->getTool( i )->getCall().c_str();
			output << "\"\n";
		}

		output << "echo Compile is done.\n\n";

		if ( gr->isGameRun() )
		{
			output << "\necho Starting " << gr->getGameName() << "...\npause\n";
			output << "\"" << gr->getGameDir() << "\"\n";
		}
		else
		{
			output << "pause\n";
		}
// DONE
	output.close();
	return true;
	}
	return false;
}

bool CCompileManager::startBatch( string filename )
{
	ShellExecute( NULL, "open", filename.c_str(), NULL, NULL, SW_SHOW );
	return true;
}

bool CCompileManager::startGame( CGroup *gr )
{
	strstream param;

	if ( gr != NULL )
	{
		for ( int i = 0; i < gr->getGameCmdCount(); i++ )
		{
			switch ( gr->getGameCommand( i )->getType() )
			{
			case TYPE_TEXT:
			case TYPE_INT:
				param << gr->getGameCommand( i )->getCall().c_str() << " " <<
					gr->getGameCommand( i )->getValue().c_str() << ends;
				break;
			case TYPE_BOOL:
				param << gr->getGameCommand( i )->getCall().c_str() << ends;
				break;
			}
		}
		HINSTANCE hResult = ShellExecute( NULL, "open", gr->getGameDir().c_str(), param.str(), NULL, SW_SHOW );
		if ( (UINT)hResult <= 32 )
		{
			switch ( (UINT)hResult )
			{
			case 0:
				msgError( "The operating system is out of memory or resources.", m_hParent );
				break;
			case ERROR_FILE_NOT_FOUND :
				msgError( "The specified file was not found.", m_hParent );
				break;
			case ERROR_PATH_NOT_FOUND :
				msgError( "The specified file was not found.", m_hParent );
				break;
			case ERROR_BAD_FORMAT :
				msgError( "The .exe file is invalid (non-Win32® .exe or error in .exe image).", m_hParent );
				break;
			case SE_ERR_ACCESSDENIED :
				msgError( "The operating system denied access to the specified file. ", m_hParent );
				break;
			case SE_ERR_ASSOCINCOMPLETE :
				msgError( "The file name association is incomplete or invalid.", m_hParent );
				break;
			case SE_ERR_DDEBUSY :
				msgError( "The DDE transaction could not be completed because other DDE transactions were being processed.", m_hParent );
				break;
			case SE_ERR_DDEFAIL :
				msgError( "The DDE transaction failed.", m_hParent );
				break;
			case SE_ERR_DDETIMEOUT :
				msgError( "The DDE transaction could not be completed because the request timed out.", m_hParent );
				break;
			case SE_ERR_DLLNOTFOUND :
				msgError( "The specified dynamic-link library was not found. ", m_hParent );
				break;
			case SE_ERR_NOASSOC :
				msgError( "There is no application associated with the given file name extension.", m_hParent );
				break;
			case SE_ERR_OOM :
				msgError( "There was not enough memory to complete the operation.", m_hParent );
				break;
			case SE_ERR_SHARE :
				msgError( "A sharing violation occurred.", m_hParent );
				break;
			}
		}
		delete param.str();
		return true;
	}
	return false;
}