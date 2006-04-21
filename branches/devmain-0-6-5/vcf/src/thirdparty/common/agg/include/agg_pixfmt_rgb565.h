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

#ifndef AGG_PIXFMT_RGB565_INCLUDED
#define AGG_PIXFMT_RGB565_INCLUDED

#include <string.h>
#include "thirdparty/common/agg/include/agg_basics.h"
#include "thirdparty/common/agg/include/agg_color_rgba8.h"

namespace agg
{

    //------------------------------------------------------------------------
    inline int16u rgb565(unsigned r, unsigned g, unsigned b)
    {
        return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
    }


    //========================================================================
    class pixfmt_rgb565
    {
    public:
        typedef rgba8 color_type;

        //--------------------------------------------------------------------
        static void pixel(int8u* p, int x, const color_type& c)
        {
            ((int16u*)p)[x] = rgb565(c.r, c.g, c.b);
        }

        //--------------------------------------------------------------------
        static color_type pixel(int8u* p, int x)
        {
            unsigned rgb = ((int16u*)p)[x];
            return color_type((rgb >> 8) & 0xF8, 
                              (rgb >> 3) & 0xFC, 
                              (rgb << 3) & 0xF8);
        }

        //--------------------------------------------------------------------
        static void pixel(int8u* ptr, int x, 
                          const color_type& c, 
                          int alpha)
        {

            int16u* p = ((int16u*)ptr) + x;
            int16u rgb = *p;

            int r = (rgb >> 8) & 0xF8;
            int g = (rgb >> 3) & 0xFC;
            int b = (rgb << 3) & 0xF8;

            *p = (((((c.r - r) * alpha) + (r << 16)) >> 8) & 0xF800) |
                 (((((c.g - g) * alpha) + (g << 16)) >> 13) & 0x7E0) |
                  ((((c.b - b) * alpha) + (b << 16)) >> 19);


        }

        //--------------------------------------------------------------------
        static void hline(int8u* ptr, int x, 
                          unsigned count, 
                          const color_type& c)
        {
            int16u* p = ((int16u*)ptr) + x;
            int16u v = rgb565(c.r, c.g, c.b);
            do
            {
                *p++ = v;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void vline(int8u* p, int x, 
                          int stride, 
                          unsigned count, 
                          const color_type& c)
        {
            int16u v = rgb565(c.r, c.g, c.b);
            p += x << 1;
            do
            {
                *(int16u*)p = v;
                p += stride;
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        static void copy(int8u* dst, 
                         const int8u* src, 
                         int xdst, 
                         int xsrc,
                         unsigned len)
        {
            memmove(dst + (xdst << 1), src + (xsrc << 1), len << 1);
        }


        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  SpanInterpolator& span)
        {
            int16u* p = ((int16u*)ptr) + x;
            do 
            {
                span.calculate();
                *p++ = rgb565(span.r(), span.g(), span.b());
                span.step();
            }
            while(--count);
        }

        //--------------------------------------------------------------------
        template<class SpanInterpolator>
        void span(int8u* ptr, 
                  int x, int,
                  unsigned count, 
                  const int8u* covers,
                  SpanInterpolator& span)
        {
            int16u* p = ((int16u*)ptr) + x;
            do
            {
                span.calculate();
                int16 rgb = *p;
                int alpha = (*covers++) * span.a();

                if(alpha)
                {
                    if(alpha == 255*255)
                    {
                        *p = rgb565(span.r(), span.g(), span.b());
                    }
                    else
                    {
                        int r = (rgb >> 8) & 0xF8;
                        int g = (rgb >> 3) & 0xFC;
                        int b = (rgb << 3) & 0xF8;
                        *p = (((((span.r() - r) * alpha) + (r << 16)) >> 8) & 0xF800) |
                             (((((span.g() - g) * alpha) + (g << 16)) >> 13) & 0x7E0) |
                              ((((span.b() - b) * alpha) + (b << 16)) >> 19);
                    }
                }
                ++p;
                span.step();
            }
            while(--count);
        }

    };

}

#endif
