# def inorder_traverse(result, tree, tree_size, index):
#     if 2 * index + 1 < tree_size:
#         inorder_traverse(result, tree, tree_size, 2 * index + 1)
#     result.append(tree[index])
#     if 2 * index + 2 < tree_size:
#         inorder_traverse(result, tree, tree_size, 2 * index + 2)


# a = [5, 3, 4, 8, 9, 6, 1]
# result = []
# inorder_traverse(result, a, len(a), 0)
# print(result)

# tree = [5, 3, 4, 8, 9, 6, 1]


# def inorder_traverse_yield(tree, tree_size, index=0):
#     if 2 * index + 1 < tree_size:
#         yield from inorder_traverse_yield(tree, tree_size, 2 * index + 1)
#     yield tree[index]
#     if 2 * index + 2 < tree_size:
#         yield from inorder_traverse_yield(tree, tree_size, 2 * index + 2)


# traverse_result = inorder_traverse_yield(tree, len(tree))

# while True:
#     try:
#         print(next(traverse_result))
#     except:
#         break

import heapq

# tree = [5, 3, 4, 8, 9, 6, 1]
tree = [14, 25, 80, 26, 27]
heap = tree.copy()
heapq.heapify(heap)
isHeap = tree == heap
print(f"isHeap: {isHeap}")

print(tree.popleft())

tree.insert()
