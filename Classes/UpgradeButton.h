#pragma once
#include "cocos2d.h"

class UpgradeButton : public cocos2d::Node
{
public:
	bool init() override;
	void setIconSprite(cocos2d::Sprite* sprite);
	void menuCallBack(cocos2d::Ref* pSender);
	void setCallback(const std::function<void(Ref*)>& callback)
	{
		m_MenuItem->setCallback(callback);
	};
	void setUpgradePrice(int price);
	int	getUpgradePrice() const {return m_UpgradePrice; }
	CREATE_FUNC(UpgradeButton);

private:
	int	m_UpgradePrice = 50.f;
	cocos2d::MenuItem*	m_MenuItem;
	cocos2d::Label*		m_Label;
};

