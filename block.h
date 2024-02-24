#pragma once
#include <vector>
#include <map>
#include "position.h"
#include "colors.h"

using namespace std;
class Block
{
private:
  int cellSize;
  int rotationState;
  vector<Color> colors;
  int rowOffset;
  int columnOffset;

public:
  int id;
  map<int, vector<Position>> cells;
  Block()
  {
    cellSize = 30;
    rotationState = 0;
    colors = GetCellColors();
    rowOffset = 0;
    columnOffset = 0;
  }

  vector<Position> GetCellPositions()
  {
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles)
    {
      Position newPos = Position(item.row + rowOffset, item.column + columnOffset);
      movedTiles.push_back(newPos);
    }
    return movedTiles;
  }

  void Draw(int offsetX, int offsetY)
  {
    vector<Position> tiles = GetCellPositions();
    for (Position item : tiles)
    {
      DrawRectangle(item.column * cellSize + offsetX, item.row * cellSize + offsetY, cellSize - 1, cellSize - 1, colors[id]);
    }
  }

  void Move(int rows, int columns)
  {
    rowOffset += rows;
    columnOffset += columns;
  }

  void Rotate()
  {
    rotationState++;
    if (rotationState == (int)cells.size())
    {
      rotationState = 0;
    }
  }

  void UndoRotation()
  {
    rotationState--;
    if (rotationState == -1)
    {
      rotationState = cells.size() - 1;
    }
  }
};