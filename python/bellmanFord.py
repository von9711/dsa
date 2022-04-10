import math
import sys
sys.stdin = open('input')


def bellmanFord(graph, nodes, s):
    path = [math.inf]*nodes
    path[s] = 0
    for i in range(nodes-1):
        for u in range(nodes):
            for e in graph[u]:
                path[e[0]] = min(path[e[0]], path[u] + e[1])
    return path


def showGraph(graph):
    for e in graph:
        print(e)


nodes = int(input())
edges = int(input())

graph = [[] for i in range(nodes)]

for i in range(edges):
    e = [int(x) for x in input().split()]
    graph[e[0]].append((e[1], e[2]))
    graph[e[1]].append((e[0], e[2]))
showGraph(graph)

s = 0
print(bellmanFord(graph, nodes, s))
