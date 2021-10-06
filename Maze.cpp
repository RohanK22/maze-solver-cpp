#include<bits/stdc++.h>

using namespace std;

class Maze {
    public:
    
    int n = -1;
    // Grid of 1s and 0s. 1s indicate wall and 0s indicate free path.
    vector<vector<int>> grid;

    Maze(int n) {
        this->n = n;
    }

    void generateRandomGrid() {
        if(n < 2) {
            cout<<"Enter valid dimension (>2) !";
            return;
        }

        for(int i = 0; i<n; i++) {
            vector<int> temp;
            for(int j = 0; j< n; j++) {
                temp.push_back(rand() % 2);
            }
            grid.push_back(temp);
        }

        // Enter grid at (0,0) and end at (n - 1, n - 1)
        grid[0][0] = 0;
        grid[n - 1][n - 1] = 0;
    }

    void printGrid() {
        for(int i = 0; i<n; i++) {
            for(int j = 0; j< n; j++) 
                cout<<grid[i][j]<<' ';
            cout<<endl;
        }
    }

    // Solve the maze and returns the path in terms a sequence of coordinates.
    void solveGridBFS() {
        map<string, vector<string>> adjList = getAdjList(); // Build a graph of all grid positions using a adjacency list.

        int nNodes = adjList.size(); // number of nodes
        string s = "0,0"; // source vertex

        queue<string> q;
        vector<bool> used(nNodes);
        vector<int> d(nNodes); // distances
        vector<string> p(nNodes); // parent

        q.push(s);
        used[s] = true;

        // Begin BFS
        while(!q.empty()) {

        }

        return ;
    }

    map<string, vector<string>> getAdjList() {
        map<string, vector<string>> adjL;
        for(int i = 0; i<n; i++) {
            for(int j = 0; j< n; j++) {
                if(grid[i][j] == 1) continue;

                vector<string> paths;
                // up left down and right are legal moves from a given grid position.
                if(i - 1 >= 0 && grid[i - 1][j] == 0) {
                    paths.push_back(coordinateToString(i - 1, j));
                }

                if(i + 1 < n - 1 && grid[i + 1][j] == 0) {
                    paths.push_back(coordinateToString(i + 1, j));
                }

                if(j - 1 >= 0 && grid[i][j - 1] == 0) {
                    paths.push_back(coordinateToString(i, j - 1));
                }

                if(j + 1 < n - 1 && grid[i][j + 1] == 0) {
                    paths.push_back(coordinateToString(i, j + 1));
                }
                adjL[coordinateToString(i,j)] = paths;
            }
        }

        /* Print List
        for ( const auto &myPair : adjL ) {
            cout << myPair.first << "\n";
            for(const auto &li: myPair.second) {
                cout<<li<<"   -    ";
            }
            cout<<endl;
        }*/

        return adjL;
    }

    string coordinateToString(int x, int y) {
        return to_string(x) + "," + to_string(y);
    }
};



int main(int argc, char const *argv[])
{
    int n;
    cout<<"Enter the maze dimension(n): ";
    cin>>n;

    Maze m(n);
    m.generateRandomGrid();
    m.printGrid();

    m.solveGridBFS();


    return 0;
}
