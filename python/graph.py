import sys

sys.stdout = open('output', 'w')
sys.stdin = open('input')


'''class Graph:
    #graph using edge listing
    def __init__(self, nodes, edges):
        self.nodes = nodes
        self.edges = edges
        self.mat = [[0 for j in range(2)] for i in range(edges)]

    def insertGraph(self):
        for i in range(self.edges):
            #print('\nEnter edges: ')
            n1 = int(input())
            n2 = int(input())
            self.mat[i][0] = n1
            self.mat[i][1] = n2

    def displayGraph(self):
        print('\nGraph: ')
        for i in range(self.edges):
            print(self.mat[i][0], self.mat[i][1])

    def convert(self):
        arr = [[0 for j in range(self.nodes+1)] for i in range(self.nodes+1)]
        for i in range(self.edges):
            arr[self.mat[i][0]][self.mat[i][1]] = 1
            arr[self.mat[i][1]][self.mat[i][0]] = 1
        return arr'''


class Graph:
    def __init__(self, nodes, edges):
        self.nodes = nodes
        self.edges = edges
        self.arr = [[] for i in range(nodes+1)]

    def insertGraph(self):
        for i in range(self.edges):
            n1 = int(input())
            n2 = int(input())
            self.arr[n1].append(n2)

    def displayGraph(self):
        print('\nGraph: ')
        for i in range(1, self.nodes+1):
            print(i, ': ', end='')
            for n in self.arr[i]:
                print(n, end=' ')
            print()

    def convert(self):
        arr1 = [[0 for i in range(self.nodes+1)] for j in range(self.nodes+1)]
        for i in range(self.nodes+1):
            for val in self.arr[i]:
                arr1[i][val] = 1
        return arr1


nodes = 4
edges = 5
graph = Graph(nodes, edges)
graph.insertGraph()
graph.displayGraph()
arr = graph.convert()
print('\nAdjacency matrix: ')
for i in range(1, nodes+1):
    for j in range(1, nodes+1):
        print(arr[i][j], end=' ')
    print()
