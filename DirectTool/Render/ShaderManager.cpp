#include "stdafx.h"
#include "ShaderManager.h"
//#include "./ComputeShader/ComputeShader.h"

SingletonCpp(ShaderManager)

ShaderManager::ShaderManager()
{
	
}


ShaderManager::~ShaderManager()
{
	ShadersIter Iter = shaders.begin();

	for (Iter; Iter != shaders.end(); ++Iter)
	{
		if (Iter->second.use_count() != 1)
		{
			LOG->Warning(__FILE__, __LINE__, "shared_ptr<Shader> use count != 1");
		}

	}

	shaders.clear();
}


shared_ptr<Shader> ShaderManager::CreateShader(string key, wstring fileName, Shader::ShaderType type, string funcName)
{
	shared_ptr<Shader> shader;
	shader = FindShader(key);

	if (shader == nullptr)
	{
		shader = make_shared<Shader>(ShaderPath + fileName, type, funcName);
		shaders.insert(make_pair(key, shader));
	}

	return shader;
}

shared_ptr<Shader> ShaderManager::FindShader(string key)
{
	ShadersIter Iter = shaders.begin();

	for (Iter; Iter != shaders.end(); ++Iter)
	{
		if (key == Iter->first)
			return Iter->second;
	}

	return nullptr;
}

void ShaderManager::BindShader(string key)
{
	currentShader = FindShader(key);

	if (currentShader != nullptr)
		currentShader->Render();
}

void ShaderManager::ReleaseShader()
{
	currentShader->ReleaseShader();
}

//ComputeShader * ShaderManager::CreateComputeShader(string key, wstring fileName, string entryPoint)
//{
//
//	ComputeShader* shader;
//	shader = FindComputeShader(key);
//
//	if (shader == nullptr)
//	{
//		shader = new ComputeShader(ShaderPath + fileName, entryPoint);
//		computeShaders.insert(make_pair(key, shader));
//	}
//
//	return shader;
//}
//
//ComputeShader * ShaderManager::FindComputeShader(string key)
//{
//	ComputeShadersIter Iter = computeShaders.begin();
//
//	for (Iter; Iter != computeShaders.end(); ++Iter)
//	{
//		if (key == Iter->first)
//			return Iter->second;
//	}
//
//	return nullptr;
//}

void ShaderManager::ShaderRelease()
{
	ShadersIter Iter = shaders.begin();

	for (Iter; Iter != shaders.end(); ++Iter)
	{
		Iter->second->ReleaseShader();
		//TODO 한번만 해도 되는것인지 확인해보고 나중에 변경할것
		break;
	}

}

void ShaderManager::Init()
{
	//this->CreateShader("colorGBuffer", L"001_GBuffer.hlsl", Shader::ShaderType::Default, "ColorDeferred");
}
