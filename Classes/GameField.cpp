#include "pch.h"
#include "GameField.h"
#include "Killer.h"
#include "Runner.h"
#include "UtilSpace.h"
#include "GameManager.h"

USING_NS_CC;

bool GameField::init()
{
    if(!Layer::init())
    {
        return false;
    }

    auto winSize = Director::getInstance()->getWinSize();
    setPosition(100.f , 250.f);

    m_Killer = Killer::create();
    addChild(m_Killer);
    m_Killer->setAnchorPoint(Vec2::ZERO);

    m_Runner = Runner::create();
    addChild(m_Runner);
    m_Runner->setAnchorPoint(Vec2::ZERO);
    m_Runner->setPosition(winSize.width - 200.f, -30.f);

    maxDistance = winSize.width - 200.f;
    scheduleUpdate();

    UtilSpace::listenEvent("Attack", CC_CALLBACK_1(GameField::onAttack, this), this);

    return true;
}

void GameField::update(float dTime)
{
    if(GET_GAME_MANAGER()->isGamePlaying())
    {
        if(m_Killer->isDead())
        {
            GET_GAME_MANAGER()->gameOver();

        }
        else
        {
            m_Killer->update(dTime);
            m_Runner->update(dTime);
            updateCharacterPosition(dTime);
        }
    }
}

void GameField::onAttack(cocos2d::EventCustom* event)
{
    auto killerPos = m_Killer->getPosition();
    auto runnerPos = m_Runner->getPosition();
    float curDistance = runnerPos.x - killerPos.x;
    auto runnerWidth = m_Runner->getWidth();
    
    if(curDistance < runnerWidth && curDistance > 0.f)
    {
        UtilSpace::dispatchEvent("Hit", event->getUserData());
    }
    else
    {
        UtilSpace::dispatchEvent("Miss", event->getUserData());
    }
}

void GameField::updateCharacterPosition(float dTime)
{
    float relativeVelocity = m_Runner->getVelocity() - m_Killer->getVelocity();
    if(relativeVelocity < 10.f)
    {
        relativeVelocity = 10.f;
        m_Killer->setVelocity(m_Runner->getVelocity() - 10.f);
    }

    float stepSize = (m_Killer->getVelocity() / m_Runner->getVelocity()) * 50.f;
    m_Killer->setStepSize(stepSize);

    float deltaDistance = dTime * relativeVelocity;
    auto killerPos = m_Killer->getPosition();
    auto runnerPos = m_Runner->getPosition();

    killerPos.x -= deltaDistance;

    float curDistance = runnerPos.x - killerPos.x;

    if(curDistance < 0)
    {
        killerPos = Vec2(runnerPos.x , 0);
    }
    else if(curDistance > maxDistance)
    {
        killerPos = Vec2::ZERO;
    }

    m_Killer->setPosition(killerPos);
}

float GameField::maxDistance = 0.f;

