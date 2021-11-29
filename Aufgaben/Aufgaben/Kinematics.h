#pragma once

#include "MoveBoundsFix.h"

class CKinematics
{
public:
	CKinematics();
	~CKinematics();

public:
	CPlacement& GetTopPlacement();
	CPlacement& GetLowestPlacement();

	CHVector GetPosition();

	///<summary>
	///<para>Gibt Vektoria-Placement-Orientierungsvektor (bezüglich lokaler -Z Richtung) zurück.</para>
	///</summary>
	CHVector GetOrientationVec();

	///<summary>
	///<para>Gibt Winkelskalar des Vektoria-Placement-Orientierungsvektors bezüglich der lokalen +Z Richtung zurück</para>
	///</summary>
	float GetOrientationAngleZX();

	CHVector GetMovementForce();
	float GetRotationForce();
	float GetMaxMovementForce();
	float GetMaxRotationForce();
	float GetMaxMovementAcceleration();

	void SetPosition(CHVector vPos);
	void ResetPosRot();
	void SetBounds(CHVector vMin, CHVector vMax);

	///<summary>
	///<para>Setzt die Orientierung (gegeben in lokaler -Z Richtung) direkt.</para>
	///<para>Nutze ApplyRotationForce um tatsächlich die Kraft zu aufzurechnen.</para>
	///</summary>
	///<param name="fAngle">Winkelskalar bezüglich lokaler -Z Richtung</param>
	void ChangeOrientation(float fAngle);

	///<summary>
	///<para>Rechnet die Bewegungskraft über Zeit auf die Position auf.</para>
	///<para>Kraft muss bezüglich lokaler -Z Richtung gegeben werden!</para>
	///</summary>
	///<param name="vMovementForce">Bewegungs-Kraftvektor zum Aufaddieren über Zeit.</param>
	///<param name="fTimeDelta">Verstrichene Zeit seit letztem Frame</param>
	void ApplyMovementForce(CHVector vMovementForce, float fTimeDelta, MoveBoundsFix eBoundsFix = MoveBoundsFix::Clamp);

	///<summary>
	///<para>Verrechnet eine Winkelkraft über Zeit an den aktuellen Drehwinkel.</para>
	///<para>Der Winkel muss in lokaler +X Richtung gegeben werden.</para>
	///</summary>
	///<param name="vel">Winkelskalar in +X Richtung</param>
	///<param name="fTimeDelta">Verstrichene Zeit seit letztem Frame</param>
	void ApplyRotationForce(float vel, float fTimeDelta);

	void SetMaxMovementForce(float force);

	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal drehen kann.
	/// </summary>
	/// <param name="vel">Maximaler Drehwinkel pro Sekunde in Bogenmaß.</param>
	void SetMaxRotationForce(float vel);

	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal beschleunigen kann.
	/// </summary>
	/// <param name="acceleration">Faktor der maximalen Beschleunigung in einer Sekunde.</param>
	void SetMaxMovementAcceleration(float acceleration);

	///<summary>
	///<para>Stößt den Character von gegebener Achse ab</para>
	///</summary>
	///<param name="vRef"></param>
	void BounceOff(CHVector vRef);

private:
	///<summary>
	///<para>Stellt mit Hilfe übergebener Option sicher, dass sich Character in den Mapgrenzen bewegt.</para>
	///</summary>
	///<param name="eBoundsFix">Option der Repositionierung an der Mapgrenze</param>
	void CheckBounds(MoveBoundsFix eBoundsFix);

private:
	// Rotation muss unabh. von Positions-Placement bleiben, sonst Rotation um aktuelle Translation
	CPlacement m_zpPos;
	CPlacement m_zpRot;

	CHVector m_MovementForce;
	float m_RotationForce;

	float m_MaxMovementAcceleration;
};
