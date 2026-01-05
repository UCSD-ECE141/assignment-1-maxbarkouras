//
// Created by Emin Tunc Kirimlioglu on 1/2/25.
//

#ifndef MEMORYTRACKER_HPP
#define MEMORYTRACKER_HPP

#include <iostream>
#include <map>
#include <sstream>
#include <cstdlib>

class MemoryTracker {

    std::map<void*, size_t> allocations;

    size_t totalAllocated = 0;
    size_t currentlyAllocated = 0;
    size_t allocationCount = 0;

    static MemoryTracker instance;

    MemoryTracker() = default;

    bool _internal_allocation = false;
    bool _enabled = true;

public:

    static MemoryTracker& getInstance() {
        return instance;
    }

    MemoryTracker& turnOn() {
        _enabled = true;
        return *this;
    }

    MemoryTracker& turnOff() {
        _enabled = false;
        return *this;
    }

    MemoryTracker& recordAllocation(void* ptr, size_t size) {
        if (_internal_allocation || !_enabled) {
            return *this;
        }
        _internal_allocation = true;
        allocations[ptr] = size;

        totalAllocated += size;
        currentlyAllocated += size;
        allocationCount++;
        _internal_allocation = false;
        return *this;
    }

    MemoryTracker& recordDeallocation(void* ptr) {
        if (_internal_allocation || !_enabled) {
            return *this;
        }
        _internal_allocation = true;
        if (auto it = allocations.find(ptr); it != allocations.end()) {
            currentlyAllocated -= it->second;
            allocations.erase(it);
        } else {
            std::cout << "[Memory] WARNING: Attempting to free unallocated pointer " << ptr << std::endl;
        }
        _internal_allocation = false;
        return *this;
    }

    // Print memory leak report
    MemoryTracker& printLeakReport() {
        if (!_enabled) {
            return *this;
        }
        std::cout << "\n=== Memory Leak Report ===\n";
        std::cout << "Total allocations: " << allocationCount << std::endl;
        std::cout << "Total bytes allocated: " << totalAllocated << std::endl;
        std::cout << "Currently allocated: " << currentlyAllocated << " bytes\n";

        if (!allocations.empty()) {
            std::cout << "\nDetected " << allocations.size() << " memory leaks:\n";
            for (const auto& [ptr, size] : allocations) {
                std::cout << "Leak: " << size << " bytes at " << ptr << "\n";
            }
        } else {
            std::cout << "\nNo memory leaks detected!\n";
        }
        std::cout << "========================\n";
        return *this;
    }

    [[nodiscard]] bool good() const {
        return allocations.empty();
    }
};

inline void* operator new(size_t size) {
    void* ptr = std::malloc(size);
    MemoryTracker::getInstance().recordAllocation(ptr, size);
    return ptr;
}

inline void* operator new[](size_t size) {
    void* ptr = std::malloc(size);
    MemoryTracker::getInstance().recordAllocation(ptr, size);
    return ptr;
}

inline void operator delete(void* ptr) noexcept {
    MemoryTracker::getInstance().recordDeallocation(ptr);
    std::free(ptr);
}

inline void operator delete[](void* ptr) noexcept {
    MemoryTracker::getInstance().recordDeallocation(ptr);
    std::free(ptr);
}

inline void operator delete(void* ptr, size_t) noexcept {
    MemoryTracker::getInstance().recordDeallocation(ptr);
    std::free(ptr);
}

inline void operator delete[](void* ptr, size_t) noexcept {
    MemoryTracker::getInstance().recordDeallocation(ptr);
    std::free(ptr);
}


#endif //MEMORYTRACKER_HPP
