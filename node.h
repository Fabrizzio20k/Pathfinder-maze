#pragma once
struct Node
{
    // Node of a maze to use with a star algorithm and dijkstra algorithm

    int x, y;       // Coordinates of the node
    double g, h;       // g = distance from start, h = distance from end
    Node *parent;   // Parent node
    bool isBlocked; // Is the node blocked or not
    bool isStart;   // Is the node the start node
    bool isEnd;     // Is the node the end node
    bool isVisited; // Is the node visited or not
    int weight;     // Weight of the node
    int fScore;     // fScore = g + h

    Node() = default;

    Node(int x, int y)
    {
        this->x = x;
        this->y = y;
        this->isBlocked = false;
        g = 0;
        h = 0;
        parent = nullptr;
        isStart = false;
        isEnd = false;
        isVisited = false;
        weight = 0;
    }

    int getF() const
    {
        return g + h;
    }

    bool operator==(const Node &other) const
    {
        return x == other.x && y == other.y;
    }

    bool operator!=(const Node &other) const
    {
        return !(*this == other);
    }

    bool operator<(const Node &other) const
    {
        return getF() < other.getF();
    }

    bool operator>(const Node &other) const
    {
        return getF() > other.getF();
    }

    bool operator<=(const Node &other) const
    {
        return getF() <= other.getF();
    }

    bool operator>=(const Node &other) const
    {
        return getF() >= other.getF();
    }
};
