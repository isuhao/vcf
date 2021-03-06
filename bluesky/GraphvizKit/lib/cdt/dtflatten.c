/* $Id: dtflatten.c,v 1.1.1.1 2004/12/23 04:03:59 ellson Exp $ $Revision: 1.1.1.1 $ */
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

/*	Flatten a dictionary into a linked list.
**	This may be used when many traversals are likely.
**
**	Written by Kiem-Phong Vo (5/25/96).
*/

#if __STD_C
Dtlink_t *dtflatten(Dt_t * dt)
#else
Dtlink_t *dtflatten(dt)
Dt_t *dt;
#endif
{
    reg Dtlink_t *t, *r, *list, *last, **s, **ends;

    /* already flattened */
    if (dt->data->type & DT_FLATTEN)
	return dt->data->here;

    list = last = NIL(Dtlink_t *);
    if (dt->data->type & (DT_SET | DT_BAG)) {
	for (ends = (s = dt->data->htab) + dt->data->ntab; s < ends; ++s) {
	    if ((t = *s)) {
		if (last)
		    last->right = t;
		else
		    list = last = t;
		while (last->right)
		    last = last->right;
		*s = last;
	    }
	}
    } else if (dt->data->type & (DT_LIST | DT_STACK | DT_QUEUE))
	list = dt->data->head;
    else if ((r = dt->data->here)) {	/*if(dt->data->type&(DT_OSET|DT_OBAG)) */
	while ((t = r->left))
	    RROTATE(r, t);
	for (list = last = r, r = r->right; r; last = r, r = r->right) {
	    if ((t = r->left)) {
		do
		    RROTATE(r, t);
		while ((t = r->left));

		last->right = r;
	    }
	}
    }

    dt->data->here = list;
    dt->data->type |= DT_FLATTEN;

    return list;
}
