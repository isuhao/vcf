/* $Id: dtextract.c,v 1.1.1.1 2004/12/23 04:03:59 ellson Exp $ $Revision: 1.1.1.1 $ */
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

#include	"dthdr.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

/*	Extract objects of a dictionary.
**
**	Written by Kiem-Phong Vo (5/25/96).
*/

#if __STD_C
Dtlink_t *dtextract(reg Dt_t * dt)
#else
Dtlink_t *dtextract(dt)
reg Dt_t *dt;
#endif
{
    reg Dtlink_t *list, **s, **ends;

    if (dt->data->type & (DT_OSET | DT_OBAG))
	list = dt->data->here;
    else if (dt->data->type & (DT_SET | DT_BAG)) {
	list = dtflatten(dt);
	for (ends = (s = dt->data->htab) + dt->data->ntab; s < ends; ++s)
	    *s = NIL(Dtlink_t *);
    } else {			/*if(dt->data->type&(DT_LIST|DT_STACK|DT_QUEUE)) */
	list = dt->data->head;
	dt->data->head = NIL(Dtlink_t *);
    }

    dt->data->type &= ~DT_FLATTEN;
    dt->data->size = 0;
    dt->data->here = NIL(Dtlink_t *);

    return list;
}
