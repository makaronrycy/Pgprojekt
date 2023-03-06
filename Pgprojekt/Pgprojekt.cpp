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

struct Node {
    int coords[2];
    struct Node* next;
};
struct Graph {
    int num_of_vertices;
    struct Node** list;
};
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
void drawBoard(bool map[][20], int robot_x = -1, int robot_y = -1) {
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
        int choice = rand() % 1;
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
Node *createNode(int x, int y) {
    Node* node = new Node;
    node->coords[0] = x;
    node->coords[1] = y;
    node->next = NULL;
    return node;
}
void addEdge(Graph &graph,int trg_x,int trg_y,int src_id) {
    src_id--;
    Node *node = createNode(trg_x, trg_y);
    node->next = graph.list[src_id];
    graph.list[src_id] = node;
}
void scout(bool map[][20], bool isVisited[][20], int scout_row, int scout_column, int& id, Graph& graph, int lookup_id[][20]) {

    if (isVisited[scout_row][scout_column]) return;
    id++;
    lookup_id[scout_row][scout_column] = id;
    isVisited[scout_row][scout_column] = 1;
    /*system("cls");
    drawBoard(isVisited, scout_row, scout_column);*/
    if (!map[scout_row - 1][scout_column] && scout_row > 0)
    {
        scout(map, isVisited, scout_row - 1, scout_column, id, graph, lookup_id);
        addEdge(graph, scout_row - 1, scout_column, lookup_id[scout_row][scout_column]);
    }
    if (!map[scout_row + 1][scout_column] && scout_row < 39)
    {
        scout(map, isVisited, scout_row + 1, scout_column, id, graph, lookup_id);
        addEdge(graph, scout_row + 1, scout_column, lookup_id[scout_row][scout_column]);
    }
    if (!map[scout_row][scout_column - 1] && scout_column > 0)
    {
        scout(map, isVisited, scout_row, scout_column - 1, id, graph, lookup_id);
        addEdge(graph, scout_row, scout_column - 1, lookup_id[scout_row][scout_column]);
    }
    if (!map[scout_row][scout_column + 1] && scout_column < 19)
    {
        scout(map, isVisited, scout_row, scout_column + 1, id, graph, lookup_id);
        addEdge(graph, scout_row, scout_column + 1, lookup_id[scout_row][scout_column]);
    }
}
//inicjalizuje graf, definiuje ilość wierzchołków i przypisuje w tablicy sąsiedztwa NULL
void initializeGraph(Graph &graph, int number_of_vertices) {
    graph.num_of_vertices = number_of_vertices;
    graph.list = new Node *[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++)
    {
        graph.list[i] = NULL;
    }
}
int main()
{
    srand(time(NULL));
    int lookup_id[40][20] = {};
    Graph graph;
    int number_of_vertices = 0,id = 0;
    bool visits[40][20] = { 0 };
    bool map[height_of_map][width_of_map];
    srand(time(NULL));
    buildTable(map,number_of_vertices);
    initializeGraph(graph, number_of_vertices);
    bool isVisited = new bool *[number_of_vertices];
    scout(map,visits,0,2,id,graph,lookup_id);

    //DEBUG
    /*cout << number_of_vertices << endl;
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            cout<<setw(4)<<lookup_id[i][j];
        }
        cout << endl;
    }
    for (int i = 0; i < number_of_vertices; i++)
    {
        Node* p = graph.list[i];
        cout << "Vector " << i << ": ";
        while (p != NULL) {
            cout<< lookup_id[p->coords[0]][p->coords[1]]-1<<" ->";
            p = p->next;
        }
        cout << endl;
    }*/
    drawBoard(map);
    
}
