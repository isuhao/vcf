/* $Id: _sfputu.c,v 1.1.1.1 2004/12/23 04:04:18 ellson Exp $ $Revision: 1.1.1.1 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include	"sfhdr.h"

#undef sfputu

#if __STD_C
int sfputu(reg Sfio_t * f, Sfulong_t u)
#else
int sfputu(f, u)
reg Sfio_t *f;
reg Sfulong_t u;
#endif
{
    return __sf_putu(f, u);
}
