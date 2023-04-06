N = int(input())

class Edge:
    def __init__(self, n, c):
        self.n = n
        self.c = c

adj = []
for i in range(N):
    a, v = map(int, input().split())
    a -= 1
    adj.append(Edge(a, v))

vis = [False for _ in range(N)]
active = [False for _ in range(N)]
answer = sum(e.c for e in adj)

curr_nodes = []
curr_costs = []
for i in range(N):
    if not vis[i]:
        n = i
        while True:
            vis[n] = True
            active[n] = True
            curr_nodes.append(n)
            curr_costs.append(adj[n].c)
            if active[adj[n].n]:
                # Find length of cycle, and subtract smallest edge cost
                loc = curr_nodes.index(adj[n].n)
                answer -= min(curr_costs[loc:])
            if vis[adj[n].n]:
                break
            n = adj[n].n
        for n in curr_nodes:
            active[n] = False
        curr_nodes.clear()
        curr_costs.clear()

print(answer)
