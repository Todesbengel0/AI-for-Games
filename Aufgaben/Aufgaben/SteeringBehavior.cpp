#include "pch.h"
#include "SteeringBehavior.h"

CSteeringBehavior::CSteeringBehavior(CNpc* user)
	: CAction(user)
{
}

CSteeringBehavior::~CSteeringBehavior()
{

}

void CSteeringBehavior::Update(float fTime, float fTimeDelta)
{
	CHVector vForce = GetForce();


}
