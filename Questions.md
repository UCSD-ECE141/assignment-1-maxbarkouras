## Questions 10%
1. What are the time complexities of the following operations for the `ArraySequence` implementation? 3pts
    - `add(int number)`
    - `remove()`
    - `get(size_t index)`
    - `insert(size_t index, int number)`
   1. answer 
2. What are the time complexities of the following operations for the `LinkedSequence` implementation? 3pts
    - `add(int number)`
    - `remove()`
    - `get(size_t index)`
    - `insert(size_t index, int number)`
   1. anwer
3. What is the purpose of the `= 0` in the `NumberSequence` interface? 2pts
```cpp
class NumberSequence {
public:
    ...
    virtual void add(int number) = 0; // what is the 0 for?
    virtual void remove() = 0;
    virtual int get(size_t index) = 0;
    virtual void insert(size_t index, int number) = 0;
    virtual int size() = 0;
    virtual bool is_empty() = 0;
};
```
   1. answer
4. What does this line do in the `NumberSequence` interface? 2pts
```cpp
    virtual ~NumberSequence() = default; // why is this here?
```
   1. answer
   
