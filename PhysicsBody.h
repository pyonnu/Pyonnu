#pragma once
#include"DrawComponent.h"
enum BodyType
{
	DYNAMIC,
	STATIC,
	KINEMATIC
};


class PhysicsBody : public DrawComponent
{
private:
	b2Body *_body;
	BodyType _type;
	Vector2 scale;
	bool _bodyActive;

public:
	PhysicsBody() { _name = "PhysicsBody"; }
	//�ٵ� Ÿ��, ������, �е�(�⺻1), �ݹ߷� (�⺻0), bullet�ΰ�, �վ �Ǵ� �ٵ��ΰ�
	void Init(BodyType type, float32 friction, float32 density=1, float32 restitution = 0 , BOOL isBullet = FALSE, BOOL isSensor = FALSE);
	void SetBodyPosition();
	virtual void Render()override;

	//�ٵ� ������ ��������
	Vector2 GetBodyPosition();
	//��� ����
	Vector2 GetBodyScale();
	//�ٵ��� Rotate ��������
	float GetBodyAngle() { return _body->GetAngle(); }
	bool GetBodyActive() { return _bodyActive; }
	//�ٵ� ��������
	inline b2Body* GetBody() { return _body; }
	//�ٵ��� GetWorldCenter ��������
	inline const b2Vec2 GetWorldCenter() { return _body->GetWorldCenter(); }
	//�ٵ��� Active ���� Ű�� ���� (������ ������)
	void SetBodyActive(bool sleep);
	//�ٵ� �� �ۿ� ��Ű��
	inline void ApplyForce(b2Vec2 force, bool wake = true) { _body->ApplyForce(force, _body->GetWorldCenter(), wake); }
	//���� ����
	void SetSensor(bool sensor);
	Vector2 Convert(Vector2 origin);
};