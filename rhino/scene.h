#ifndef RHINO_SCENE_H
#define RHINO_SCENE_H
#include <QString>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QColor>
#include "drawable.h"

class RHINO_EXPORT Scene : public Drawable
{
public:
	Scene();
	virtual ~Scene() = 0;
public:
	void setName(const QString& name) { sceneName = name; }
	QString getName()const { return sceneName; }

	void setBackGroundColor(const QColor& color) { backgroundColor = color; }
	QColor getBackGroundColor()const { return backgroundColor; }
public:
	virtual void initGL() = 0;
	virtual void glDraw() = 0;
	virtual void qtDraw(QWidget* widget) = 0;
	virtual void update(int time) = 0;
public:
	virtual void resizeGL(int width,int height);
	virtual void mousePressEvent(QMouseEvent* event) {}
	virtual void mouseMoveEvent(QMouseEvent* event) {}
	virtual void keyPressEvent(QKeyEvent* event) {}
private:
	QString sceneName;
	QColor  backgroundColor;
};

#endif