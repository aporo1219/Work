#include "Map.h"
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;

Map::Map()
{
    //ID�̑��
    ID = MAP;
}

int Map::Action(list<unique_ptr<Base>>& base)
{
    return 0;
}

void Map::Draw()
{
    //CSV�̓ǂݍ���
    std::vector<std::vector<int>> LoadCSV(const std::string & FileName);

    //�}�b�v�̓ǂݍ���
    auto Land = LoadCSV("MYMap.csv");

    //�}�b�v�̕`��
    for (int y = 0; y < Land.size(); y++)
    {
        for (int x = 0; x < Land[y].size(); x++)
        {
            int Value = Land[y][x];
            DrawFormatString(x * 32, y * 32, GetColor(255, 255, 255), "%d", Value);
        }
    }

    ScreenFlip();
}

//
std::vector<std::vector<int>> LoadCSV(const std::string& FileName)
{
    std::vector<std::vector<int>> Data;
    std::ifstream File(FileName);
    std::string  Line;

    while (std::getline(File, Line))
    {
        std::vector<int> Row;
        std::stringstream SS(Line);
        std::string Cell;
        while (std::getline(SS, Cell, ','))
        {
            Row.push_back(std::stoi(Cell));
        }
        Data.push_back(Row);
    }

    return Data;
}
