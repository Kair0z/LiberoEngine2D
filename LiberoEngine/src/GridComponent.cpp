#include "PCH.h"
#include "GridComponent.h"

namespace Libero
{
	Grid2DComponent::Grid2DComponent(size_t nX, size_t nY, const GridCell& cell)
		: m_NX{nX}
		, m_NY{nY}
	{
		m_Cells.reserve(nX* nY);

		for (size_t r{}; r < nY; ++r)
			for (size_t c{}; c < nX; ++c)
			{
				// Width & height get copied from constructorcell
				m_Cells.push_back(cell);

				m_Cells.back().m_LeftTop[0] = c * cell.m_W;
				m_Cells.back().m_LeftTop[1] = r * cell.m_H;
			}
	}

	Grid2DComponent::Grid2DComponent(float spanX, float spanY, size_t nX, size_t nY)
		: m_NX{nX}
		, m_NY{nY}
	{
		float width{spanX / nX};
		float height{spanY / nY};

		m_Cells.reserve(nX* nY);

		for (size_t r{}; r < nY; ++r)
			for (size_t c{}; c < nX; ++c)
			{
				m_Cells.push_back(GridCell{});
				m_Cells.back().m_W = width;
				m_Cells.back().m_H = height;
				m_Cells.back().m_LeftTop[0] = c * width;
				m_Cells.back().m_LeftTop[1] = height + (r * height); 
			}
	}


	Grid2DComponent::~Grid2DComponent()
	{
		m_Cells.clear();
	}

	const std::vector<GridCell>& Grid2DComponent::GetCells() const
	{
		return m_Cells;
	}

	GridCell Grid2DComponent::GetCell(int idx)
	{
		if (idx < 0) return m_Cells[0];
		if ((size_t)idx >= m_Cells.size()) return m_Cells.back();

		return m_Cells[idx];
	}

	GridCell Grid2DComponent::GetCell(int x, int y)
	{
		int idx = (y * (int)m_NX) + x;
		return GetCell(idx);
	}
}


