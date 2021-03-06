#ifndef _VCF_APPLICATIONKITPRIVATE_H__
#define _VCF_APPLICATIONKITPRIVATE_H__
//ApplicationKitPrivate.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


#if _MSC_VER > 1000
#   pragma once
#endif


#include "vcf/GraphicsKit/GraphicsKitPrivate.h"

/****************/
#if defined(VCF_WIN) && !defined(VCF_AGG)
//controls & GDI stuff
#include <Commdlg.h>
#	include "vcf/FoundationKit/Win32Peer.h"
#	include "vcf/ApplicationKit/Win32ToolKit.h"
#	include "vcf/ApplicationKit/Win32Object.h"
#	include "vcf/ApplicationKit/AbstractWin32Component.h"
#elif VCF_AGG

#elif VCF_OSX
#	include "vcf/ApplicationKit/OSXUIToolkit.h"
#elif VCF_XCB
#	include "vcf/ApplicationKit/XCBUIToolkit.h"
#endif


#endif // _VCF_APPLICATIONKITPRIVATE_H__

/**
$Id$
*/
