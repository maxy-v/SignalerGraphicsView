#pragma once
#include <QWidget>
#include <QGraphicsItem>
#include <QRandomGenerator>
#include "../SignalerGraphicsView.h"
#include "../ValueSlider/ValueSlider.h"

namespace Ui { class MainWidget; }

class MainWidget : public QWidget
{
	Q_OBJECT
public:
	MainWidget(QWidget* a_parent = nullptr);
	~MainWidget();

private slots:
	void onZoomIn();
	void onZoomOut();
	void onCreate(const QPointF& a_position);
	void onCopy  (const QPointF& a_position);
	void onDelete(QGraphicsItem* a_item);
	void onResize(QGraphicsItem* a_item, sgv::ResizeMode a_mode, const QRectF& a_initial_size, QPointF a_size_delta);

private:
	QGraphicsRectItem* createItem(const QPointF& a_position, int a_width, int a_height);

	Ui::MainWidget* m_ui;
	QGraphicsScene m_scene;
	ValueSlider<float,3> m_scales{0.7f, 0.8f, 0.9f, 1.0f, 1.1f, 1.2f};
};
