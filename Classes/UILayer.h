#pragma once
#include "cocos2d.h"
#include <array>
#include "UpgradeButton.h"

class KillerHpBar;
class RunnerHpBar;
class Killer;
class Runner;

enum ActiveButtonType
{
	RUNNING,
	ATTACKING,
};

enum UpgradeButtonType
{
	HEART_UPGRADE,
	SPEED_UPGRADE,
	SPOON_UPGRADE,
	UPGRADE_MAX,
};

class UILayer : public cocos2d::Layer
{
public:
	bool init() override;
	void setKiller(Killer* killer);
	void setRunner(Runner* runner);

	void menuSwapCallback(cocos2d::Ref* pSender);
	void menuAttackCallback(cocos2d::Ref* pSender);
	void menuRunCallback(cocos2d::Ref* pSender);
	
	void upgradeHeartCallback(cocos2d::Ref* pSender);
	void upgradeSpeedCallback(cocos2d::Ref* pSender);
	void upgradeSpoonCallback(cocos2d::Ref* pSender);

	CREATE_FUNC(UILayer);

private:
	void makeActiveButtons();
	void makeHPBars();
	void makeUpgradeButtons();
	void makeScoreBoard();

private:
	ActiveButtonType	m_ButtonType;
	cocos2d::MenuItem*	m_AttackButton;
	cocos2d::MenuItem*	m_RunningButton;
	Killer*				m_Killer;
	Runner*				m_Runner;
	KillerHpBar*		m_KillerHpBar;
	RunnerHpBar*		m_RunnerHpBar;
	std::array<UpgradeButton*, UPGRADE_MAX> m_UpgradeButtons;
};