#pragma once
#include <QMouseEvent>
#include <QGraphicsItem>

namespace sgv
{
	class DeleteHandler
	{
	public:
		DeleteHandler(class SignalerGraphicsView& a_view);

		void mousePressEvent  (const QMouseEvent* a_event);
		void mouseMoveEvent   (const QMouseEvent* a_event);
		void mouseReleaseEvent(const QMouseEvent* a_event);

	private:
		class SignalerGraphicsView& m_view;
	};
}
