#include "GameObject.h"

GameObject::GameObject(int rows, int cols)
{
	m_rows = rows;
	m_columns = cols;

	for (int row = 0; row < rows; row++) {

		std::deque<GamePiece> rowVector;
		for (int col = 0; col < cols; col++) {
			rowVector.push_back(EMPTY);
		}

		m_board.push_back(rowVector);
	}
}

GameObject::GameObject(const GameObject& other)
{
	if (*this == other) {
		return;
	}

	m_rows = other.m_rows;
	m_columns = other.m_columns;

	auto other_board = other.GetBoard();
	for (int row = 0; row < m_rows; row++) {

		std::deque<GamePiece> rowVector;
		for (int col = 0; col < m_columns; col++) {
			rowVector.push_back(other_board[row][col]);
		}

		m_board.push_back(rowVector);
	}
}

GameObject::~GameObject()
{

}

bool GameObject::DropPiece(int col, GamePiece piece)
{
	// need to drop piece from the top down
	// if the top is empty, move down until a piece is found
	// then place on top of that piece
	
	//std::cout << "Dropping piece " << (char)piece << " in column " << col << std::endl;
	//std::cout << "m_rows = " << m_rows << std::endl;

	// try to get the maximum row for the column
	for (int row = 0; row < m_rows; row++) {

		if (GetPiece(row, col) != EMPTY) {
			if(row-1 >= 0) {
				m_board[row-1][col] = piece;
				break;
			}
			else {
				return false;
			}

			break;
		}
		else if (GetPiece(row, col) == EMPTY && row == m_rows - 1) {
			m_board[row][col] = piece;
		}
	}

	return true;
}

GameObject::GamePiece GameObject::GetPiece(int row, int col) const
{
	return m_board[row][col];
}

std::deque<std::pair<int, GameObject*>> GameObject::GetSuccessors(GamePiece piece) const
{
	std::deque<std::pair<int, GameObject*>> successors;

	for (int col = 0; col < m_columns; col++) {
		GameObject* new_state = new GameObject(*this);
		
		// can we even add a piece to this column?
		if (new_state->DropPiece(col, piece)) {
			successors.push_back(std::make_pair(col, new_state)); 
		}
		else {
			delete new_state;
		}

	}

	return successors;
}

std::deque<std::deque<GameObject::GamePiece>> GameObject::GetBoard() const
{
	return m_board;
}

int GameObject::GetNumberOfRows() const
{
	return m_rows;
}

int GameObject::GetNumberOfColumns() const
{
	return m_columns;
}

bool GameObject::operator==(const GameObject& other) const
{
	bool equals = (m_rows == other.m_rows) 
			   && (m_columns == other.m_columns)
			   && (m_board == other.m_board);

	return equals;
}

bool GameObject::operator!=(const GameObject& other) const
{
	if(*this == other) {
		return false;
	}

	return true;
}