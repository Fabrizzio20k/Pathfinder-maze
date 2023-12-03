#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <functional>
#include <ctime>
#include <cstdlib>
#include <limits>
#include <queue>
#include <algorithm>
#include <cmath>
#include <chrono>
#include "node.h"

using namespace std;

class Maze
{
    // Maze class to use with a star algorithm and dijkstra algorithm

    int rows, cols;             // Width and height of the maze
    vector<vector<Node>> nodes; // Nodes of the maze

    pair<int, int> start; // Start node coordinates
    pair<int, int> end;   // End node coordinates

    long long timeAlgorithm; // Time it took to run the algorithm

    double pesoDiagonal = 14;
    double pesoVH = 10;

public:
    Maze() = default;
    Maze(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
        this->timeAlgorithm = 0.0;

        // Initialize nodes
        nodes.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            nodes[i].resize(cols);
            for (int j = 0; j < cols; j++)
            {
                nodes[i][j] = Node(i, j);
            }
        }
    }

    void create(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;

        nodes.clear();

        // Initialize nodes
        nodes.resize(rows);
        for (int i = 0; i < rows; i++)
        {
            nodes[i].resize(cols);
            for (int j = 0; j < cols; j++)
            {
                nodes[i][j] = Node(i, j);
            }
        }

        this->timeAlgorithm = 0.0;
    }

    void setBlocked(int row, int col)
    {
        nodes[row][col].isBlocked = true;
    }

    vector<vector<Node>> getNodes()
    {
        return nodes;
    }

    vector<Node> getObstacles()
    {
        vector<Node> obstacles;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (nodes[i][j].isBlocked && !nodes[i][j].isStart && !nodes[i][j].isEnd)
                {
                    obstacles.push_back(nodes[i][j]);
                }
            }
        }
        return obstacles;
    }

    void copyMaze(Maze &maze)
    {
        this->rows = maze.rows;
        this->cols = maze.cols;
        this->nodes = maze.nodes;
        this->start = maze.start;
        this->end = maze.end;
    }

    void setStart(int row, int col)
    {
        nodes[row][col].isStart = true;
        start = make_pair(row, col);
    }

    void setEnd(int row, int col)
    {
        nodes[row][col].isEnd = true;
        end = make_pair(row, col);
    }

    void print() const
    {
        for (int i = 0; i < rows; i++)
        {
            string line = "";
            for (int j = 0; j < cols; j++)
            {
                if (nodes[i][j].isStart && nodes[i][j].isBlocked == false)
                {
                    line += "S";
                }
                else if (nodes[i][j].isEnd && nodes[i][j].isBlocked == false)
                {
                    line += "E";
                }
                else if (nodes[i][j].isBlocked)
                {
                    line += "#";
                }
                else
                {
                    line += ".";
                }
            }
            cout << line << endl;
        }

        cout << "El inicio es: " << start.first << ", " << start.second << endl;
        cout << "El final es: " << end.first << ", " << end.second << endl;
    }

    void generateRandomMaze(float probability)
    {
        srand(time(nullptr));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; ++j)
            {
                if (rand() % 100 < probability * 100)
                {
                    setBlocked(i, j);
                }
            }
        }
        nodes[start.first][start.second].isBlocked = false;
        nodes[end.first][end.second].isBlocked = false;
    }

    void reset()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; ++j)
            {
                nodes[i][j].g = 0;
                nodes[i][j].h = 0;
                nodes[i][j].parent = nullptr;
                nodes[i][j].isVisited = false;
            }
        }
    }

    vector<Node *> reconstructPath()
    {
        vector<Node *> path;
        Node *current = &nodes[end.first][end.second];
        while (current != nullptr)
        {
            path.push_back(current);
            current = current->parent;
        }
        reverse(path.begin(), path.end());
        return path;
    }

    void dijkstra()
    {
        reset();

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                nodes[i][j].g = numeric_limits<int>::max();
            }
        }

        nodes[start.first][start.second].g = 0;

        auto compare = [](Node *a, Node *b)
        { return a->g > b->g; };

        priority_queue<Node *, vector<Node *>, decltype(compare)> queue(compare);

        queue.push(&nodes[start.first][start.second]);

        while (!queue.empty())
        {
            Node *current = queue.top();
            queue.pop();

            if (current->isVisited)
                continue;
            else{
                current->isVisited = true;
            }

            if (current == &nodes[end.first][end.second])
            {
                return;
            }

            for (int dx = -1; dx <= 1; dx++)
            {
                for (int dy = -1; dy <= 1; dy++)
                {
                    if (dx == 0 && dy == 0)
                        continue;

                    int nx = current->x + dx;
                    int ny = current->y + dy;

                    if (nx < 0 || nx >= rows || ny < 0 || ny >= cols)
                        continue;

                    Node *neighbor = &nodes[nx][ny];

                    if (neighbor->isBlocked || neighbor->isVisited)
                        continue;

                    int newDistance = current->g + ((dx == 0 || dy == 0) ? 10 : 14); // Assign a higher cost to diagonal movements

                    if (newDistance < neighbor->g)
                    {
                        neighbor->g = newDistance;
                        neighbor->parent = current;

                        queue.push(neighbor);
                    }
                }
            }
        }
    }

    void astarEuclidean()
    {
        reset();

        nodes[start.first][start.second].g = 0;
        nodes[start.first][start.second].h = 0;
        nodes[start.first][start.second].isVisited = true;
        nodes[start.first][start.second].parent = nullptr;

        auto compare = [](Node *a, Node *b)
                { return (a->g + a->h) > (b->g + b->h); };
        priority_queue<Node *, vector<Node *>, decltype(compare)> pq(compare);

        pq.push(&nodes[start.first][start.second]);

        while (!pq.empty())
        {
            Node *current = pq.top();
            pq.pop();

            if (current == &nodes[end.first][end.second])
            {
                return;
            }

            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

            for (const auto &direction : directions)
            {
                int new_row = current->x + direction.first;
                int new_col = current->y + direction.second;

                if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
                {
                    Node *neighbor = &nodes[new_row][new_col];
                    if (!neighbor->isBlocked)
                    {
                        double newG = current->g + ((abs(direction.first) == 1 && abs(direction.second) == 1) ? pesoDiagonal/10 : pesoVH/10);
                        if (!neighbor->isVisited || newG < neighbor->g)
                        {
                            neighbor->parent = current;
                            neighbor->g = newG;
                            neighbor->h = sqrt(pow(new_row - end.first, 2) + pow(new_col - end.second, 2)); // Euclidean distance
                            if (!neighbor->isVisited)
                            {
                                neighbor->isVisited = true;
                                pq.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }


    void astarManhattan()
    {
        reset();

        nodes[start.first][start.second].g = 0;
        nodes[start.first][start.second].h = 0;
        nodes[start.first][start.second].isVisited = true;
        nodes[start.first][start.second].parent = nullptr;

        auto compare = [](Node *a, Node *b)
        { return a->g + a->h > b->g + b->h; };
        priority_queue<Node *, vector<Node *>, decltype(compare)> pq(compare);

        pq.push(&nodes[start.first][start.second]);

        while (!pq.empty())
        {
            Node *current = pq.top();
            pq.pop();

            if (current == &nodes[end.first][end.second])
            {
                return;
            }

            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

            for (const auto &direction : directions)
            {
                int new_row = current->x + direction.first;
                int new_col = current->y + direction.second;

                if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
                {
                    Node *neighbor = &nodes[new_row][new_col];
                    if (!neighbor->isBlocked)
                    {
                        int newG = current->g + (abs(direction.first) == 1 && abs(direction.second) == 1 ? pesoDiagonal/10 : pesoVH/10);
                        if (!neighbor->isVisited || newG < neighbor->g)
                        {
                            neighbor->parent = current;
                            neighbor->g = newG;
                            neighbor->h = abs(new_row - end.first) + abs(new_col - end.second); // Manhattan distance
                            if (!neighbor->isVisited)
                            {
                                neighbor->isVisited = true;
                                pq.push(neighbor);
                            }
                        }
                    }
                }
            }
        }
    }

    void greedyBFSManhattan()
    {
        reset();

        nodes[start.first][start.second].h = 0;
        nodes[start.first][start.second].isVisited = true;
        nodes[start.first][start.second].parent = nullptr;

        auto compare = [](Node *a, Node *b)
        { return a->h > b->h; };
        priority_queue<Node *, vector<Node *>, decltype(compare)> pq(compare);

        pq.push(&nodes[start.first][start.second]);

        while (!pq.empty())
        {
            Node *current = pq.top();
            pq.pop();

            if (current == &nodes[end.first][end.second])
            {
                return;
            }

            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

            for (const auto &direction : directions)
            {
                int new_row = current->x + direction.first;
                int new_col = current->y + direction.second;

                if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
                {
                    Node *neighbor = &nodes[new_row][new_col];
                    if (!neighbor->isBlocked && !neighbor->isVisited)
                    {
                        neighbor->parent = current;
                        neighbor->h = abs(new_row - end.first) + abs(new_col - end.second); // Manhattan distance
                        neighbor->isVisited = true;
                        pq.push(neighbor);
                    }
                }
            }
        }
    }

    void greedyBFSEuclidean()
    {
        reset();

        nodes[start.first][start.second].h = 0;
        nodes[start.first][start.second].isVisited = true;
        nodes[start.first][start.second].parent = nullptr;

        auto compare = [](Node *a, Node *b)
        { return a->h > b->h; };
        priority_queue<Node *, vector<Node *>, decltype(compare)> pq(compare);

        pq.push(&nodes[start.first][start.second]);

        while (!pq.empty())
        {
            Node *current = pq.top();
            pq.pop();

            if (current == &nodes[end.first][end.second])
            {
                return;
            }

            vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

            for (const auto &direction : directions)
            {
                int new_row = current->x + direction.first;
                int new_col = current->y + direction.second;

                if (new_row >= 0 && new_row < rows && new_col >= 0 && new_col < cols)
                {
                    Node *neighbor = &nodes[new_row][new_col];
                    if (!neighbor->isBlocked && !neighbor->isVisited)
                    {
                        neighbor->parent = current;
                        neighbor->h = sqrt(pow(new_row - end.first, 2) + pow(new_col - end.second, 2));
                        neighbor->isVisited = true;
                        pq.push(neighbor);
                    }
                }
            }
        }
    }

    vector<Node> getVisitedNodes()
    {
        vector<Node> visited;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (nodes[i][j].isVisited && !nodes[i][j].isStart && !nodes[i][j].isEnd)
                {
                    visited.push_back(nodes[i][j]);
                }
            }
        }
        return visited;
    }

    [[nodiscard]] string getTimeAlgorithm() const
    {
        string timeRunned;
        timeRunned += to_string(this->timeAlgorithm) + " ms";
        return timeRunned;
    }

    ~Maze()
    {
        nodes.clear();
    }
};