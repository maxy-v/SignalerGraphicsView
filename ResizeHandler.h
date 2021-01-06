#pragma once
#include <array>
#include <QMouseEvent>
#include <QGraphicsItem>
#include "ResizeMode.h"

namespace sgv
{
	class ResizeHandler
	{
	public:
		ResizeHandler(class SignalerGraphicsView& a_view);

		void mousePressEvent  (const QMouseEvent* a_event);
		void mouseMoveEvent   (const QMouseEvent* a_event);
		void mouseReleaseEvent(const QMouseEvent* a_event);

		void setAreaSize(int a_size);
		void setMinimumWidth (int a_width);
		void setMinimumHeight(int a_height);
		void setModes(sgv::ResizeMode a_mode);

		bool isResizing() const;

	private:
		QRect resizeArea(const QGraphicsItem* a_item, sgv::ResizeMode a_mode) const;

		class SignalerGraphicsView& m_view;

		// Options

		static constexpr int DefaultAreaSize = 3;
		int                  m_area_size = DefaultAreaSize;

		int m_minimum_item_width  = 1;
		int m_minimum_item_height = 1;

		sgv::ResizeMode m_possible_resize_modes = sgv::All;

		// Resizing process

		sgv::ResizeMode       m_current_mode = sgv::None;
		bool                  m_processing   = false;
		QPointF               m_pivot;
		QList<QGraphicsItem*> m_items;
		QList<QRectF>         m_initial_sizes;
	};
}
