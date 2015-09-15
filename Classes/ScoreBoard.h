#pragma once
#include "cocos2d.h"

class ScoreBoard : public cocos2d::Node
{
public:
	bool init() override;
	void update(float dTime) override;
	CREATE_FUNC(ScoreBoard);
private:
	void makeBoards();
	void setTime(int microsec);
	void setScore(int score);
	
private:
	cocos2d::Label* m_TimeLabel;
	cocos2d::Label* m_SpoonScoreLabel;
};

