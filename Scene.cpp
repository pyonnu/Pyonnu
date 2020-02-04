#include "stdafx.h"
#include "Scene.h"

HRESULT Scene::init()
{
	SCENEMANAGER->addScene("LobbyScene", _lobby = new Lobby);
	SCENEMANAGER->addScene("MapToolScene", _mapTool = new MapTool);

	SCENEMANAGER->changeScene("LobbyScene");
	return S_OK;
}

void Scene::release()
{
}

void Scene::update()
{
	
}

void Scene::render()
{
	SCENEMANAGER->render();
}
