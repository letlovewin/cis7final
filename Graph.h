/**
 * @author Gray
 * @details Header for the Graph class. Implemented using a basic adjacency list. Weights are included in the edges.
 */

// Beginning includes, all of that necessary stuff

#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

#include <climits>
#include <stdexcept>

using namespace std;

// Beginning implementation of the Graph class.

template <typename T>
class Graph
{
private:
    string graphName;
    unordered_map<T, vector<tuple<T, float>>> adjacency_list;

public:
    Graph(string name);
    string getName();
    float getWeight(T u, T v);
    void setName(string name);
    void addVertex(T ID);
    void removeVertex(T ID);
    int degree(T vertex);
    void addEdge(T u, T v, float weight);
    void addUndirectedEdge(T u, T v, float weight);
    void removeEdge(T u, T v);
    void removeUndirectedEdge(T u, T v);
    unordered_map<T, float> singleSourceCheapestPaths(T origin);
    vector<T> depthFirstSearch(T origin, T target);
};

// Beginning implementation of member functions of Graph.

template <typename T>
Graph<T>::Graph(string name)
{
    graphName = name;
}

template <typename T>
string
Graph<T>::getName()
{
    return graphName;
}

template <typename T>
float
Graph<T>::getWeight(T u, T v) {
    if(adjacency_list.count(u) == 0)
        throw invalid_argument("Provided vertex does not exist in Graph " + graphName);
    for(int i = 0; i < adjacency_list[u].size(); i++) {
        if(get<0>(adjacency_list[u][i]) == v) {
            return get<1>(adjacency_list[u][i]);
        }
    }
    throw invalid_argument("Provided edge does not exist in Graph " + graphName);
}

template <typename T>
void Graph<T>::setName(string name)
{
    graphName = name;
}

template <typename T>
int Graph<T>::degree(T vertex)
{
    if (adjacency_list.count(vertex) == 0)
        throw invalid_argument("Provided vertex does not exist in Graph " + graphName);
    return adjacency_list[vertex].size();
}

// Adds a vertex to the adjacency list.
template <typename T>
void Graph<T>::addVertex(T ID)
{
    if (adjacency_list.count(ID) != 0)
        throw invalid_argument("Provided vertex already exists in Graph " + graphName);
    adjacency_list.insert({ID, {}});
}

// Removes a vertex from the adjacency list.
template <typename T>
void Graph<T>::removeVertex(T ID)
{

    if (adjacency_list.count(ID) == 0)
        throw invalid_argument("Provided vertex does not exist in Graph " + graphName);

    adjacency_list.erase(ID);

    // This block of code iterates through each entry in the adjacency list and scrubs the vertex from those entries to stop any ghost edges from persisting in the graph.
    for (auto i = adjacency_list.begin(); i != adjacency_list.end(); i++)
    {

        T key = i->first;
        vector<tuple<T, float>> list = i->second;

        for (int j = 0; j < list.size(); j++)
        {

            if (get<0>(list[j]) == ID)
                list.erase(list.begin() + j);
        }
    }
}

// Adds a directed edge in the form (u, v)
template <typename T>
void Graph<T>::addEdge(T u, T v, float weight)
{
    if (adjacency_list.count(u) == 0)
        throw invalid_argument("Vertex u does not exist in Graph " + graphName);
    if (adjacency_list.count(v) == 0)
        throw invalid_argument("Vertex v does not exist in Graph " + graphName);
    adjacency_list[u].push_back(make_tuple(v, weight));
}

// Adds an undirected edge in the form {u, v}
template <typename T>
void Graph<T>::addUndirectedEdge(T u, T v, float weight)
{
    addEdge(u, v, weight);
    addEdge(v, u, weight);
}

// Removes the directed edge (u,v)
template <typename T>
void Graph<T>::removeEdge(T u, T v)
{
    if (adjacency_list.count(u) == 0)
        throw invalid_argument("Vertex u does not exist in Graph " + graphName);

    vector<tuple<T, float>> list = adjacency_list[u];

    for (int i = 0; i < list.size(); i++)
    {
        if (get<0>(list[i]) == u)
            list.erase(list.begin() + i);
    }
}

template <typename T>
void Graph<T>::removeUndirectedEdge(T u, T v)
{
    if (adjacency_list.count(u) == 0)
        throw invalid_argument("Vertex u does not exist in Graph " + graphName);
    if (adjacency_list.count(v) == 0)
        throw invalid_argument("Vertex v does not exist in Graph " + graphName);
    removeEdge(u, v);
    removeEdge(v, u);
}

// See https://en.wikipedia.org/wiki/Dijkstra's_algorithm#Algorithm
template <typename T>
unordered_map<T, float> Graph<T>::singleSourceCheapestPaths(T origin)
{
    if(adjacency_list.count(origin) == 0)
        throw invalid_argument("Vertex does not exist in Graph " + graphName);
    queue<T> Q;
    unordered_set<T> V;
    unordered_map<T, float> OPT; // This is the meat of Djikstra's algorithm. This is essentially a breadth-first search, but at each step, you're setting opt[vertex.child] to min { opt[vertex] + weight(child), opt[child] }.

    for (auto i = adjacency_list.begin(); i != adjacency_list.end(); i++)
    {
        T key = i->first;
        OPT.insert({key, INT_MAX});
    }

    OPT[origin] = 0;

    Q.push(origin);
    while (!(Q.empty()))
    {
        T vertex = Q.front();

        V.insert(vertex);

        vector<tuple<T, float>> list = adjacency_list[vertex];

        for (int i = 0; i < list.size(); i++)
        {

            T child_name = get<0>(list[i]);
            if (V.count(child_name) == 0)
            {
                float child_weight = get<1>(list[i]);

                OPT[child_name] = min(OPT[vertex] + child_weight, OPT[child_name]);

                Q.push(child_name);
            }
        }

        Q.pop();
    }

    return OPT;
}

template <typename T>
vector<T> Graph<T>::depthFirstSearch(T origin, T target)
{
    queue<T> Q;
    unordered_set<T> V;

    vector<T> path;

    Q.push(origin);

    while (!(Q.empty()))
    {
        T vertex = Q.front();

        if (V.count(vertex) == 0)
        {
            V.insert(vertex);

            vector<tuple<T, float>> list = adjacency_list[vertex];

            for (int i = 0; i < list.size(); i++)
            {
                T child_name = get<0>(list[i]);
                Q.push(child_name);
                path.push_back(child_name);
                if(child_name==target) {
                    return path;
                }
            }
        }
    }

    return vector<T>();
}