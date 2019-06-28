#ifndef RHINO_DRAWABLE_H
#define RHINO_DRAWABLE_H
#include "rhino.h"

class RHINO_EXPORT Drawable
{
public:
	Drawable();
	virtual ~Drawable();
public:
	void setVisible(bool show = true);
	void hide();
	void show();
	bool isVisible()const;

	void setZOrder(float z);
	float getZOrder()const { return zOrder; }
public:	
	virtual void initGL() = 0;
	virtual void glDraw() = 0;
	virtual void qtDraw(QWidget* widget) = 0;
	virtual void update(int time) = 0;
private:
	bool visible;
	float zOrder;
};

#endif