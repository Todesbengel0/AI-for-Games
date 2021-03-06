#pragma once

enum class NpcAIMode
{
	Idle,

	KinematicSeek,
	KinematicFlee,
	DynamicSeek,
	DynamicFlee,

	DynamicArrive,
	DynamicWander,

	VelocityMatching,
	Seperation,
	Cohesion,
	Flocking
};
