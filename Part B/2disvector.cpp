#include <iostream>

using namespace std;
struct node {
    int dist[10];
    int from[10];
} DVR[10];

int main() {
    cout << "\n \n program to implement distance vector routing algorithm";
    int costmat[10][10];
    int nodes, i, j, k;
    cout << "\n \n enter the number of node:\n";
    cin >> nodes;

    cout << "\n enter the cost matrix:\n";
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            cin >> costmat[i][j];
            costmat[i][i] = 0;
            DVR[i].dist[j] = costmat[i][j];
            DVR[i].from[j] = j;
        }
    }
    for (i = 0; i < nodes; i++)
        for (j = 0; j < nodes; j++)
            for (k = 0; k < nodes; k++)
                if (DVR[i].dist[j] > costmat[i][k] + DVR[k].dist[j]) {
                    DVR[i].dist[j] = DVR[i].dist[k] + DVR[k].dist[j];
                    DVR[j].dist[i] = DVR[i].dist[j];
                    DVR[i].from[j] = k;
                    DVR[j].from[i] = k;
                }
    for (i = 0; i < nodes; i++) {
        cout << "\n \n for router: " << i + 1;

        for (j = 0; j < nodes; j++)
            cout << "\t \n node " << j + 1 << " via " << (DVR[i].from[j]) + 1 << " distance " << DVR[i].dist[j];
    }
    cout << endl;
    return 0;
}

// Output
// /tmp/BLClkZu8oX.o
// program to implement distance vector routing algorithm

//  enter the number of node:
// 3
// enter the cost matrix:
// 0 2 7
// 2 0 1
// 4 1 0
// for router: 1	 
//  node 1 via 1 distance 0	 
//  node 2 via 2 distance 2	 
//  node 3 via 2 distance 3

//  for router: 2	 
//  node 1 via 1 distance 2	 
//  node 2 via 2 distance 0	 
//  node 3 via 3 distance 1

//  for router: 3	 
//  node 1 via 2 distance 3	 
//  node 2 via 2 distance 1	 
//  node 3 via 3 distance 0

