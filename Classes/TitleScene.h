#pragma once

//ù ȭ�鿡�� �ΰ��ӱ��� �̾��ִ� 
class TitleScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene*	createScene();
	bool init() override;
	void menuCloseCallback(cocos2d::Ref* pSender);
	void menuStartCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(TitleScene);

private:
	void					makeButtons();

private:

};

