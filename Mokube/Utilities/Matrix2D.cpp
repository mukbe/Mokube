#include "stdafx.h"
#include "Matrix2D.h"


ID2D1RenderTarget* Matrix2D::renderTarget = nullptr;

void Matrix2D::SetRenderTarget()
{
	if (renderTarget != nullptr)
	{
		LOG->Warning(__FILE__ , __LINE__, "Matrix2D Already Connected RenderTarget");
		return;
	}
	
	Log_WarnAssert(renderTarget = p2DRenderer->GetRenderTarget());
}

void Matrix2D::UpdateMatrix()
{
	//SRT
	result = scale * rotate * trans;
	rc = FloatRect(pos, size, pivot);
}

Matrix2D::Matrix2D()
	:pos(0, 0), size(0, 0), rotation(0.f), pivot(Pivot::LEFT_TOP)
{
	result = rotate = trans = scale = Matrix3x2F::Identity();
}

Matrix2D::Matrix2D(D3DXVECTOR2 pos, D3DXVECTOR2 size, Pivot p)
{
	result = rotate = Matrix3x2F::Identity();
	trans = Matrix3x2F::Translation(pos.x, pos.y);
	scale = Matrix3x2F::Identity();
	rotation = 0.f;
	this->pos = pos;
	this->size = size;
	pivot = p;

	UpdateMatrix();
}

void Matrix2D::SetScale(D3DXVECTOR2 s, D3DXVECTOR2 center)
{
	scale = Matrix3x2F::Scale(s.x, s.y, Point2F(center.x,center.y));
	UpdateMatrix();
	
}

void Matrix2D::SetScale(D3DXVECTOR2 s)
{
	scale = Matrix3x2F::Scale(s.x, s.y);
	UpdateMatrix();
}

void Matrix2D::SetScale(float x, float y)
{
	scale = Matrix3x2F::Scale(x, y);
	UpdateMatrix();

}

void Matrix2D::SetScale(float v)
{
	scale = Matrix3x2F::Scale(v,v);
	UpdateMatrix();
}

void Matrix2D::SetSize(D3DXVECTOR2 s)
{
	size = s;
	UpdateMatrix();
}

void Matrix2D::SetSize(float v)
{
	size = { v,v };
	UpdateMatrix();
}

void Matrix2D::SetSize(float x, float y)
{
	size = {x, y};
	UpdateMatrix();
}

void Matrix2D::SetRotate(float rad, D3DXVECTOR2 pos, bool isLocal)
{
	rotation = rad;
	if (isLocal)
	{
		rotate = Matrix3x2F::Rotation(D3DXToDegree(rad), Point2F(pos.x, pos.y));
	}
	else
	{
		rotate = Matrix3x2F::Rotation(D3DXToDegree(rad));
	}

	UpdateMatrix();
}

void Matrix2D::SetRadian(float rad)
{
	rotation = rad;
	rotate = Matrix3x2F::Rotation(D3DXToDegree(rad));
	UpdateMatrix();
}

void Matrix2D::SetPos(D3DXVECTOR2 p)
{
	pos = p;
	trans = Matrix3x2F::Translation(p.x, p.y);
	UpdateMatrix();
}

void Matrix2D::SetPos(float x, float y)
{
	pos = { x,y };
	trans = Matrix3x2F::Translation(x, y);
	UpdateMatrix();
}

void Matrix2D::SetPos(POINT p)
{
	pos = { (float)p.x, (float)p.y };
	trans = Matrix3x2F::Translation(p.x, p.y);
	UpdateMatrix();
}

FloatRect Matrix2D::GetWorldRect(FloatRect localRect)
{
	D2D1_POINT_2F lt = { localRect.left,localRect.top };
	D2D1_POINT_2F rb = { localRect.right,localRect.bottom };

	lt = lt * result;
	rb = rb * result;

	FloatRect temp;
	temp.left = lt.x;
	temp.top = lt.y;
	temp.right = rb.x;
	temp.bottom = rb.y;

	return temp;
}

void Matrix2D::Bind()
{
	renderTarget->SetTransform(result);
}

void Matrix2D::Render()
{
	FloatRect temp(D3DXVECTOR2(0.f, 0.f), size, pivot);
	p2DRenderer->DrawRectangle(temp, DefaultBrush::black);
}

//테스트 안해봄
Matrix2D  Matrix2D::operator*(const Matrix2D & other)
{
	Matrix2D val;
	val.scale = this->scale * other.scale;
	val.rotate = this->rotate * other.rotate;
	val.trans = this->trans * other.trans;
	val.result = this->result * other.result;
	val.pos = this->pos + other.pos;
	val.size.x = this->size.x * other.size.x;
	val.size.y = this->size.y * other.size.y;
	val.rotation = this->rotation + other.rotation;

	return val;
}


