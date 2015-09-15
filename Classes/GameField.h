#pragma once
#include "cocos2d.h"
#include "Killer.h"
#include "Runner.h"

class GameField : public cocos2d::Layer
{
public:
	bool init() override;
	void update(float dTime) override;
	void onAttack(cocos2d::EventCustom* event);
	Killer*	getKiller() {return m_Killer; }
	Runner*	getRunner() {return m_Runner; }

	CREATE_FUNC(GameField);

private:
	void updateCharacterPosition(float dTime);

private:
	static float maxDistance;
	Killer* m_Killer;
	Runner* m_Runner;
};