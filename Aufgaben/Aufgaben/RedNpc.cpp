#include "pch.h"
#include "RedNpc.h"

CRedNpc::CRedNpc()
{
}

CRedNpc::~CRedNpc()
{
}

void CRedNpc::Init()
{
	CNpc::Init();
	m_zgSchneemann->SetMaterial(&m_zmSchneemannRed);

}
