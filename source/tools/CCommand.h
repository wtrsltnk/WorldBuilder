#ifndef CCOMMAND_H
#define CCOMMAND_H

#include <string.h>
#include <vector>
#include <fstream>
using namespace std;
#include	"xmlparser.h"
#include "..\funclib.h"

#define			TYPE_TEXT	0
#define			TYPE_INT	1
#define			TYPE_BOOL	2

class CCommand
{
private:
	string				cmdName;
	string				cmdDescription;
	string				cmdCall;
	string				cmdValue;
	int					cmdType;

public:
	CCommand( string, string );		//name & call
	CCommand( void );
	~CCommand( void );

	////////////////////////////////////////////////////////
	//Savefunctions
	////////////////////////////////////////////////////////
    bool save( string );
    bool save( ofstream &, int );
    bool load( string );
    bool load( CXMLParser * );

	////////////////////////////////////////////////////////
	//Command functions
	////////////////////////////////////////////////////////
	string getName( void );
	void setName( string );

	string getDescription( void );
	void setDescription( string );

	string getCall( void );
	void setCall( string );

	string getValue( void );
	void setValue( string );

	int getType( void );
	void setType( int );
};
#endif
