#include "graph.h"


/// Vertex constructor
Vertex::Vertex(char name) {
    if (!std::regex_match(std::string(1, name), std::regex("[a-zA-Z]")))
        throw std::invalid_argument("Invalid vertex name");
    _name = name;
}


/// Connect this to the <vertex> and set the edge <weight>
void Vertex::setEdge(Vertex *vertex, int weight) {
    edges[vertex] = weight;
}


/// Print the vertex`s name
std::ostream& operator<< (std::ostream& os, const Vertex& vertex) {
    if (vertex._name) os << vertex._name;
    return os;
}


/// Edge constructor
Edge::Edge(int weight, Vertex *first, Vertex *second) {
    this->weight = weight;
    u = first;
    v = second;
}


/// Access to the weight
int Edge::getWeight() const {
    return weight;
}


/// Access to the first vertex
Vertex* Edge::getU() {
    return u;
}


/// Access to the second vertex
Vertex* Edge::getV() {
    return v;
}


/// Print the edge
std::ostream& operator<< (std::ostream& os, Edge& edge) {
    os << *(edge.getU()) << " <-" << edge.getWeight() << "-> " << *(edge.getV());
    return os;
}

/// Compare the weight of two edges, used for sorting
bool Edge::operator< (const Edge& other) const{
    return weight < other.getWeight();
}


/// Default constructor for empty graph
Graph::Graph() {
    vertices = {};
}


/// Graph constructor from adjacency matrix
Graph::Graph(const std::vector<char> &names, const std::vector<std::vector<int>> &weights) {
    // Create all vertices
    for (auto &name : names)
        vertices.push_back(new Vertex(name));

    // Add edges between the vertices
    for (int i = 0; i < vertices.size(); ++i)
        for (int j = 0; j < vertices.size(); ++j)
            if (i != j && weights[i][j] != 0)
                vertices[i]->setEdge(vertices[j], weights[i][j]);
}


/// Return a vector of vertices in DFS order
std::vector<Vertex*> Graph::depthFirstSearch() {
    if (vertices.empty()) return {};

    std::vector<Vertex*> result;
    std::map<Vertex*, bool> visited;
    std::stack<Vertex*> stack;

    stack.push(vertices[0]);
    visited[vertices[0]] = true;
    while (!stack.empty()) {
        // Move front vertex from stack to result
        Vertex* top = stack.top();
        stack.pop();
        result.push_back(top);

        // Add unvisited neighbors to stack
        for (auto &edge : top->edges) {
            if (!visited[edge.first]) {
                stack.push(edge.first);
                visited[edge.first] = true;
            }
        }
    }

    return result;
}


/// Return a vector of vertices in BFS order
std::vector<Vertex*> Graph::breadthFirstSearch() {
    if (vertices.empty()) return {};

    std::vector<Vertex*> result;
    std::map<Vertex*, bool> visited;
    std::queue<Vertex*> queue;

    queue.push(vertices[0]);
    visited[vertices[0]] = true;
    while (!queue.empty()) {
        // Move from queue to result
        Vertex* front = queue.front();
        queue.pop();
        result.push_back(front);

        // Add unvisited neighbors to queue
        for (auto &edge : front->edges) {
            if (!visited[edge.first]) {
                queue.push(edge.first);
                visited[edge.first] = true;
            }
        }
    }

    return result;
}


/// Sort the vertices by their weight
std::vector<Edge> Graph::getSortedByWeight() {
    if (vertices.empty()) return {};

    std::vector<Edge> result;
    for (auto *vertex : vertices)
        for (auto &edge : vertex->edges)
            if (vertex < edge.first) result.emplace_back(edge.second, vertex, edge.first);

    std::sort(result.begin(), result.end());
    return result;
}