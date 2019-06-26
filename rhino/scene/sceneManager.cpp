#include <algorithm>
#include "sceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

void SceneManager::setCurrentScene(std::shared_ptr<Scene> scene)
{
	if(currentScene == scene)
		return;

	if (!hasScene(scene))
		return;

	currentScene = scene;
}
	
std::shared_ptr<Scene> SceneManager::getCurrentScene()
{
	return currentScene;
}

void SceneManager::addScene(std::shared_ptr<Scene> scene)
{
	if (hasScene(scene))
		return;

	scenes.push_back(scene);
}

void SceneManager::addSceneAsCurrent(std::shared_ptr<Scene> scene)
{
	if (hasScene(scene))
		return;

	currentScene = scene;
	scenes.push_back(scene);
}
	
void SceneManager::removeScene(std::shared_ptr<Scene> scene)
{
	auto itr = std::find(scenes.begin(), scenes.end(), scene);
	if (itr == scenes.end())
		return;

	scenes.removeOne(scene);
}

bool SceneManager::hasScene(std::shared_ptr<Scene> scene)
{
	auto itr = std::find(scenes.begin(), scenes.end(), scene);
	return itr != scenes.end();
}

int SceneManager::getSceneSize()
{
	return scenes.size();
}