from itertools import product

a = range(2)  # 0 1
b = range(3)  # 0 1 2
for x, y in product(a, b):
    print(x, y)


from time import time
from datetime import timedelta
from itertools import product
import heapq

# 최소 신장 트리 (Minimum Spanning Tree, MST)
# 가중 그래프에서 최소 비용(가중치 합)으로 모든 정점을 잇는 트리


def print_result(callback):
    def wrapper(*args):
        print()
        start = time()
        result = callback(*args)
        end = time()
        print(result)
        print(f"소요 시간: {timedelta(seconds=(end - start))}")
        print()

    return wrapper


class PrintResult:
    def __init__(self, f):
        self.callback = f

    def __call__(self, *args):
        print()
        start = time()
        result = self.callback(*args)
        end = time()
        print(result)
        print(f"소요 시간: {timedelta(seconds=(end - start))}")
        print()


AdjMatrix = list[list[int]]
G: AdjMatrix = [
    [0, 30, 28, 17, 0],
    [30, 0, 0, 42, 0],
    [28, 0, 0, 22, 15],
    [17, 42, 22, 0, 19],
    [0, 0, 15, 19, 0],
]

V = ["보람동", "해밀동", "아람동", "고운동", "도담동"]


# Prim's Algorithm -> O(v^3)
@print_result
def Prim(graph: AdjMatrix, vertices: list[str], start_index: int):
    edges = []
    visited = []

    visited.append(start_index)
    print(f"[{vertices[start_index]}]에서 시작")

    while len(edges) < len(vertices) - 1:
        min = (start_index, start_index, float("inf"))
        for each_visited_vertex, new_vertex in product(visited, range(len(vertices))):
            if new_vertex not in visited:
                if 0 < graph[each_visited_vertex][new_vertex] < min[2]:
                    min = (
                        each_visited_vertex,
                        new_vertex,
                        graph[each_visited_vertex][new_vertex],
                    )
        visited.append(min[1])
        print(f"[{vertices[min[1]]}]을 연결함")
        new_edge = (vertices[min[0]], vertices[min[1]], min[2])
        edges.append(new_edge)

    total_weight = sum(edge[2] for edge in edges)
    print(f"가중치 총합: {total_weight}")

    return edges


# Prim's Algorithm with Priority Queue
@PrintResult
def Prim_PQ(graph: AdjMatrix, vertices: list[str], start_index: int):
    edges = []
    visited = []
    pq = []

    visited.append(start_index)
    heapq.heappush(pq, (0, start_index, start_index))
    # for new, new_weight in enumerate(graph[start_index]):
    #     heapq.heappush(pq, (new_weight, start_index, new))

    while len(edges) < len(vertices):
        cur_weight, prev, cur = heapq.heappop(pq)
        # if (cur_weight > 0) and (cur not in visited):
        edges.append((vertices[prev], vertices[cur], cur_weight))
        visited.append(cur)
        print(f"[{vertices[cur]}]을 연결함")

        for new, new_weight in enumerate(graph[cur]):
            if (new not in visited) and (new_weight != 0):
                heapq.heappush(pq, (new_weight, cur, new))

    del edges[0]
    total_weight = sum(edge[-1] for edge in edges)
    print(f"가중치 총합: {total_weight}")

    return edges


# Kruskal Algorithm


if __name__ == "__main__":
    Prim(G, V, 0)
    Prim_PQ(G, V, 0)
