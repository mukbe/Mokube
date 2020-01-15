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

	//초기화
	virtual void Init();
	//메모리 해제
	virtual void Release();
	//카메라에 관한 최초업데이트 - 사용 안해두됨
	virtual void PreUpdate();
	//메인 루틴
	virtual void Update(float tick);
	//이동관련 계산
	virtual void PostUpdate();

	//이미지 렌더링 - direct2D
	virtual void Render(bool isRelative = true);
	//후처리 렌더링 -direct3D
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