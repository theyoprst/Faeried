#include "FrameEditorWidget.h"

#include <assert.h>
#include <QtGui/QHeaderView>
#include <QtGui/QStandardItemModel>
#include <QtGui/QTableWidgetItem>

#include "NoEditDelegate.h"
#include "SpinBoxDelegate.h"

FrameEditorWidget::FrameEditorWidget(QWidget* parent)
	: QTableView(parent)
	, _isInit(true)
{
	const int ROWS = 13;
	_model = new QStandardItemModel(ROWS, 2);
	setModel(_model);
	setItemDelegateForColumn(1, new SpinBoxDelegate(-180, 180));
	setItemDelegateForColumn(0, new NoEditDelegate());
	
	setGridStyle(Qt::DotLine);
	for (int i = 0; i < ROWS; ++i) {
		setRowHeight(i, 20);
		_model->setItem(i, 1, new QStandardItem(tr("0")));
	}
	setColumnWidth(0, 150);
	setColumnWidth(1, 50);
	verticalHeader()->hide();
	horizontalHeader()->hide();

	_model->setItem(0, 0, new QStandardItem(tr("Голова")));
	_model->item(0, 0)->setToolTip(tr("Угол поворота головы"));
	_model->item(0, 1)->setToolTip(tr("Угол поворота головы"));

	_model->setItem(1, 0, new QStandardItem(tr("Туловище")));
	_model->item(1, 0)->setToolTip(tr("Угол поворота туловища"));
	_model->item(1, 1)->setToolTip(tr("Угол поворота туловища"));

	_model->setItem(2, 0, new QStandardItem(tr("Поясница")));
	_model->item(2, 0)->setToolTip(tr("Угол поворота поясницы"));
	_model->item(2, 1)->setToolTip(tr("Угол поворота поясницы"));

	_model->setItem(3, 0, new QStandardItem(tr("Левое предплечье")));
	_model->item(3, 0)->setToolTip(tr("Угол поворота левого предплечья"));
	_model->item(3, 1)->setToolTip(tr("Угол поворота левого предплечья"));

	_model->setItem(4, 0, new QStandardItem(tr("Левая рука")));
	_model->item(4, 0)->setToolTip(tr("Угол поворота левой руки"));
	_model->item(4, 1)->setToolTip(tr("Угол поворота левой руки"));

	_model->setItem(5, 0, new QStandardItem(tr("Правое предплечье")));
	_model->item(5, 0)->setToolTip(tr("Угол поворота правого предплечья"));
	_model->item(5, 1)->setToolTip(tr("Угол поворота правого предплечья"));

	_model->setItem(6, 0, new QStandardItem(tr("Правая рука")));
	_model->item(6, 0)->setToolTip(tr("Угол поворота правой руки"));
	_model->item(6, 1)->setToolTip(tr("Угол поворота правой руки"));

	_model->setItem(7, 0, new QStandardItem(tr("Левое бедро")));
	_model->item(7, 0)->setToolTip(tr("Угол поворота левого бедра"));
	_model->item(7, 1)->setToolTip(tr("Угол поворота левого бедра"));

	_model->setItem(8, 0, new QStandardItem(tr("Левая голень")));
	_model->item(8, 0)->setToolTip(tr("Угол поворота левой голени"));
	_model->item(8, 1)->setToolTip(tr("Угол поворота левой голени"));

	_model->setItem(9, 0, new QStandardItem(tr("Правое бедро")));
	_model->item(9, 0)->setToolTip(tr("Угол поворота правого бедра"));
	_model->item(9, 1)->setToolTip(tr("Угол поворота правого бедра"));

	_model->setItem(10, 0, new QStandardItem(tr("Правая голень")));
	_model->item(10, 0)->setToolTip(tr("Угол поворота правой голени"));
	_model->item(10, 1)->setToolTip(tr("Угол поворота правой голени"));

	_model->setItem(11, 0, new QStandardItem(tr("Смещение по x")));
	_model->item(11, 0)->setToolTip(tr("Горизонтальное смещение в пикселах"));
	_model->item(11, 1)->setToolTip(tr("Горизонтальное смещение в пикселах"));

	_model->setItem(12, 0, new QStandardItem(tr("Смещение по y")));
	_model->item(12, 0)->setToolTip(tr("Вертикальное смещение в пикселах"));
	_model->item(12, 1)->setToolTip(tr("Вертикальное смещение в пикселах"));

	connect(_model, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
		this, SLOT(dataChanged(const QModelIndex&, const QModelIndex&)));

	_isInit = false;
}

