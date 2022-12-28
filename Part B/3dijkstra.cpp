#include <iostream>
//#include <climits>
using namespace std;

int miniDist(int distance[], bool Tset[]) {
    int minimum = INT_MAX, ind;
    for (int k = 0; k < 6; k++) {
        if (!Tset[k] && distance[k] <= minimum) {
            minimum = distance[k];
            ind = k;
        }
    }
    return ind;
}

void DijkstraAlgo(int graph[6][6], int src) {
    int distance[6];
    bool Tset[6];
    for (int k = 0; k < 6; k++) {
        distance[k] = INT_MAX;
        Tset[k] = false;
    }
    distance[src] = 0;
    for (int i = 0; i < 6; i++) {
        int m = miniDist(distance, Tset);
        Tset[m] = true;
        for (int k = 0; k < 6; k++) {
            if (!Tset[k] && graph[m][k] && distance[m] != INT_MAX &&
                distance[m] + graph[m][k] < distance[k])
                distance[k] = distance[m] + graph[m][k];
        }
    }
//    int distances[10] ={0,1,2,4,2,3};
    cout << "Vertex\t\tDistance from source vertex" << endl;
    for (int k = 0; k < 6; k++) {
        char str = 65 + k;
        cout << str << "\t\t\t" << distance[k] << endl;
    }
}

int main() {
    int graph[6][6] = {
            {0, 1, 2, 0, 0, 0},
            {1, 0, 0, 5, 1, 0},
            {2, 0, 0, 2, 3, 0},
            {0, 5, 2, 0, 2, 2},
            {0, 1, 3, 2, 0, 1},
            {0, 0, 0, 2, 1, 0}};
    DijkstraAlgo(graph, 0);
//    cout<<INT_MAX;
    return  0;
}
// Output
// /tmp/BLClkZu8oX.o
// Vertex		Distance from source vertex
// A			2
// B			3
// C			0
// D			2
// E			3
// F			4
