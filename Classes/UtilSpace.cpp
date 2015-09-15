#include "pch.h"
#include "UtilSpace.h"
USING_NS_CC;

Animation* UtilSpace::makeAnimation(const char* animationName, int startIdx, size_t frameSize, float delay)
{
	auto animation = Animation::create();
	animation->setDelayPerUnit(delay);

	for(size_t i = 0; i < frameSize; ++i)
	{
		auto frame = SpriteFrameCache::getInstance()->
			getSpriteFrameByName(StringUtils::format("%s%d.png", animationName, i + startIdx));
		animation->addSpriteFrame(frame);
	}
	return animation;
}

void UtilSpace::listenEvent(const char* eventName, const std::function<void(cocos2d::EventCustom*)>& function, cocos2d::Node* subject)
{
	subject->getEventDispatcher()->
		addEventListenerWithSceneGraphPriority(cocos2d::EventListenerCustom::create(eventName, function), subject);
}

void UtilSpace::dispatchEvent(const char* eventName, void* contents)
{
	cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(eventName, contents);
}

unsigned int UtilSpace::getTickCount()
{
	struct timeval gettick;
	unsigned int tick;
	gettimeofday(&gettick, NULL);

	tick = gettick.tv_sec * 1000 + gettick.tv_usec / 1000;

	return tick;
}

