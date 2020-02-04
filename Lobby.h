#pragma once
#include"gameNode.h"

#define PTM_RATIO 16
class Lobby :public gameNode
{
private:
	image* _lobbyImage;
	b2World* _world;
public:
	Lobby() {};
	~Lobby() {};
	
	HRESULT init();
	void release();
	void update();
	void render();

	void onEnter();
	void onExit();
	void tick(float dt);
	void addNewSpriteAtPosition(b2Vec2 location);
};

