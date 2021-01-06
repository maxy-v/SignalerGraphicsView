#pragma once
#include <array>
#include <QMouseEvent>
#include <QGraphicsItem>

namespace sgv
{
	class CreateHandler: public QObject
	{
		Q_OBJECT
	public:
		CreateHandler(class SignalerGraphicsView& a_view);

		void mousePressEvent  (const QMouseEvent* a_event);
		void mouseReleaseEvent(const QMouseEvent* a_event);

	private:
		class SignalerGraphicsView& m_view;
		bool m_clicked_on_item = false;
	};
}
