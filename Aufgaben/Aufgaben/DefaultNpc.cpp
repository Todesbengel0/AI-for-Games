#include "pch.h"
#include "DefaultNpc.h"

CDefaultNpc::CDefaultNpc()
{
	
}

CDefaultNpc::~CDefaultNpc()
{
}

void CDefaultNpc::Init()
{
	CNpc::Init();
	m_zgSchneemann->SetMaterial(&m_zmSchneemannBlack);
	
}
