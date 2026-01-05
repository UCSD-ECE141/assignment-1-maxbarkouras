[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/gnIogORD)
[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/Bmy_rCX3)
# WI25-Assignment1
## Data Structures: Sequence<T> Implementation
**Due Date: January 12th, 2026, 11:30 PM PST**

## Overview
In this assignment, you will implement two different custom data structures that conform to the `Sequence` interface:
1. `ContiguousSequence<T>`: A sequence backed by a dynamic array
2. `NonContiguousSequence<T>`: A sequence backed by a singly-linked list

These are custom classes you write yourself, You may not use STL or other pre-existing solutions.

Think carefully about these classes. Why is there a hierarchy?  Why templates?  What are the implications in terms of testing, and code reuse?  

## Requirements
### Sequence<T> Interface
Both implementations must implement the following pure virtual functions:
- `add(T anElement)`: Adds an element to the end of the sequence
- `remove(int aPos=-1)`: Removes the nth element from the sequence (negative indexes from end)
- `T get(int index)`: Returns element at the given index (negative indexes from end)
- `insert(int aPos=, T anElement)`: Inserts an element at the given index
- `size()`: Returns the current number of elements
- `is_empty()`: Returns true if the sequence contains no elements

### ContiguousSequence Implementation
- Must use a resizable array implementation
- Initial capacity should be non-zero
- Should double in size when capacity is reached
- Must implement proper dynamic memory management
- Should handle array resizing efficiently
- Must implement all interface methods with negative index support
Some suggested member variables:
```cpp
private:
    T* data;        // Pointer to dynamic array
    size_t currentSize;    // Current number of elements
    size_t maxCapacity;    // Current array capacity

```

### NonContiguousSequence Implementation
- Suggest you implement a singly-linked list structure
- Should maintain proper node connections
- Must implement proper memory management (no leaks)
- Must have zero compiler warnings
- Must implement all interface methods with negative index support
Some suggested structure and member variables:
```cpp
private:
    struct Node {
        T data;
        Node* next;
        // TODO: Implement constructor
    };

    Node* head;
    Node* tail;  // Optional but recommended for efficiency
    int count;
```

## Error Handling
Your implementations must handle the following error cases:
- Throwing `std::out_of_range` for invalid index access
- Throwing `std::runtime_error` when removing from empty sequence
- Properly handling negative indices that are out of bounds

## Grading
A comprehensive test suite is provided in `Testing.hpp` that checks:
- Basic functionality tests (with zero warnings) 30%
- Stress tests with many operations 30%
- Edge case handling 20%
- Memory leak detection 10%

## Grading Criteria
- Basic tests (30%)
- Stress tests (40%)
- Edge case handling (10%)
- Memory management (10%)
- Answers to the questions in questions.md (10%)

## Implementation Tips
1. **ContiguousSequence**:
   - Think carefully about resizing strategy
   - Consider efficiency of insert/remove operations
   - Remember to free memory in destructor
   - Handle negative indices carefully

2. **NonContiguousSequence**:
   - Consider using a tail pointer for efficient append operations
   - Be careful with pointer management
   - Handle single element/empty list cases
   - Consider efficiency of accessing elements with negative indices

3. **General**:
   - Test with different template types (int, double, string)
   - Pay attention to memory management
   - Consider edge cases in your implementation
   - Test thoroughly with both positive and negative indices

## Submission
- Submit your implementation in `Sequence.hpp`
- Ensure all tests pass
- Make sure there are no memory leaks
- Code should be well-commented and properly formatted

