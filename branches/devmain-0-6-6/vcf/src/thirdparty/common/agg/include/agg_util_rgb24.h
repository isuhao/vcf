//----------------------------------------------------------------------------
// Anti-Grain Geometry - Version 2.0 
// Copyright (C) 2002 Maxim Shemanarev (McSeem)
//
// Permission to copy, use, modify, sell and distribute this software 
// is granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied
// warranty, and with no claim as to its suitability for any purpose.
//
//----------------------------------------------------------------------------
// Contact: mcseem@antigrain.com
//          mcseemagg@yahoo.com
//          http://www.antigrain.com
//----------------------------------------------------------------------------
//
// class uril_rgb24
//
//----------------------------------------------------------------------------

#ifndef AGG_UTIL_RGB24_INCLUDED
#define AGG_UTIL_RGB24_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{

    //========================================================================
    class util_rgb24
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void  render_span(unsigned char* ptr, int x, unsigned count, rgba8 c)
        {
            unsigned char* p = ptr + x + x + x;
            unsigned char  r = c.r;
            unsigned char  g = c.g;
            unsigned char  b = c.b;
            do
            {
                *p++ = r;
                *p++ = g; 
                *p++ = b; 
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void  pixel(unsigned char* ptr, int x, rgba8 c)
        {
            ptr += x + x + x;
            *ptr++ = c.r;
            *ptr++ = c.g;
            *ptr   = c.b;
        }

        //--------------------------------------------------------------------
        static rgba8 pixel(unsigned char* ptr, int x)
        {
            ptr += x + x + x;
            return rgba8(unsigned(ptr[0]), unsigned(ptr[1]), unsigned(ptr[2]));
        }

        //--------------------------------------------------------------------
        static void copy(unsigned char* dst, 
                         const unsigned char* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + xdst * 3, src + xsrc * 3, len * 3);
        }
    };
}


#endif
