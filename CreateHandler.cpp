#include "CreateHandler.h"
#include "SignalerGraphicsView.h"

sgv::CreateHandler::CreateHandler(SignalerGraphicsView& a_view)
	: m_view(a_view)
{
}

void sgv::CreateHandler::mousePressEvent(const QMouseEvent* a_event)
{
	QPointF pos = m_view.scenePosition(a_event);
	QGraphicsItem* item = nullptr;
	if (m_view.scene() != nullptr)
		item = m_view.scene()->itemAt(pos.toPoint(), m_view.transform());

	m_clicked_on_item = (item != nullptr);
}

void sgv::CreateHandler::mouseReleaseEvent(const QMouseEvent* a_event)
{
	bool clicked = m_clicked_on_item;
	m_clicked_on_item = false;
	if (clicked)
		return;

	if (a_event->button() != Qt::LeftButton ||
		m_view.rubberBandRect().isValid()   )
		return;

	QPointF pos = m_view.scenePosition(a_event);
	QGraphicsItem* item = nullptr;
	if (m_view.scene() != nullptr)
		item = m_view.scene()->itemAt(pos, m_view.transform());

	if (item != nullptr)
		return;

	switch(a_event->modifiers())
	{
	case Qt::NoModifier:
		emit m_view.createItem(pos);
		break;
	case Qt::ControlModifier:
		emit m_view.copyItem(pos);
		break;
	}
}
