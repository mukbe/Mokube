#include "stdafx.h"
#include "SceneBase.h"

#include "./Systems/Object/ObjectManager.h"
#include "./Systems/Message/MessageManager.h"


SceneBase::SceneBase()
	:objectManager(new ObjectManager), messageManager(new MessageManager)
{
	
}


SceneBase::~SceneBase()
{
	Release();
	SafeDelete(objectManager);
	SafeDelete(messageManager);
}

void SceneBase::Init()
{
	objectManager->Init();
}

void SceneBase::Release()
{
	messageManager->RemoveAllMessage();
}

void SceneBase::PreUpdate()
{
	objectManager->PostUpdate();
}

void SceneBase::Update(float tick)
{
	messageManager->Update(tick);
	objectManager->Update(tick);
}

void SceneBase::PostUpdate()
{
	objectManager->PostUpdate();
}

void SceneBase::Render()
{
	objectManager->Render();
}

void SceneBase::PostRender()
{
	objectManager->PostRender();
}

void SceneBase::ImguiRender()
{
	objectManager->ImguiRender();
}
