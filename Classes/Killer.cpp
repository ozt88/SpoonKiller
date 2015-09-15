#include "pch.h"
#include "Killer.h"
#include "UtilSpace.h"

USING_NS_CC;

bool Killer::init()
{
	if(!Character::init())
	{
		return false;
	}
 	initAnimations();
 	changeState(KILLER_MOVING);
	setScale(0.6f);
	setPosition(0, 20.f);

	setMaxHp(100.f);
	setCurHp(100.f);

	UtilSpace::listenEvent("AttackButton", CC_CALLBACK_1(Killer::onAttackButton, this), this);
	UtilSpace::listenEvent("Run", CC_CALLBACK_1(Killer::onRun, this), this);
	UtilSpace::listenEvent("Hit", CC_CALLBACK_1(Killer::onHit, this), this);
	UtilSpace::listenEvent("Miss", CC_CALLBACK_1(Killer::onMiss, this), this);

	return true;
}

void Killer::changeState(int state)
{
	if(m_State == state)
	{
		return;
	}
	m_State = state;
	m_Sprite->stopAllActions();

	auto stateAnimation = std::find_if(m_Animations.begin(), m_Animations.end(), [state](const StateAnimation& value)
	{
		return value.first == state;
	})->second;

	auto animate = Animate::create(stateAnimation);
	auto callfunc = CallFuncN::create(CC_CALLBACK_0(Killer::onAnimationEnd, this));
	auto sequence = Sequence::create(animate, callfunc, NULL);

	m_Sprite->runAction(RepeatForever::create(sequence));
}

void Killer::onAnimationEnd()
{
	switch(m_State)
	{
		case KILLER_ATTACK:
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("Attack", (void*)this);
			changeState(KILLER_MOVING);
			break;
		}
		default:
		break;
	}
}

void Killer::initAnimations()
{
	auto walkAnimation = UtilSpace::makeAnimation("KillerWalk", 0, 4, 0.1f);
	walkAnimation->retain();
	m_Animations.push_back(StateAnimation {KILLER_MOVING, walkAnimation});

	auto attackAnimation = UtilSpace::makeAnimation("KillerAttack", 0, 5, 0.1f);
	attackAnimation->retain();
	m_Animations.push_back(StateAnimation {KILLER_ATTACK, attackAnimation});
}

void Killer::onAttackButton(EventCustom* event)
{
	changeState(KILLER_ATTACK);
}

void Killer::onRun(EventCustom* event)
{
	auto pos = getPosition();
	pos.x += m_StepSize;
	setPosition(pos);
}

void Killer::onHit(EventCustom* event)
{
	setPosition(Vec2(getPosition().x - m_StepSize * 0.8f, 0.f));
	setCurHp(getCurHp() + m_SpoonPower * 0.4f);
}

void Killer::onMiss(cocos2d::EventCustom* event)
{
	setPosition(Vec2(getPosition().x - m_StepSize, 0.f));
	setCurHp(getCurHp() - m_SpoonPower * 0.2f);
}

void Killer::update(float dTime)
{
	float tickDmg = dTime * m_Dot;
	setCurHp(getCurHp() - tickDmg);
}

Killer::~Killer()
{
	for(auto pair : m_Animations)
	{
		pair.second->release();
	}
}

