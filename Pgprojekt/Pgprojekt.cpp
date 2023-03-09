#include <iostream>
#include <cstdlib>
#include <iomanip>
using namespace std;

const int width_of_map = 20;
const int height_of_map = 40;
const char black_square = char(219);
const char white_square = ' ';
const char robot = char(232);

struct Node {
    int id;
    int coords[2];
    Node* next;
};
struct Graph {
    int num_of_vertices;
    Node** list;
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
void drawBoard(bool map[][20], int robot_x = -1, int robot_y = -1);
void fillTable(bool map[][20], const bool segment[][5], int segment_number, int& nr_of_vertices);
void buildTable(bool map[][20], int& nr_of_vertices);
Node* createNode(int x, int y, int id);
void addEdge(Graph& graph, int trg_x, int trg_y, int src_id, int trg_id);
void scout(bool map[][20], int scout_row, int scout_col, int& id, Graph& graph, int lookup_id[][20]);
void constructGraph(Graph& graph, int number_of_vertices);
bool DFS(Graph graph, int** path, bool visited[], bool map[][20], int& path_index, int A, int B);

int main()
{
    srand(time(NULL));
    
    Graph graph;
    int lookup_id[40][20] = {};
    int number_of_vertices = 0, id = 0, path_index=0;
    bool map[height_of_map][width_of_map];
    
    buildTable(map,number_of_vertices);
    constructGraph(graph, number_of_vertices);
    scout(map,0,2,id,graph,lookup_id);
    
    //Wybieranie randomowych punktów, startowy i końcowy
    int A = rand() % number_of_vertices;
    int B = rand() % number_of_vertices;

    //Tablica punktów odwiedzonych i drogi;
    bool* visited = new bool[number_of_vertices]();
    int** path = new int*[number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++) path[i] = new int[3]{};
    DFS(graph,path, visited, map,path_index,A, B);
    //Drukowanie drogi
    for (int i = 0; i < path_index; i++)
    {
        system("cls");
        drawBoard(map, path[i][1], path[i][2]);
    }
    cout << "A: " << A << " B: " << B << endl;
    for (int i = 0; i < path_index; i++)
    {
        cout << path[i][0]<<"->";
    }
   
    //DEBUG
    cout <<endl<< number_of_vertices << endl;

    //UWAGA ID WIERZCHOŁKÓW W DRUKOWANEJ TABELECE SĄ WIĘKSZE O 1 OD WARTOŚCI W WIERZCHOŁKACH
    /*for (int i = 0; i < 40; i++)
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
        cout << "vector " << i << ": ";
        while (p != NULL) {
            cout<< p->id<<" ->";
            p = p->next;
        }
        cout << endl;
    }*/

    //usuwanko :)
    for (int i = 0; i < number_of_vertices; i++) delete path[i];
    delete []path;
    delete []visited;
    for (int i = 0; i < number_of_vertices; i++) delete graph.list[i];
}
void drawBoard(bool map[][20], int robot_x = -1, int robot_y = -1) {
    cout << setw(0);
    for (int i = 0; i < 40; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (robot_x == i && robot_y == j) {
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
void fillTable(bool map[][20], const bool segment[][5], int segment_number, int& nr_of_vertices) {
    int row = (segment_number / 4) * 5;
    int col = (segment_number % 4) * 5;
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (!segment[i][j]) nr_of_vertices++;
            map[i + row][j + col] = segment[i][j];
        }
    }
}
void buildTable(bool map[][20], int& nr_of_vertices) {
    for (int i = 0; i < 32; i++)
    {
        int choice = rand() % 6;
        switch (choice)
        {
        case 0:
            fillTable(map, A, i, nr_of_vertices);
            break;
        case 1:
            fillTable(map, B, i, nr_of_vertices);
            break;
        case 2:
            fillTable(map, C, i, nr_of_vertices);
            break;
        case 3:
            fillTable(map, D, i, nr_of_vertices);
            break;
        case 4:
            fillTable(map, E, i, nr_of_vertices);
            break;
        case 5:
            fillTable(map, F, i, nr_of_vertices);
            break;
        default:
            break;
        }
    }
}

Node* createNode(int x, int y, int id) {
    Node* node = new Node;
    node->coords[0] = x;
    node->coords[1] = y;
    node->id = id;
    node->next = NULL;
    return node;
}
void addEdge(Graph& graph, int trg_x, int trg_y, int src_id, int trg_id) {
    src_id--;
    trg_id--;
    Node* node = createNode(trg_x, trg_y, trg_id);
    node->next = graph.list[src_id];
    graph.list[src_id] = node;
}
void scout(bool map[][20], int scout_row, int scout_col, int& id, Graph& graph, int lookup_id[][20]) {

    if (lookup_id[scout_row][scout_col] != 0) return;
    int dir[4][2] = { {1,0},{-1,0},{0,1},{0,-1} };
    id++;
    lookup_id[scout_row][scout_col] = id;
    for (int i = 0; i < 4; i++)
    {
        int new_row = scout_row + dir[i][0];
        int new_col = scout_col + dir[i][1];
        if (!map[new_row][new_col] && new_row >= 0 && new_row < 40 && new_col >= 0 && new_col < 20) {
            scout(map, new_row, new_col, id, graph, lookup_id);
            addEdge(graph, new_row, new_col, lookup_id[scout_row][scout_col], lookup_id[new_row][new_col]);
        }
    }
}
//inicjalizuje graf, definiuje ilość wierzchołków i przypisuje w tablicy sąsiedztwa NULL
void constructGraph(Graph& graph, int number_of_vertices) {
    graph.num_of_vertices = number_of_vertices;
    graph.list = new Node * [number_of_vertices];
    for (int i = 0; i < number_of_vertices; i++) graph.list[i] = nullptr;
}
bool DFS(Graph graph, int** path, bool visited[], bool map[][20], int& path_index, int A, int B) {
    Node* node = graph.list[A];
    path[path_index][0] = A;
    path[path_index][1] = node->coords[0];
    path[path_index][2] = node->coords[1];

    path_index++;
    visited[A] = true;
    if (A == B) {
        return true;
    }
    while (node != nullptr) {
        A = node->id;
        if (!visited[A]) {
            if (DFS(graph, path, visited, map, path_index, A, B)) {
                return true;
            }
        }
        node = node->next;
    }
    path[path_index][0] = NULL;
    path[path_index][1] = NULL;
    path[path_index][2] = NULL;
    path_index--;
    return false;
}
