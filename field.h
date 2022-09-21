#ifndef FIELD_H
#define FIELD_H
#include <vector>
#include <algorithm>

class Field
{

private:
int width;
int height;
int size;
int diff;
int mines;

public:
Field();
Field(int, int, int);
~Field();
std::vector<int> data;
int getWidth();
int getHeight();
int getSize();
int getMines();
int calculateMines(int, int);
int generateField();
void simpledraw();


};

#endif // FIELD_H
