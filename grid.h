#pragma once
#include <vector>
#include <raylib.h>
#include <iostream>
#include "colors.h"

using namespace std;

class Grid
{
private:
  int numRows;
  int numCols;
  int cellSize;
  vector<Color> colors;
  bool IsRowFull(int row)
  {
    for (int column = 0; column < numCols; column++)
    {
      if (grid[row][column] == 0)
      {
        return false;
      }
    }
    return true;
  }

  void ClearRow(int row)
  {
    for (int column = 0; column < numCols; column++)
    {
      grid[row][column] = 0;
    }
  }

  void MoveRowDown(int row, int numRows)
  {
    for (int column = 0; column < numCols; column++)
    {
      grid[row + numRows][column] = grid[row][column];
      grid[row][column] = 0;
    }
  }

public:
  int grid[20][10];
  bool IsCellOutside(int row, int column)
  {
    if (row >= 0 && row < numRows && column >= 0 && column < numCols)
    {
      return false;
    }
    return true;
  }

  Grid()
  {
    numRows = 20;
    numCols = 10;
    cellSize = 30;
    Initialize();
    colors = GetCellColors();
  }

  void Initialize()
  {
    for (int row = 0; row < numRows; row++)
    {
      for (int column = 0; column < numCols; column++)
      {
        grid[row][column] = 0;
      }
    }
  }

  void Print()
  {
    for (int row = 0; row < numRows; row++)
    {
      for (int column = 0; column < numCols; column++)
      {
        cout << grid[row][column] << " ";
      }
      cout << endl;
    }
  }

  void Draw()
  {
    for (int row = 0; row < numRows; row++)
    {
      for (int column = 0; column < numCols; column++)
      {
        int cellValue = grid[row][column];
        DrawRectangle(column * cellSize + 11, row * cellSize + 11, cellSize - 1, cellSize - 1, colors[cellValue]);
      }
    }
  }

  bool IsCellEmpty(int row, int column)
  {
    if (grid[row][column] == 0)
    {
      return true;
    }
    return false;
  }

  int ClearFullRows()
  {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--)
    {
      if (IsRowFull(row))
      {
        ClearRow(row);
        completed++;
      }
      else if (completed > 0)
      {
        MoveRowDown(row, completed);
      }
    }
    return completed;
  }
};