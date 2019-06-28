#include <qopengl.h>
#include "world.h"
#include "kochScene.h"

KochScene::KochScene()
{
}

KochScene::~KochScene()
{
}

void KochScene::initGL()
{
	glShadeModel(GL_FLAT);
}

void KochScene::glDraw()
{
	glPushMatrix();

	World::getInstance().getGLPainter()->setColor(Qt::gray);

	int width = World::getInstance().getViewport()->getViewSize().width();
	int height = World::getInstance().getViewport()->getViewSize().height();
 
	QVector2D beg,end;
	beg.setX(width/3);
	beg.setY(height/3*2);
	end.setX(width/3*2);
	end.setY(height/3*2);
	drawKoch(beg,end,8,true);

	beg.setX(width/3);
	beg.setY(height/3*2);
	end.setX(width/2);
	end.setY(height/3*2-(width/3)*(sqrt(3)/2));
	drawKoch(beg,end,8,false);

	beg.setX(width/2);
	beg.setY(height/3*2-(width/3)*(sqrt(3)/2));
	end.setX(width/3*2);
	end.setY(height/3*2);
	drawKoch(beg,end,8,false);

	glPopMatrix();
}

void KochScene::qtDraw(QWidget* widget)
{
}

void KochScene::update(int time)
{
}

void KochScene::mousePressEvent(QMouseEvent* event)
{

}

void KochScene::mouseMoveEvent(QMouseEvent* event)
{
}

void KochScene::keyPressEvent(QKeyEvent* event)
{
}

void KochScene::drawKoch(const QVector2D& beg,const QVector2D& end,int depth,bool left)
{
	if(depth == 0)
	{
		World::getInstance().getGLPainter()->drawLine(QPointF(beg.x(),beg.y()),QPointF(end.x(),end.y()));
		return;
	}

	QVector2D pts[3];
	QVector2D vct = end - beg;
	pts[0] = beg + (vct * (1.0 / 3.0));
	pts[2] = beg + (vct * (2.0 / 3.0));
	
	QVector2D nvct;

	if (left)
	{
		nvct.setX(-vct.y());
		nvct.setY(vct.x());
	}
	else
	{
		nvct.setX(vct.y());
		nvct.setY(-vct.x());
	}

	double size = sqrt(nvct.x() * nvct.x() + nvct.y() * nvct.y());
	double len = (size / 3) * (sqrt(3) / 2);
	nvct.setX(nvct.x() / size * len);
	nvct.setY(nvct.y() / size * len);
	pts[1] = beg + (vct * 0.5);
	pts[1] = pts[1] + nvct;

	drawKoch(beg, pts[0], depth - 1, left);
	drawKoch(pts[0], pts[1], depth - 1, left);
	drawKoch(pts[1], pts[2], depth - 1, left);
	drawKoch(pts[2], end, depth - 1, left);
}