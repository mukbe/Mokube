#pragma once
#include "Unit.h"
#include <deque>

class PathFinder;
class Tile;
class Player : public Unit
{
public:

	Player(string name, D3DXVECTOR2 pos, D3DXVECTOR2 size, ObjectType type, Pivot p = Pivot::CENTER);
	virtual~Player();

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
	virtual void ImguiRender();
private:

	shared_ptr<Texture> tex;


	PathFinder* path;
};

