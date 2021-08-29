#include <iostream>
#include "rng.h" // haha wont gett ittt in github because i cannot find it
#include <random>
#include <time.h> // for srand seed

constexpr int height = 10;
constexpr int width = 10;

int maxBoats = 10;

std::string grid[height][width];
std::string enemyBoats[height][width];

int RandomInt(int min, int max)
{
    const std::uniform_int_distribution<int> dist(min, max);
    return dist(g_rng);
}

void Show()
{
    std::cout << "0|1|2|3|4|5|6|7|8| 9" << '\n';
    for(int i = 1; i < height; i++)
    {
        for(int j = 1; j < width; j++)
        {
            grid[i][j] = "* ";
            int boats = 0;
            while (boats < maxBoats)
            {
                boats++;
                int boatX = RandomInt(0, width);
                int boatY = RandomInt(0, height);

                if (grid[boatX][boatY] == "* ")
                {
                    grid[boatX][boatY] = "H ";
                }
            }
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void enemySet()
{
    int enemyBoatsCount;
    for(int i = 1; i < height; i++)
    {
        for(int j = 1; j < width; j++)
        {
            grid[i][j] = "* ";
            enemyBoats[i][j] = "* ";
            while (enemyBoatsCount < maxBoats)
            {
                enemyBoatsCount++;
                int boatX = RandomInt(0, width);
                int boatY = RandomInt(0, height);

                if (enemyBoats[boatX][boatY] == "* ")
                {
                    enemyBoats[boatX][boatY] == "H ";
                }
            }
            std::cout << grid[i][j];
        }
        std::cout << '\n';
    }
}

void playerGuessing()
{

}

int main()
{
    srand(unsigned(time));
    Show();
    std::cout << "-----------------------" << '\n';
    enemySet();
    return 0;
}
