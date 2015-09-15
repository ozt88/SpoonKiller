#include "pch.h"
#include "Character.h"

USING_NS_CC;

bool Character::init()
{
	if(!Node::init())
	{
		return false;
	}

	m_Sprite = Sprite::create();
	addChild(m_Sprite);
	return true;
}
