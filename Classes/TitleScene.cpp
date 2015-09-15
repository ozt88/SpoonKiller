#include "pch.h"
#include "TitleScene.h"
#include "GameManager.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = TitleScene::create();
	scene->addChild(layer);
	return scene;
}

bool TitleScene::init()
{
	if(!Layer::init())
	{
		return false;
	}


	auto bgSprite = Sprite::createWithSpriteFrameName("TitleBackground.png");
	bgSprite->setAnchorPoint(Vec2::ZERO); 
	addChild(bgSprite);
	makeButtons();
	return true;
}

void TitleScene::makeButtons()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto startItem = MenuItemImage::create(
		"StartButton.png","StartButtonPressed.png", 
		CC_CALLBACK_1(TitleScene::menuStartCallback, this));
	auto closeItem = MenuItemImage::create(
		"ExitButton.png","ExitButtonPressed.png",
		CC_CALLBACK_1(TitleScene::menuCloseCallback, this));

	auto menu = Menu::create(startItem, closeItem, NULL);
	menu->alignItemsVerticallyWithPadding(30.f);
	menu->setPosition(visibleSize.width/2, visibleSize.height/2 - 150.f);
	this->addChild(menu, 1);
}

void TitleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.", "Alert");
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void TitleScene::menuStartCallback(cocos2d::Ref* pSender)
{
	GET_GAME_MANAGER()->gameStart();
}


