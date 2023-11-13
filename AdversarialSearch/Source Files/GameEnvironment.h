#pragma once
#include "Player.h"

// define what game environment should be
// 2 players, a board, and some back and forth for 
// connect 4
class GameEnvironment
{
public:
	GameEnvironment(GameObject* game, Player* p1, Player* p2);
	~GameEnvironment();

	void PlayGame();

private:
	GameObject* m_game;
	Player* m_player1;
	Player* m_player2;
};