#pragma once
#include "SpriteComponent.h"

using namespace Libero;

namespace MySprites
{
#pragma region CharacterSprites
	inline SpriteComponent MainCharRightSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f}
		};
	}

	inline SpriteComponent MainCharLeftSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 16.f}
		};
	}

	inline SpriteComponent SndCharRightSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 32.f}
		};
	}

	inline SpriteComponent SndCharLeftSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 48.f}
		};
	}
#pragma endregion

#pragma region Enemies
	inline SpriteComponent EnemyRightSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 64.f}
		};
	}

	inline SpriteComponent EnemyLeftSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 80.f}
		};
	}

	inline SpriteComponent Enemy2RightSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 96.f}
		};
	}

	inline SpriteComponent Enemy2LeftSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites0.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 112.f}
		};
	}

	inline SpriteComponent BubbledEnemySprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites1.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 16.f * 14.f}
		};
	}

	inline SpriteComponent PoppedEnemySprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites2.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 16.f * 8.f}
		};
	}
#pragma endregion

#pragma region Bullet
	inline SpriteComponent BubbleSprite(const Rectf& dest)
	{
		return SpriteComponent
		{
			"../Resources/Textures/sprites1.png",
			dest,
			0.5f,
			8,
			8,
			0,
			Vector2f{16.f, 16.f},
			Vector2f{18.f, 0.f},
			Vector2f{0.f, 16.f * 12.f}
		};
	}
#pragma endregion
}