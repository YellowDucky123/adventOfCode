from collections import defaultdict

file = open("input.txt", "r")

graph = defaultdict(set)
nodes = defaultdict(set)
groups = set()

for line in file:
    name1 = line[:2].strip()
    name2 = line[3:].strip()

    graph[name1].add(name2)
    graph[name2].add(name1)
    nodes[name1]


candidates = [c for c in graph if c.startswith('t')]

for t in candidates:
    for a in graph[t]:
        for b in graph[a]:
            if b in graph[t]:
                groups.add(tuple(sorted([t, a, b])))

print("length is ", len(groups))

nodes = sorted(nodes)
string = ""
first = True
for e in nodes:
    if first:
        string += e
        first = False
    else:
        string += ',' + e

print("string is ", string)