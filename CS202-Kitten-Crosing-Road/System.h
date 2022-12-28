#pragma once
#include "SystemFunction.h"
#include "Menu.h"

class System : ListTextures
{
public:
	enum class GameState
	{
		Win,
		Lose,
		Continue,
		Pause,
		Save,
		Menu,
		Restart
	};
	enum GameMode
	{
		Endless,
		Classic,
		TwoPlayer
	};
	System(View& view, RenderWindow& window);
	System(View& view, RenderWindow& window, pair<int, int> score, GameState state, GameMode game_mode, int level, int fish_coin);
	bool gameLose();
	bool gameRestart();
	bool gameContinue();
	bool gameWin();
	bool gamePause();
	bool setLose();
	bool setRestart();
	bool setContinue();
	bool setWin();
	bool setPause();
	void draw(const Vector2f& mouse);
	void handleEvent(const Event& event, const Vector2f& mouse);
	friend class Player;
private:
	vector<Scene*>      mainMenu;
	vector<FloatingButton>buttons;
	vector<Object>		fish_boost;
	vector<FishCoin>	fish_boost_name;
	Object      gamePaused, gameOver, gameWon;
	Object				scoreBoard;
	pair<int, int>		score;
	GameState			state;
	GameMode			game_mode;
	int					level;
	int					fish_coin;
	RenderWindow& window;
	View& view;
	InfoScore			fish_score, game_score;
	void				generateNextNormalBoost(Object& curBoost);
	FishCoin			generateNextSpecialBoost(Object& curBoost);
};