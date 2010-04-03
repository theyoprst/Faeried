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
	
	for (int row = 0; row < ROWS; ++row) {
		_model->setItem(row, 0, new QStandardItem("hello"));
		_model->setItem(row, 1, new QStandardItem("0"));
	}

	setGridStyle(Qt::DotLine);
	for (int i = 0; i < ROWS; ++i) {
		setRowHeight(i, 20);
	}
	setColumnWidth(0, 150);
	setColumnWidth(1, 50);
	verticalHeader()->hide();
	horizontalHeader()->hide();

	_model->setItem(0, 0, new QStandardItem(tr("голова")));
	_model->setItem(1, 0, new QStandardItem(tr("туловище")));
	_model->setItem(2, 0, new QStandardItem(tr("поясница")));
	_model->setItem(3, 0, new QStandardItem(tr("левое предплечье")));
	_model->setItem(4, 0, new QStandardItem(tr("левая рука")));
	_model->setItem(5, 0, new QStandardItem(tr("правое предплечье")));
	_model->setItem(6, 0, new QStandardItem(tr("правая рука")));
	_model->setItem(7, 0, new QStandardItem(tr("левое бедро")));
	_model->setItem(8, 0, new QStandardItem(tr("левая голень")));
	_model->setItem(9, 0, new QStandardItem(tr("правое бедро")));
	_model->setItem(10, 0, new QStandardItem(tr("правая голень")));
	_model->setItem(11, 0, new QStandardItem(tr("смещение по x")));
	_model->setItem(12, 0, new QStandardItem(tr("смещение по y")));

	connect(_model, SIGNAL(dataChanged(const QModelIndex&)), this, SLOT(dataChanged(const QModelIndex&)));

	_isInit = false;
}

void FrameEditorWidget::dataChanged(const QModelIndex& topLeft, const QModelIndex& bottomRight) {
	if (!_isInit) {
		assert(topLeft.column() == bottomRight.column());
		assert(topLeft.row() == bottomRight.row());
		QModelIndex index = topLeft;
		emit UserChangedFrame(CreateFrame());
	}
}

FaerieFrame FrameEditorWidget::CreateFrame() {
	FaerieFrame frame;
	frame.SetBone("head", _model->data(_model->index(0, 1)).toInt());
	frame.SetBone("body", _model->data(_model->index(1, 1)).toInt());
	frame.SetBone("pelvis", _model->data(_model->index(2, 1)).toInt());
	frame.SetBone("leftArm", _model->data(_model->index(3, 1)).toInt());
	frame.SetBone("leftForearm", _model->data(_model->index(4, 1)).toInt());
	frame.SetBone("rightArm", _model->data(_model->index(5, 1)).toInt());
	frame.SetBone("rightForearm", _model->data(_model->index(6, 1)).toInt());
	frame.SetBone("leftThigh", _model->data(_model->index(7, 1)).toInt());
	frame.SetBone("leftLeg", _model->data(_model->index(8, 1)).toInt());
	frame.SetBone("rightThigh", _model->data(_model->index(9, 1)).toInt());
	frame.SetBone("rightLeg", _model->data(_model->index(10, 1)).toInt());
	int x = _model->data(_model->index(11, 1)).toInt();
	int y = _model->data(_model->index(12, 1)).toInt();
	frame.SetShift(FPoint(Point(x, y)));
	return frame;
}