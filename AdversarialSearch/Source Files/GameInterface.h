#pragma once
#include <iostream>
#include "GameObject.h"

void PrintGame(GameObject* gameobj);
int EvaluateBoard(GameObject* gameobj, GameObject::GamePiece piece1, GameObject::GamePiece piece2);
bool TerminationTest(GameObject* gameobj, GameObject::GamePiece piece);
bool IsBoardFull(GameObject* gameobj);