#include "stdafx.h"
#include "Scene.h"

HRESULT Scene::init()
{
	SCENEMANAGER->addScene("LobbyScene", _lobby);
	SCENEMANAGER->addScene("MapToolScene", _mapTool);
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
}
