#ifndef PARTICLEEDITOR_H
#define PARTICLEEDITOR_H

#include "vcf/ApplicationKit/ApplicationKit.h"
#include "vcf/ApplicationKit/Panel.h"
#include "vcf/ApplicationKit/SliderControl.h"
#include "vcf/ApplicationKit/CheckBoxControl.h"
#include "vcf/ApplicationKit/DropDownControl.h"

#include "Spinner.h"
#include "ColorPicker.h"

class ParticleRenderer;
class ParticleSystem;
class ParticleResource;

class ParticleEditor:public VCF::Window{
public:
	ParticleEditor();

protected:
	void onViewChanged(VCF::ScrollEvent *e);

	void onReset(VCF::ButtonEvent *e);
	void onGradualStart(VCF::ButtonEvent *e);
	void onNumParticles(VCF::TextEvent *e);
	void onParticleLife(VCF::TextEvent *e);
	void onSystemLife(VCF::TextEvent *e);
	void onInitialSpeed(VCF::TextEvent *e);
	void onInitialVariance(VCF::TextEvent *e);
	void onGravity(VCF::TextEvent *e);
	void onGravityVariance(VCF::TextEvent *e);

	void onParticleType(VCF::ItemEvent *e);
	void onAlignment(VCF::ItemEvent *e);
	void onBlending(VCF::ItemEvent *e);
	void onDepthTest(VCF::ButtonEvent *e);
	void onStartColor(VCF::ButtonEvent *e);
	void onEndColor(VCF::ButtonEvent *e);

	void onTrailingSystem(VCF::TextEvent *e);
	void onEndingSystem(VCF::TextEvent *e);
	void onNewTexture(VCF::ButtonEvent *e);
	void onDeleteTexture(VCF::ButtonEvent *e);

	void onFileLoad(MenuItemEvent *e);
	void onFileSave(MenuItemEvent *e);
	void onFileExit(MenuItemEvent *e);

	void setParticleResource(ParticleResource *r);

	VCF::SliderControl *mYaw;
	VCF::SliderControl *mPitch;
	VCF::SliderControl *mZoom;

	VCF::CheckBoxControl *mGradualStart;
	VCF::Spinner *mNumParticles;
	VCF::Spinner *mPartLife;
	VCF::Spinner *mSystemLife;
	VCF::TextControl *mInitialSpeed;
	VCF::TextControl *mInitialVariance;
	VCF::TextControl *mGravity;
	VCF::TextControl *mGravityVariance;

	VCF::DropDownControl *mParticleType;
	VCF::DropDownControl *mAlignment;
	VCF::DropDownControl *mBlending;
	VCF::CheckBoxControl *mDepthTest;
	ColorPicker *mStartColor;
	ColorPicker *mEndColor;

	VCF::TextControl *mTrailingSystem;
	VCF::TextControl *mEndingSystem;

	VCF::Panel *mTexturePanel;
	VCF::DropDownControl *mTextureList;

	ParticleRenderer *mParticleRenderer;
	ParticleSystem *mParticleSystem;
	ParticleResource *mParticleResource;
};

#endif

/**
$Id$
*/
