#include "pch.h"
#include "RedNpc.h"

CRedNpc::CRedNpc()
{
}

CRedNpc::~CRedNpc()
{
}

void CRedNpc::InitMaterial()
{
	m_zm.MakeTextureDiffuse("textures\\schneeman_rot.png");
	m_zgMesh->SetMaterial(&m_zm);
}