void FrameEditorWidget::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) {
	if (!_isInit) {
		assert(topLeft.column() == bottomRight.column());
		assert(topLeft.row() == bottomRight.row());
		QModelIndex index = topLeft;
		emit GuiChangedFrame(CreateFrame());
	}
}

FaerieFrame FrameEditorWidget::CreateFrame() {
	FaerieFrame frame;
	frame.SetBoneAngle("head", _model->data(_model->index(0, 1)).toFloat());
	frame.SetBoneAngle("body", _model->data(_model->index(1, 1)).toFloat());
	frame.SetBoneAngle("pelvis", _model->data(_model->index(2, 1)).toFloat());
	frame.SetBoneAngle("leftArm", _model->data(_model->index(3, 1)).toFloat());
	frame.SetBoneAngle("leftForearm", _model->data(_model->index(4, 1)).toFloat());
	frame.SetBoneAngle("rightArm", _model->data(_model->index(5, 1)).toFloat());
	frame.SetBoneAngle("rightForearm", _model->data(_model->index(6, 1)).toFloat());
	frame.SetBoneAngle("leftThigh", _model->data(_model->index(7, 1)).toFloat());
	frame.SetBoneAngle("leftLeg", _model->data(_model->index(8, 1)).toFloat());
	frame.SetBoneAngle("rightThigh", _model->data(_model->index(9, 1)).toFloat());
	frame.SetBoneAngle("rightLeg", _model->data(_model->index(10, 1)).toFloat());
	int x = _model->data(_model->index(11, 1)).toInt();
	int y = _model->data(_model->index(12, 1)).toInt();
	frame.SetShift(FPoint(Point(x, y)));
	return frame;
}

void FrameEditorWidget::FaerieChandedFrame(FaerieFrame frame) {
	_isInit = true;
	_model->setData(_model->index(0, 1), frame.GetBoneAngle("head"));
	_model->setData(_model->index(1, 1), frame.GetBoneAngle("body"));
	_model->setData(_model->index(2, 1), frame.GetBoneAngle("pelvis"));
	_model->setData(_model->index(3, 1), frame.GetBoneAngle("leftArm"));
	_model->setData(_model->index(4, 1), frame.GetBoneAngle("leftForearm"));
	_model->setData(_model->index(5, 1), frame.GetBoneAngle("rightArm"));
	_model->setData(_model->index(6, 1), frame.GetBoneAngle("rightForearm"));
	_model->setData(_model->index(7, 1), frame.GetBoneAngle("leftThigh"));
	_model->setData(_model->index(8, 1), frame.GetBoneAngle("leftLeg"));
	_model->setData(_model->index(9, 1), frame.GetBoneAngle("rightThigh"));
	_model->setData(_model->index(10, 1), frame.GetBoneAngle("rightLeg"));
	_model->setData(_model->index(11, 1), Math::Round(frame.GetShift().x));
	_model->setData(_model->index(12, 1), Math::Round(frame.GetShift().y));

	// Вот этот грязный хак нужен чтобы таблица перерисовалась
	setEnabled(false);
	setEnabled(true);
	//assert(_model->submit());
	//update();
	//repaint();
	//updateGeometries();

	_isInit = false;
}