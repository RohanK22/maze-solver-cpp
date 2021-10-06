#include<bits/stdc++.h>

using namespace std;

class Maze {
    public:
    
    int n = -1;
    // Grid of 1s and 0s. 1s indicate wall and 0s indicate free path.
    vector<vector<int>> grid;
    string startCoordinate;
    string endCoordinate;
    int probabilityOfBlock = 30; // Percentage
    char blockCharcter = 33; // ASCII

    Maze(int n) {
        this->n = n;
        this->startCoordinate = coordinateToString(0,0);
        this->endCoordinate = coordinateToString(n - 1, n - 1);
    }

    void generateRandomGrid() {
        if(n < 2) {
            cout<<"Enter valid dimension (>2) !";
            return;
        }

        srand(time(NULL));
        for(int i = 0; i<n; i++) {
            vector<int> temp;
            for(int j = 0; j< n; j++) {
                temp.push_back(rand() % 100 + 1 <= probabilityOfBlock);
            }
            grid.push_back(temp);
        }

        // Enter grid at (0,0) and end at (n - 1, n - 1) **** Change this
        grid[0][0] = 0;
        grid[n - 1][n - 1] = 0;
    }

    void printGrid() {
        for(int i = 0; i<n; i++) {
            for(int j = 0; j< n; j++) {
                if(i == 0 && j == 0) cout<<"S"<<' ';
                else if ( i == n - 1 && j == n -1) cout<<"E"<<' ';
                else cout<<(grid[i][j] == 1 ? blockCharcter : '_')<<' ';
            }
            cout<<endl;
        }
    }
    
    void printSolutionGrid(vector<string> path) {
        cout<<"SOLUTION: "<<endl;
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(find(path.begin(), path.end(), coordinateToString(i, j)) == path.end()) {
                    cout<<(grid[i][j] == 1 ? blockCharcter: '_')<< ' ';
                } else {
                    cout<<"* ";
                }
            }
            cout<<endl;
        }
        cout<<"STEPS: "<<path.size()<<endl;
    }

    // Solve the maze and returns the path in terms a sequence of coordinates.
    vector<string> solveGridBFS() {
        map<string, vector<string>> adjList = getAdjList(); // Build a graph of all grid positions using a adjacency list.

        int nNodes = adjList.size(); // number of nodes
        string s = startCoordinate; // source vertex

        queue<string> q;
        map<string, bool> used;
        map<string, int> d; // distances
        map<string, string> p; // parent

        // Initialize Variables
        for(int i = 0; i<n; i++) {
            for(int j = 0; j< n; j++) {
                if(grid[i][j] == 1) continue;
                string pointStr = coordinateToString(i,j);
                used[pointStr] = false;
                d[pointStr] = INT16_MAX;
                p[pointStr] = "";
            }
        }

        q.push(s);
        used[s] = true;
        d[s] = 0;
        p[s] = "-1";

        // Begin BFS
        while(!q.empty()) {
            string point = q.front();
            q.pop();

            // cout<<point<<endl;
            for(string neighbour: adjList[point]) {
                if(!used[neighbour]) {
                    // cout<<"N: "<<neighbour<<" of "<<point<<endl;
                    used[neighbour] = true;
                    q.push(neighbour);
                    d[neighbour] = d[point] + 1;
                    p[neighbour] = point;
                }
            }
        }

        vector<string> path;

        // Construct path if possible
        if(!used[endCoordinate]) {
            // no possible paths;
            cout<<"UNSOLVEABLE MAZE"<<endl;
            return path;
        } 
        
        for(string point = endCoordinate; point != "-1"; point = p[point]) {
            path.push_back(point);
        }
        reverse(path.begin(), path.end());        
        return path;
    }

    map<string, vector<string>> getAdjList() {
        map<string, vector<string>> adjL;
        for(int i = 0; i<n; i++) {
            for(int j = 0; j< n; j++) {
                if(grid[i][j] == 1) continue;

                vector<string> paths;
                // up left down and right are legal moves from a given grid position.
                if(i - 1 >= 0) paths.push_back(coordinateToString(i - 1, j));
                if(i + 1 < n) paths.push_back(coordinateToString(i + 1, j));
                if(j - 1 >= 0) paths.push_back(coordinateToString(i, j - 1));
                if(j + 1 < n) paths.push_back(coordinateToString(i, j + 1));
                
                // UL, UR, DL, DR are also legal moves
                if(i - 1 >=0 && j - 1>=0) paths.push_back(coordinateToString(i - 1, j - 1));
                if(i - 1 >=0 && j + 1 >= 0) paths.push_back(coordinateToString(i - 1, j + 1));
                if(i + 1 < n && j - 1 >= 0) paths.push_back(coordinateToString(i + 1, j - 1));
                if(i + 1 < n && j + 1 < n) paths.push_back(coordinateToString(i + 1, j + 1));
                
                adjL[coordinateToString(i,j)] = paths;
            }
        }

        /* Print List 
        cout<<"PRINT ADJ LIST"<<endl;
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

    vector<string> path = m.solveGridBFS();

    if(path.size() == 0) {
        cout<<"NO PATHS FOUND"<<endl;
    } else {
        cout<<"PATH FOUND"<<endl;
        for(string point: path) {
            cout<<"  ->  "<<point;
        }
        cout<<endl;

        m.printSolutionGrid(path);
    }
    return 0;
}
