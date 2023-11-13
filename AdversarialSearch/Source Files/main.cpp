#include "GameInterface.h"
#include <iostream>
#include "Player.h"
#include "GameEnvironment.h"

void PlayerVSPlayer();
void PlayerVSAI(AI_Player::Objective obj, AI_Player::Algorithm alg);
void AIVSAI(AI_Player::Objective obj1, AI_Player::Algorithm alg1, AI_Player::Objective obj2, AI_Player::Algorithm alg2);

int main() {

	//PlayerVSPlayer();
	//PlayerVSAI(AI_Player::Objective::MAXIMIZE, AI_Player::Algorithm::AB_PRUNING);

	// maximize minimax vs minimize ab_pruning
	AIVSAI(AI_Player::Objective::MAXIMIZE, AI_Player::Algorithm::MINIMAX, AI_Player::Objective::MINIMIZE, AI_Player::Algorithm::AB_PRUNING);

	// minimize minimax vs maximize ab_pruning
	//AIVSAI(AI_Player::Objective::MINIMIZE, AI_Player::Algorithm::MINIMAX, AI_Player::Objective::MAXIMIZE, AI_Player::Algorithm::AB_PRUNING);

	// minimize minimax vs minimize ab_pruning
	//AIVSAI(AI_Player::Objective::MINIMIZE, AI_Player::Algorithm::MINIMAX, AI_Player::Objective::MINIMIZE, AI_Player::Algorithm::AB_PRUNING);

	// maximize minimax vs maximize ab_pruning
	//AIVSAI(AI_Player::Objective::MAXIMIZE, AI_Player::Algorithm::MINIMAX, AI_Player::Objective::MAXIMIZE, AI_Player::Algorithm::AB_PRUNING);

	return 0;
}

void PlayerVSPlayer()
{
	GameObject* connect_four = new GameObject(6, 7);
	PrintGame(connect_four);

	HumanPlayer* player1 = new HumanPlayer(connect_four, GameObject::GamePiece::BLUE);
	HumanPlayer* player2 = new HumanPlayer(connect_four, GameObject::GamePiece::RED);

	GameEnvironment* gameEnv = new GameEnvironment(connect_four, player1, player2);
	gameEnv->PlayGame();
}

void PlayerVSAI(AI_Player::Objective obj, AI_Player::Algorithm alg)
{
	GameObject* connect_four = new GameObject(6, 7);
	PrintGame(connect_four);

	HumanPlayer* player1 = new HumanPlayer(connect_four, GameObject::GamePiece::BLUE);
	AI_Player* ai = new AI_Player(connect_four, GameObject::GamePiece::RED);
	ai->SetDecisionAlgorithm(alg);
	ai->SetObjective(obj);
	ai->SetOpponentPiece(GameObject::GamePiece::BLUE);

	GameEnvironment* gameEnv = new GameEnvironment(connect_four, player1, ai);
	gameEnv->PlayGame();
}

void AIVSAI(AI_Player::Objective obj1, AI_Player::Algorithm alg1, AI_Player::Objective obj2, AI_Player::Algorithm alg2)
{
	GameObject* connect_four = new GameObject(6, 7);
	PrintGame(connect_four);

	AI_Player* ai1 = new AI_Player(connect_four, GameObject::GamePiece::BLUE);
	ai1->SetObjective(obj1);
	ai1->SetDecisionAlgorithm(alg1);
	ai1->SetOpponentPiece(GameObject::GamePiece::RED);

	AI_Player* ai2 = new AI_Player(connect_four, GameObject::GamePiece::RED);
	ai2->SetObjective(obj2);
	ai2->SetDecisionAlgorithm(alg2);
	ai2->SetOpponentPiece(GameObject::GamePiece::BLUE);

	GameEnvironment* gameEnv = new GameEnvironment(connect_four, ai1, ai2);
	gameEnv->PlayGame();
}
