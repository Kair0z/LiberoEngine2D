#include "PCH.h"
#include "TransformComponent.h"


namespace Libero
{
	//**********************
	// 3D
	//**********************





	//**********************
	// 2D
	//**********************
	void Transform2DComponent::Translate(const Vector2f& translate)
	{
		m_Position += translate;
	}

	void Transform2DComponent::AddRotation(const float rotAdd)
	{
		m_Rotation += rotAdd;
	}

#pragma region ToFile
	std::ofstream& TransformComponent::ToFile(std::ofstream& ofs) const
	{
		ofs << "- TransformComponent:\n";
		ofs << "Pos: [" << GetPosition().x << ", " << GetPosition().y << ", " << GetPosition().z << "] \n";
		ofs << "Rot: [" << GetRotation().x << ", " << GetRotation().y << ", " << GetRotation().z << "] \n";
		ofs << "Scale: [" << GetScale().x << ", " << GetScale().y << ", " << GetScale().z << "] \n";
		ofs << "\n";

		return ofs;
	}

	std::ofstream& Transform2DComponent::ToFile(std::ofstream& ofs) const
	{
		ofs << "- Transform2DComponent:\n";
		ofs << "Pos: [" << GetPosition().x << ", " << GetPosition().y << "] \n";
		ofs << "Rot: [" << GetRotation() << "] \n";
		ofs << "Scale: [" << GetScale().x << ", " << GetScale().y << "] \n";
		ofs << "\n";

		return ofs;
	}
#pragma endregion
}

