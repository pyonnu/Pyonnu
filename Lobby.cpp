#include "stdafx.h"
#include "Lobby.h"

HRESULT Lobby::init()
{
	_lobbyImage = IMAGEMANAGER->addImage("LobbyImage","Resources/Lobby/Lobby.bmp",1280,720,false,RGB(255,0,255));

	b2Vec2 gravity = b2Vec2(0.0f, -10.0f);
	// ���带 �����Ѵ�.
	_world = new b2World(gravity);
	// �޽� �����϶� ���Ե� �ٵ���� ���߰�(sleep) �� ���� �����Ѵ�.
	_world->SetAllowSleeping(true);
	_world->SetContinuousPhysics(true);

    // �����ڸ�(�׵θ�)�� �����Ͽ� ����(Ground Box)�� �����.
    // �ٵ����� ��ǥ�� �����Ѵ�.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0);

    // ���忡 �ٵ����� ����(��ǥ)�� �ٵ� �����.
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
