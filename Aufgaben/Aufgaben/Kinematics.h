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
	void ApplyRotationForce(float vel, float fTimeDelta);
	void SetMaxMovementForce(float force);
	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal drehen kann.
	/// </summary>
	/// <param name="vel">Maximaler Drehwinkel pro Sekunde in Bogenmaﬂ.</param>
	void SetMaxRotationForce(float vel);
	/// <summary>
	/// Setzt den Wert, um den sich ein Objekt maximal beschleunigen kann.
	/// </summary>
	/// <param name="acceleration">Faktor der maximalen Beschleunigung in einer Sekunde.</param>
	void SetMaxMovementAcceleration(float acceleration);

	static float AngleVektoriaToXZ(CHVector vVektoriaDirection);
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
