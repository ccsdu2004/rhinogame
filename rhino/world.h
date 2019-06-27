#ifndef RHINO_WORLD_H
#define RHINO_WORLD_H
#include <cstdint>
#include <memory>
#include <QString>
#include <QSize>
#include <QRect>
#include <QTime>
#include <QWidget>
#include "glPainter.h"
#include "viewport.h"
#include "gridCellManger.h"
#include "timeManager.h"
#include "resourceManager.h"
#include "scene.h"
#include "sceneManager.h"

class RHINO_EXPORT World : public Scene
{
	Q_DISABLE_COPY(World)
public:
	~World();
	static World& getInstance();
public:
	void init(int cellmode,const QString& log);
	void initGL();

	QString getLogName()const { return logName; }

	void setWorldName(const QString& name) { worldName = name; }
	QString getWorldName()const { return worldName; }

	void setWorldSize(const QSize& size) { worldSize = size; }
	QSize getWorldSize()const { return worldSize; }

	void setWorldResolution(int32_t resolution) { worldResolution = resolution; }
	int32_t getWorldResolution()const { return worldResolution; }

	int getFPS()const;
public:
	Viewport* getViewport()const { return viewport.get(); }
	TimeManager* getTimeManager()const { return timeManager.get(); }
	ResourceManager* getResourceManager()const { return resourceManager.get(); }
	GridCellManager* getGridCellManager()const { return gridCellManager.get(); }
	SceneManager* getSceneManager()const { return sceneManager.get(); }
	GLPainter* getGLPainter()const { return painter.get(); }
public:
	void glDraw();
	void qtDraw(QWidget* widget);
	void update(int time);
	void update();
public:
	void resizeGL(int width,int height);
	void mousePressEvent(QMouseEvent* event);
	void mouseMoveEvent(QMouseEvent* event);
	void keyPressEvent(QKeyEvent* event);
private:
	void drawGridCell();
	void updateFPS();
private:
	World();

	QString logName;
	QString worldName;
	QSize worldSize;
	int32_t worldResolution;

	std::unique_ptr<Viewport> viewport;
	std::unique_ptr<TimeManager> timeManager;
	std::unique_ptr<ResourceManager> resourceManager;
	std::unique_ptr<GridCellManager> gridCellManager;
	std::unique_ptr<SceneManager> sceneManager;
	std::unique_ptr<GLPainter> painter;

	int fps;
	QTime lastTime;
};

#endif