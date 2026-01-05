//
// Created by Emin Tunc Kirimlioglu on 1/2/25.
//

#include <iostream>
#include "MemoryTracker.hpp"
#include "Testing.hpp"
#include "Sequence.hpp"
#include <cstdlib>
#include <ctime>
#include <string>

MemoryTracker MemoryTracker::instance;

struct GradeTracker {
    bool basicTestsPassed = false;    // 30 points
    bool stressTestsPassed = false;   // 40 points
    bool edgeCasesPassed = false;     // 10 points
    bool memoryTestsPassed = false;   // 10 points
    // Note: Remaining 10 points come from questions.md

    int calculateGrade() const {
        int grade = 0;
        if (basicTestsPassed) grade += 30;
        if (stressTestsPassed) grade += 40;
        if (edgeCasesPassed) grade += 10;
        if (memoryTestsPassed) grade += 10;
        return grade;
    }

    void printGrade() const {
        int grade = calculateGrade();
        std::cout << "\n----------------------------------------" << std::endl;
        std::cout << "Grade Breakdown:" << std::endl;
        std::cout << "Basic Tests (30%): " << (basicTestsPassed ? "PASSED" : "FAILED") << std::endl;
        std::cout << "Stress Tests (40%): " << (stressTestsPassed ? "PASSED" : "FAILED") << std::endl;
        std::cout << "Edge Cases (10%): " << (edgeCasesPassed ? "PASSED" : "FAILED") << std::endl;
        std::cout << "Memory Management (10%): " << (memoryTestsPassed ? "PASSED" : "FAILED") << std::endl;
        std::cout << "Implementation Grade: " << grade << "/90" << std::endl;
        std::cout << "NOTE: Remaining 10 points come from answering questions.md" << std::endl;
        std::cout << "----------------------------------------\n" << std::endl;
    }
};

int testSequence(GradeTracker& grade) {
    std::cout << "\nTesting ContiguousSequence..." << std::endl;

    // Basic tests
    {
        ContiguousSequence<int> sequence;
        if (int result = SequenceTester::doBasicTests(sequence)) {
            return result;
        }
        NonContiguousSequence<int> nonContiguousSequence;
        if (int result = SequenceTester::doBasicTests(nonContiguousSequence)) {
            return result;
        }
    }
    grade.basicTestsPassed = true;

    // Stress tests
    {
        ContiguousSequence<int> sequence;
        if (int result = SequenceTester::doStressTest(sequence)) {
            return result;
        }
        NonContiguousSequence<int> non_contiguous_sequence;
        if (int result = SequenceTester::doStressTest(non_contiguous_sequence)) {
            return result;
        }
    }
    grade.stressTestsPassed = true;

    // Edge case tests
    {
        ContiguousSequence<int> sequence;
        if (int result = SequenceTester::doEdgeCaseTests(sequence)) {
            return result;
        }
        NonContiguousSequence<int> non_contiguous_sequence;
        if (int result = SequenceTester::doEdgeCaseTests(non_contiguous_sequence)) {
            return result;
        }
    }
    grade.edgeCasesPassed = true;

    std::cout << "All ContiguousSequence tests passed!" << std::endl;
    return kNoErrorsDetected;
}


int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    MemoryTracker::getInstance().turnOn();

    GradeTracker grade;

    try {
        if (int result = testSequence(grade)) {
            std::cout << "ArraySequence tests failed with code: " << result << std::endl;
            grade.printGrade();
            return result;
        }

        std::cout << "\nAll tests passed successfully!" << std::endl;

        MemoryTracker::getInstance().printLeakReport().turnOff();
        grade.memoryTestsPassed = MemoryTracker::getInstance().good();

        grade.printGrade();
        return grade.memoryTestsPassed ? 0 : 1;
    }
    catch (const std::exception& e) {
        std::cout << "Unexpected exception: " << e.what() << std::endl;
        grade.printGrade();
        return -1;
    }
    catch (...) {
        std::cout << "Unknown exception occurred" << std::endl;
        grade.printGrade();
        return -1;
    }
}