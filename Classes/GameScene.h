#pragma once

enum ZOrderType
{
	BACKGROUND,
	GAME_OBJECT,
	UI_OBJECT,
};

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene*	createScene();
	bool init() override;
	CREATE_FUNC(GameScene);

private:

private:

};

