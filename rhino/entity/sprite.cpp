#include <QDebug>
#include <QPainter>
#include "sprite.h"
#include "world.h"
#include "rhinoMath.h"
#include "resourceManager.h"
#include <iostream>

#define SPRITE_POLYGON_SIZE 0.75

Sprite::Sprite():
spriteID(-1),
visibleBorder(false),
borderColor(Qt::blue)
{
}

Sprite::Sprite(const QPointF& position,const QSizeF& size):
Entity(position,size),
spriteID(-1),
visibleBorder(false),
borderColor(Qt::blue)
{
}

Sprite::Sprite(const QPointF& position,const QSizeF& size,std::shared_ptr<QImage> image):
Entity(position,size),
spriteID(-1),
spriteImage(image),
visibleBorder(false),
borderColor(Qt::blue)
{
}

Sprite::Sprite(std::shared_ptr<QImage> image):
spriteID(-1),
spriteImage(image),
visibleBorder(false),
borderColor(Qt::blue)
{
}

Sprite::~Sprite()
{
}

void Sprite::setSpriteID(int id)
{
	spriteID = id;
}

QString Sprite::getSpriteName()const
{
	return spriteName;
}

void Sprite::setSpriteText(const QString& text)
{
	spriteText = text;
}

QString Sprite::getSpriteText()const
{
	return spriteText;
}

void Sprite::setSpriteTextColor(const QColor& color)
{
	spriteTextColor = color;
}

QColor Sprite::getSpriteTextColor()const
{
	return spriteTextColor;
}

void Sprite::setSpriteImage(std::shared_ptr<QImage> image)
{
	spriteImage = image;
}

void Sprite::setSpriteColor(const QColor& color)
{
	spriteColor = color;
}

QColor Sprite::getSpriteColor()const
{
	return spriteColor;
}

void Sprite::showBorder(bool show)
{
	visibleBorder = show;
}

bool Sprite::isShowBorder()const
{
	return visibleBorder;
}

void Sprite::setBorderColor(const QColor& color)
{
	borderColor = color;
}

QColor Sprite::getBorderColor()const
{
	return borderColor;
}

void Sprite::initGL()
{
}

void Sprite::glDraw()
{
	if(spriteImage)
		drawTexture();
	else
		drawPolygon();
	drawBorder();
}

void Sprite::qtDraw(QWidget* widget)
{
	if(spriteText.isEmpty())
		return;

	QPainter painter(widget);
	painter.setPen(spriteTextColor);
	painter.setFont(World::getInstance().getResourceManager()->getSpriteFont());

	auto viewportSize = World::getInstance().getViewport()->getViewSize();
	QPoint pos(getPosition().x(),viewportSize.height()-getPosition().y());
	
	const int offset = 20;
	
	painter.drawText(pos.x(),pos.y()+offset,spriteText);
}

void Sprite::update(int time)
{
	Q_UNUSED(time)
}

void Sprite::drawTexture()
{
	auto texture = World::getInstance().getResourceManager()->buildTexture(spriteImage);
	if (!texture)
		return;

	auto id = texture->textureId();

	float cor[] = {0,0,1,0,1,1,0,1};

	QVector2D pos = getPosition();
	QSizeF  size = getSize();

	glPushMatrix();
	glTranslatef(pos.x(),pos.y(),0.0f);
	float r = getRotate();
	if(!rhino::isZero(r))
		glRotatef(getRotate(), 0, 0, 1.0f);
	glTranslatef(-pos.x(),-pos.y(), 0.0f);

	float vertices[] = 
	{
		pos.x() - size.width()*0.5f,pos.y() - size.height()*0.5f,
		pos.x() + size.width()*0.5f,pos.y() - size.height()*0.5f,
		pos.x() + size.width()*0.5f,pos.y()+size.height()*0.5f,
		pos.x() - size.width()*0.5f,pos.y()+ size.height()*0.5f
	};

	World::getInstance().getGLPainter()->drawTexture(id,cor,vertices);
	glPopMatrix();
}

void Sprite::drawPolygon()
{
	GLScopedColor scoped;
	
	glPushMatrix();
	glTranslatef(pos.x(),pos.y(),0.0f);
	glRotatef(getRotate(),0,0,1.0f);
	glTranslatef(-pos.x(),-pos.y(),0.0f);

	World& world = World::getInstance();
	
	if (world.getGridCellManager()->getCellMode() == GridCellManager_CellMode6)
	{
		float size = std::min<float>(getSize().width(), getSize().height())*SPRITE_POLYGON_SIZE;
		world.getGLPainter()->drawHexGon(pos.x(), pos.y(), size, spriteColor);
	}
	else
	{
		world.getGLPainter()->setColor(spriteColor);
		float w = getSize().width()*SPRITE_POLYGON_SIZE;
		float h = getSize().height()*SPRITE_POLYGON_SIZE;
		float x = getPosition().x();
		float y = getPosition().y();
		world.getGLPainter()->drawRectangle(x-0.5*w,y-0.5*h,w,h,true);
	}
	glPopMatrix();
}

void Sprite::drawBorder()
{
	if(visibleBorder)
	{
		GLScopedColor scpoed;
		auto pos = getPosition();
		auto size = getSize();
		World::getInstance().getGLPainter()->setColor(borderColor);

		glTranslatef(pos.x(),pos.y(),0.0f);
		glRotatef(getRotate(),0,0,1.0f);
		glTranslatef(-pos.x(),-pos.y(),0.0f);
		World::getInstance().getGLPainter()->setLineWidth(2.0);
		World::getInstance().getGLPainter()->drawRectangle(pos.x()-size.width()*0.5,pos.y()-size.height()*0.5,size.width(),size.height(), false);
		World::getInstance().getGLPainter()->setLineWidth(1.0);
	}
}