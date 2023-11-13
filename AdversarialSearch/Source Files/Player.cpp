#include "Player.h"

Player::Player(GameObject* gameBoard, GameObject::GamePiece playerPiece)
{
	m_gameBoard = gameBoard;
	m_playerPiece = playerPiece;
}

HumanPlayer::HumanPlayer(GameObject* game, GameObject::GamePiece playerPiece)
	: Player(game, playerPiece)
{
}

void HumanPlayer::GetInput()
{
	int input = 0;

	// do human operations on the board
	std::cout << "Select a column to drop a piece in (1-7)(Player piece " << (char)m_playerPiece << "): " << std::endl;
	std::cin >> input;

	m_gameBoard->DropPiece(input - 1, m_playerPiece);
}

AI_Player::AI_Player(GameObject* game, GameObject::GamePiece playerPiece)
	: Player(game, playerPiece)
{
	m_maxDepth = 2;
	m_myObjective = MAXIMIZE;
    m_decisionAlgorithm = MINIMAX;
	m_depth = 0;
    m_bestMoveColumn = -1;
}

void AI_Player::GetInput()
{
	int move = GenerateMove();
	m_gameBoard->DropPiece(move, m_playerPiece);
}

void AI_Player::SetObjective(Objective obj)
{
	m_myObjective = obj;
}

void AI_Player::SetDecisionAlgorithm(Algorithm alg)
{
    m_decisionAlgorithm = alg;
}

void AI_Player::SetOpponentPiece(GameObject::GamePiece piece)
{
	m_opponentPiece = piece;
}

int AI_Player::GenerateMove()
{
    m_root = new GameObject(*m_gameBoard);

    bool maximizingPlayer = (m_myObjective == MAXIMIZE) ? true : false;
    std::pair<int, GameObject*> best_move = { -1, NULL };

    switch (m_decisionAlgorithm) {
        case MINIMAX:
            best_move = MiniMax(m_root, 0, maximizingPlayer);
			break;
        
        case AB_PRUNING:
			best_move = AB_PruningMiniMax(m_root, 0, maximizingPlayer, INT_MIN, INT_MAX);
            break;
    }

    delete m_root;
	return m_bestMoveColumn;
}

std::pair<int, GameObject*> AI_Player::MiniMax(GameObject* game_obj, int current_depth, bool maximizingPlayer) {
    
    if (current_depth == m_maxDepth || TerminationTest(game_obj, m_playerPiece) || TerminationTest(game_obj, m_opponentPiece)) {
        auto return_pair = std::pair<int, GameObject*>(EvaluateBoard(game_obj, (maximizingPlayer ? m_playerPiece : m_opponentPiece), (maximizingPlayer ? m_opponentPiece : m_playerPiece)), game_obj);
        return return_pair;
    }

    // Get all possible successor game states
    std::deque<std::pair<int, GameObject*>> successors = game_obj->GetSuccessors((maximizingPlayer ? m_playerPiece : m_opponentPiece));

    // Initialize best move and score
    int bestScore = (maximizingPlayer) ? INT_MIN : INT_MAX;
    std::pair<int, GameObject*> bestMove = { bestScore, nullptr };
    int next_depth = current_depth + 1;

    // Perform minimax search
    for (const auto& successor : successors) {
        int score = MiniMax(successor.second, next_depth, !maximizingPlayer).first;

        // Update best move and score based on the maximizing or minimizing player
        if ((maximizingPlayer && score > bestMove.first) || (!maximizingPlayer && score < bestMove.first)) {
            m_bestMoveColumn = successor.first;
            bestMove = { score, successor.second };
        }
    }

    return bestMove;
}

std::pair<int, GameObject*> AI_Player::AB_PruningMiniMax(GameObject* game_obj, int current_depth, bool maximizingPlayer, int alpha, int beta)
{
    if (current_depth == m_maxDepth || TerminationTest(game_obj, m_playerPiece) || TerminationTest(game_obj, m_opponentPiece)) {
		auto return_pair = std::pair<int, GameObject*>(EvaluateBoard(game_obj, (maximizingPlayer ? m_playerPiece : m_opponentPiece), (maximizingPlayer ? m_opponentPiece : m_playerPiece)), game_obj);
		return return_pair;
	}

    // Get all possible successor game states
    std::deque<std::pair<int, GameObject*>> successors = game_obj->GetSuccessors((maximizingPlayer ? m_playerPiece : m_opponentPiece));

    // Initialize best move and score
    std::pair<int, GameObject*> bestMove = { -1, nullptr };
    int bestScore = (maximizingPlayer) ? INT_MIN : INT_MAX;
    int next_depth = current_depth + 1;

    // Perform minimax search
    for (const auto& successor : successors) {
        int score = AB_PruningMiniMax(successor.second, next_depth, !maximizingPlayer, alpha, beta).first;

        if (maximizingPlayer) {
            if (score > bestMove.first) {
				m_bestMoveColumn = successor.first;
				bestMove = { score, successor.second };
			}
			alpha = std::max(alpha, score);
		}
        else {
            if (score < bestMove.first) {
				m_bestMoveColumn = successor.first;
				bestMove = { score, successor.second };
			}
			beta = std::min(beta, score);
		}

        if (beta <= alpha) {
			break;
		}
    }

    return bestMove;
}
