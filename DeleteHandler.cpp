#include "DeleteHandler.h"
#include "SignalerGraphicsView.h"

sgv::DeleteHandler::DeleteHandler(SignalerGraphicsView& a_view)
	: m_view(a_view)
{
	setParent(&m_view);
}

void sgv::DeleteHandler::mousePressEvent(const QMouseEvent* a_event)
{
	// Disable rubber band selection for RMB to use RMB for deleting only

	if (a_event->button() == Qt::LeftButton)
		m_view.setDragMode(QGraphicsView::DragMode::RubberBandDrag);
	else
		m_view.setDragMode(QGraphicsView::DragMode::NoDrag);
}

void sgv::DeleteHandler::mouseMoveEvent(const QMouseEvent* a_event)
{
	// Delete items while RMB is pressed
	if (!a_event->buttons().testFlag(Qt::RightButton))
		return;
		
	QPointF pos = m_view.scenePosition(a_event);
	QGraphicsItem* item = nullptr;
	if (m_view.scene() != nullptr)
		item = m_view.scene()->itemAt(pos, m_view.transform());

	if (item != nullptr)
		emit m_view.deleteItem(item);
}

void sgv::DeleteHandler::mouseReleaseEvent(const QMouseEvent* a_event)
{
	if (a_event->button() != Qt::RightButton)
		return;

	QPointF pos = m_view.scenePosition(a_event);
	QList<QGraphicsItem*> items;
	if (m_view.scene() != nullptr)
		items = m_view.scene()->items(pos, Qt::IntersectsItemShape, Qt::DescendingOrder, m_view.transform());

	for (auto item: items)
		emit m_view.deleteItem(item);
}
