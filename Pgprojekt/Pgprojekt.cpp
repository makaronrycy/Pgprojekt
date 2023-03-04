// Pgprojekt.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int widthOfMap = 1;
const int heightOfMap = 1;
const char blackSquare = char(219);
const char whiteSquare = ' ';

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
void drawBoard(const bool map[][5]) {
    cout << setw(0);
   
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            switch (map[i][j])
            {
            case 1:
                cout << blackSquare;
                break;
            case 0:
                cout << whiteSquare;
                break;
            }
        }
        cout << endl;
    }
}
//
//void drawSegB() {
//    cout << setw(0);
//    for (int i = 0; i < 5; i++)
//    {
//        for (int j = 0; j < 5; j++)
//        {
//            switch (B[i][j])
//            {
//            case 1:
//                cout << blackSquare;
//                break;
//            case 0:
//                cout << whiteSquare;
//                break;
//            }
//        }
//        cout << endl;
//    }
//}

int main()
{
    //int map[5][5];
    drawBoard(A);
    drawBoard(B);
    drawBoard(C);
    drawBoard(D);
    drawBoard(E);
}
