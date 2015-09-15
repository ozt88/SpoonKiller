#pragma once
#include "cocos2d.h"
#include "Runner.h"

class BackGround : public cocos2d::Layer
{
public:
	bool	init() override;
	void	update(float dTime) override;
	void	setRunner(Runner* runner) {m_Runner = runner; }
	CREATE_FUNC(BackGround);

private:
	float m_Velocity = -300.f;
	Runner*			 m_Runner = nullptr;
	cocos2d::Sprite* m_BackSprite1;
	cocos2d::Sprite* m_BackSprite2;
};