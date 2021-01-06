#include "MainWidget.h"
#include "ui_MainWidget.h"

MainWidget::MainWidget(QWidget* a_parent)
	: QWidget(a_parent)
	, m_ui(new Ui::MainWidget)
{
	m_ui->setupUi(this);
	m_ui->graphicsView->setScene(&m_scene);
	m_ui->graphicsView->setSceneRect(0,0,1000,1000);
	m_ui->graphicsView->setResizeAreaSize(6);
	m_ui->graphicsView->setMinimumItemWidth(10);
	m_ui->graphicsView->setMinimumItemHeight(10);
	m_ui->graphicsView->setResizeModes( sgv::Left| sgv::Right | sgv::Down );

	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::zoomIn    , this, &MainWidget::onZoomIn);
	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::zoomOut   , this, &MainWidget::onZoomOut);
	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::createItem, this, &MainWidget::onCreate);
	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::copyItem  , this, &MainWidget::onCopy);
	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::deleteItem, this, &MainWidget::onDelete);
	connect(m_ui->graphicsView, &sgv::SignalerGraphicsView::resizeItem, this, &MainWidget::onResize);
}

MainWidget::~MainWidget()
{
	delete m_ui;
}

void MainWidget::onZoomIn()
{
	if (m_scales.prev())
	{
		auto scale = m_scales.value();
		m_ui->graphicsView->setTransform( QTransform::fromScale(scale,scale) );
	}
}

void MainWidget::onZoomOut()
{
	if (m_scales.next())
	{
		auto scale = m_scales.value();
		m_ui->graphicsView->setTransform( QTransform::fromScale(scale,scale) );
	}
}

void MainWidget::onCreate(const QPointF& a_position)
{
	auto item = createItem(a_position, 50, 50);
	QColor color = QRandomGenerator::global()->bounded(0x707070, 0xD0D0D0);
	item->setBrush(color);
	m_scene.addItem(item);
}

void MainWidget::onCopy(const QPointF& a_position)
{
	auto items = m_scene.selectedItems();
	if (items.size() != 1)
		return;

	auto source = dynamic_cast<QGraphicsRectItem*>( items.back() );
	Q_ASSERT(source != nullptr);

	auto item = createItem(
		a_position,
		source->rect().width(),
		source->rect().height() );
	item->setBrush( source->brush() );
	m_scene.addItem(item);
}

void MainWidget::onDelete(QGraphicsItem* a_item)
{
	m_scene.removeItem(a_item);
	delete a_item;
}

void MainWidget::onResize(QGraphicsItem* a_item, sgv::ResizeMode a_mode, const QRectF& a_initial_size, QPointF a_size_delta)
{
	auto item = dynamic_cast<QGraphicsRectItem*>(a_item);
	Q_ASSERT(item != nullptr);

	QRect rect = a_initial_size.toRect();

	if (a_mode.testFlag(sgv::Left))
		rect.setLeft ( rect.left()  + a_size_delta.x());
	else if (a_mode.testFlag(sgv::Right))
		rect.setRight( rect.right() + a_size_delta.x());

	if (a_mode.testFlag(sgv::Up))
		rect.setTop   ( rect.top()    + a_size_delta.y());
	else if (a_mode.testFlag(sgv::Down))
		rect.setBottom( rect.bottom() + a_size_delta.y());

	// Issue: Qt makes it 1 pixel wider and taller each time
	// Fix  : Manual adjustment
	rect.adjust(0,0,-1,-1);

	item->setRect(rect);
}

QGraphicsRectItem* MainWidget::createItem(const QPointF& a_position, int a_width, int a_height)
{
	Q_ASSERT(a_width  > 0);
	Q_ASSERT(a_height > 0);

	auto item = new QGraphicsRectItem(
		a_position.x(),
		a_position.y(),
		a_width,
		a_height);

	item->setFlag(QGraphicsItem::ItemIsSelectable);
	item->setFlag(QGraphicsItem::ItemIsMovable);
	return item;
}
