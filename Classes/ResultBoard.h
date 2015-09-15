#pragma once
#include "cocos2d.h"

class ResultBoard : public cocos2d::Node
{
public:
	bool init() override;
	void menucallback(cocos2d::Ref* psender);
	CREATE_FUNC(ResultBoard);
private:
	void makeBoards();
	void setTime(int microsec);
	void setScore(int score);

private:
	cocos2d::Label* m_TimeLabel;
	cocos2d::Label* m_SpoonScoreLabel;
};

