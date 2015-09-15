#include "pch.h"
#include "UILayer.h"
#include "UtilSpace.h"
#include "HPBar.h"
#include "Killer.h"
#include "Runner.h"
#include "UpgradeButton.h"
#include "ScoreBoard.h"
#include "GameManager.h"

USING_NS_CC;

bool UILayer::init()
{
	if(!Layer::init())
	{
		return false;
	}
	makeActiveButtons();
	makeHPBars();
	makeUpgradeButtons();
	makeScoreBoard();
	return true;
}


void UILayer::makeActiveButtons()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto swapItem = MenuItemImage::create(
		"SwapButton.png", "SwapButtonPressed.png",
		CC_CALLBACK_1(UILayer::menuSwapCallback, this));

	m_AttackButton = MenuItemImage::create(
		"SpoonButton.png", "SpoonButtonPressed.png",
		CC_CALLBACK_1(UILayer::menuAttackCallback, this));

	m_RunningButton = MenuItemImage::create(
		"RunButton.png", "RunButtonPressed.png",
		CC_CALLBACK_1(UILayer::menuRunCallback, this));

	swapItem->setPosition(Vec2(visibleSize.width * 1 / 10, visibleSize.height / 7));
	m_AttackButton->setPosition(Vec2(visibleSize.width * 9 / 10, visibleSize.height / 7));
	m_RunningButton->setPosition(Vec2(visibleSize.width * 9 / 10,visibleSize.height / 7));

	auto menu = Menu::create(swapItem, m_AttackButton, m_RunningButton, NULL);
	menu->setPosition(Vec2::ZERO);
	m_AttackButton->setVisible(false);
	m_AttackButton->setEnabled(false);
	m_ButtonType = RUNNING;

	this->addChild(menu, 10);
}

void UILayer::menuSwapCallback(cocos2d::Ref* pSender)
{
	if(m_ButtonType == RUNNING)
	{
		m_RunningButton->setVisible(false);
		m_RunningButton->setEnabled(false);
		m_AttackButton->setVisible(true);
		m_AttackButton->setEnabled(true);
		m_ButtonType = ATTACKING;
	}
	else if(m_ButtonType == ATTACKING)
	{
		m_RunningButton->setVisible(true);
		m_RunningButton->setEnabled(true);
		m_AttackButton->setVisible(false);
		m_AttackButton->setEnabled(false);
		m_ButtonType = RUNNING;
	}
}

void UILayer::menuAttackCallback(cocos2d::Ref* pSender)
{
	UtilSpace::dispatchEvent("AttackButton", nullptr);
}

void UILayer::menuRunCallback(cocos2d::Ref* pSender)
{
	UtilSpace::dispatchEvent("Run", nullptr);
}

void UILayer::makeHPBars()
{
	auto winSize = Director::getInstance()->getWinSize();
	auto killerHead = Sprite::createWithSpriteFrameName("KillerHead.png");
	auto runnerHead = Sprite::createWithSpriteFrameName("RunnerHead.png");
	addChild(killerHead);
	addChild(runnerHead);
	m_KillerHpBar = KillerHpBar::create();
	m_RunnerHpBar = RunnerHpBar::create();
	m_KillerHpBar->setAnchorPoint(Vec2::ZERO);
	m_RunnerHpBar->setAnchorPoint(Vec2::ZERO);

	addChild(m_KillerHpBar);
	addChild(m_RunnerHpBar);
	m_KillerHpBar->setPosition(winSize.width / 9, winSize.height - 100.f);
	killerHead->setPosition(winSize.width / 9, winSize.height - 50.f);
	m_RunnerHpBar->setPosition(winSize.width - winSize.width / 9, winSize.height - 100.f);
	runnerHead->setPosition(winSize.width - winSize.width / 9 , winSize.height - 50.f);
}

void UILayer::setKiller(Killer* killer)
{
	m_Killer = killer;
	m_KillerHpBar->setCharacter(killer);
}

void UILayer::setRunner(Runner* runner)
{
	m_Runner = runner;
	m_RunnerHpBar->setCharacter(runner);
}

void UILayer::makeUpgradeButtons()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	float posX = -visibleSize.width / 5;
	float posY = -visibleSize.height / 3;

	for(int i = 0; i < UPGRADE_MAX; ++i)
	{
		m_UpgradeButtons[i] = UpgradeButton::create();
		
		switch(i)
		{
			case HEART_UPGRADE:
			m_UpgradeButtons[i]->setIconSprite(Sprite::createWithSpriteFrameName("HeartIcon.png"));
			m_UpgradeButtons[i]->setCallback(CC_CALLBACK_1(UILayer::upgradeHeartCallback, this));
			break;
			case SPEED_UPGRADE:
			m_UpgradeButtons[i]->setIconSprite(Sprite::createWithSpriteFrameName("SpeedIcon.png"));
			m_UpgradeButtons[i]->setCallback(CC_CALLBACK_1(UILayer::upgradeSpeedCallback, this));
			break;
			case SPOON_UPGRADE:
			m_UpgradeButtons[i]->setIconSprite(Sprite::createWithSpriteFrameName("PowerIcon.png"));
			m_UpgradeButtons[i]->setCallback(CC_CALLBACK_1(UILayer::upgradeSpoonCallback, this));
			break;
			default:
			break;
		}

		addChild(m_UpgradeButtons[i]);
		m_UpgradeButtons[i]->setPosition(posX, posY);
		posX += visibleSize.width / 5;
	}
}

void UILayer::upgradeHeartCallback(cocos2d::Ref* pSender)
{
	auto upgradeButton = m_UpgradeButtons[HEART_UPGRADE];
	auto currentScore = GET_GAME_MANAGER()->getScore();
	auto currentPrice = upgradeButton->getUpgradePrice();
	if(currentScore >= currentPrice)
	{
		GET_GAME_MANAGER()->setScore(currentScore - currentPrice);
		upgradeButton->setUpgradePrice(currentPrice + 10);
		m_Killer->setCurHp(m_Killer->getMaxHp());
	}
}

void UILayer::upgradeSpoonCallback(cocos2d::Ref* pSender)
{
	auto upgradeButton = m_UpgradeButtons[SPOON_UPGRADE];
	auto currentScore = GET_GAME_MANAGER()->getScore();
	auto currentPrice = upgradeButton->getUpgradePrice();
	if(currentScore >= currentPrice)
	{
		GET_GAME_MANAGER()->setScore(currentScore - currentPrice);
		upgradeButton->setUpgradePrice(currentPrice + 10);
		m_Killer->setPower(m_Killer->getPower() + 5.f);
	}
}

void UILayer::upgradeSpeedCallback(cocos2d::Ref* pSender)
{
	auto upgradeButton = m_UpgradeButtons[SPEED_UPGRADE];
	auto currentScore = GET_GAME_MANAGER()->getScore();
	auto currentPrice = upgradeButton->getUpgradePrice();
	if(currentScore >= currentPrice)
	{
		GET_GAME_MANAGER()->setScore(currentScore - currentPrice);
		upgradeButton->setUpgradePrice(currentPrice + 10);
		m_Killer->setVelocity(m_Killer->getVelocity() + 5.f);
	}
}

void UILayer::makeScoreBoard()
{
	auto scoreBoard = ScoreBoard::create();
	addChild(scoreBoard);
}

