#include "pch.h"
#include "ScoreBoard.h"
#include <sstream>
#include "GameManager.h"
USING_NS_CC;

bool ScoreBoard::init()
{
	if(!Node::init())
	{
		return false;
	}
	makeBoards();
	scheduleUpdate();

	return true;
}

void ScoreBoard::makeBoards()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto timerSprite = Sprite::createWithSpriteFrameName("TimerBoard.png");
	auto spoonSprite = Sprite::createWithSpriteFrameName("ScoreBoard.png");
	auto timerSpriteSize = timerSprite->getContentSize();
	auto spoonSpriteSize = spoonSprite->getContentSize();

	addChild(timerSprite);
	addChild(spoonSprite);

	timerSprite->setPosition(visibleSize.width / 2, visibleSize.height * 6/7 );
	spoonSprite->setPosition(visibleSize.width / 2 , visibleSize.height * 6 / 7 - spoonSpriteSize.height - 10.f);
	Size timerLabelSize(timerSpriteSize.width * 4 / 5, timerSpriteSize.height);
	Size spoonLabelSize(spoonSpriteSize.width * 4 / 5, spoonSpriteSize.height);
	m_TimeLabel = Label::createWithSystemFont("", "Arial", 30.f, timerLabelSize, TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_SpoonScoreLabel = Label::createWithSystemFont("", "Arial", 20.f, spoonLabelSize, TextHAlignment::RIGHT, TextVAlignment::CENTER);

	timerSprite->addChild(m_TimeLabel);
	spoonSprite->addChild(m_SpoonScoreLabel);

	m_TimeLabel->setAnchorPoint(Vec2::ZERO);
	m_SpoonScoreLabel->setAnchorPoint(Vec2::ZERO);
	m_TimeLabel->setPosition(timerSpriteSize.width * 1 / 8, 0.f);
	m_SpoonScoreLabel->setPosition(spoonSpriteSize.width * 1 / 8, 0.f);
}

void ScoreBoard::update(float dTime)
{
	if(GET_GAME_MANAGER()->isGamePlaying())
	{
		setScore(GET_GAME_MANAGER()->getScore());
		setTime(GET_GAME_MANAGER()->getCurrentTime());
	}
}

void ScoreBoard::setTime(int millisecond)
{
	int secsec = millisecond / 10;
	int sec = secsec / 100;
	secsec -= sec * 100;
	int min = sec / 60;
	sec -= min * 60;

	std::string secsecstr = std::to_string(secsec);
	std::string secstr = std::to_string(sec);
	std::string minstr = std::to_string(min);

	if(secsec < 10)
	{
		secsecstr = "0" + secsecstr;
	}
	if(sec < 10)
	{
		secstr = "0" + secstr;
	}
	if(min < 10)
	{
		minstr = "0" + minstr;
	}

	m_TimeLabel->setString(minstr + ":" + secstr + ":" + secsecstr);
}

void ScoreBoard::setScore(int score)
{
	m_SpoonScoreLabel->setString(std::to_string(score) + " pt");
}


