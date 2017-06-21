#ifndef CCOMPILEMANAGER_H
#define CCOMPILEMANAGER_H

#include <windows.h>
#include "..\resource\resource.h"
#include "tools\CGroup.h"
#include <strstream>
#include <fstream>
using namespace std;

class CCompileManager
{
private:
	HINSTANCE				m_hInstance;
	HWND					m_hParent;
public:
	CCompileManager( HINSTANCE, HWND );
	~CCompileManager( void );

	bool buildBatch( string, CGroup * ) throw();
	bool startBatch( string );
	bool startGame( CGroup * );
};

#endif
