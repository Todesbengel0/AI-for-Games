#pragma once

#include "Action.h"
#include "SteeringForce.h"

class CSteeringBehavior : public CAction
{
public:
	CSteeringBehavior(CNpc* user, NpcAIMode npcAiMode = NpcAIMode::Idle);
	virtual ~CSteeringBehavior();

public:
	// final, da erbende Steering Behaviors GetForce() implementieren sollen, nicht Update()
	void Update(float fTime, float fTimeDelta) final;
	virtual SSteeringForce GetForce(float fTimeDelta) = 0;

protected:
	static void Limit(CHVector& v, float minLength, float maxLength);
	static void Limit(float& angle, float maxAngle);

	/// <summary>
	/// Limitiert eine Vektorrotation auf einen maximalen Winkel.
	/// </summary>
	/// <param name="v">Bereits um targetAngle gedrehter Vektor.</param>
	/// <param name="rotationAngle">Der Winkel, um den der Vektor gedreht wurde.</param>
	/// <param name="maxAngle">Der Winkel, um den der Vektor maximal gedreht werden dürfte.</param>
	static void LimitToRotation(CHVector& v, float rotationAngle, float maxAngle);

protected:
	/// <summary>
	/// <para>Verändert einen Vektor so, dass die Bremsregulationen des Objektes zutreffen.</para>
	/// </summary>
	/// <param name="vForce">Geschwindigkeitsvektor</param>
	/// <param name="fTimeDelta">Zeit, die seit letztem Tick vergangen ist.</param>
	void BreakThrottle(CHVector& vForce, float fTimeDelta);

	/// <summary>
	/// <para>Verändert einen Vektor so, dass die Beschleunigungsregulationen des Objekts zutreffen.</para>
	/// </summary>
	/// <param name="vForce">Geschwindigkeitsvektor</param>
	/// <param name="fTimeDelta">Zeit, die seit letztem Tick vergangen ist.</param>
	void AccelerationThrottle(CHVector& vForce, float fTimeDelta);

	/// <summary>
	/// Gibt die Winkeldifferenz zur vorher berechneten Bewegungsrichtung aus.
	/// </summary>
	/// <returns>Winkel im Bereich [-PI,PI]</returns>
	float AngleDiffToPreviousForce(CHVector vForce);
};
