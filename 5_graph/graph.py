from collections import deque

# 그래프를 파이썬으로 표현하는 방법에는 2가지가 있다.
# 1. 인접 행렬 (Adjoint Matrix)
# 2. 딕셔너리 (Adjoint List)

Node = int | str
AdjList = dict[Node, set[Node]]

G: AdjList = {
    0: {1, 2},
    1: {0, 2, 3},
    2: {0, 1, 4},
    3: {1, 4},
    4: {2, 3, 5},
    5: {4, 6},
    6: {5},
}

G2: AdjList = {
    0: set(),
    1: {0},
    2: {0, 1},
    3: {1},
    4: {2, 3},
    5: {4},
    6: {5},
}


# BFS (Breadth First Search, 너비 우선 탐색)
def BFS(graph: AdjList, start: Node) -> list[Node]:
    visited = []
    queue = deque()

    visited.append(start)
    queue.append(start)
    print(f"{start}번 노드 방문함")

    while len(queue) > 0:
        cur_vertex = queue.popleft()
        for each_vertex in graph[cur_vertex]:
            if each_vertex not in visited:
                visited.append(each_vertex)
                queue.append(each_vertex)
                print(f"{each_vertex}번 노드 방문함")

    return visited


# DFS (Depth First Search, 깊이 우선 탐색)
def DFS(graph: AdjList, start: Node) -> list[Node]:
    visited = []
    _dfs(graph, visited, start)
    return visited


def _dfs(graph: AdjList, visited: list, cur: Node):
    if cur not in visited:
        visited.append(cur)
        print(f"{cur}번 노드 방문함")
        for each_vertex in graph[cur]:
            _dfs(graph, visited, each_vertex)


# Topological Sort (위상 정렬)
def topol_sort(graph: AdjList):
    visited = []
    graph_copy = graph.copy()  # shallow copy
    while len(graph_copy) > 0:
        for node in graph_copy.keys():
            topol_check = False
            for each_adjoint_list in graph_copy.values():
                if node in each_adjoint_list:
                    topol_check = True
                    break
            if not topol_check:  # 진입 차수가 0인 경우
                print(f"{node}번 노드 방문함")
                visited.append(node)
                del graph_copy[
                    node
                ]  # this just detaches graph_copy[i] from graph_copy, not freeing it
                break
    return visited


if __name__ == "__main__":
    print(f"BFS result: {BFS(G, 4)}")
    print(f"DFS result: {DFS(G, 4)}")
    print(f"Topological Sort result: {topol_sort(G2)}")
