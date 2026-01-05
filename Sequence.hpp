//
// Created by Emin Tunc Kirimlioglu on 1/2/25.
//

#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <stdexcept>
#include <cassert>

template<typename T>
class Sequence {
public:
    virtual ~Sequence() = default;
    virtual void add(T value) = 0;
    virtual void remove(int position = -1) = 0;
    virtual T get(int index) = 0;
    virtual void insert(int index, T value) = 0;
    virtual size_t size() = 0;
    virtual bool is_empty() = 0;

protected:
    // Helper function to convert Python-style negative indices
    // Returns normalized positive index or throws if invalid
    int normalize_index(int index, int size, bool allow_end = false) {
        // TODO: Implement this helper
        // Remember: -1 means last element, -2 means second to last, etc.
        return 0; // placeholder
    }
};

template<typename T>
class ContiguousSequence : public Sequence<T> {
private:
    T* data;
    size_t currentSize;
    size_t maxCapacity;

    void resize() {
        // TODO: Implement resizing logic
        // Remember to:
        // 1. Double the capacity
        // 2. Allocate new array
        // 3. Copy old elements
        // 4. Delete old array
        // 5. Update member variables
    }

public:
    ContiguousSequence() {
        // TODO: Initialize with capacity of 4
    }

    ~ContiguousSequence() override {
        // TODO: Clean up dynamically allocated memory
    }

    void add(T value) override {
        // TODO: Add value to end of sequence
        // Remember to resize if needed
    }

    void remove(int position = -1) override {
        // TODO: Remove element at normalized position
        // Default -1 means remove last element
        // Remember to:
        // 1. Check for empty sequence
        // 2. Normalize the position
        // 3. Shift elements as needed
    }

    T get(int index) override {
        // TODO: Return element at normalized index
        // Remember to check for empty sequence
        throw std::runtime_error("Not implemented");
    }

    void insert(int index, T value) override {
        // TODO: Insert value at normalized index
        // Remember to:
        // 1. Normalize index
        // 2. Resize if needed
        // 3. Shift elements to make room
        // 4. Insert new element
    }

    size_t size() override {
        return currentSize;
    }

    bool is_empty() override {
        return currentSize == 0;
    }
};

template<typename T>
class NonContiguousSequence : public Sequence<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node(T value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    NonContiguousSequence() : head(nullptr), tail(nullptr), count(0) {}

    ~NonContiguousSequence() override {
        // TODO: Clean up all nodes
    }

    void add(T value) override {
        // TODO: Add new node to end of sequence
        // Remember to handle empty sequence case
    }

    void remove(int position = -1) override {
        // TODO: Remove node at normalized position
        // Default -1 means remove last node
        // Remember to:
        // 1. Check for empty sequence
        // 2. Normalize position
        // 3. Handle head/tail updates
        // 4. Update count
    }

    T get(int index) override {
        // TODO: Return value at normalized index
        // Remember to check for empty sequence
        throw std::runtime_error("Not implemented");
    }

    void insert(int index, T value) override {
        // TODO: Insert new node at normalized index
        // Remember to:
        // 1. Normalize index
        // 2. Handle head/tail updates
        // 3. Update count
    }

    size_t size() override {
        return count;
    }

    bool is_empty() override {
        return head == nullptr;
    }
};

#endif //SEQUENCE_HPP