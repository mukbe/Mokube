#pragma once

using namespace D2D1;

class Matrix2D
{
private:
	static 	ID2D1RenderTarget* renderTarget;

public:
	static void SetRenderTarget();

private:
	Matrix3x2F rotate;
	Matrix3x2F scale;
	Matrix3x2F trans;
	Matrix3x2F result;

	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	float rotation;
	Pivot pivot;

	FloatRect rc;

	void UpdateMatrix();

public:
	Matrix2D();
	Matrix2D(D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p);

	Matrix3x2F GetResult() { return result; }
	D3DXVECTOR2 GetPos() { return pos; }
	D3DXVECTOR2 GetSize() { return size; }
	Pivot GetPivot() { return pivot; }
	FloatRect GetRect() { return rc; }
	float GetRotation() { return rotation; }

	void SetScale(D3DXVECTOR2 s, D3DXVECTOR2 center);
	void SetScale(D3DXVECTOR2 s);
	void SetScale(float x, float y);
	void SetScale(float v);

	void SetSize(D3DXVECTOR2 s);
	void SetSize(float v);
	void SetSize(float x, float y);

	void SetRotate(float rad, D3DXVECTOR2 pos = D3DXVECTOR2(0,0), bool isLocal = true);
	//for physics
	void SetRadian(float rad);

	void SetPos(D3DXVECTOR2 p);
	void SetPos(float x, float y);
	void SetPos(POINT p);
	
	Matrix3x2F GetInv() 
	{
		Matrix3x2F temp = result;
		D2D1InvertMatrix(&temp);
		return temp;
		
	}
	FloatRect GetWorldRect(FloatRect localRect);


	void Bind();

	void Render();

	Matrix2D operator*(const Matrix2D& other);
	
};

