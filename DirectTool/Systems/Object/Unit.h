#pragma once
#include <deque>

class Tile;
class Unit : public GameObject
{
	friend class StateBase;
	friend class StateOneStep;
	friend class StateIdle;
public:
	Unit(string name = "");
	Unit(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~Unit();

	//�ʱ�ȭ
	virtual void Init();
	//�޸� ����
	virtual void Release();
	//ī�޶� ���� ���ʾ�����Ʈ - ��� ���صε�
	virtual void PreUpdate();
	//���� ��ƾ
	virtual void Update(float tick);
	//�̵����� ���
	virtual void PostUpdate();

	//�̹��� ������ - direct2D
	virtual void Render(bool isRelative = true);
	//��ó�� ������ -direct3D
	virtual void PostRender();
	//imgui debugUI render
	virtual void ImguiRender() {}

	void ChangeState(string key);
	void SetTurn(bool val) { bMyTurn = val; }
	bool IsMoving() { return bMoving; }
	bool IsMyTurn() { return bMyTurn; }
protected:
	unordered_map<string, class StateBase*> states;
	StateBase* currentState;
	deque<Tile*> path;

	bool bMoving;
	bool bMyTurn;
};



class StateBase
{
public:
	StateBase(Unit* p)
		:me(p) {}
	virtual void Enter() = 0;
	virtual void Update() = 0;
protected:
	Unit* me;
};

class StateOneStep : public StateBase
{
public:
	StateOneStep(Unit* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
	float time;
};
class StateIdle : public StateBase
{
public:
	StateIdle(Unit* p) : StateBase(p) {}
	virtual void Enter();
	virtual void Update();
private:
};