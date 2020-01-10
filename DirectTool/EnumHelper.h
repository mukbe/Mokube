#pragma once
enum Pivot
{
	LEFT_TOP, CENTER, BOTTOM, TOP, Pivot_End,
};
enum ObjectType : short
{
	Background = 0, Character, Monster, Interact, StaticObject, Projectile, Effect, UI, Tiles, ObjectType_End
};
enum TileType
{
	TileType_End
};
enum RigidType : short
{
	Dynamic = 0, Static, RigidType_End
};