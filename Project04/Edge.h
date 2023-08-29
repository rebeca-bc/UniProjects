#pragma once

template <typename T>
struct Edge
{
    T source;
    T target;
    int weight;
    Edge();
    Edge(T s, T tar, int w);
};

template <typename T>
Edge<T>::Edge()
{
    source = "NULL";
    target = "NULL";
    weight = 0;
}

template <typename T>
Edge<T>::Edge(T s, T tar, int w)
{
    source = s;
    target = tar;
    weight = w;
}