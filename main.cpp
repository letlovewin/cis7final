#include <iostream>
#include "Graph.h"
#include <unordered_map>
#include <string>

using namespace std;

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

    vector<string> cities = {"Riverside", "Perris", "Moreno Valley", "Hemet"};

    /**
     * @todo Generate all trips the salesperson can take using Heap's algorithm.
    */

    // Demonstrating single-source shortest paths from Riverside

    unordered_map<string, float> cheapestPaths = G.singleSourceCheapestPaths("Riverside");
    for (auto i = cheapestPaths.begin(); i != cheapestPaths.end(); i++)
    {
        string key = i->first;
        float weight = i->second;
        if(key != "Riverside")
            cout << "Cheapest path from Riverside to " << key << ": " << weight << endl;
    }

    return 0;
}