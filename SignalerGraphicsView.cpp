#include "SignalerGraphicsView.h"
#include "CreateHandler.h"
#include "DeleteHandler.h"
#include "ResizeHandler.h"
#include "ZoomHandler.h"

sgv::SignalerGraphicsView::SignalerGraphicsView(QWidget* a_parent)
	: QGraphicsView(a_parent)
	, m_create_handler( new sgv::CreateHandler(*this)  )
	, m_delete_handler( new sgv::DeleteHandler(*this)  )
	, m_resize_handler( new sgv::ResizeHandler(*this)  )
	, m_zoom_handler  ( new sgv::ZoomHandler  (*this)  )
{
	// For proper mouse move handling
	setMouseTracking(true);
}

void sgv::SignalerGraphicsView::setResizeAreaSize(int a_size)
{
	Q_ASSERT(a_size >= 1);
	m_resize_handler->setAreaSize(a_size);
}

void sgv::SignalerGraphicsView::setMinimumItemWidth(int a_width)
{
	Q_ASSERT(a_width >= 1);
	m_resize_handler->setMinimumWidth(a_width);
}

void sgv::SignalerGraphicsView::setMinimumItemHeight(int a_height)
{
	Q_ASSERT(a_height >= 1);
	m_resize_handler->setMinimumHeight(a_height);
}

void sgv::SignalerGraphicsView::setResizeModes(sgv::ResizeMode a_mode)
{
	m_resize_handler->setModes(a_mode);
}

void sgv::SignalerGraphicsView::mousePressEvent(QMouseEvent* a_event)
{
	m_create_handler->mousePressEvent(a_event);
	m_delete_handler->mousePressEvent(a_event);
	m_resize_handler->mousePressEvent(a_event);
	if (!m_resize_handler->isResizing())
		// Prevent default handling (moving, selecting)
		QGraphicsView::mousePressEvent(a_event);
}

void sgv::SignalerGraphicsView::mouseMoveEvent(QMouseEvent* a_event)
{
	m_resize_handler->mouseMoveEvent(a_event);
	m_delete_handler->mouseMoveEvent(a_event);
	QGraphicsView   ::mouseMoveEvent(a_event);
}

void sgv::SignalerGraphicsView::mouseReleaseEvent(QMouseEvent* a_event)
{
	m_create_handler->mouseReleaseEvent(a_event);
	m_delete_handler->mouseReleaseEvent(a_event);
	m_resize_handler->mouseReleaseEvent(a_event);
	QGraphicsView::mouseReleaseEvent(a_event);
}

void sgv::SignalerGraphicsView::wheelEvent(QWheelEvent* a_event)
{
	m_zoom_handler->wheelEvent(a_event);
	QGraphicsView::wheelEvent(a_event);
}

QPointF sgv::SignalerGraphicsView::scenePosition(const QMouseEvent* a_event)
{
	QPoint  local_pos = a_event->localPos().toPoint();
	QPointF scene_pos = mapToScene(local_pos);
	return scene_pos;
}
