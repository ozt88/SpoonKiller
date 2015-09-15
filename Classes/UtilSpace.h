#pragma once
#include "cocos2d.h"
namespace UtilSpace
{
	cocos2d::Animation* makeAnimation(const char* animationName, int startIdx, size_t size, float delay);
	void	listenEvent(const char* eventName, const std::function<void(cocos2d::EventCustom*)>& function, cocos2d::Node* subject);
	void	dispatchEvent(const char* eventName, void* contents);
	unsigned int getTickCount();
}