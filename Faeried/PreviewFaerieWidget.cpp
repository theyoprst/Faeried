#include "PreviewFaerieWidget.h"

#include <assert.h>
#include <hge.h>
#include <QtGui/QMouseEvent>

#include "Point.h"
#include "Faerie.h"
#include "FaerieAnimationsDelegate.h"

HGE* PreviewFaerieWidget::_hge = NULL;
Faerie* PreviewFaerieWidget::_faerie = NULL;
QTime PreviewFaerieWidget::_time = QTime::currentTime();

PreviewFaerieWidget::PreviewFaerieWidget(QWidget* parent, FaerieAnimationsDelegate* animations)
	: QWidget(parent, Qt::Widget)
	, _animations(animations)
{
	assert(testAttribute(Qt::WA_PaintOnScreen) == false);
	setAttribute(Qt::WA_PaintOnScreen, true);
	setFixedSize(WIDTH, HEIGHT);
	setMouseTracking(true);
	InitHGE();
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
	connect(_animations, SIGNAL(GuiChangedFrameSignal(FaerieFrame)), _faerie, SLOT(GuiChangedFrame(FaerieFrame)));
	connect(_faerie, SIGNAL(FaerieChangedFrameSignal(FaerieFrame)), _animations, SLOT(FaerieChangedFrame(FaerieFrame)));
	connect(_animations, SIGNAL(AnimationIsSelected(bool)), _faerie, SLOT(SlotShowFaerie(bool)));
	_timer.start(10); // 1000 fps max
	connect(&_timer, SIGNAL(timeout()), this, SLOT(RenderFunc()));
	_time = QTime::currentTime();
}

PreviewFaerieWidget::~PreviewFaerieWidget() {
	_hge->System_Shutdown();
}

bool PreviewFaerieWidget::FrameFunc() {
	return false;
}

void PreviewFaerieWidget::ProcessHgeMessages() {
	hgeInputEvent event;
	while (_hge->Input_GetEvent(&event)) {
		if (event.type == INPUT_KEYDOWN) {
		} else if (event.type == INPUT_KEYUP) {
		} else if (event.type == INPUT_MBUTTONDOWN) {
			if (event.key == HGEK_LBUTTON) {
				int x = int(event.x) - WIDTH / 2;
				int y = int(event.y) - HEIGHT / 2;
				_faerie->OnLeftMouseDown(Point(x, y));
			} else if (event.key == HGEK_RBUTTON) {
			} else if (event.key == HGEK_MBUTTON) {
			} else {
				assert(false);
			}
		} else if (event.type == INPUT_MBUTTONUP) {
			if (event.key == HGEK_LBUTTON) {
				int x = int(event.x) - WIDTH / 2;
				int y = int(event.y) - HEIGHT / 2;
				_faerie->OnLeftMouseUp(Point(x, y));
			} else if (event.key == HGEK_RBUTTON) {
			} else if (event.key == HGEK_MBUTTON) {
			} else {
				assert(false);
			}
		} else if (event.type == INPUT_MOUSEMOVE) {
			int x = int(event.x) - WIDTH / 2;
			int y = int(event.y) - HEIGHT / 2;
			_faerie->OnMouseMove(Point(x, y));
		} else if (event.type == INPUT_MOUSEWHEEL) {
		} else {
			assert(false);
		}
	}
}

bool PreviewFaerieWidget::RenderFunc() {
	ProcessHgeMessages();
	int msecs = _time.msecsTo(QTime::currentTime());
	assert(msecs >= 0);
	_time = QTime::currentTime();
	Update(msecs / 1000.0f);
	Draw();
	return false;
}

void PreviewFaerieWidget::Draw() {
	_hge->Gfx_BeginScene();
	_hge->Gfx_Clear(0x00000000);
	_hge->Gfx_RenderLine(0, HEIGHT / 2, WIDTH, HEIGHT / 2, 0xff222222);
	_hge->Gfx_RenderLine(WIDTH / 2, 0, WIDTH / 2, HEIGHT, 0xff222222);
	if (_faerie != NULL) {
		_faerie->Draw(WIDTH / 2, HEIGHT / 2);
	}
	_hge->Gfx_EndScene();
}

void PreviewFaerieWidget::Update(float dt) {
	if (_faerie != NULL) {
		_faerie->Update(dt);
	}
}

Bone* PreviewFaerieWidget::GetBoneByName(std::string boneName) {
	return _faerie->GetBoneByName(boneName);
}

