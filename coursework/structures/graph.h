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


/// Edge between two vertices. Represented as <first> - <weight> - <second>
class Edge {
    friend class Graph;

private:
    int weight;
    Vertex *u;
    Vertex *v;

public:
    Edge(int, Vertex*, Vertex*);
    [[nodiscard]] int getWeight() const;
    Vertex * getU();
    Vertex * getV();
    friend std::ostream& operator<< (std::ostream&, Edge&);
    bool operator< (const Edge&) const;
};


/// Weighted undirected graph. Contains the <amount> and <vertices>
class Graph {
private:
    std::vector<Vertex*> vertices; // Store each vertex

public:
    // Constructors and destructors
    Graph();
    Graph(const std::vector<char>&, const std::vector<std::vector<int>>&);

    // Basic methods
    std::vector<Vertex*> depthFirstSearch();
    std::vector<Vertex*> breadthFirstSearch();
    std::vector<Edge> getSortedByWeight();
};


#endif //ADS_GRAPH_H
