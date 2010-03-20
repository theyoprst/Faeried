#include "PreviewFaerieWidget.h"

#include <assert.h>
#include <hge.h>

#include "Faerie.h"

HGE* PreviewFaerieWidget::_hge = NULL;
Faerie* PreviewFaerieWidget::_faerie = NULL;
QTime PreviewFaerieWidget::_time = QTime::currentTime();

PreviewFaerieWidget::PreviewFaerieWidget(QWidget* parent)
	: QWidget(parent/*, Qt::SubWindow*/)
{
	assert(testAttribute(Qt::WA_PaintOnScreen) == false);
	setAttribute(Qt::WA_PaintOnScreen, true);
	InitHGE();
	setWindowTitle("Faerie preview");
	setFixedSize(WIDTH, HEIGHT);
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
	_faerie = new Faerie(_hge);
	_timer.start(1);
	connect(&_timer, SIGNAL(timeout()), this, SLOT(RenderFunc()));
	_time = QTime::currentTime();
}

PreviewFaerieWidget::~PreviewFaerieWidget() {
	_hge->System_Shutdown();
}

bool PreviewFaerieWidget::FrameFunc() {
	return false;
}

bool PreviewFaerieWidget::RenderFunc() {
	int msecs = _time.msecsTo(QTime::currentTime());
	assert(msecs >= 0);
	_time = QTime::currentTime();
	// _hge->Timer_GetDelta()
	Update(msecs / 1000.0f);
	Draw();
	return false;
}

void PreviewFaerieWidget::Draw() {
	_hge->Gfx_BeginScene();
	_hge->Gfx_Clear(0x00000000);
	if (_faerie != NULL) {
		_faerie->Draw();
	}
	_hge->Gfx_EndScene();
}

void PreviewFaerieWidget::Update(float dt) {
	if (_faerie != NULL) {
		_faerie->Update(dt);
	}
}

void PreviewFaerieWidget::paintEvent(QPaintEvent*) {
	//repaint();
	RenderFunc();
}
QPaintEngine * PreviewFaerieWidget::paintEngine () const {
	return NULL;
}
