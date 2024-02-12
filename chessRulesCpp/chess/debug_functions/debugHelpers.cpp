#include "debugHelpers.h"
#include <iostream>
#define COLUMNS 8 
#define ROWS    8

namespace debug
{
    void printArrs(std::bitset<NUM_OF_PIECES>** arr)
    {
        int count = 0;

        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLUMNS; x++)
            {
                count = 0;

                for (int index = 0; index < NUM_OF_PIECES; index++)
                {
                    if (arr[y][x][index])
                    {
                        std::cout << index << ',';
                        count++;
                    }
                }
                if (count == 0)
                {
                    std::cout << "n";
                }
                std::cout << "   ";
            }
            std::cout << std::endl;
        }
        std::cout << "\n\n\n";
    }

    void resetArr(std::bitset<NUM_OF_PIECES>** arr)
    {
        for (int i = 0; i < ROWS; i++)
        {
            for (int j = 0; j < COLUMNS; j++)
            {
                arr[i][j].reset();
            }
        }
    }

    void printaArrIndex(std::bitset<NUM_OF_PIECES>** arr, const int& index)
    {
        for (int y = 0; y < ROWS; y++)
        {
            for (int x = 0; x < COLUMNS; x++)
            {

               if (arr[y][x][index])
               {
                   std::cout << index;
               }
               else
               {
                   std::cout << "n";
               }
                std::cout << "   ";
            }
            std::cout << std::endl;
        }

        std::cout << "\n\n\n";
    }
}