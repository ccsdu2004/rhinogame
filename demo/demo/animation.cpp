#include <qopengl.h>
#include <QPainter>
#include "world.h"
#include "animation.h"

Animation::Animation()
{
	sprite.reset(new MovingSprite(QPointF(240,180),QSizeF(36,36)));
	sprite->showBorder(true);
	sprite->setSpriteText(QStringLiteral("八路军新一团"));
	sprite->setBorderColor(Qt::blue);
	sprite->setRotate(45.0);
	//sprite->setVel(QVector2D(0.0064,0.0048));
}

Animation::~Animation()
{
}

void Animation::initGL()
{
	QColor bgcolor(30,30,120,120);
	World::getInstance().getGLPainter()->setBackgroundColor(bgcolor);
	glShadeModel(GL_FLAT);

	{
		sprite->setImageFile("data/side1.png");
		auto image = World::getInstance().getResourceManager()->getImageByFile("data/side1.png");
		auto texture = World::getInstance().getResourceManager()->buildTexture(image);
	}
}

void Animation::glDraw()
{
	glPushMatrix();
	sprite->glDraw();
	glPopMatrix();
}

void Animation::qtDraw(QWidget* widget)
{
	sprite->qtDraw(widget);
}

void Animation::update(int time)
{
	sprite->update(time);

	if (sprite->getPosition().x() > 640)
		sprite->setPosition(QVector2D(0, 0));
}

void Animation::mousePressEvent(QMouseEvent* event)
{

}

void Animation::mouseMoveEvent(QMouseEvent* event)
{
}

void Animation::keyPressEvent(QKeyEvent* event)
{

}