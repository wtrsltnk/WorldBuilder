cmake_minimum_required(VERSION 3.1)

project(WorldBuilder)

add_executable(WorldBuilder WIN32
    source/CCompileManager.cpp
    source/CCompileManager.h
    source/CControlsManager.cpp
    source/CControlsManager.h
    source/CDialogsManager.cpp
    source/CDialogsManager.h
    source/CMainFrame.cpp
    source/CMainFrame.h
    source/CSettings.cpp
    source/CSettings.h
    source/custommsg.h
    source/CWin.cpp
    source/CWin.h
    source/dialogs
    source/files.txt
    source/funclib.cpp
    source/funclib.h
    source/WinMain.cpp
    source/controls/CButton.cpp
    source/controls/CButton.h
    source/controls/CCheck.cpp
    source/controls/CCheck.h
    source/controls/CCombo.cpp
    source/controls/CCombo.h
    source/controls/CCommonDialogs.cpp
    source/controls/CCommonDialogs.h
    source/controls/CControl.cpp
    source/controls/CControl.h
    source/controls/CEdit.cpp
    source/controls/CEdit.h
    source/controls/CFileView.cpp
    source/controls/CFileView.h
    source/controls/CFolderView.cpp
    source/controls/CFolderView.h
    source/controls/CFrame.cpp
    source/controls/CFrame.h
    source/controls/CLabel.cpp
    source/controls/CLabel.h
    source/controls/CList.cpp
    source/controls/CList.h
    source/controls/CReportView.cpp
    source/controls/CReportView.h
    source/controls/CSlider.cpp
    source/controls/CSlider.h
    source/controls/CStatusBar.cpp
    source/controls/CStatusBar.h
    source/controls/CToolBar.cpp
    source/controls/CToolBar.h
    source/controls/CTreeView.cpp
    source/controls/CTreeView.h
    source/controls/GUI.H
    source/dialogs/CCommandDlg.cpp
    source/dialogs/CCommandDlg.h
    source/dialogs/CDirectoryDlg.cpp
    source/dialogs/CDirectoryDlg.h
    source/dialogs/CGroupDlg.cpp
    source/dialogs/CGroupDlg.h
    source/dialogs/CNewDlg.cpp
    source/dialogs/CNewDlg.h
    source/dialogs/CNewNameDlg.cpp
    source/dialogs/CNewNameDlg.h
    source/dialogs/COpenSaveDlg.cpp
    source/dialogs/COpenSaveDlg.h
    source/dialogs/CToolDlg.cpp
    source/dialogs/CToolDlg.h
    source/tools/CCommand.cpp
    source/tools/CCommand.h
    source/tools/CGroup.cpp
    source/tools/CGroup.h
    source/tools/CGroupManager.cpp
    source/tools/CGroupManager.h
    source/tools/CTool.cpp
    source/tools/CTool.h
    source/tools/trash.txt
    source/tools/XMLParser.cpp
    source/tools/XMLParser.h
    resource/resource.h
    resource/resource.rc
    )

target_link_libraries(WorldBuilder
    comctl32
    winmm
    )

target_compile_features(WorldBuilder
	PRIVATE cxx_auto_type
	PRIVATE cxx_nullptr
	PRIVATE cxx_range_for
	)
