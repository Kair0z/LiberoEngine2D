#pragma once

namespace Libero
{
	class GameObject;
	class ICommand
	{
	public:
		virtual ~ICommand() = default;
		virtual void Exe(GameObject* pObject) = 0;
	};
}


