#include "pch.h"
#include "GameScene.h"
#include "Background.h"
#include "GameField.h"
#include "UILayer.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
	return scene;
}

bool GameScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	auto background = BackGround::create(); 
	addChild(background, BACKGROUND);

	auto gameField = GameField::create();
	addChild(gameField, GAME_OBJECT);

	auto uiLayer = UILayer::create();
	addChild(uiLayer, UI_OBJECT);

	background->setRunner(gameField->getRunner());
	uiLayer->setKiller(gameField->getKiller());
	uiLayer->setRunner(gameField->getRunner());

	return true;
}


