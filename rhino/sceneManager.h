#ifndef RIHINO_SCENEMANAGER_H
#define RIHINO_SCENEMANAGER_H
#include <memory>
#include <QVector>
#include "scene.h"

class RHINO_EXPORT SceneManager : public Scene
{
public:
	SceneManager();
	virtual ~SceneManager();
public:
	void setCurrentScene(std::shared_ptr<Scene> scene);
	std::shared_ptr<Scene> getCurrentScene();

	void addScene(std::shared_ptr<Scene> scene);
	void addSceneAsCurrent(std::shared_ptr<Scene> scene);
	void removeScene(std::shared_ptr<Scene> scene);

	bool hasScene(std::shared_ptr<Scene> scene);

	int getSceneSize();
private:
	std::shared_ptr<Scene> currentScene;
	QVector<std::shared_ptr<Scene>> scenes;
};

#endif