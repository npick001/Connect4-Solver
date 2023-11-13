#pragma once
#include <utility>
#include <algorithm>
#include <deque>

#include "GameInterface.h"

// Define the player class interface
// the Game will require 2 players to play
// the player can be either human or computer
class Player
{
public:
	virtual void GetInput() = 0;

	GameObject::GamePiece GetPlayerPiece() const { return m_playerPiece; }

protected:
	Player(GameObject* gameBoard, GameObject::GamePiece playerPiece);
	~Player() = default;

	GameObject* m_gameBoard;
	GameObject::GamePiece m_playerPiece;
};

// implement the player class
// the player can be human and take in input
// from the input stream
class HumanPlayer : public Player
{
public:
	HumanPlayer(GameObject* game, GameObject::GamePiece playerPiece);
	~HumanPlayer() = default;

	void GetInput() override;

private:
};

// encapsulate the AI methods
// so the human can play against the computer
// AI NEEDS ALGORITHM, OBJECTIVE, AND OPPONENT PIECE KNOWLEDGE
class AI_Player : public Player
{
public:
	enum Objective {
		MINIMIZE,
		MAXIMIZE
	};
	enum Algorithm {
		MINIMAX,
		AB_PRUNING
	};

	AI_Player(GameObject* game, GameObject::GamePiece playerPiece);
	~AI_Player() = default;

	void GetInput() override;
	void SetObjective(Objective obj);
	void SetDecisionAlgorithm(Algorithm alg);
	void SetOpponentPiece(GameObject::GamePiece piece);

protected:
	int GenerateMove();
	std::pair<int, GameObject*> MiniMax(GameObject* game_obj, int current_depth, bool maximizingPlayer);
	std::pair<int, GameObject*> AB_PruningMiniMax(GameObject* game_obj, int current_depth, bool maximizingPlayer, int alpha, int beta);

private:
	Objective m_myObjective;
	Algorithm m_decisionAlgorithm;
	GameObject::GamePiece m_opponentPiece;
	GameObject* m_root;

	int m_maxDepth;
	int m_depth;
	int m_bestMoveColumn;
};