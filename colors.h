#pragma once
#include <raylib.h>
#include <vector>

using namespace std;

extern const Color darkGrey = {26, 31, 40, 255};
extern const Color green = {47, 230, 23, 255};
extern const Color red = {232, 18, 18, 255};
extern const Color orange = {226, 116, 17, 255};
extern const Color yellow = {237, 234, 4, 255};
extern const Color purple = {166, 0, 247, 255};
extern const Color cyan = {21, 204, 209, 255};
extern const Color blue = {13, 64, 216, 255};
extern const Color lightBlue = {59, 85, 162, 255};
extern const Color darkBlue = {44, 44, 127, 255};

vector<Color> GetCellColors()
{
  return {darkGrey, green, red, orange, yellow, purple, cyan, blue, lightBlue, darkBlue};
};