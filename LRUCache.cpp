//
// Created by shawn on 23-11-1.
//
#include <unordered_map>

using namespace std;

struct DLinkedNode {
    int key, value;
    DLinkedNode *next;
    DLinkedNode *prev;
    DLinkedNode(int key = 0, int value = 0) : key(key), value(value), next(nullptr), prev(nullptr) {}
};

class LRUCache {
private:
    int capacity;
    int size;
    DLinkedNode *head;
    DLinkedNode *tail;
    unordered_map<int, DLinkedNode *> cache;

public:
    LRUCache(int capacity) : capacity(capacity), size(0) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        DLinkedNode *node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            DLinkedNode *node = new DLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            size++;
            if (size > capacity) {
                DLinkedNode *removed = removeTail();
                cache.erase(removed->key);
                delete (removed);
                size--;
            }
        } else {
            DLinkedNode *node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode *node) {
        node->next = head->next;
        node->prev = head;
        // bug不能先head->next=node,会导致head->next->prev找不到节点
        head->next->prev = node;
        head->next = node;
    }

    void moveToHead(DLinkedNode *node) {
        removeNode(node);
        addToHead(node);
    }

    void removeNode(DLinkedNode *node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    DLinkedNode *removeTail() {
        DLinkedNode *node = tail->prev;
        removeNode(node);
        return node;
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
int main() {
    int capacity=2,key=1,value=1;
    LRUCache *obj = new LRUCache(capacity);
    int param_1 = obj->get(key);
    obj->put(key, value);
}