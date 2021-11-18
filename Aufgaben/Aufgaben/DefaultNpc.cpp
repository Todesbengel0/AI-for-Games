#include "pch.h"
#include "DefaultNpc.h"

CDefaultNpc::CDefaultNpc()
{
	//Add all available Options for Default NPC
}

CDefaultNpc::~CDefaultNpc()
{
}

void CDefaultNpc::Init()
{
	CNpc::Init();
	m_zgSchneemann->SetMaterial(&m_zmSchneemannBlack);
	
}
