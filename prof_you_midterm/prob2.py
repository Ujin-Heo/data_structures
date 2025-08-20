from prob1 import Heap

# 1. 레벨 순회 결과에서 왼쪽, 오른쪽 subtree를 각각 다른 배열에 저장함.
# 2. 왼쪽 배열을 heapArr로 만들고 remove를 계속 진행해서 오름차순으로 출력되는지 확인.
# 3. 오른쪽 배열을 inorder traversal해서 오름차순으로 출력되는지 확인.


# tree 그리기 함수
def print_tree(tree, tree_size, root_index=0, depth=0):
    if 2 * root_index + 2 < tree_size:
        print_tree(tree, tree_size, 2 * root_index + 2, depth + 1)

    print(f"{"\t"*depth}{tree[root_index]}")

    if 2 * root_index + 1 < tree_size:
        print_tree(tree, tree_size, 2 * root_index + 1, depth + 1)

    if depth == 0:
        print()


def inorder_traverse(tree, tree_size, index=0):
    if 2 * index + 1 < tree_size:
        yield from inorder_traverse(tree, tree_size, 2 * index + 1)
    yield tree[index]
    if 2 * index + 2 < tree_size:
        yield from inorder_traverse(tree, tree_size, 2 * index + 2)


if __name__ == "__main__":
    # left, right subtree를 각각 list에 저장하기
    left_subtree = []
    right_subtree = []
    tree = map(int, input().split())
    _ = next(tree)

    level = 1
    while True:
        try:
            for j in range(0, level):
                left_subtree.append(next(tree))
            for j in range(0, level):
                right_subtree.append(next(tree))
            level *= 2
        except:
            break

    print(f"\nleft: {left_subtree}")
    print_tree(left_subtree, len(left_subtree))

    print(f"right: {right_subtree}\n")
    print_tree(right_subtree, len(right_subtree))

    # left subtree가 heap인지 확인
    heap = Heap[int](lambda a, b: a < b)
    heap.count = len(left_subtree)
    heap.heapArr = left_subtree

    isHeap = True
    prev = heap.remove()
    for i in range(0, len(left_subtree) - 1):
        cur = heap.remove()
        if prev > cur:
            isHeap = False
            break
    print(f"isHeap: {isHeap}")

    # right subtree가 BST인지 확인
    isBST = True
    traverse_result = inorder_traverse(right_subtree, len(right_subtree))
    prev = next(traverse_result)
    for val in traverse_result:
        if prev > val:
            isBST = False
            break
        prev = val
    print(f"isBST: {isBST}\n")

    # 최종 결과 출력
    print("YES" if isHeap and isBST else "NO")
