from typing import TypeVar, Generic, Callable
from dataclasses import dataclass
from math import floor

# Priority Queue를 사용하여 문제 해결.
# Heap으로 구현함.
#######################################################################
T = TypeVar("T")


# Heap
class Heap(Generic[T]):
    def __init__(self, compare: Callable[[T, T], bool]):
        self.count: int = 0
        self.compare = compare
        self.heapArr: list[T] = []

    def insert(self, node):
        self.heapArr.append(node)
        self.reheap_up(self.count)
        self.count += 1

    def reheap_up(self, index):
        if index == 0:
            return

        parent_index = floor((index - 1) / 2)
        if self.compare(self.heapArr[index], self.heapArr[parent_index]) == False:
            return
        else:
            self.swap(self.heapArr, parent_index, index)
            self.reheap_up(parent_index)

    def remove(self):
        if self.count == 1:
            output = self.heapArr.pop()
            self.count -= 1
            return output

        output = self.heapArr[0]
        self.heapArr[0] = self.heapArr.pop()
        self.count -= 1
        self.reheap_down(0)
        return output

    def reheap_down(self, index):
        #     n
        # 2n+1 2n+2
        left_index = 2 * index + 1
        right_index = 2 * index + 2

        if left_index >= self.count:
            return

        if right_index >= self.count:
            if self.compare(self.heapArr[index], self.heapArr[left_index]) == False:
                self.swap(self.heapArr, index, left_index)
            return

        if self.compare(self.heapArr[left_index], self.heapArr[right_index]) == True:
            larger_index = left_index
        else:
            larger_index = right_index

        if self.compare(self.heapArr[index], self.heapArr[larger_index]) == True:
            return
        else:
            self.swap(self.heapArr, index, larger_index)
            self.reheap_down(larger_index)

    def print_tree(self, root_index, depth=0):
        if 2 * root_index + 1 < self.count:
            self.print_tree(2 * root_index + 1, depth + 1)
        print(f"{"\t"*depth}{self.heapArr[root_index]}")
        if 2 * root_index + 2 < self.count:
            self.print_tree(2 * root_index + 2, depth + 1)

    @staticmethod
    def swap(array: list, i: int, j: int):
        temp = array[i]
        array[i] = array[j]
        array[j] = temp


#######################################################################
# client data class
@dataclass(frozen=True)
class ClientInfo:
    name: str
    skypass: bool
    order: int

    @property
    def client_key(self) -> tuple[int, int]:
        return (0 if self.skypass else 1, self.order)

    def __repr__(self):
        prefix = ""
        if self.skypass == True:
            prefix = "[SP]"
        return f"{self.order+1}: {prefix}{self.name}"


# a가 b보다 우선순위가 앞이면 True 반환
def compare_clients(a: ClientInfo, b: ClientInfo) -> bool:
    return a.client_key < b.client_key


#######################################################################
if __name__ == "__main__":
    # create priority queue
    P_Queue = Heap[ClientInfo](compare_clients)

    # insert nodes into the priority queue
    for client in input().split():
        if client[:4] == "[SP]":
            skypass = True
            name = client[4:]
        else:
            skypass = False
            name = client

        new_node = ClientInfo(name, skypass, P_Queue.count)
        P_Queue.insert(new_node)

    # print the generated priority queue
    print()
    print("Heap Array:")
    print(P_Queue.heapArr)
    print()
    print("Heap Tree:")
    P_Queue.print_tree(0)
    print()

    # search the target in the priority queue
    target = input()
    count = 0
    while True:
        count += 1
        output = P_Queue.remove()
        if target == output.name:
            break
    print(count)
