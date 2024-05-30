#include <iostream>
#include "Graph.h"
#include <unordered_map>
#include <string>
#include <climits>
#include <algorithm>

using namespace std;

vector<vector<string>> permutations;

void generatePermutations(int k, vector<string> A)
{
    if (k <= 1)
    {
        permutations.push_back(A);
        return;
    }
    generatePermutations(k - 1, A);
    for (int i = 0; i < k - 1; i++)
    {
        if (k % 2 == 0)
        {
            swap(A[i], A[k - 1]);
        }
        else
        {
            swap(A[0], A[k - 1]);
        }
        generatePermutations(k - 1, A);
    }
}

float getPathWeight(vector<string> &path, Graph<string> &graph)
{
    float weight = 0;
    for (int i = 1; i < path.size(); i++)
    {
        weight += graph.getWeight(path[i - 1], path[i]);
    }
    return weight;
}

int main()
{
    Graph<string> G("Inland Empire");

    // Constructing the graph as found on the assignment.
    G.addVertex("Riverside");
    G.addVertex("Perris");
    G.addVertex("Moreno Valley");
    G.addVertex("Hemet");

    G.addUndirectedEdge("Riverside", "Perris", 24);
    G.addUndirectedEdge("Riverside", "Moreno Valley", 16);
    G.addUndirectedEdge("Riverside", "Hemet", 33);
    G.addUndirectedEdge("Perris", "Moreno Valley", 18);
    G.addUndirectedEdge("Perris", "Hemet", 30);
    G.addUndirectedEdge("Moreno Valley", "Hemet", 26);

    vector<string> cities = {"Perris", "Moreno Valley", "Hemet"};
    unordered_map<string, float> cheapestPaths = G.singleSourceCheapestPaths("Riverside");
    generatePermutations(3, cities);
    for(int i = 0; i < 6; i++) {
        permutations[i].push_back("Riverside");
        swap(permutations[i][0],permutations[i][3]);
        permutations[i].push_back("Riverside");
    }
    int choice;

selectionScreen:
    cout << "____________________________________________________________________________" << '\n';
    cout << "|                                                                          |" << '\n';
    cout << "|                                                                          |" << '\n';
    cout << "|   Inland Empire Salesperson Trip                                         |" << '\n';
    cout << "|                                                                          |" << '\n';
    cout << "|                                                                          |" << '\n';
    cout << "|   (1) - Generate all possible paths the salesperson can take             |" << '\n';
    cout << "|   (2) - Find the cheapest Hamiltonian circuit the salesperson can take   |" << '\n';
    cout << "|   (3) - Find the cheapest path from Riverside to all other cities        |" << '\n';
    cout << "|   (4) - Exit                                                             |" << '\n';
    cout << "|                                                                          |" << '\n';
    cout << "|__________________________________________________________________________|" << '\n';
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        for (int i = 0; i < 6; i++)
        {
            for (auto j : permutations[i])
            {
                cout << j << ' ';
            }
            cout << '\n';
        }
        goto selectionScreen;
        break;
    }
    case 2:
    {
        vector<string> min = permutations[0];
        float min_total = getPathWeight(permutations[0], G);
        for (int i = 1; i < 6; i++)
        {
            vector<string> temp = permutations[i];
            float temp_total = getPathWeight(permutations[i], G);
            if (temp_total < min_total)
                min = temp;
        }
        cout << "The cheaapest Hamiltonian circuit on this graprh is ";
        for (auto i : min)
        {
            cout << i << ' ';
        }
        cout << '\n';
        goto selectionScreen;
        break;
    }
    case 3:
    {
        // Dijkstra

        for (auto i = cheapestPaths.begin(); i != cheapestPaths.end(); i++)
        {
            string key = i->first;
            float weight = i->second;
            if (key != "Riverside")
            {
                cout << "Cheapest path from Riverside to " << key << ": " << weight << endl;
            }
        }
        goto selectionScreen;
        break;
    }
    case 4:
    {
        cout << "Goodbye!" << endl;
        break;
    }
    default:
    {
        cout << "That is an invalid choice!" << endl;
        goto selectionScreen;
    }
    }

    return 0;
}