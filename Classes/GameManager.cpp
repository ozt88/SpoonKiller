#include "pch.h"
#include "GameManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "UtilSpace.h"
#include "ResultBoard.h"
#include "base\CCDirector.h"

USING_NS_CC;

GameManager::GameManager()
{
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spritePlist.plist");
}

GameManager::~GameManager()
{
}

GameManager* GameManager::getInstance()
{
	static GameManager* instance = nullptr;
	if(instance == nullptr)
	{
		instance = new GameManager();
	}
	return instance;
}

void GameManager::releaseInstance()
{

}

void GameManager::changeScene(SceneType sceneType)
{
	auto director = Director::getInstance();

	Scene* scene = nullptr;
	switch(sceneType)
	{
		case SceneType::TITLE_SCENE:
		{
			scene = TitleScene::createScene();
			break;
		}
		case SceneType::GAME_SCENE:
		{
			scene = GameScene::createScene();
			break;
		}
		default:
		{
			CCASSERT(false, "no scene to take");
			break;
		}
	}

	if(!director->getRunningScene())
	{
		director->runWithScene(scene);
	}
	else
	{
		director->replaceScene(scene);
	}
}

void GameManager::gameStart()
{
	m_IsGamePlaying = true;
	changeScene(SceneType::GAME_SCENE);
	m_StartTime = UtilSpace::getTickCount();
	m_Score = 0;
}

int GameManager::getCurrentTime()
{
	return UtilSpace::getTickCount() - m_StartTime;
}

void GameManager::gameOver()
{
	m_IsGamePlaying = false;
	auto resultBoard = ResultBoard::create();
	Director::getInstance()->getRunningScene()->addChild(resultBoard);
	
}

