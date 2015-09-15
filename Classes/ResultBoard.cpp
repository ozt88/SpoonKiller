#include "pch.h"
#include "ResultBoard.h"
#include <sstream>
#include "GameManager.h"
USING_NS_CC;

bool ResultBoard::init()
{
	if(!Node::init())
	{
		return false;
	}
	makeBoards();

// 	setScale(0.01f);
// 	runAction(ScaleTo::create(0.5f, 1.0f));

	return true;
}

void ResultBoard::makeBoards()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto resultSprite = Sprite::createWithSpriteFrameName("ResultBox.png");
	auto spriteSize = resultSprite->getContentSize();

	addChild(resultSprite);

	resultSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	Size labelSize(spriteSize.width * 3 / 4, spriteSize.height / 5);
	m_TimeLabel = Label::createWithSystemFont("", "Arial", 70.f, labelSize, TextHAlignment::RIGHT, TextVAlignment::CENTER);
	m_SpoonScoreLabel = Label::createWithSystemFont("", "Arial", 70.f, labelSize, TextHAlignment::RIGHT, TextVAlignment::CENTER);

	resultSprite->addChild(m_TimeLabel);
	resultSprite->addChild(m_SpoonScoreLabel);

	m_TimeLabel->setAnchorPoint(Vec2::ZERO);
	m_SpoonScoreLabel->setAnchorPoint(Vec2::ZERO);
	m_TimeLabel->setPosition(spriteSize.width * 1 / 6, spriteSize.height* 3 / 6);
	m_SpoonScoreLabel->setPosition(spriteSize.width * 1 / 6, spriteSize.height * 2 / 6 - 30.f);

	auto menuItem = MenuItemImage::create("ExitButton.png", "ExitButtonPressed.png",
									   CC_CALLBACK_1(ResultBoard::menucallback, this));
	auto menuButton = Menu::create(menuItem, nullptr);
	auto buttonSize = menuItem->getContentSize();
	menuButton->setPosition(spriteSize.width / 2, buttonSize.height/2);
	resultSprite->addChild(menuButton);

	setTime(GET_GAME_MANAGER()->getCurrentTime());
	setScore(GET_GAME_MANAGER()->getScore());
}


void ResultBoard::setTime(int millisecond)
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

void ResultBoard::setScore(int score)
{
	m_SpoonScoreLabel->setString(std::to_string(score) + " pt");
}

void ResultBoard::menucallback(cocos2d::Ref* psender)
{
	GET_GAME_MANAGER()->changeScene(SceneType::TITLE_SCENE);
}


