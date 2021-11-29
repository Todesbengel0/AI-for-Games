#pragma once

///<summary>
///<para>Rechnet Vektoria-Placement-Orientierungsvektor (bezüglich lokaler -Z Richtung) in Skalarwinkel bezüglich +Z Richtung um.</para>
///</summary>
///<param name="vVektoriaDirection">Vektoria-Placement-Orientierungsvektor</param>
inline float AngleVektoriaToZX(CHVector vVektoriaDirection)
{
	// Vektoria Placement Ausrichtung ist (warum auch immer) standardmäßig relativ zur -Z Achse
	// Für unsere Berechnungen wollen wir gerne Winkel bezüglich der +X Achse

	// Zuerst -Z nach +Z, dann projiziert an XZ Ebene mit 0 = Z-Achse
	return (-vVektoriaDirection).AngleZX();
}

///<summary>
///<para>Errechnet einen Einheitsvektor (Länge 1) in Richtung eines gegebenen Winkelskalars, bezüglich Vektoria's -Z Ausrichtungen</para>
///</summary>
///<param name="fAngle">Winkelskalar</param>
inline CHVector AngleVektoriaToVector(float fAngle)
{
	return -CHVector(std::sinf(fAngle), 0.0f, std::cosf(fAngle));
}

///<summary>
///<para>Berechnet die Differenz zwischen zwei Skalarwinkel, sodass diese im Bereich [-PI , PI] bleiben.</para>
///</summary>
///<param name="aSource">Ausganswinkel</param>
///<param name="aTarget">Zielwinkel</param>
inline float AngleDiff(float aSource, float aTarget)
{
	//return std::atan2f(std::sinf(a2 - a1), std::cosf(a2 - a1));
	float a = aTarget - aSource;

	if (a > PI) a -= TWOPI;
	else if (a < -PI) a += TWOPI;

	return a;
}

/// <summary>
/// <para>Multipliziert die Elemente zweier Vektoren miteinander.</para>
/// </summary>
/// <param name="v1">Vektor 1</param>
/// <param name="v2">Vektor 2</param>
inline CHVector MultiplyElements(CHVector v1, CHVector v2)
{
	v1.x *= v2.x;
	v1.y *= v2.y;
	v1.z *= v2.z;
	return v1;
}

template <typename T, std::size_t n>
inline std::vector<T*> ArrayToPointerVector(T(&arr)[n])
{
	std::vector<T*> res;

	for (auto& elem : arr)
		res.emplace_back(&elem);

	return res;
}

template <typename TPtr, typename T, std::size_t n>
inline std::vector<TPtr> ArrayToPointerVector(T(&arr)[n])
{
	std::vector<TPtr> res;

	for (auto& elem : arr)
		res.emplace_back(&elem);

	return res;
}
