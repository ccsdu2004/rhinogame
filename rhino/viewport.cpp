#include "viewport.h"

Viewport::Viewport():
viewPosition(0,0),
viewSize(640,480)
{
}

Viewport::Viewport(int x,int y,int width,int height):
viewPosition(x,y),
viewSize(width,height)
{
}

void Viewport::setViewport(int x,int y,int width,int height)
{
	setViewPosition(x,y);
	setViewSize(width, height);
}

void Viewport::setViewSize(int width, int height)
{
	viewSize.setWidth(width);
	viewSize.setHeight(height);
}

QSize Viewport::getViewSize()const
{
	return viewSize;
}

void Viewport::setViewPosition(int x,int y)
{
	viewPosition.setX(x);
	viewPosition.setY(y);
}

QPoint Viewport::getViewPosition()const
{
	return viewPosition;
}

bool Viewport::isContain(int x,int y)
{
	if (x < viewPosition.x() ||
		y < viewPosition.y() ||
		x > viewPosition.x() + viewSize.width() ||
		y > viewPosition.y() + viewSize.height())
		return false;

	return true;
}

bool Viewport::isContain(const QPoint& position)
{
	return isContain(position.x(),position.y());
}