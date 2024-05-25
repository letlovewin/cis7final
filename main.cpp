#include <iostream>
#include "Graph.h"
#include <unordered_map>
#include <string>
#include <algorithm>

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
     * @todo plz fix, see https://github.com/letlovewin/cis7final/pull/4 for more info
     */
    vector<vector<string>> permutations;
    do
    {
        vector<string> perm = {"Riverside"};
        perm.insert(perm.end(), cities.begin(), cities.end());
        perm.push_back("Riverside");
        permutations.push_back(perm);
    } while (next_permutation(cities.begin(), cities.end()));

    // Calculate the weight for each permutation and print them out
    for (int i = 0; i < permutations.size(); ++i)
    {
        float totalWeight = 0;
        for (int j = 0; j < permutations[i].size() - 1; ++j)
        {
            totalWeight += G.getWeight(permutations[i][j], permutations[i][j + 1]);
        }
        cout << "Trip " << i + 1 << ": ";
        for (int k = 0; k < permutations[i].size(); ++k)
        {
            cout << permutations[i][k];
            if (k < permutations[i].size() - 1)
                cout << " -> ";
        }
        cout << " (Total Weight: " << totalWeight << ")" << endl;
    }

    // Demonstrating single-source shortest paths from Riverside

    unordered_map<string, float> cheapestPaths = G.singleSourceCheapestPaths("Riverside");
    for (auto i = cheapestPaths.begin(); i != cheapestPaths.end(); i++)
    {
        string key = i->first;
        float weight = i->second;
        if (key != "Riverside")
            cout << "Cheapest path from Riverside to " << key << ": " << weight << endl;
    }

    return 0;
}