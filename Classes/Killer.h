#pragma once
#include "Character.h"


enum KillerStatus
{
	KILLER_IDLE,
	KILLER_MOVING,
	KILLER_ATTACK,
	KILLER_STATUS_MAX,
};

class Killer : public Character
{
public:
	virtual ~Killer();

	bool	init() override;
	void	update(float dTime) override;

	void	changeState(int state);
	void	onAnimationEnd();

	void	onAttackButton(cocos2d::EventCustom* event);
	void	onRun(cocos2d::EventCustom* event);
	void	onHit(cocos2d::EventCustom* event);
	void	onMiss(cocos2d::EventCustom* event);
	bool	isDead() const {return m_CurHp < 0.001f;}
	float	getPower() const {return m_SpoonPower;}
	void	setPower(float power) {m_SpoonPower = power; }
	float	getVelocity() const {return m_Velocity; }
	void	setVelocity(float velocity ) {m_Velocity = velocity; }
	void	setStepSize(float stepSize) {m_StepSize = stepSize;}

	CREATE_FUNC(Killer);

private:
	void	initAnimations();

private:
	using StateAnimation = std::pair < int, cocos2d::Animation* > ;
	std::vector<StateAnimation>		m_Animations;
	float	m_Dot = 5.f;
	float	m_StepSize = 0.f;
	float	m_SpoonPower = 10.f;
	float	m_Velocity = 10.f;
};