#pragma once


// Dealing with global const because it's more convenient to change them here than in the code itself
// Of course, it's not the best way to do it
// But since it's a small project and there won't be any modifications after release, it's fine
namespace Consts
{
	// Window CONSTS
	constexpr int WIN_WIDTH = 400, WIN_HEIGHT = 680;

	// GameScene CONSTS
	constexpr char BACKGROUND_SPRITE_PATH[] = "data/bck.png";
	constexpr char MENU_BACKGROUND_SPRITE_PATH[] = "data/Default@2x.png";
	// Doodler CONSTS
	constexpr char DOODLER_SPRITE_LEFT_PATH[] = "data/frozen-left@2x.png";
	constexpr char DOODLER_SPRITE_RIGHT_PATH[] = "data/frozen-right@2x.png";
	constexpr float GRAVITY = 14 / 10000.0f;
	constexpr float JUMP_VELOCITY = 0.7f;
	constexpr float DOODLER_SPEED = 0.42f;

	// Projectiles CONSTS 
	constexpr char PROJECTILE_SPRITE_PATH[] = "data/bubble@2x.png";
	constexpr float PROJECTILE_SPEED = 0.7f;
	constexpr float PROJECTILE_LIFETIME = 500;
	constexpr int PROJECTILE_WIDTH = 16;
	constexpr int PROJECTILE_HEIGHT = 16;

	// Platform CONSTS
	constexpr char PLATFORM_SPRITE_PATH[] = "data/game-platform-ice2x.png";
    constexpr int PLATFORM_WIDTH = 61;
    constexpr int PLATFORM_HEIGHT = 20;

	// MovablePlatform CONSTS
	constexpr float MOVABLE_PLATFORM_MOVE_DISTANCE = 50;
	constexpr float MOVABLE_PLATFORM_MOVE_SPEED = 0.1f;

	//Enemy CONSTS
	constexpr char ENEMY_SPRITE_PATH[] = "data/enemy-tile-ice2x.png";
	constexpr int ENEMY_WIDTH = 52;
	constexpr int ENEMY_HEIGHT = 50;

	// Ability CONSTS
	constexpr char ABILITY_SPRITE_PATH[] = "data/Invincibility.png";
	constexpr int ABILITY_WIDTH = 45;
	constexpr int ABILITY_HEIGHT = 50;
	constexpr int ABILITY_DURATION = 20000;

	// BUTTON CONSTS
	constexpr char PLAY_BUTTON_SPRITE_PATH[] = "data/play.png";
	constexpr char PLAY_AGAIN_BUTTON_SPRITE_PATH[] = "data/play-again-on.png";

	constexpr int  Button_WIDTH = 111;
	constexpr int  Button_HEIGHT = 40;

}	