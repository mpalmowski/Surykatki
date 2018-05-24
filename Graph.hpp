#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <list>

class Graph
{
public:
    int lines = 0, columns = 0;
    int **data = nullptr;

    Graph() = default;

    Graph(int lines, int columns) : lines(lines), columns(columns)
    {
        data = new int *[lines];
        for (int i = 0; i < lines; ++i)
        {
            data[i] = new int[columns];
            for (int j = 0; j < columns; ++j)
                data[i][j] = 0;
        }

        paths = new int *[columns];
        for (int i = 0; i < columns; ++i)
        {
            paths[i] = new int[columns];
            for (int j = 0; j < columns; ++j)
                paths[i][j] = 0;
        }

        visited = new bool[columns];
    }

    ~Graph()
    {
        for (int i = 0; i < lines; ++i)
        {
            delete[] data[i];
        }
        delete data;

        for (int i = 0; i < columns; ++i)
        {
            delete[] paths[i];
        }
        delete paths;

        delete visited;
    }

    int &node(int i, int j)
    {
        return data[i][j];
    }

    void BreadthFirstSearch(int start_node)
    {
        for (int i = 0; i < columns; ++i)
            visited[i] = false;

        std::list<int> q;
        visited[start_node] = true;
        q.push_back(start_node);

        int current;
        while (!q.empty())
        {
            current = q.front();
            q.pop_front();
            for (int i = 0; i < columns; ++i)
            {
                if (!visited[i] && data[current][i] != 0)
                {
                    visited[i] = true;
                    q.push_back(i);
                    updatePaths(start_node, i, paths[start_node][current] + paths[current][i]);
                }
            }
        }
    }

    void updatePaths()
    {
        for(int i = 0; i < columns; ++i)
            for(int j = 0; j < columns; ++j)
                if(paths[i][j] == 0 && data[i][j] != 0)
                    paths[i][j] = data[i][j];
    }

    int getDistance(int node1, int node2)
    {
        return paths[node1][node2];
    }

private:
    bool *visited = nullptr;
    int **paths = nullptr;

    void updatePaths(int node1, int node2, int distance)
    {
        int min_distance = distance;

        if (paths[node1][node2] > 0 && paths[node1][node2] < min_distance)
            min_distance = paths[node1][node2];

        paths[node1][node2] = min_distance;
    }
};

#endif //GRAPH_HPP
