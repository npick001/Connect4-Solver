#include "GameInterface.h"

void PrintGame(GameObject* gameobj)
{
	int rows = gameobj->GetNumberOfRows();
	int cols = gameobj->GetNumberOfColumns();

    // output the column numbers above where the pieces will be placed

    std::cout << "|";
    for (int col = 1; col <= cols; col++) {

        if (col == cols) {
			std::cout << col << "|";
		}
        else {
			std::cout << col << " ";
		}
	}
    std::cout << std::endl;

	for (int col = 0; col < 2 * cols + cols / 4; col++) {
		std::cout << "-";
	}
	std::cout << std::endl;

	for (int row = 0; row < rows; row++) {

		std::cout << "|";

		for (int col = 0; col < cols; col++) {

			std::string edge = "|";
			std::cout << (char)gameobj->GetPiece(row, col) << edge;
		}
		std::cout << std::endl;
	}

	for (int col = 0; col < 2 * cols + cols / 4; col++) {
		std::cout << "-";
	}
	std::cout << std::endl;
}

int EvaluateBoard(GameObject* gameobj, GameObject::GamePiece piece1, GameObject::GamePiece piece2)
{
    int score = 0;
    int rows = gameobj->GetNumberOfRows();
    int cols = gameobj->GetNumberOfColumns();
    
    // evaluate horizontal connections
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            int player_count = 0;
            int opponent_count = 0;

            for (int i = 0; i < 4; i++) {
                if(gameobj->GetPiece(row,col + i) == piece1) {
					player_count++;
				}
				else if(gameobj->GetPiece(row,col + i) == piece2) {
					opponent_count++;
				}
            }

            if (player_count == 4) {
                return INT_MAX;
            }
            else if (opponent_count == 4) {
                return INT_MIN;
            }

            score += static_cast<int>(pow(player_count, player_count));
            score -= static_cast<int>(pow(opponent_count, opponent_count));
        }
    }

    // evaluate vertical connections
    for (int row = 3; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int player_count = 0;
            int opponent_count = 0;

            for (int i = 0; i < 4; i++) {
                if (gameobj->GetPiece(row - i, col) == piece1) {
                    player_count++;
                }
                else if (gameobj->GetPiece(row - i, col) == piece2) {
                    opponent_count++;
                }
            }

            if (player_count == 4) {
                return INT_MAX;
            }
            else if (opponent_count == 4) {
                return INT_MIN;
            }

            score += static_cast<int>(pow(player_count, player_count));
            score -= static_cast<int>(pow(opponent_count, opponent_count));
        }
    }

    // evaluate diagonal connections
    // Check diagonally (bottom-left to top-right)
    for (int row = 3; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            int player_count = 0;
            int opponent_count = 0;

            for (int i = 0; i < 4; i++) {
                if (gameobj->GetPiece(row - i, col + i) == piece1) {
                    player_count++;
                }
                else if (gameobj->GetPiece(row - i, col + i) == piece2) {
                    opponent_count++;
                }
            }

            if (player_count == 4) {
                return INT_MAX;
            }
            else if (opponent_count == 4) {
                return INT_MIN;
            }

            score += static_cast<int>(pow(player_count, player_count));
            score -= static_cast<int>(pow(opponent_count, opponent_count));
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols - 3; col++) {
            int player_count = 0;
            int opponent_count = 0;

            for (int i = 0; i < 4; i++) {
                if (gameobj->GetPiece(row + i, col + i) == piece1) {
                    player_count++;
                }
                else if (gameobj->GetPiece(row + i, col + i) == piece2) {
                    opponent_count++;
                }
            }

            if (player_count == 4) {
                return INT_MAX;
            }
            else if (opponent_count == 4) {
                return INT_MIN;
            }

            score += static_cast<int>(pow(player_count, player_count));
            score -= static_cast<int>(pow(opponent_count, opponent_count));
        }
    }

    return score;
}

bool TerminationTest(GameObject* gameobj, GameObject::GamePiece piece)
{
	// to determine if someone has 4 in a row,
	// we need to check all the rows, columns, and diagonals
	// for each of the 2 players
	int rows = gameobj->GetNumberOfRows();
	int cols = gameobj->GetNumberOfColumns();

    // Check horizontally
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (gameobj->GetPiece(row, col) == piece &&
                gameobj->GetPiece(row, col + 1) == piece &&
                gameobj->GetPiece(row, col + 2) == piece &&
                gameobj->GetPiece(row, col + 3) == piece) {
                return true;
            }
        }
    }

    // Check vertically
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols; col++) {
            if (gameobj->GetPiece(row, col) == piece &&
                gameobj->GetPiece(row + 1, col) == piece &&
                gameobj->GetPiece(row + 2, col) == piece &&
                gameobj->GetPiece(row + 3, col) == piece) {
                return true;
            }
        }
    }

    // Check diagonally (bottom-left to top-right)
    for (int row = 3; row < rows; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (gameobj->GetPiece(row, col) == piece &&
                gameobj->GetPiece(row - 1, col + 1) == piece &&
                gameobj->GetPiece(row - 2, col + 2) == piece &&
                gameobj->GetPiece(row - 3, col + 3) == piece) {
                return true;
            }
        }
    }

    // Check diagonally (top-left to bottom-right)
    for (int row = 0; row < rows - 3; row++) {
        for (int col = 0; col < cols - 3; col++) {
            if (gameobj->GetPiece(row, col) == piece &&
                gameobj->GetPiece(row + 1, col + 1) == piece &&
                gameobj->GetPiece(row + 2, col + 2) == piece &&
                gameobj->GetPiece(row + 3, col + 3) == piece) {
                return true;
            }
        }
    }

    return false;
}

bool IsBoardFull(GameObject* game_obj)
{
    int rows = game_obj->GetNumberOfRows();
    int cols = game_obj->GetNumberOfColumns();

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            if (game_obj->GetPiece(row, col) == GameObject::GamePiece::EMPTY) {
                return false; // Found an empty slot, board is not full
            }
        }
    }
    return true; // No empty slot found, board is full
}
