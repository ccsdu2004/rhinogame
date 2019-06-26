#include <qrandom.h>
#include <QOpenGLFunctions>
#include <QTime>
#include <QFile>
#include <QTextStream>
#include "world.h"
#include "glPainter.h"
#include "time/timeManagerPriv.h"
#include "gridcell/gridCell4Manager.h"
#include "gridcell/gridCell6Manager.h"
#include "resource/resourceManagerPriv.h"
#include "scene/SceneManagerPriv.h"
#include "troopMatrix.h"

static void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
	QString txt;
	switch (type)
	{
	case QtDebugMsg:
		txt = QString("Debug: %1").arg(msg);
		break;
	case QtWarningMsg:
		txt = QString("Warning: %1").arg(msg);
		break;
	case QtCriticalMsg:
		txt = QString("Critical: %1").arg(msg);
		break;
	case QtFatalMsg:
		txt = QString("Fatal: %1").arg(msg);
		abort();
	default:
		break;
	}

	QString date = QDate::currentDate().toString("yyyy-MM-dd");
	QString time = QTime::currentTime().toString();
	txt = date + " " + time + " " + txt;

	QFile outFile(World::getInstance().getLogName());
	outFile.open(QIODevice::WriteOnly | QIODevice::Append);
	QTextStream ts(&outFile);
	ts << txt << endl;
}

World::World():
logName("rhino"),
worldName("rhino"),
worldSize(640,480),
worldResolution(32),
viewport(640,480)
{
	qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
}

World::~World()
{
}

World& World::getInstance()
{
	static World world;
	return world;
}

void World::init(int cellmode,const QString& logname)
{
	logName = logname;
	qInstallMessageHandler(customMessageHandler);

	painter.reset(new GLPainter());

	if(cellmode == GridCellManager_CellMode4  )
		gridCellManager.reset(new GridCell4Manager());
	else
		gridCellManager.reset(new GridCell6Manager());

	resourceManager.reset(new ResourceManagerPriv());
	sceneManager.reset(new SceneManagerPriv());

	timeManager.reset(new TimeManagerPriv());
}

void World::initGL()
{
	sceneManager->initGL();
}

void World::setViewPort(const QSize& vp)
{
	viewport = vp;
}

QSize World::getViewPort()const
{
	return viewport;
}

void World::setViewPortPos(const QPoint& pos)
{
	viewportPos = pos;
}

QPoint World::getViewPortPos()const
{
	return viewportPos;
}

int World::getFPS()const
{
	return fps;
}

void World::glDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	sceneManager->glDraw();
	gridCellManager->drawGridCell();
}

void World::qtDraw(QWidget* widget)
{
	sceneManager->qtDraw(widget);
}

void World::update(int time)
{
	sceneManager->update(time);
}

void World::update()
{
	updateFPS();
	int time = timeManager->getSpeed();
	update(time);
}

void World::resizeGL(int width,int height)
{
	viewport = QSize(width,height);
	sceneManager->resizeGL(width,height);
}

void World::mousePressEvent(QMouseEvent* event)
{
	sceneManager->mousePressEvent(event);
}

void World::mouseMoveEvent(QMouseEvent* event)
{
	sceneManager->mouseMoveEvent(event);
}

void World::keyPressEvent(QKeyEvent* event)
{
	sceneManager->keyPressEvent(event);
}

void World::updateFPS()
{
	QTime current = QTime::currentTime();
	int delta = lastTime.msecsTo(current);
	
	static float avgDur = 0.0f;
	static float alpha = 0.01f;
	static unsigned int frameCount = 0;

	++frameCount;
	if (1 == frameCount)
		avgDur = static_cast<float>(delta);
	else
		avgDur = avgDur * (1 - alpha) + delta * alpha;

	lastTime = QTime::currentTime();
	fps = static_cast<int>(1.0f / avgDur * 1000);
}