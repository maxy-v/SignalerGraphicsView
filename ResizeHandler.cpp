#include "ResizeHandler.h"
#include "SignalerGraphicsView.h"

sgv::ResizeHandler::ResizeHandler(SignalerGraphicsView& a_view)
	: m_view(a_view)
{
}

void sgv::ResizeHandler::mousePressEvent(const QMouseEvent* a_event)
{
	QPointF pos = m_view.scenePosition(a_event);
	
	QGraphicsItem* item = nullptr;
	if (m_view.scene() != nullptr)
		item = m_view.scene()->itemAt(pos.toPoint(), m_view.transform());

	if (item == nullptr || m_current_mode == sgv::None)
		return;

	m_processing = true;
	m_pivot = pos;
	Q_ASSERT(m_items.size() == 0);
	Q_ASSERT(m_initial_sizes.size() == 0);
	auto selection = m_view.scene()->selectedItems();
	if (selection.contains(item))
		m_items << selection;
	else
		m_items << item;
	for (auto& item: qAsConst(m_items))
		m_initial_sizes << item->boundingRect();
}

void sgv::ResizeHandler::mouseMoveEvent(const QMouseEvent* a_event)
{
	if (m_processing)
	{
		Q_ASSERT(m_current_mode != sgv::None);
		QPointF pos = m_view.scenePosition(a_event);

		Q_ASSERT(m_items.size() == m_initial_sizes.size());
		for (int i = 0; i < m_items.size(); i++)
		{
			qreal dx = pos.x() - m_pivot.x();
			qreal dy = pos.y() - m_pivot.y();
			const QRectF& initial_size = m_initial_sizes[i];

			if (m_current_mode.testFlag(sgv::Left)) {
				if (dx >  initial_size.width()-m_minimum_item_width)
					dx =  initial_size.width()-m_minimum_item_width;
			}
			else if (m_current_mode.testFlag(sgv::Right)) {
				if (dx < -initial_size.width()+m_minimum_item_width)
					dx = -initial_size.width()+m_minimum_item_width;
			}
			else
				dx = 0;

			if (m_current_mode.testFlag(sgv::Up)) {
				if (dy >  initial_size.height()-m_minimum_item_height)
					dy =  initial_size.height()-m_minimum_item_height;
			}
			else if (m_current_mode.testFlag(sgv::Down)) {
				if (dy < -initial_size.height()+m_minimum_item_height)
					dy = -initial_size.height()+m_minimum_item_height;
			}
			else
				dy = 0;

			emit m_view.resizeItem(m_items[i], m_current_mode, initial_size, {dx, dy});
		}
		return;
	}

	// Check resizing possibility

	m_view.setCursor(Qt::ArrowCursor);
	m_current_mode = sgv::None;

	if (a_event->buttons() != Qt::NoButton)
		return;
	
	QPointF pos = m_view.scenePosition(a_event);
	QGraphicsItem* item = nullptr;
	if (m_view.scene() != nullptr)
		item = m_view.scene()->itemAt(pos.toPoint(), m_view.transform());

	if (item == nullptr)
		return;
	
	QPoint cursor_pos = a_event->pos();

	struct AreaDefinition{
		sgv::ResizeModeFlags mode;
		Qt::CursorShape shape;
	};
	constexpr std::array<AreaDefinition, 8> definitions {{
		{ sgv::UpLeft   , Qt::SizeFDiagCursor },
		{ sgv::UpRight  , Qt::SizeBDiagCursor },
		{ sgv::DownLeft , Qt::SizeBDiagCursor },
		{ sgv::DownRight, Qt::SizeFDiagCursor },
		{ sgv::Up       , Qt::SizeVerCursor   },
		{ sgv::Down     , Qt::SizeVerCursor   },
		{ sgv::Left     , Qt::SizeHorCursor   },
		{ sgv::Right    , Qt::SizeHorCursor   },
		}};

	for (size_t index = 0; index < definitions.size(); index++)
	{
		const auto& area = definitions[index];
		if ((m_possible_resize_modes.testFlag(area.mode)) &&
			resizeArea(item, area.mode).contains(cursor_pos))
		{
			m_current_mode = area.mode;
			m_view.setCursor(area.shape);
		}

		if (m_current_mode != sgv::None)
			break;
	}
}

void sgv::ResizeHandler::mouseReleaseEvent(const QMouseEvent* a_event)
{
	Q_UNUSED(a_event);

	m_processing = false;
	m_items.clear();
	m_initial_sizes.clear();
}

void sgv::ResizeHandler::setAreaSize(int a_size)
{
	if (a_size >= 1)
		m_area_size = a_size;
}

void sgv::ResizeHandler::setMinimumWidth(int a_width)
{
	if (a_width > 1)
		m_minimum_item_width = a_width;
}

void sgv::ResizeHandler::setMinimumHeight(int a_height)
{
	if (a_height > 1)
		m_minimum_item_height = a_height;
}

void sgv::ResizeHandler::setModes(sgv::ResizeMode a_mode)
{
	m_possible_resize_modes = a_mode;
}

bool sgv::ResizeHandler::isResizing() const
{
	return m_processing;
}

QRect sgv::ResizeHandler::resizeArea(const QGraphicsItem* a_item, sgv::ResizeMode a_mode) const
{
	QRect item_rect = m_view.mapFromScene(a_item->sceneBoundingRect() ).boundingRect();

	QPoint p;
	switch(a_mode)
	{
	case sgv::UpLeft:
		p = item_rect.topLeft();
		return QRect(p.x(), p.y(),  m_area_size,  m_area_size);
	case sgv::UpRight:
		p = item_rect.topRight();
		return QRect(p.x(), p.y(), -m_area_size,  m_area_size);
	case sgv::DownLeft:
		p = item_rect.bottomLeft();
		return QRect(p.x(), p.y(),  m_area_size, -m_area_size);
	case sgv::DownRight:
		p = item_rect.bottomRight();
		return QRect(p.x(), p.y(), -m_area_size, -m_area_size);
	case sgv::Up:
		return QRect(item_rect.left() , item_rect.top()   , item_rect.width(),  m_area_size);
	case sgv::Down:
		return QRect(item_rect.left() , item_rect.bottom(), item_rect.width(), -m_area_size);
	case sgv::Left:
		return QRect(item_rect.left() , item_rect.top()   ,  m_area_size, item_rect.height());
	case sgv::Right:
		return QRect(item_rect.right(), item_rect.top()   , -m_area_size, item_rect.height());
	default:
		return QRect();
	}
}
