#pragma once
#include "cocos2d.h"
#include "Character.h"

class HpBar : public cocos2d::Node
{
public:
	bool	init() override;
	void	update(float dTime) override;
	float	getPercent() const {return m_Percent;}
	void	setCharacter(Character* character) {m_Subject = character; }

protected:
	Character*				m_Subject = nullptr;
	cocos2d::ProgressTimer* m_ProgressBar;
	cocos2d::Sprite*		m_BarBody;
	float					m_Percent;
};


class KillerHpBar : public HpBar
{
public:
	bool init() override;
	CREATE_FUNC(KillerHpBar);

private:

};

class RunnerHpBar : public HpBar
{
public:
	bool init() override;
	CREATE_FUNC(RunnerHpBar);
};