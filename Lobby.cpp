#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	_lobbyImage = IMAGEMANAGER->addImage("LobbyImage","Resources/Lobby/Lobby.bmp",1280,720,false,RGB(255,0,255));

	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	// 월드를 생성한다.
	_world = new b2World(gravity);
	// 휴식 상태일때 포함된 바디들을 멈추게(sleep) 할 건지 결정한다.
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

    // 가장자리(테두리)를 지정하여 공간(Ground Box)을 만든다.
    // 바디데프에 좌표를 설정한다.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);

    // 월드에 바디데프의 정보(좌표)로 바디를 만든다.
    b2Body* groundBody = _world->CreateBody(&groundBodyDef);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.0f, 10.0f);
    groundBody->CreateFixture(&groundBox, 0.0f);

    _timeStep = 1.0f / 60.0f;
    _velocityIterations = 6;
    _positionIterations = 2;

    

	return S_OK;
}

void Lobby::release()
{
    delete _world;
    _world = nullptr;
}

void Lobby::update()
{
}

void Lobby::render()
{
}

void Lobby::onEnter()
{
}

void Lobby::onExit()
{
}

void Lobby::tick(float dt)
{
}

void Lobby::addNewSpriteAtPosition(b2Vec2 location)
{
}
