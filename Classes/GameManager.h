#pragma once
#define GET_GAME_MANAGER GameManager::getInstance

enum class SceneType
{
	TITLE_SCENE,
	GAME_SCENE,
};

class PlayerModel;
class MachineModel;
class GameManager : public cocos2d::Object
{
public:
	static GameManager*	getInstance();
	void				releaseInstance();
	void				gameStart();

	void				changeScene(SceneType scene);
	int					getScore(){return m_Score;}
	void				setScore(int score) {m_Score = score;}
	int					getCurrentTime();
	void				gameOver();
	bool				isGamePlaying() const {return m_IsGamePlaying;};

private:
	GameManager();
	virtual ~GameManager();

private:
	int m_Score = 0;
	int m_StartTime = 0;
	bool m_IsGamePlaying = false;
};

