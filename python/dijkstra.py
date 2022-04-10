import math
import sys
sys.stdin = open('input')


def dijkstra(graph, nodes, s):
    dist = [math.inf]*nodes
    


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
print(dijkstra(graph, nodes, s))
