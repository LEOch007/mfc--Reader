// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__9B1777F5_2D54_4227_80D9_491342B62ABF__INCLUDED_)
#define AFX_STDAFX_H__9B1777F5_2D54_4227_80D9_491342B62ABF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ADD
#ifndef   _WIN32_WINNT 
#define   _WIN32_WINNT   0x0400 
#endif 

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers



#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "SkinMagicLib.h"
#pragma comment(lib,"SkinMagic.lib")
#pragma comment(lib,"SkinMagicLibMT6.lib") 
#pragma comment(linker, "/FORCE:MULTIPLE") 
#pragma comment(linker, "/OPT:NOREF")

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__9B1777F5_2D54_4227_80D9_491342B62ABF__INCLUDED_)
