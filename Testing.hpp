//
// Created by Emin Tunc Kirimlioglu on 1/2/25.
//

#ifndef TESTING_HPP
#define TESTING_HPP

#include <iostream>
#include <vector>
#include <string>
#include "Sequence.hpp"

constexpr int kNoErrorsDetected = 0;
constexpr int kAddFailure = 100;
constexpr int kRemoveFailure = 200;
constexpr int kGetFailure = 300;
constexpr int kInsertFailure = 400;
constexpr int kSizeFailure = 500;

template<typename T>
inline bool matchesVector(Sequence<T>& sequence, const std::vector<T>& vec) {
    if (sequence.size() != vec.size()) {
        return false;
    }

    for (size_t i = 0; i < vec.size(); i++) {
        if (sequence.get(i) != vec[i]) {
            return false;
        }
    }
    return true;
}

// Base test functions that work with any Sequence implementation
class SequenceTester {
public:
    template<typename T>
    static int doBasicTests(Sequence<T>& sequence) {
        // Test add and get
        sequence.add(T(100));
        sequence.add(T(200));
        sequence.add(T(300));

        std::vector<T> expected = {T(100), T(200), T(300)};
        if (!matchesVector(sequence, expected)) {
            std::cout << "Basic add/get test failed\n";
            return kAddFailure;
        }

        // Test negative indexing
        if (sequence.get(-1) != T(300) || sequence.get(-2) != T(200)) {
            std::cout << "Negative indexing test failed\n";
            return kGetFailure;
        }

        // Test insert with negative index
        sequence.insert(-2, T(150));  // Insert before second-to-last
        expected = {T(100), T(200), T(150), T(300)};
        if (!matchesVector(sequence, expected)) {
            std::cout << "Insert with negative index test failed\n";
            return kInsertFailure;
        }

        // Test remove with position
        sequence.remove(1);  // Remove second element
        expected = {T(100), T(150), T(300)};
        if (!matchesVector(sequence, expected)) {
            std::cout << "Remove with position test failed\n";
            return kRemoveFailure;
        }

        // Test remove with negative index
        sequence.remove(-1);  // Remove last element
        expected = {T(100), T(150)};
        if (!matchesVector(sequence, expected)) {
            std::cout << "Remove with negative index test failed\n";
            return kRemoveFailure;
        }

        // Test size
        if (sequence.size() != 2) {
            std::cout << "Size test failed\n";
            return kSizeFailure;
        }

        return kNoErrorsDetected;
    }

    template<typename T>
    static int doStressTest(Sequence<T>& sequence) {
        std::vector<T> expected;

        // Test adding many elements
        for (int i = 0; i < 1000; i++) {
            sequence.add(T(i));
            expected.push_back(T(i));
        }

        if (!matchesVector(sequence, expected)) {
            std::cout << "Stress test - adding elements failed\n";
            return kAddFailure;
        }

        // Test random inserts with negative indices
        for (int i = 0; i < 100; i++) {
            int pos = (rand() % (sequence.size() * 2)) - sequence.size(); // Mix of positive and negative
            T value = T(rand() % 1000);
            sequence.insert(pos, value);
            pos = pos < 0 ? sequence.size() + pos : pos; // Convert negative to positive for vector
            expected.insert(expected.begin() + pos, value);

            if (!matchesVector(sequence, expected)) {
                std::cout << "Stress test - random inserts failed\n";
                return kInsertFailure;
            }
        }

        // Test random removes from various positions
        for (int i = 0; i < 100; i++) {
            int pos = (rand() % (sequence.size() * 2)) - sequence.size(); // Mix of positive and negative
            sequence.remove(pos);
            pos = pos < 0 ? sequence.size() + pos + 1: pos; // Convert negative to positive for vector
            expected.erase(expected.begin() + pos);

            if (!matchesVector(sequence, expected)) {
                std::cout << "Stress test - random removes failed\n";
                return kRemoveFailure;
            }
        }

        return kNoErrorsDetected;
    }

    template<typename T>
    static int doEdgeCaseTests(Sequence<T>& sequence) {
        try {
            // Test empty sequence operations
            if (!sequence.is_empty()) {
                std::cout << "Empty check failed\n";
                return kSizeFailure;
            }

            // Test remove from empty
            try {
                sequence.remove();
                std::cout << "Remove from empty should throw\n";
                return kRemoveFailure;
            } catch (...) {
                // Expected
            }

            // Test get with invalid negative index
            try {
                sequence.get(-1);
                std::cout << "Get with invalid negative index should throw\n";
                return kGetFailure;
            } catch (...) {
                // Expected
            }

            // Test insert with out-of-bounds negative index
            try {
                sequence.insert(-2, T(100));
                std::cout << "Insert with invalid negative index should throw\n";
                return kInsertFailure;
            } catch (...) {
                // Expected
            }

            // Test operations with single element
            sequence.add(T(100));

            if (sequence.get(-1) != T(100)) {
                std::cout << "Get last element with negative index failed\n";
                return kGetFailure;
            }

            sequence.remove(-1);
            if (!sequence.is_empty()) {
                std::cout << "Remove with negative index failed\n";
                return kRemoveFailure;
            }

        } catch (const std::exception& e) {

            std::cout << "Unexpected exception in edge case tests\n";
            return -1;
        }

        return kNoErrorsDetected;
    }
};

#endif //TESTING_HPP