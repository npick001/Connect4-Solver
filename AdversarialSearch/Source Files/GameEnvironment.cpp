#include "GameEnvironment.h"

GameEnvironment::GameEnvironment(GameObject* game, Player* p1, Player* p2)
{
	m_game = game;
	m_player1 = p1;
	m_player2 = p2;
}

GameEnvironment::~GameEnvironment()
{
}

void GameEnvironment::PlayGame()
{
	bool terminate = false;
	bool board_full = false;
	int round = 1;
	while (!terminate) {

		std::cout << "Round " << round << std::endl;

		m_player1->GetInput();
		terminate = TerminationTest(m_game, m_player1->GetPlayerPiece());
		board_full = IsBoardFull(m_game);

		if (terminate) {
			std::cout << "Player 1 Wins!" << std::endl;
			PrintGame(m_game);
			break;
		}
		else if (board_full) {
			std::cout << "Board is full, game is a draw!" << std::endl;
			PrintGame(m_game);
			break;
		}

		std::cout << std::endl;
		std::cout << "Player 1 move: " << std::endl;

		PrintGame(m_game);
		//std::cout << "Board evaluation value: " << EvaluateBoard(m_game, m_player1->GetPlayerPiece(), m_player2->GetPlayerPiece()) << std::endl;

		// if player 1 doesnt win on this turn, player 2 gets a turn
		m_player2->GetInput();
		terminate = TerminationTest(m_game, m_player2->GetPlayerPiece());
		board_full = IsBoardFull(m_game);

		if (terminate) {
			std::cout << "Player 2 Wins!" << std::endl;
			PrintGame(m_game);
			break;
		}
		else if (board_full) {
			std::cout << "Board is full, game is a draw!" << std::endl;
			PrintGame(m_game);
			break;
		}

		std::cout << std::endl;
		std::cout << "Player 2 move: " << std::endl;

		PrintGame(m_game);
		//std::cout << "Board evaluation value: " << EvaluateBoard(m_game, m_player2->GetPlayerPiece(), m_player1->GetPlayerPiece()) << std::endl;
		round++;
	}
}