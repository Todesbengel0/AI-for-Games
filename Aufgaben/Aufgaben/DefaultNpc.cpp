#include "pch.h"
#include "DefaultNpc.h"
#include "SteeringBehaviorsInclude.h"

CDefaultNpc::CDefaultNpc()
{
}

CDefaultNpc::~CDefaultNpc()
{
}

void CDefaultNpc::InitMaterial()
{
	m_zm.MakeTextureDiffuse("textures\\schneeman_farbe.png");
	m_zgMesh->SetMaterial(&m_zm);
}
