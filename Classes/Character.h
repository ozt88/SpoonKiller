#pragma once
#include "cocos2d.h"


class Character : public cocos2d::Node
{
public:
	bool init() override;

	float getMaxHp() const {return m_MaxHp; }
	float getCurHp() const {return m_CurHp; }
	void setMaxHp(float maxHp) 
	{
		if(maxHp < m_CurHp)
		{
			return;
		}
		m_MaxHp = maxHp;
	}
	void setCurHp(float curHp)
	{
		if(m_MaxHp < curHp)
		{
			m_CurHp = m_MaxHp;
			return;
		}
		m_CurHp = curHp;
	}
	CREATE_FUNC(Character);

protected:
	cocos2d::Sprite*				m_Sprite;
	int								m_State = 0;
	float							m_MaxHp = 0.f;
	float							m_CurHp = 0.f;
};