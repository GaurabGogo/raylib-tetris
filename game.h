#pragma once
#include <vector>
#include "grid.h"
#include "blocks.h"
#include <random>

using namespace std;

class Game
{
private:
  vector<Block> blocks;
  Block currentBlock;
  Block nextBlock;

  Grid grid;
  Sound rotateSound;
  Sound clearSound;

  vector<Block> GetAllBlocks()
  {
    return {IBlock(),
            JBlock(),
            LBlock(),
            OBlock(),
            SBlock(),
            TBlock(),
            ZBlock()};
  }

  Block GetRandomBlock()
  {
    if (blocks.empty())
    {
      blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
  }

  void MoveBlockLeft()
  {
    if (!gameOver)
    {
      currentBlock.Move(0, -1);
      if (IsBlockOutside() || BlockFits() == false)
      {
        currentBlock.Move(0, 1);
      }
    }
  }
  void MoveBlockRight()
  {
    if (!gameOver)
    {
      currentBlock.Move(0, 1);
      if (IsBlockOutside() || BlockFits() == false)
      {
        currentBlock.Move(0, -1);
      }
    }
  }

  bool IsBlockOutside()
  {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
      if (grid.IsCellOutside(item.row, item.column))
      {
        return true;
      }
    }
    return false;
  }

  void RotateBlock()
  {
    if (!gameOver)
    {
      currentBlock.Rotate();
      if (IsBlockOutside() || BlockFits() == false)
      {
        currentBlock.UndoRotation();
      }
      else
      {
        PlaySound(rotateSound);
      }
    }
  }

  void LockBlock()
  {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
      grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;
    if (BlockFits() == false)
    {
      gameOver = true;
    }
    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();
    if (rowsCleared > 0)
    {
      PlaySound(clearSound);
      UpdateScore(rowsCleared, 0);
    }
  }

  bool BlockFits()
  {
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
      if (grid.IsCellEmpty(item.row, item.column) == false)
      {
        return false;
      }
    }
    return true;
  }

  void Reset()
  {
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
  }

  void UpdateScore(int linesCleared, int moveDownPoints)
  {
    switch (linesCleared)
    {
    case 1:
      score += 100;
      break;
    case 2:
      score += 300;
      break;
    case 3:
      score += 500;
      break;
    default:
      break;
    }
    score += moveDownPoints;
  }

public:
  bool gameOver;
  int score;
  Music music;
  Game()
  {
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    InitAudioDevice();
    music = LoadMusicStream("Sounds/music.mp3");
    PlayMusicStream(music);
    rotateSound = LoadSound("Sounds/rotate.mp3");
    clearSound = LoadSound("Sounds/clear.mp3");
  }

  ~Game()
  {
    UnloadSound(rotateSound);
    UnloadSound(clearSound);
    UnloadMusicStream(music);
    CloseAudioDevice();
  }

  void Draw()
  {
    grid.Draw();
    currentBlock.Draw(11, 11);
    switch (nextBlock.id)
    {
    case 3:
      nextBlock.Draw(255, 290);
      break;
    case 4:
      nextBlock.Draw(255, 280);
      break;
    default:
      nextBlock.Draw(270, 270);
      break;
    }
  }

  void HandleInput()
  {
    int keyPressed = GetKeyPressed();
    if (gameOver && keyPressed != 0)
    {
      gameOver = false;
      Reset();
    }
    switch (keyPressed)
    {
    case KEY_LEFT:
      MoveBlockLeft();
      break;
    case KEY_RIGHT:
      MoveBlockRight();
      break;
    case KEY_DOWN:
      MoveBlockDown();
      UpdateScore(0, 1);
      break;
    case KEY_UP:
      RotateBlock();
      break;
    }
  }

  void MoveBlockDown()
  {
    if (!gameOver)
    {
      currentBlock.Move(1, 0);
      if (IsBlockOutside() || BlockFits() == false)
      {
        currentBlock.Move(-1, 0);
        LockBlock();
      }
    }
  }
};