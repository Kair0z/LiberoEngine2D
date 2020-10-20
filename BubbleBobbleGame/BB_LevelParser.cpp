#include "BB_LevelParser.h"
#include "TextureComponent.h"
#include "SpriteComponent.h"
#include <fstream>

using namespace Libero;

BB_EnviromentLoader::BB_EnviromentLoader()
{
    m_Blocks.reserve((25 * 32 * 100) / 8);
}

void BB_EnviromentLoader::ParseBlocks()
{
        std::ifstream ifs;
        ifs.open("../Resources/LevelData/SeperatedLevelData.dat", std::ios_base::binary);

        if (!ifs.is_open()) return;
        Chunk chunk{}; // == 8 blocks
        while (!ifs.eof())
        {
            ifs >> chunk.Byte;

            for (size_t i{}; i < 8; ++i)
            {
                if (chunk[i]) m_Blocks.push_back(BlockType::Default);
                else m_Blocks.push_back(BlockType::Empty);
            }
        }
}

Libero::GameObject* BB_EnviromentLoader::LoadBlock(Libero::LiberoScene* pScene, int idx, float w, float h) const
{
    if (m_Blocks.size() == 0) return nullptr;
    if (m_Blocks[idx] == BlockType::Empty) return nullptr;

    GameObject* pBlock = pScene->AddGameObject();

    Rectf dest{};
    dest.m_LeftTop = {-w / 2, h / 2};
    dest.m_W = w;
    dest.m_H = h;

    Rectf src{};
    src.m_LeftTop = {};
    src.m_H = 8.f;
    src.m_W = 8.f;

    pBlock->AddComponent<Texture2DComponent>("../Resources/Textures/blocks.png", dest, src);
    return pBlock;
}

Libero::GameObject* BB_EnviromentLoader::LoadBlock(Libero::LiberoScene* pScene, int x, int y, float w, float h) const
{
    int idx = x + (y * 32);
    return LoadBlock(pScene, idx, w, h);
}
