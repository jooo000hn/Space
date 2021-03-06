#include "stdafx.h"
#include "../Include/Transform.h" 
using namespace SpaceGameEngine;

REGISTERCOMPONENTCLASS(TransformComponent);

SpaceGameEngine::TransformComponent::TransformComponent()
{
	m_TypeName = "TransformComponent";
	m_Position = { 0,0,0 };
	m_Rotation = { 0,0,0 };
	m_Scale = { 1,1,1 };
}

SpaceGameEngine::TransformComponent::~TransformComponent()
{

}

void SpaceGameEngine::TransformComponent::InitFromFile(const std::string & filename, int mode)
{
	std::fstream file(filename, std::ios::in);

	file >> m_Position.x >> m_Position.y >> m_Position.z;
	file >> m_Rotation.x >> m_Rotation.y >> m_Rotation.z;
	file >> m_Scale.x >> m_Scale.y >> m_Scale.z;

	file.close();
}

void SpaceGameEngine::TransformComponent::Run(float DeltaTime)
{

}

void SpaceGameEngine::TransformComponent::SetPosition(const XMFLOAT3 & position)
{
	m_Position = position;
}

void SpaceGameEngine::TransformComponent::SetRotation(const XMFLOAT3 & rotation)
{
	m_Rotation = rotation;
}

void SpaceGameEngine::TransformComponent::SetScale(const XMFLOAT3 & scale)
{
	m_Scale = scale;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetPosition()
{
	return m_Position;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetRotation()
{
	return m_Rotation;
}

XMFLOAT3 SpaceGameEngine::TransformComponent::GetScale()
{
	return m_Scale;
}
