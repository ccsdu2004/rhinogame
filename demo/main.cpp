#include "rhinoWidget.h"
#include <QtWidgets/QApplication>
#include "world.h"
#include "demo/miniPath/minPath.h"
#include "demo/animation.h"
#include "demo/matrix/matrix.h"
#include "demo/koch/kochScene.h"
#include "demo/title/tileScene.h"
#include "demo/flocking/BoidFlockingWidget.h"
#include "demo/move/moveScene.h"
#include "rhinoWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	rhino w;
	World::getInstance().init(GridCellManager_CellMode6,"rhino.log");
	World::getInstance().setWorldResolution(16);

	World::getInstance().getGridCellManager()->setGridCellVisible(true);
	World::getInstance().setBackGroundColor(QColor(60,60,96));

	QFont font;
	font.setPointSize(9);
	World::getInstance().getResourceManager()->setSpriteFont(font);

	std::shared_ptr<Scene> scene(new MatrixDemo);
	World::getInstance().getSceneManager()->addSceneAsCurrent(scene);

	w.show();
	
	/*BoidFlockingWidget boid;
	boid.show();*/
	return app.exec();
}
