//CommonPrintDialog.cpp

/*
Copyright 2000-2004 The VCF Project.
Please see License.txt in the top level directory
where you installed the VCF.
*/


/* Generated by Together */
#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/CommonPrintDialog.h"



using namespace VCF;

CommonPrintDialog::CommonPrintDialog( Control* owner ):
	peer_(NULL)
{
	peer_ = UIToolkit::createCommonPrintDialogPeer(owner);
}

CommonPrintDialog::~CommonPrintDialog()
{
	delete peer_;
}

bool CommonPrintDialog::execute()
{
	return peer_->execute();
}

String CommonPrintDialog::getTitle()
{
	return title_;
}

void CommonPrintDialog::setTitle( const String& title )
{
	title_ = title;
	peer_->setTitle( title );
}

void CommonPrintDialog::setNumberOfCopies( const ulong32& val )
{
	peer_->setNumberOfCopies( val );
}

ulong32 CommonPrintDialog::getNumberOfCopies()
{
	return peer_->getNumberOfCopies();
}

void CommonPrintDialog::setStartPage( const ulong32& val )
{
	peer_->setStartPage( val );
}

ulong32 CommonPrintDialog::getStartPage()
{
	return peer_->getStartPage();
}


void CommonPrintDialog::setEndPage( const ulong32& val )
{
	peer_->setEndPage( val );
}

ulong32 CommonPrintDialog::getEndPage()
{
	return peer_->getEndPage();
}



void CommonPrintDialog::setPrintJobType( PrintSession::PrintJob val )
{
	peer_->setPrintJobType( val );
}

PrintSession::PrintJob CommonPrintDialog::getPrintJobType()
{
	return peer_->getPrintJobType();
}

void CommonPrintDialog::setPrintInfo( PrintInfoHandle info )
{
	peer_->setPrintInfo( info );
}

PrintInfoHandle CommonPrintDialog::getPrintInfo()
{
	return peer_->getPrintInfo();
}


/**
$Id$
*/