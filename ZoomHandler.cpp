#include "ZoomHandler.h"
#include "SignalerGraphicsView.h"

sgv::ZoomHandler::ZoomHandler(SignalerGraphicsView& a_view)
	: m_view(a_view)
{
}

void sgv::ZoomHandler::wheelEvent(const QWheelEvent* a_event)
{
	if (a_event->modifiers() == Qt::ControlModifier)
	{
		int dy = a_event->angleDelta().y();
		if (dy != 0)
		{
			if      (dy < 0)
				emit m_view.zoomIn();
			else if (dy > 0)
				emit m_view.zoomOut();
		}
		return;
	}
}
