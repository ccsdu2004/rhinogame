#ifndef RHINO_VIEWPORT_H
#define RHINO_VIEWPORT_H
#include <QPoint>
#include <QSize>
#include "rhino.h"

class RHINO_EXPORT Viewport
{
public:
	Viewport();
	Viewport(int x,int y,int width,int height);
	~Viewport() = default;
public:
	void setViewport(int x,int y,int width,int height);

	void setViewSize(int width,int height);
	QSize getViewSize()const;
	
	void setViewPosition(int x,int y);
	QPoint getViewPosition()const;

	bool isContain(int x,int y);
	bool isContain(const QPoint& position);
private:
	QPoint viewPosition;
	QSize viewSize;
};

#endif
