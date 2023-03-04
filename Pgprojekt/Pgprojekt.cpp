// Pgprojekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int width_of_map = 20;
const int height_of_map = 40;
const char black_square = char(219);
const char white_square = ' ';
const char robot = char(234);

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
void fillTable(bool map[][20], const bool segment[][5], int segment_number, int &nr_of_vertices);
void drawBoard(bool map[][20], int robot_x = NULL, int robot_y = NULL) {
    cout << setw(0);
   
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (robot_x == i  && robot_y == j) {
                cout << robot;
                continue;
            }
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
void buildTable(bool map[][20],int& nr_of_vertices) {
    for (int i = 0; i < 32; i++)
    {
        int choice = rand() % 6;
        switch (choice)
        {
        case 0:
            fillTable(map, A, i,nr_of_vertices);
            break;
        case 1:
            fillTable(map, B, i,nr_of_vertices);
            break;
        case 2:
            fillTable(map, C, i,nr_of_vertices);
            break;
        case 3:
            fillTable(map, D, i,nr_of_vertices);
            break;
        case 4:
            fillTable(map, E, i,nr_of_vertices);
            break;
        case 5:
            fillTable(map, F, i,nr_of_vertices);
            break;
        default:
            break;
        }
    }
}
void fillTable(bool map[][20],const bool segment[][5], int segment_number, int &nr_of_vertices) {
    int row = (segment_number / 4)*5;
    int column = (segment_number % 4)*5;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!segment[i][j]) nr_of_vertices++;
            map[i + row][j + column] = segment[i][j];
        }
    }
}

void scout(bool map[][20],bool isVisited[][20],int scout_row ,int scout_column) {
        isVisited[scout_row][scout_column] = 1;
        if (!map[scout_row-1][scout_column] && scout_row > 0 && !isVisited[scout_row-1][scout_column])
        {
            scout(map,isVisited, scout_row - 1, scout_column);
        }
        if (!map[scout_row + 1][scout_column] && scout_row < 39 && !isVisited[scout_row + 1][scout_column])
        {
            scout(map, isVisited,scout_row + 1, scout_column);
        }
        if (!map[scout_row][scout_column - 1] && scout_column > 0 && !isVisited[scout_row][scout_column - 1])
        {
            scout(map,isVisited, scout_row, scout_column - 1);
        }
        if (!map[scout_row][scout_column + 1] && scout_column < 19 && !isVisited[scout_row][scout_column +1])
        {
            scout(map,isVisited,scout_row, scout_column+1);
        }
}
int main()
{
    int number_of_vertices = 0;
    srand(time(NULL));
    bool map[height_of_map][width_of_map];
    buildTable(map,number_of_vertices);
    bool isVisited = new bool *[number_of_vertices];
    bool visits[40][20] = { 0 };
    scout(map,visits,0,2);
    //drawBoard(map);
    
}
