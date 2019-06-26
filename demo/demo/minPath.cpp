#include <qopengl.h>
#include <QPainter>
#include "world.h"
#include "rhinoMath.h"
#include "minPath.h"

#define START QPoint(0,0)
#define END   QPoint(16,11)

MinPath::MinPath()
{
}

MinPath::~MinPath()
{
}

void MinPath::initGL()
{
	font.setPointSize(11);
	QColor bgcolor(30,30,90,90);
	World::getInstance().getGLPainter()->setBackgroundColor(bgcolor);
}

void MinPath::glDraw()
{
	auto painter = World::getInstance().getGLPainter();

	auto mgr = World::getInstance().getGridCellManager();
	auto res = World::getInstance().getWorldResolution()*0.6;

	painter->setLineWidth(2.0);

	glColor3f(0.9, 0.2, 0.3);
	auto p = mgr->getWorldPosByCellCoordinate(START.x(), START.y());
	painter->drawHexGon(p.x(), p.y(), res*0.6);
	p = mgr->getWorldPosByCellCoordinate(END.x(), END.y());
	painter->drawHexGon(p.x(), p.y(), res*0.6);

	glColor3f(0.6, 0.1, 0.1);
	foreach(auto item, points)
	{
		p = mgr->getWorldPosByCellCoordinate(item.x(), item.y());
		painter->drawWrongNumber(p, res);
	}

	glColor3f(0.1, 0.6, 0.2);

	int count = drawPoints.size();
	if (count > 0)
	{
		for (int i = 0; i < count - 1; i++)
		{
			auto p1 = mgr->getWorldPosByCellCoordinate(drawPoints[i].x(),drawPoints[i].y());
			auto p2 = mgr->getWorldPosByCellCoordinate(drawPoints[i+1].x(), drawPoints[i+1].y());
			painter->drawLine(p1,p2);
		}
	}

	painter->setLineWidth(1.0);
}

void MinPath::qtDraw(QWidget* widget)
{
	QPainter pter(widget);
	pter.setPen(QColor(30,120,90));
	pter.setFont(font);
	pter.drawText(8,20,QStringLiteral("鼠标左键设置和取消障碍,空格键计算最短路径"));
	pter.end();
}

void MinPath::update(int time)
{
}

void MinPath::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::RightButton)
	{
		return;
	}

	lastPos = event->pos();
	int height = World::getInstance().getWorldSize().height();
	auto pos = World::getInstance().getGridCellManager()->getCellCoordinateByWorldPos(lastPos.x(), height - lastPos.y());

	if (pos == START || pos == END)
		return;

	auto itr = qFind(points, pos);
	if (itr == points.end())
		points.push_back(pos);
	else
	{
		std::remove(points.begin(), points.end(), pos);
	}
}

void MinPath::mouseMoveEvent(QMouseEvent* event)
{
}

void MinPath::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key::Key_Space)
	{
		auto edges = World::getInstance().getGridCellManager()->getAdjacentCellsInMap(END.x(), END.y(),points);

		QList<QPoint> allPoints;
		for (int i = 0; i <= END.x(); i++)
			for (int j = 0; j <= END.y(); j++)
			{
				allPoints.append(QPoint(i,j));
			}

		int cnt = floyd(allPoints, edges, START, END, drawPoints);
		if (cnt == -1)
			drawPoints.clear();
	}
}