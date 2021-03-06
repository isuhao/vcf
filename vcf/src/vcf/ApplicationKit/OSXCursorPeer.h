#ifndef _VCF_OSXCURSORPEER_H__
#define _VCF_OSXCURSORPEER_H__
//OSXCursorPeer.h

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


namespace VCF {

/**

*/
class OSXCursorPeer : public Object, public CursorPeer {
public:

	OSXCursorPeer( Cursor* cursor );

	virtual ~OSXCursorPeer();

	virtual OSHandleID getCursorHandleID(){
		return (OSHandleID)cursorInst_;
	}

	virtual void createFromImage( Image* cursorImage, Point* hotSpot );

	virtual void createSystemCursor( const Cursor::SystemCursorType& systemCursor );

	virtual void createFromResourceName( const String& cursorName, OSHandleID instanceHandle );

	virtual int32 getCursorID() {
		return cursorID_;
	}

	virtual void setCursorID( const int32& cursorID ) {
		cursorID_ = cursorID;
	}

	virtual Cursor* getCursor() {
		return  cursor_;
	}

	virtual void setCursor( Cursor* cursor ) {
		cursor_ = cursor;
	}
	
	bool isSystemCursor() {
		return isSystemCursor_;
	}

protected:
	bool isSystemCursor_;
	int32 cursorID_; 
	Cursor* cursor_;
    NSCursor* cursorInst_;
};


};


#endif // _VCF_OSXCURSORPEER_H__

/**
$Id$
*/
