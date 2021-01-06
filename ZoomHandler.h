#pragma once
#include <QMouseEvent>
#include <QGraphicsItem>
#include "ResizeMode.h"

namespace sgv
{
	class ZoomHandler
	{
	public:
		ZoomHandler(class SignalerGraphicsView& a_view);

		void wheelEvent(const QWheelEvent* a_event);

	private:
		class SignalerGraphicsView& m_view;
	};
}
