#pragma once
#include <iostream>
#include <deque>

// Define the GameObject class
// this class is the base class for the connect 4 board
class GameObject
{
public:
	enum GamePiece {
		BLUE = 'O',
		RED = 'X',
		EMPTY = '.'
	};

	GameObject(int rows, int cols);
	GameObject(const GameObject& other);
	~GameObject();

	bool DropPiece(int col, GamePiece piece);
	GamePiece GetPiece(int row, int col) const;

	// return a vector of pairs of (col, gameobject)
	// where the gameobject is the new gameobject after the move
	// and the col is the column that was played
	std::deque<std::pair<int, GameObject*>> GetSuccessors(GamePiece piece) const;
	std::deque<std::deque<GamePiece>> GetBoard() const;

	int GetNumberOfRows() const;
	int GetNumberOfColumns() const;

	bool operator==(const GameObject& other) const;
	bool operator!=(const GameObject& other) const;

private:
	int m_rows;
	int m_columns;
	std::deque<std::deque<GamePiece>> m_board;
};

