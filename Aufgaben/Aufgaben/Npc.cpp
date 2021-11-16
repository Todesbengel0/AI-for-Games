#include "pch.h"
#include "Npc.h"

CNpc::CNpc()
{
}

CNpc::~CNpc()
{
}

void CNpc::Update(float fTime, float fTimeDelta)
{
	m_AvailableOptions.ExecutePreferred(fTime, fTimeDelta);
}
