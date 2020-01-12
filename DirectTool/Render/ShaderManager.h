#pragma once



class ShaderManager
{
	SingletonHeader(ShaderManager)
public:
	shared_ptr<Shader> CreateShader(string key, wstring fileName, Shader::ShaderType type = Shader::ShaderType::Default, string funcName = "");
	shared_ptr<Shader> FindShader(string key);
	void BindShader(string key);
	void ReleaseShader();

	//class ComputeShader* CreateComputeShader(string key, wstring fileName, string entryPoint);
	//ComputeShader* FindComputeShader(string key);
public:
	void Init();
	void ShaderRelease();

private:
	typedef map<string, shared_ptr<Shader>> ShadersContain;
	typedef map<string, shared_ptr<Shader>>::iterator ShadersIter;
	//typedef map<string, ComputeShader*> ComputeShadersContain;
	//typedef map<string, ComputeShader*>::iterator ComputeShadersIter;

private:
	ShadersContain shaders;
	shared_ptr<Shader> currentShader;
	//ComputeShadersContain computeShaders;
	//class ComputeShader* computeShader;
};

#define Shaders ShaderManager::Get()