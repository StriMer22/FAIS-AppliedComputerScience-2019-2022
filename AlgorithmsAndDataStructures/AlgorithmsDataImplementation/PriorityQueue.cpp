//
// Created by Dmytro on 22.03.2021
//

#include <vector>
#include <iostream>

class PriorityQueue {
public:
    PriorityQueue() {}

    PriorityQueue(unsigned max_size) {
        heap.resize(max_size);
    }

    unsigned size() const {
        return heap.size();
    }

    void insert(int value) {
        heap.push_back(value);
        unsigned node_idx = heap.size() - 1;
        while (node_idx > 0) {
            unsigned parent_idx = (node_idx - 1) / 2;
            if (heap[node_idx] < heap[parent_idx]) {
                swap_nodes(node_idx, parent_idx);
                node_idx = parent_idx;
            } else {
                break;
            }
        }
    }

    int get_minimum() const {
        return heap[0];
    }

    int pop() {
        int result = heap[0];
        if (heap.size() == 1) {
            heap.pop_back();
            return result;
        }
        heap[0] = heap.back();
        heap.pop_back();
        unsigned node_idx = 0;
        while (2 * node_idx + 1 < heap.size()) {
            int min_child_idx = 2 * node_idx + 1;
            int min_child_value = heap[min_child_idx];
            if (min_child_idx + 1 < heap.size() && heap[min_child_idx + 1] < min_child_value) {
                min_child_idx++;
                min_child_value = heap[min_child_idx];
            }
            if (min_child_value < heap[node_idx]) {
                swap_nodes(min_child_idx, node_idx);
                node_idx = min_child_idx;
            } else {
                break;
            }
        }
        return result;
    }

    void printQueue() {
        for (int i : heap) {
            std::cout << i << ' ';
        }
        std::cout << "\n";
    }

private:
    std::vector<int> heap;

    void swap_nodes(int idx1, int idx2) {
        int tmp = heap[idx1];
        heap[idx1] = heap[idx2];
        heap[idx2] = tmp;
    }
};

//int main() {
//    PriorityQueue priorityQueue;
//    priorityQueue.insert(10);
//    priorityQueue.insert(103);
//    priorityQueue.insert(4);
//    priorityQueue.insert(120);
//    priorityQueue.pop();
//    priorityQueue.insert(12);
//    priorityQueue.insert(8);
//    priorityQueue.insert(98);
//    priorityQueue.pop();
//    priorityQueue.insert(53);
//    priorityQueue.printQueue();
//}
