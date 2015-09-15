#pragma once
#include "Character.h"
#include <array>

enum RunnerStateType
{
	RUNNER_IDLE,
	RUNNER_MOVING,
	RUNNER_HITTED,
};

enum LevelType
{
	NORMAL_SALARY_MAN,
	TIRED_SALARY_MAN,
	LITTLE_TOUGH_MAN,
	RAGE_WARRIOR,
 	NO_LIFE_MAN,
	NO_LIFE_BIKE,
 	PANZER_NAMED_VENGENCY,
	LEVEL_MAX,
};

class Runner : public Character
{
public:
	bool	init() override;
	void	update(float dTime) override;

	void	changeState(int state);
	void	changeLevel();
	void	onAnimationEnd();

	float	getVelocity() const {return m_Velocity;};
	float	getWidth() const {return m_Width * getScaleX(); }
	void	onHit(cocos2d::EventCustom* event);

	CREATE_FUNC(Runner);

private:
	void initAnimations();

private:
	using StateAnimation = std::pair < int, cocos2d::Animation* > ;
	using Animations = std::vector < StateAnimation > ;
	std::array<Animations, LEVEL_MAX> m_Animations;

	unsigned int m_CurrentLevel = 0;
	float m_Velocity = 20.f;
	float m_Hot = 1.f;
	float m_Score = 50.f;
	float m_Width = 0.f;
};