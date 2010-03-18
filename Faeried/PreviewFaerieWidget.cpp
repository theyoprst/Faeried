#include "PreviewFaerieWidget.h"

#include <assert.h>
#include <hge.h>

HGE* PreviewFaerieWidget::_hge = NULL;

PreviewFaerieWidget::PreviewFaerieWidget(QWidget* parent)
	: QWidget(parent, Qt::SubWindow)
{
	InitHGE();
	setWindowTitle("Faerie preview");
	setFixedSize(WIDTH, HEIGHT);
	
	//setWindowFlags( Qt::Widget );
	//setWindowModality(Qt::WindowModal);
	//setWindowFlags(flags);
}

void PreviewFaerieWidget::InitHGE() {
	assert(_hge == NULL);
	_hge = hgeCreate(HGE_VERSION);
	_hge->System_SetState(HGE_SHOWSPLASH, false);
	_hge->System_SetState(HGE_HWNDPARENT, this->winId());
	_hge->System_SetState(HGE_FRAMEFUNC, &PreviewFaerieWidget::FrameFunc);
	_hge->System_SetState(HGE_RENDERFUNC, &PreviewFaerieWidget::RenderFunc);
	_hge->System_SetState(HGE_WINDOWED, true);
	_hge->System_SetState(HGE_USESOUND, false);
	_hge->System_SetState(HGE_SCREENWIDTH, WIDTH);
	_hge->System_SetState(HGE_SCREENHEIGHT, HEIGHT);
	_hge->System_Initiate();
	_hge->System_Start();
}

PreviewFaerieWidget::~PreviewFaerieWidget() {
	_hge->System_Shutdown();
}

bool PreviewFaerieWidget::FrameFunc() {
	return false;
}

bool PreviewFaerieWidget::RenderFunc() {
	Update(_hge->Timer_GetDelta());
	Draw();
	return false;
}

void PreviewFaerieWidget::Draw() {
	_hge->Gfx_BeginScene();
	_hge->Gfx_Clear(0x00000000);
	_hge->Gfx_EndScene();
}

void PreviewFaerieWidget::Update(float dt) {
}

void PreviewFaerieWidget::OnQuit() {
	int i = 1;
}