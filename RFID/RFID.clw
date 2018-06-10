; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDebugger
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "RFID.h"

ClassCount=5
Class1=CRFIDApp
Class2=CRFIDDlg
Class3=CAboutDlg

ResourceCount=5
Resource1=IDD_ABOUTBOX
Resource2=IDR_MAINFRAME
Resource3=IDD_APPDEV
Resource4=IDD_RFID_DIALOG
Class4=CAppDev
Class5=CDebugger
Resource5=IDD_DEBUGGER

[CLS:CRFIDApp]
Type=0
HeaderFile=RFID.h
ImplementationFile=RFID.cpp
Filter=N

[CLS:CRFIDDlg]
Type=0
HeaderFile=RFIDDlg.h
ImplementationFile=RFIDDlg.cpp
Filter=D
LastObject=CRFIDDlg
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=RFIDDlg.h
ImplementationFile=RFIDDlg.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_RFID_DIALOG]
Type=1
Class=CRFIDDlg
ControlCount=1
Control1=IDC_TAB,SysTabControl32,1342177280

[DLG:IDD_APPDEV]
Type=1
Class=CAppDev
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[DLG:IDD_DEBUGGER]
Type=1
Class=CDebugger
ControlCount=7
Control1=IDC_STATIC,button,1342177287
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1484849280
Control5=IDC_EDIT2,edit,1484849280
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_BUTTON2,button,1342242816

[CLS:CAppDev]
Type=0
HeaderFile=AppDev.h
ImplementationFile=AppDev.cpp
BaseClass=CDialog
Filter=D
LastObject=CAppDev

[CLS:CDebugger]
Type=0
HeaderFile=Debugger.h
ImplementationFile=Debugger.cpp
BaseClass=CDialog
Filter=D
LastObject=CDebugger
VirtualFilter=dWC

