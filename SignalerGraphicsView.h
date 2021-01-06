#pragma once
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QMouseEvent>
#include <QPoint>
#include "ResizeMode.h"

namespace sgv
{
	class SignalerGraphicsView: public QGraphicsView
	{
		Q_OBJECT
	public:
		SignalerGraphicsView(QWidget* a_parent = nullptr);
	
		void setResizeAreaSize(int a_size);
		void setMinimumItemWidth(int a_width);
		void setMinimumItemHeight(int a_height);
		void setResizeModes(sgv::ResizeMode a_mode);

		QPointF scenePosition(const QMouseEvent* a_event);

	signals:
		void zoomIn();
		void zoomOut();
		void createItem(const QPointF& a_position);
		void copyItem  (const QPointF& a_position);
		void deleteItem(QGraphicsItem* a_item);
		void resizeItem(QGraphicsItem* a_item, sgv::ResizeMode a_mode, const QRectF& a_initial_size, QPointF a_size_delta);
	
	protected:
		virtual void mousePressEvent  (QMouseEvent* a_event) override;
		virtual void mouseMoveEvent   (QMouseEvent* a_event) override;
		virtual void mouseReleaseEvent(QMouseEvent* a_event) override;
		virtual void wheelEvent       (QWheelEvent* a_event) override;

	private:
		QScopedPointer<class CreateHandler> m_create_handler;
		QScopedPointer<class DeleteHandler> m_delete_handler;
		QScopedPointer<class ResizeHandler> m_resize_handler;
		QScopedPointer<class ZoomHandler  > m_zoom_handler;
	};
}
