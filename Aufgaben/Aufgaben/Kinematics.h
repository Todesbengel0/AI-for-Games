﻿#pragma once

class CKinematics
{
public:
	CKinematics();
	~CKinematics();

public:
	CPlacement& GetTopPlacement();
	CPlacement& GetLowestPlacement();

	CHVector GetPosition();
	float GetOrientationAngleXZ();
	CHVector GetOrientationVec();
	CHVector GetMovementForce();
	float GetRotationForce();
	float GetMaxMovementForce();
	float GetMaxRotationForce();
	float GetMaxMovementAcceleration();

	void SetPosition(CHVector vPos);
	void ResetPosRot();
	void SetBounds(CHVector vMin, CHVector vMax);
	void ChangeOrientation(float fAngle);
	void ApplyMovementForce(CHVector vMovementForce, float fTimeDelta);

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
	///<para>Rechnet Vektoria-Placement-Orientierungsvektor (bezüglich lokaler -Z Richtung) in Skalarwinkel bezüglich +X Richtung um.</para>
	///</summary>
	///<param name="vVektoriaDirection">Vektoria-Placement-Orientierungsvektor</param>
	static float AngleVektoriaToXZ(CHVector vVektoriaDirection);

	///<summary>
	///<para>Berechnet die Differenz zwischen zwei Skalarwinkel, sodass diese im Bereich [-PI , PI] bleiben.</para>
	///</summary>
	///<param name="aSource">Ausganswinkel</param>
	///<param name="aTarget">Zielwinkel</param>
	static float AngleDiff(float aSource, float aTarget);

private:
	void ClampInBounds();

private:
	// Rotation muss unabh. von Positions-Placement bleiben, sonst Rotation um aktuelle Translation
	CPlacement m_zpPos;
	CPlacement m_zpRot;

	CHVector m_MovementForce;
	float m_RotationForce;

	float m_MaxMovementAcceleration;
};
