#pragma once
#include "System.h"
#include "LiberoMath.h"

using namespace Libero;

class Sys_CharacterSaver : public Libero::System<Sys_CharacterSaver>
{
public:
	Sys_CharacterSaver() 
	{ 
		m_Respawnzone0.m_LeftTop = { -160.f, 300.f };
		m_Respawnzone1.m_LeftTop = { 60.f, 300.f };

		m_Respawnzone0.m_W = m_Respawnzone1.m_W = 100.f;
		m_Respawnzone0.m_H = m_Respawnzone1.m_H = 40.f;

		m_UpdateInterval = 0.8f; 
	}
	void Update(float dt) override;
	void PostDraw() const override;

private:
	Rectf m_Respawnzone0{};
	Rectf m_Respawnzone1{};
};

