#include "rhinoWidget.h"
#include <QtWidgets/QApplication>
#include "world.h"
#include "demo/minPath.h"
#include "demo/animation.h"
#include "demo/matrix.h"
#include "koch/kochScene.h"
#include "rhinoWidget.h"
#include "tile/tileScene.h"
#include "flocking/BoidFlockingWidget.h"

int main(int argc, char *argv[])
{
	QApplication app(argc,argv);

	rhino w;
	World::getInstance().init(GridCellManager_CellMode6,"rhino.log");
	World::getInstance().setWorldResolution(24);

	World::getInstance().getGridCellManager()->setGridCellVisible(true);
	World::getInstance().setBackGroundColor(Qt::blue);

	QFont font;
	font.setPointSize(9);
	World::getInstance().getResourceManager()->setSpriteFont(font);

	std::shared_ptr<Scene> scene(new MinPath());
	World::getInstance().getSceneManager()->addSceneAsCurrent(scene);

	w.show();
	
	/*BoidFlockingWidget boid;
	boid.show();*/
	return app.exec();
}
