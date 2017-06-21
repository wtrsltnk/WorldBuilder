# Microsoft Developer Studio Project File - Name="WorldBuilder" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=WorldBuilder - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "WorldBuilder.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "WorldBuilder.mak" CFG="WorldBuilder - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "WorldBuilder - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "WorldBuilder - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "WorldBuilder - Win32 Release"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /machine:I386 /out:"bin/WorldBuilder_release.exe"

!ELSEIF  "$(CFG)" == "WorldBuilder - Win32 Debug"

# PROP BASE Use_MFC 2
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x409 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x409 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib comctl32.lib /nologo /subsystem:windows /debug /machine:I386 /out:"bin/WorldBuilder.exe" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "WorldBuilder - Win32 Release"
# Name "WorldBuilder - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\source\CCompileManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CControlsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CDialogsManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CMainFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\source\CWin.cpp
# End Source File
# Begin Source File

SOURCE=.\source\funclib.cpp
# End Source File
# Begin Source File

SOURCE=.\source\WinMain.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\source\CCompileManager.h
# End Source File
# Begin Source File

SOURCE=.\source\CControlsManager.h
# End Source File
# Begin Source File

SOURCE=.\source\CDialogsManager.h
# End Source File
# Begin Source File

SOURCE=.\source\CMainFrame.h
# End Source File
# Begin Source File

SOURCE=.\source\custommsg.h
# End Source File
# Begin Source File

SOURCE=.\source\CWin.h
# End Source File
# Begin Source File

SOURCE=.\source\funclib.h
# End Source File
# Begin Source File

SOURCE=.\resource\resource.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\resource\resource.rc
# End Source File
# Begin Source File

SOURCE=.\resource\toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\tv_nodes.bmp
# End Source File
# Begin Source File

SOURCE=.\resource\WRENCH.ICO
# End Source File
# End Group
# Begin Group "controls"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\controls\CButton.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CButton.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCheck.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCheck.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCombo.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCombo.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCommonDialogs.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CCommonDialogs.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CControl.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CControl.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CEdit.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CFrame.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CFrame.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CLabel.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CList.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CList.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CReportView.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CReportView.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CStatusBar.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CStatusBar.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CToolBar.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\CTreeView.cpp
# End Source File
# Begin Source File

SOURCE=.\source\controls\CTreeView.h
# End Source File
# Begin Source File

SOURCE=.\source\controls\GUI.H
# End Source File
# End Group
# Begin Group "tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\tools\CCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tools\CCommand.h
# End Source File
# Begin Source File

SOURCE=.\source\tools\CGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tools\CGroup.h
# End Source File
# Begin Source File

SOURCE=.\source\tools\CGroupManager.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tools\CGroupManager.h
# End Source File
# Begin Source File

SOURCE=.\source\tools\CTool.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tools\CTool.h
# End Source File
# Begin Source File

SOURCE=.\source\tools\XMLParser.cpp
# End Source File
# Begin Source File

SOURCE=.\source\tools\XMLParser.h
# End Source File
# End Group
# Begin Group "dialogs"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\source\dialogs\CCommandDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CCommandDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CDirectoryDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CDirectoryDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CGroupDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CGroupDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CNewDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CNewDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CNewNameDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CNewNameDlg.h
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CToolDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\source\dialogs\CToolDlg.h
# End Source File
# End Group
# End Target
# End Project
