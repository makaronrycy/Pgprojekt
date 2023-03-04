// Pgprojekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int width_of_map = 20;
const int height_of_map = 40;
const char black_square = '1'/*char(219) */;
const char white_square = '0';

const bool A[5][5] = {
    {1,1,0,1,1},
    {1,0,0,1,1},
    {0,0,1,0,0},
    {1,0,0,0,1},
    {1,1,0,1,1}
};
const bool B[5][5] = {
    {1,1,0,0,1},
    {0,1,1,0,1},
    {0,0,0,0,0},
    {1,0,0,0,1},
    {1,1,0,0,1}
};
const bool C[5][5] = {
    {0,0,0,0,0},
    {0,0,1,0,0},
    {0,0,1,1,0},
    {1,0,1,1,1},
    {1,0,0,0,0}
};
const bool D[5][5] = {
    {1,1,0,0,0},
    {1,0,0,1,0},
    {0,0,1,0,0},
    {0,1,0,0,1},
    {1,0,0,1,1}
};
const bool E[5][5] = {
    {0,0,0,1,1},
    {1,0,0,0,1},
    {0,0,1,0,0},
    {0,0,1,0,0},
    {0,0,0,0,1}
};
const bool F[5][5] = {
    {1,1,0,1,1},
    {1,1,0,1,1},
    {0,0,0,0,0},
    {1,1,0,1,1},
    {1,1,0,1,1}
};
/*Segmenty ID:
    A = 0
    B = 1
    C = 2
    D = 3
    E = 4
    F = 5
*/
void fillTable(bool map[][20], const bool segment[][5], int segment_number);
void drawBoard(bool map[][20]) {
    cout << setw(0);
   
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            switch (map[i][j])
            {
            case 1:
                cout << black_square;
                break;
            case 0:
                cout << white_square;
                break;
            }
        }
        cout << endl;
    }
}
void buildTable(bool map[][20]) {
    for (int i = 0; i < 32; i++)
    {
        int choice = rand() % 5;
        switch (choice)
        {
        case 0:
            fillTable(map, A, i);
            break;
        case 1:
            fillTable(map, B, i);
            break;
        case 2:
            fillTable(map, C, i);
            break;
        case 3:
            fillTable(map, D, i);
            break;
        case 4:
            fillTable(map, E, i);
            break;
        case 5:
            fillTable(map, F, i);
            break;
        default:
            break;
        }
    }
}
void fillTable(bool map[][20],const bool segment[][5], int segment_number) {
    int row = (segment_number / 4)*5;
    int column = (segment_number % 4)*5;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            map[i + row][j + column] = segment[i][j];
        }
    }
}
int main()
{
    srand(time(NULL));
    bool map[height_of_map][width_of_map];
    buildTable(map);
    drawBoard(map);
}
