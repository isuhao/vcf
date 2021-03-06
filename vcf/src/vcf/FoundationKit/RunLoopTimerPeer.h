#ifndef _VCF_RUNLOOPTIMERPEER_H__
#define _VCF_RUNLOOPTIMERPEER_H__

//
// Copyright 2000-2007 The VCF Project.
// Please see License.txt in the top level directory
// where you installed the VCF.
//

namespace VCF {
    class FOUNDATIONKIT_API RunLoopTimerPeer {
    public:
        virtual ~RunLoopTimerPeer();
        
        virtual void create( const DateTime &fireDate ) = 0;
        virtual void create( const DateTimeSpan &interval ) = 0;
        virtual void create( const DateTime &fireDate, const DateTimeSpan &interval ) = 0;        

		virtual bool isActive() const = 0;
		virtual void setActive( const bool& val ) = 0;

		virtual bool doesRepeat() const = 0;
        virtual DateTimeSpan getInterval() const = 0;
        virtual DateTime getNextFireDate() const = 0;
    };
    
    inline RunLoopTimerPeer::~RunLoopTimerPeer()
    {
    }
}

#endif // _VCF_RUNLOOPTIMERPEER_H__

/**
$Id$
*/
