#if     _MSC_VER > 1000
#pragma once
#endif


//Command.h



#ifndef _VCF_COMMAND_H__
#define _VCF_COMMAND_H__



/**
Copyright (c) 2000-2001, Jim Crafton
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions
are met:
	Redistributions of source code must retain the above copyright
	notice, this list of conditions and the following disclaimer.

	Redistributions in binary form must reproduce the above copyright
	notice, this list of conditions and the following disclaimer in 
	the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS
OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS 
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

NB: This software will not save the world.
*/


namespace VCF  {

class UndoRedoStack;


/**
*A Command represents an interface describing a single 
*action, that is potentially undoable.
*Commands are placed on the application wide UndoRedoStack object
*during the course of the application. Each command should represent
*a single user action like, typing text, or removing an item from
*a tree. The actual implementation will vary widely and will need 
*whatever state variables are neccessary to both execute/redo the 
*command, and undo the command.
*/
class APPKIT_API Command { 
public:
	virtual ~Command(){};

	/**
	*Undo the command
	*/
	virtual void undo() = 0;

	/**
	*redo the command. Generally the same, or similar, code
	*as performed in the execute() method
	*/
	virtual void redo() = 0;

	/**
	*execute the command. Usually called by the UndoRedoStack after 
	*the command has been added to it.
	*/
	virtual void execute() = 0;

	/**
	*returns the UndoRedoStack that owns this command.
	*@return UndoRedoStack a pointer to the current UndoRedoStack
	*instance for this command object.
	*/
	virtual UndoRedoStack* getOwningStack() = 0;
	
	/**
	*sets the owning UndoRedoStack for this command
	*@param UndoRedoStack the UndoRedoStack that will 
	*own this command
	*/
	virtual void setOwningStack( UndoRedoStack* stack ) = 0;

	/**
	*The name of this command. Frequently the name is the basis for the 
	*display text that is shown in the "Edit | Undo" or "Edit | Redo" menu
	*items.
	*@return String the name of this command
	*/
	virtual String getName() = 0;

	/**
	*sets the name of this command
	*/
	virtual void setName( const String& name ) = 0;

	/**
	*Is this command undoable ? 
	*@return bool true if the command's undo()/redo() methods 
	*can be safely called, otherwise false. Commands that return 
	*false for this method are usually not added to the UndoRedoStack
	*though they will be executed.
	*/
	virtual bool isUndoable() = 0;
protected:

private:
};


}; //end of namespace VCF


/**
*CVS Log info
*$Log$
*Revision 1.1.2.1  2004/04/28 00:28:14  ddiego
*migration towards new directory structure
*
*Revision 1.5.4.1  2004/04/26 21:58:18  marcelloptr
*changes for dir reorganization: _VCF_MACRO_H__
*
*Revision 1.5  2003/12/18 05:15:56  ddiego
*merge from devmain-0-6-2 branch into the stable branch
*
*Revision 1.4.26.2  2003/09/21 04:15:34  ddiego
*moved the cvs info data to teh bottom of the header instead of the
*top so it is easier to get to the actual header class declarations
*instead of having to wade through all the cvs info stuff.
*
*Revision 1.4.26.1  2003/09/12 00:09:32  ddiego
*added better tabbing behaviour - fixed an earlier bug.
*Code is easier to understand and it simplified the implementation
*a bit as well
*Moved around the RTTI definitions for various Appkit classes to a
*single inline and stripped them from the various class headers
*
*Revision 1.4  2002/01/24 01:46:47  ddiego
*added a cvs "log" comment to the top of all files in vcf/src and vcf/include
*to facilitate change tracking
*
*/

#endif // _VCF_COMMAND_H__


