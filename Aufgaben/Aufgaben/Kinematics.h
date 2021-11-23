#pragma once

class CKinematics
{
public:
	CKinematics();
	~CKinematics();

public:
	CPlacement& GetTopPlacement();
	CPlacement& GetLowestPlacement();

	CHVector GetPosition();
	float GetOrientationAngle();
	CHVector GetOrientationVec();
	CHVector GetMovementForce();
	float GetRotationVelocity();
	float GetMaxMovementForce();
	float GetMaxRotationVelocity();
	float GetMaxMovementAcceleration();

	void SetPosition(CHVector vPos);
	void ResetPosRot();
	void SetBounds(CHVector vMin, CHVector vMax);
	void ChangeOrientation(float fAngle);
	void ApplyMovementForce(CHVector vMovementForce, float fTimeDelta);
	void SetRotationVelocity(float vel);
	void SetMaxMovementForce(float force);
	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal drehen kann.
	/// </summary>
	/// <param name="vel">Maximaler Drehwinkel pro Sekunde in Bogenmaﬂ.</param>
	void SetMaxRotationVelocity(float vel);
	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal beschleunigen kann.
	/// </summary>
	/// <param name="acceleration">Faktor der maximalen Beschleunigung in einer Sekunde.</param>
	void SetMaxMovementAcceleration(float acceleration);

private:
	void ClampInBounds();

private:
	// Rotation muss unabh. von Positions-Placement bleiben, sonst Rotation um aktuelle Translation
	CPlacement m_zpPos;
	CPlacement m_zpRot;

	CHVector m_MovementForce;
	float m_RotationVelocity;

	float m_MaxMovementAcceleration;
};
