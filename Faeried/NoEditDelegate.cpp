#include "NoEditDelegate.h"

NoEditDelegate::NoEditDelegate()
	: QItemDelegate()
{
}

QWidget* NoEditDelegate::createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const {
	return NULL;
}
