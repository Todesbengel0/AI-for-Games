#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
	m_AvailableOptions = CAvailableOptions();
}

CNpc::~CNpc()
{
}

void CNpc::Update(float fTime, float fTimeDelta)
{
	m_AvailableOptions.ExecutePreferred(fTime, fTimeDelta);
}
