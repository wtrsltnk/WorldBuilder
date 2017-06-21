#include "CSettings.h"


/////////////////////////////////////
// Constructors / Destructors      //
/////////////////////////////////////
CSettings::CSettings( string filename )
{
	this->filename = filename;

	settings.m_PosX = CW_USEDEFAULT;
	settings.m_PosY = CW_USEDEFAULT;
	settings.m_dwCreationWidth = CW_USEDEFAULT;
	settings.m_dwCreationHeight = CW_USEDEFAULT;
	settings.m_dwCreationFlags = SW_SHOW;
	
}

CSettings::~CSettings( void )
{
}

/////////////////////////////////////
// Memberfuncties                  //
/////////////////////////////////////

bool CSettings::load( void )
{
	ifstream input;

// CONTROLE
	if ( stricmp(filename.c_str(), "") == 0 )
	{
		throw( "No file name specified !\n" );
		return false;
	}

	input.open((const char *)filename.c_str());
	if (input.fail())
	{
		throw( "Couldn't open this file\n" );
		return false;
	}

// LEZEN
	input >> settings.m_PosX 
		>> settings.m_PosY 
		>> settings.m_dwCreationWidth 
		>> settings.m_dwCreationHeight
		>> settings.m_dwCreationFlags;


// DONE
	input.close();
	return true;
}

bool CSettings::save( void ) 
{
	ofstream output;

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
	output << settings.m_PosX;
	output << settings.m_PosY;
	output << settings.m_dwCreationWidth;
	output << settings.m_dwCreationHeight;
	output << settings.m_dwCreationFlags;


// DONE
	output.close();
	return true;
}

SETTINGS CSettings::get( void )
{
	return settings;
}

void CSettings::set( SETTINGS settings )
{
	this->settings = settings;
}
