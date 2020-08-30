import math

class Graph:
    def __init__(self, vertices):
        self.V = vertices
        self.edges = []
    
    def add_edge(self, edge):
        self.edges.append(edge)
        
def bellmanFord(graph, s):
    d = dict.fromkeys(graph.V, math.inf)
    pi = dict.fromkeys(graph.V, None)
    
    d[s] = 0
    
    def relax(u, v, w):
        if d[v] > d[u] + w:
            d[v] = d[u] + w
            pi[v] = u
    
    for i in graph.V[:-1]:
        for u, v, w in graph.edges:
            relax(u, v, w)
            
    for u, v, w in graph.edges:
        if d[v] > d[u] + w:
            raise ValueError
                
    return d, pi

if __name__ == '__main__':
    n, m = map(int, input().split())
    v = [i+1 for i in range(n)]
    g = Graph(v)
    edges = []
    for i in range(m):
        edge = tuple(map(int, input().split()))
        g.add_edge(edge)

    fail_flag = False
    try:
        d, pi = bellmanFord(g, v[0])
    except ValueError:
        print("bug")
        fail_flag = True

    if not fail_flag:
        print(d[v[-1]])
