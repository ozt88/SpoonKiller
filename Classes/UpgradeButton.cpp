#include "pch.h"
#include "UpgradeButton.h"

USING_NS_CC;

bool UpgradeButton::init()
{
	if(!Node::init())
	{
		return false;
	}
	m_MenuItem = MenuItemImage::create("UpgradeButton.png", "UpgradeButtonPressed.png", 
										  CC_CALLBACK_1(UpgradeButton::menuCallBack, this));

	auto menuButton = Menu::create(m_MenuItem, nullptr);
	addChild(menuButton);
	m_MenuItem->setScale(1.7f);
	auto menuSize = m_MenuItem->getContentSize();
	auto labelSize = Size(menuSize.width * 4 / 5, menuSize.height * 4 / 5);

	m_Label = Label::createWithSystemFont("", "Ariel", 15.f, menuSize, TextHAlignment::CENTER, TextVAlignment::CENTER);
	m_Label->setString("0000");
	m_Label->setColor(cocos2d::Color3B::BLACK);
	m_MenuItem->addChild(m_Label);
	m_Label->setPosition(menuSize.width * 2 / 3, menuSize.height/2);

	setUpgradePrice(m_UpgradePrice);
	return true;
}

void UpgradeButton::menuCallBack(cocos2d::Ref* pSender)
{
	
}

void UpgradeButton::setIconSprite(cocos2d::Sprite* sprite)
{
	auto menuSize = m_MenuItem->getContentSize();
	m_MenuItem->addChild(sprite);
	sprite->setPosition(menuSize.width / 4, menuSize.height / 2);
}

void UpgradeButton::setUpgradePrice(int price)
{
	m_UpgradePrice = price;
	m_Label->setString(std::to_string(price) + " pt");
}

