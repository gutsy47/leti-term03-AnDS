#ifndef ADS_GRAPH_H
#define ADS_GRAPH_H


#include <regex>
#include <map>
#include <vector>
#include <stack>
#include <queue>


/// Node of the graph. Contains the <name> and map of adjacent <edges>
class Vertex {
    friend class Graph;

private:
    char _name;
    std::map<Vertex*, int> edges;

public:
    explicit Vertex(char);
    void setEdge(Vertex*, int);
    friend std::ostream& operator<< (std::ostream&, const Vertex&);
};


/// Weighted undirected graph. Contains the <amount> and <vertices>
class Graph {
private:
    int amount;                    // Total amount of the vertices
    std::vector<Vertex*> vertices; // Store each vertex

public:
    // Constructors and destructors
    Graph();
    Graph(const std::vector<char>&, const std::vector<std::vector<int>>&);

    // Basic methods
    std::vector<Vertex*> depthFirstSearch();
    std::vector<Vertex*> breadthFirstSearch();
};


#endif //ADS_GRAPH_H
