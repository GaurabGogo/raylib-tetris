#pragma once

class Position
{
private:
public:
  int row;
  int column;
  Position(int row, int column)
  {
    this->row = row;
    this->column = column;
  }
};