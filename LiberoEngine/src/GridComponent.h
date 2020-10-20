#pragma once
#include "Component.h"
#include <vector>
#include "LiberoMath.h"

namespace Libero
{
	typedef Rectf GridCell;

	class Grid2DComponent : public Component<Grid2DComponent>
	{
	public:
		enum class GridOrientation
		{
			LeftTop,
			LeftBottom
		};

		Grid2DComponent(size_t nX, size_t nY, const GridCell& cell);
		Grid2DComponent(float spanX, float spanY, size_t nX, size_t nY);
		virtual ~Grid2DComponent();

		const std::vector<GridCell>& GetCells() const;
		GridCell GetCell(int idx);
		GridCell GetCell(int x, int y);

	private:
		std::vector<GridCell> m_Cells;
		size_t m_NX;
		size_t m_NY;
	};
}

// 3D grid for now not applicable

