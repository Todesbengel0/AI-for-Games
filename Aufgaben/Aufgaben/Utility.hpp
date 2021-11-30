#pragma once

///<summary>
///<para>Rechnet Vektoria-Placement-Orientierungsvektor (bez�glich lokaler -Z Richtung) in Skalarwinkel bez�glich +Z Richtung um.</para>
///</summary>
///<param name="vVektoriaDirection">Vektoria-Placement-Orientierungsvektor</param>
inline float AngleVektoriaToZX(CHVector vVektoriaDirection)
{
	// Vektoria Placement Ausrichtung ist (warum auch immer) standardm��ig relativ zur -Z Achse
	// F�r unsere Berechnungen wollen wir gerne Winkel bez�glich der +X Achse

	// Zuerst -Z nach +Z, dann projiziert an XZ Ebene mit 0 = Z-Achse
	return (-vVektoriaDirection).AngleZX();
}

///<summary>
///<para>Errechnet einen Einheitsvektor (L�nge 1) in Richtung eines gegebenen Winkelskalars, bez�glich Vektoria's -Z Ausrichtungen</para>
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

/// <summary>
/// Gibt einen gesuchten Funktionswert f�r eine lineare Funktion aus.
/// </summary>
/// <param name="y0">y-Achsenabschnitt.</param>
/// <param name="x1">x-Wert des zweiten bekannten Funktionswertes.</param>
/// <param name="y1">Bekannter Funktionswert f(x1).</param>
/// <param name="xInput">Der Parameterwert, f�r den der Funktionswert gesucht wird.</param>
/// <returns>Gesuchter Funktionswert.</returns>
inline float LinearFunctionY(float y0, float x1, float y1, float xInput)
{
	return xInput * (y1 - y0) / x1 + y0;
}

/// <summary>
/// Gibt einen gesuchten Funktionswert f�r eine lineare Funktion aus.
/// </summary>
/// <param name="y0">y-Achsenabschnitt.</param>
/// <param name="y1">Bekannter Funktionswert f(1).</param>
/// <param name="xInput">Der Parameterwert, f�r den der Funktionswert gesucht wird.</param>
/// <returns>Gesuchter Funktionswert.</returns>
inline float LinearFunctionY(float y0, float y1, float xInput)
{
	return xInput * (y1 - y0) + y0;
}

/// <summary>
/// Gibt einen gesuchten Parameterwert f�r eine lineare Funktion aus.
/// </summary>
/// <param name="v0">Funktionswert an y-Achsenabschnitt.</param>
/// <param name="x1">Parameterwert des zweiten bekannten Funktionswertes.</param>
/// <param name="v1">Bekannter Funktionswert f(x1).</param>
/// <param name="vfunctionValue">Der Funktionswert, f�r den der entsprechende Parameterwert gesucht wird.</param>
/// <returns>Gesuchter Parameterwert.</returns>
inline float LinearFunctionX(float y0, float x1, float y1, float functionValue)
{
	if (y1 == y0)
		return 0.0f;
	return x1 * (functionValue - y0) / (y1 - y0);
}

/// <summary>
/// Gibt einen gesuchten Parameterwert f�r eine lineare Funktion aus.
/// </summary>
/// <param name="v0">Funktionswert an y-Achsenabschnitt.</param>
/// <param name="v1">Bekannter Funktionswert f(1).</param>
/// <param name="vfunctionValue">Der Funktionswert, f�r den der entsprechende Parameterwert gesucht wird.</param>
/// <returns>Gesuchter Parameterwert.</returns>
inline float LinearFunctionX(float y0, float y1, float functionValue)
{
	if (y1 == y0)
		return 0.0f;
	return (functionValue - y0) / (y1 - y0);
}
