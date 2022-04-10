from queue import Queue


class Graph:
    def __init__(self, nodes, edges):
        self.nodes = nodes
        self.edges = edges
        self.arr = [[] for i in range(self.nodes)]

    def insert(self):
        for i in range(self.edges):
            n1 = int(input())
            n2 = int(input())
            self.arr[n1].append(n2)
            self.arr[n2].append(n1)

    def display(self):
        for i in range(self.nodes):
            print(i, ' : ', self.arr[i])

    def dfs(self, s, visited):
        visited[s] = True
        print('start: ', s)
        for u in self.arr[s]:
            if visited[u] is False:
                self.dfs(u, visited)
        print('return: ', s)

    def bfs(self, s):
        que = Queue()
        visited = [False] * self.nodes
        dist = [0] * self.nodes
        que.put_nowait(s)
        while que.empty() is False:
            u = que.get_nowait()
            if visited[u] is True:
                continue
            visited[u] = True
            for v in self.arr[u]:
                if visited[v] is False:
                    dist[v] = dist[u] + 1
                    que.put_nowait(v)
        return dist

    def isConnected(self):
        visited = [False] * self.nodes
        self.dfs(0, visited)
        for node in visited:
            if node is False:
                return False
        return True

nodes = 6
edges = 6
graph = Graph(nodes, edges)
#visited = [False] * nodes
s = 0
graph.insert()
graph.display()
#print('\nGraph traversal:')
#graph.dfs(s, visited)
#dist = graph.bfs(s)
print(graph.isConnected())
