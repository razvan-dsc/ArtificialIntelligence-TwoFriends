#include<iostream>
#include<string>
#include<ctime>
#include<cstring>
using namespace std;
int N;
int id;
int graph[10][10];
int dist[10];
bool visited[10];
int parent[10];
void createGraph()//Creates the Graph and adds values for each node and cost
{
    int i, j, max, u, v, w;
    cout << "Enter the number of nodes : ";//Allow to enter a number of total nodes for our graph
    cin >> N;
    for (i = 0; i <= N; i++)
        for (j = 0; j <= N; j++) //Creates the matrix for the map
            graph[i][j] = 0;
    max = N * (N + 1);
    for (i = 0; i < max; i++)
    {
        cout << "Enter both Nodes and Weight (Enter -1 to exit): ";//Introduce -1 in the console to exit the Edge and Weight submenu
        cin >> u >> v >> w;
        if (u == -1)    break;
        else
        {
            graph[u][v] = w; 
            graph[v][u] = w;
        }
    }
}
/*Graph is created where further functions like the two friends function is performed*/
int minDistance()//Calculates the minimum distance for the path
{
    int min = 10000, minDist;
    for (int v = 0; v < N; v++)
        if (visited[v] == false && dist[v] <= min)
        {
            min = dist[v];
            minDist = v;
        }
    return minDist;
}
void printPath(int j)//Creates the path for the friends to follow
{
    if (parent[j] == -1)
        return;
    printPath(parent[j]);
    cout << j << " ";
}
/*Prints the path to reach the friend's station*/
int Algorithm(int x, int f)//A* algorithm used for the problem as presented in the course
{
    int src;
    cout << "Enter the Source Node : ";//The program asks you to introduce a source node for each friend
    cin >> src;
    for (int i = 0; i < N; i++)
    {
        parent[0] = -1;
        dist[i] = 10000;//Represents the maximum distance
        visited[i] = false;
    }
    dist[src] = 0;
    for (int count = 0; count < N - 1; count++)
    {
        int u = minDistance();//Finds the minimum distance for each friend path
        visited[u] = true;
        for (int v = 0; v < N; v++) {
            if (!visited[v] && graph[u][v] &&
                dist[u] + graph[u][v] < dist[v])
            {
                // cout << "Good" << endl;
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
    if (f != 2)
        cout << "Src->Dest\tDistance\tPath" << endl;//Indicates the output display for the first friend, displaying the search of the nodes and the destination from node to node, the distance(cost) used from each branch of the graph and the path where friend 1 calls and waits for friend 2.
    else
    {
        cout << "Src->Dest\tDistance\t\t\tPath" << endl;//Indicates the output display for the second friend, displaying the search of the nodes and the destination from node to node, the distance(cost) used from each branch of the graph and the path where friend 2 calls and waits for friend 1.
    }
    int idx = 0;
    for (int i = 1; i < N; i++)
    {
        if (f == 2)
        {
            //cout << "Src->Dest\t\t\t\tPath" << endl;//output display
            cout << src << "->" << i << "\t\t" << "\t\t" << src << " ";
        }
        else
        {
            // cout << "Src->Dest\tDistance\tPath" << endl;//output display
            cout << src << "->" << i << "\t\t" << dist[i] << "\t\t" << src << " ";
        }
        if (src == x)
        {
            cout << "Path:";
            printPath(i);
            return x;//The path is created for every friend
        }
        else
        {
            cout << "Friend " << f << " calling his friend.  Path: ";//This is where the first/second friend calls the other friend and waits for his move
            printPath(i);
        }
        idx = dist[i];
        cout << endl;
    }
    return x;
}
/*Here the source node is taken and the path along with other features is displayed while the friends are on their way to meet eachother. Here distance is returned where both of the friends can meet together with the fastest route possbile */
int main()
{
    cout << "Graph Creation." << endl;
    createGraph();
    int goal, goal1;
    cout << "Enter the Goal Point:";//Represents the node (city) where we want the 2 friends to meet
    int n;
    cin >> n;
    cout << "For Friend 1." << endl;//We input the starting node for the first friend
    goal = Algorithm(n, 1);
    if (goal == -1)
    {
        cout << "Goal Not Reached." << endl;//Error displaying that the common node was not reached by the two friends
        exit(0);
    }
    cout << "For Friend 2." << endl;//We input the starting node for the second friend
    goal1 = Algorithm(n, 2);
    if (goal1 == -1)
    {
        cout << "Goal Not Reached." << endl;//Error displaying that the common node was not reached by the two friends
        exit(0);
    }

    cout << "Friends meet at point " << goal << endl;//This indicates the the two friends reached the goal, meaning the shortest distance between them.
    return 0;
}