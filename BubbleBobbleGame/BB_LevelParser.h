#pragma once
#include <string>
#include "GameObject.h"
#include "LiberoScene.h"

class BB_EnviromentLoader
{
	enum class BlockType
	{
		Empty,
		Default
	};

	union Chunk
	{
#define BIT(x) x >> 1
		unsigned char Byte;

		struct 
		{
			bool b0 : 1;
			bool b1 : 1;
			bool b2 : 1;
			bool b3 : 1;
			bool b4 : 1;
			bool b5 : 1;
			bool b6 : 1;
			bool b7 : 1;
		};

		bool operator[](size_t idx)
		{
			switch (idx)
			{
			case 0: return b7;
			case 1: return b6;
			case 2: return b5;
			case 3: return b4;
			case 4: return b3;
			case 5: return b2;
			case 6: return b1;
			case 7: return b0;
			default: return false;
			}
		}
	};

public:
	BB_EnviromentLoader();
	void ParseBlocks();
	Libero::GameObject* LoadBlock(Libero::LiberoScene* pScene, int idx, float w, float h) const;
	Libero::GameObject* LoadBlock(Libero::LiberoScene* pScene, int x, int y, float w, float h) const;

private:
	std::vector<BlockType> m_Blocks;
};

