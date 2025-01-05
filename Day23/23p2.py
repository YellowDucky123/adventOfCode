from collections import defaultdict

def bronKerbosch(R, P, X, subGraph, cliques):
    if not bool(P) and not bool(X):
        print(R)
        cliques.append(R)
    
    for v in list(P):
        bronKerbosch(R | {v}, P & subGraph[v], X & subGraph[v], subGraph, cliques)
        P = P.difference({v})
        X = X | {v}

graph = defaultdict(set)
with open("input.txt", "r") as file:
    for line in file:
        parts = line.strip().split('-')
        name1, name2 = parts
        graph[name1].add(name2)
        graph[name2].add(name1)


R = set()
P = set()
X = set()
cliques = []
for n in graph:
    P.add(n)
bronKerbosch(R, P, X, graph, cliques)
res = []

for s in cliques:
    if len(res) < len(s):
        res = s

print(','.join(sorted(res)))