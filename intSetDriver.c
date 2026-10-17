#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "intSet.c"

// Global tracking variables for the test suite
int tests_run = 0;
int tests_failed = 0;

// Helper macro to assert conditions and track stats
#define TEST_ASSERT(message, condition) do { \
    tests_run++; \
    if (condition) { \
        printf("  [PASS] %s\n", message); \
    } else { \
        printf("  [FAIL] %s (Line %d)\n", message, __LINE__); \
        tests_failed++; \
    } \
} while(0)

// -------------------------------------------------------------
// Test Case 1: Initial Lifecycle State
// -------------------------------------------------------------
void test_initialization_and_lifecycle() {
    printf("\n--- Running Lifecycle & Initialization Tests ---\n");
    intSet s = createSet();
    
    TEST_ASSERT("Set should not be NULL upon allocation", s != NULL);
    TEST_ASSERT("New set must report isEmpty as true", isEmpty(s) == true);
    TEST_ASSERT("New set cardinality must equal 0", card(s) == 0);
    
    char *str = toString(s);
    TEST_ASSERT("Empty set representation must match '{}'", strcmp(str, "{}") == 0);
    free(str);
    
    destroySet(s);
    printf("  [INFO] Lifecycle validation complete.\n");
}

// -------------------------------------------------------------
// Test Case 2: Insertion, Ordering, and Duplicates
// -------------------------------------------------------------
void test_add_and_ordering() {
    printf("\n--- Running Insertion & Sorting Tests ---\n");
    intSet s = createSet();
    
    // Add items out of order to ensure the set automatically sorts them
    add(s, 42);
    add(s, -10);
    add(s, 5);
    
    TEST_ASSERT("Cardinality should be 3 after three distinct additions", card(s) == 3);
    TEST_ASSERT("isEmpty should return false", isEmpty(s) == false);
    
    // Check ascending sorted structure via toString
    char *str = toString(s);
    TEST_ASSERT("Output string must display elements in ascending order '{-10,5,42}'", 
                strcmp(str, "{-10,5,42}") == 0);
    free(str);
    
    // Attempt duplicate insert (Set property check)
    add(s, 5);
    TEST_ASSERT("Duplicate insertion must not change cardinality", card(s) == 3);
    
    char *str_dup = toString(s);
    TEST_ASSERT("Output string must remain unique '{-10,5,42}'", 
                strcmp(str_dup, "{-10,5,42}") == 0);
    free(str_dup);
    
    destroySet(s);
}

// -------------------------------------------------------------
// Test Case 3: Membership & Extremas
// -------------------------------------------------------------
void test_membership_and_extremas() {
    printf("\n--- Running Membership & Boundary Extrema Tests ---\n");
    intSet s = createSet();
    add(s, 100);
    add(s, -500);
    add(s, 0);
    
    TEST_ASSERT("contains() finds existing active element", contains(s, 0) == true);
    TEST_ASSERT("contains() correctly identifies missing elements", contains(s, 7) == false);
    
    TEST_ASSERT("smallest() returns correct minimum value", smallest(s) == -500);
    TEST_ASSERT("largest() returns correct maximum value", largest(s) == 100);
    
    destroySet(s);
}

// -------------------------------------------------------------
// Test Case 4: Array Conversion Logic
// -------------------------------------------------------------
void test_array_conversion() {
    printf("\n--- Running toArray Conversion Tests ---\n");
    intSet s = createSet();
    add(s, 20);
    add(s, 10);
    
    int size_out = 0;
    // Calling with two arguments as required by your method footprint
    int *arr = toArray(s, &size_out);
    
    TEST_ASSERT("Size variable passed by pointer should be set to 2", size_out == 2);
    TEST_ASSERT("Array element 0 must be the lowest value (10)", arr[0] == 10);
    TEST_ASSERT("Array element 1 must be the highest value (20)", arr[1] == 20);
    
    free(arr);
    destroySet(s);
}

// -------------------------------------------------------------
// Test Case 5: Set Structural Equality
// -------------------------------------------------------------
void test_set_equality() {
    printf("\n--- Running Set Equality Tests ---\n");
    intSet s1 = createSet();
    intSet s2 = createSet();
    
    TEST_ASSERT("Two distinct newly created sets must be equal", equals(s1, s2) == true);
    
    // Add identical items using different insertion sequences
    add(s1, 1); add(s1, 2);
    add(s2, 2); add(s2, 1);
    TEST_ASSERT("Sets with identical elements are equal regardless of entry sequence", equals(s1, s2) == true);
    
    add(s2, 3);
    TEST_ASSERT("Sets with different cardinalities/elements must not be equal", equals(s1, s2) == false);
    
    destroySet(s1);
    destroySet(s2);
}

// -------------------------------------------------------------
// Test Case 6: Element Removal
// -------------------------------------------------------------
void test_removal() {
    printf("\n--- Running Element Removal Tests ---\n");
    intSet s = createSet();
    add(s, 10); add(s, 20); add(s, 30);
    
    remove_(s, 20);
    TEST_ASSERT("Removing an element decreases set size", card(s) == 2);
    TEST_ASSERT("Removed element no longer flagged by contains()", contains(s, 20) == false);
    
    char *str = toString(s);
    TEST_ASSERT("Remaining array elements must preserve ordered alignment", strcmp(str, "{10,30}") == 0);
    free(str);
    
    // Safe failure check
    remove_(s, 999);
    TEST_ASSERT("Removing non-existent element alters nothing", card(s) == 2);
    
    destroySet(s);
}

// -------------------------------------------------------------
// Test Case 7: Algebraic Set Operations (Union, Intersect, Diff)
// -------------------------------------------------------------
void test_set_algebra() {
    printf("\n--- Running Set Algebra Operations Tests ---\n");
    intSet A = createSet();
    intSet B = createSet();
    
    // A = {1, 2, 3}
    add(A, 1); add(A, 2); add(A, 3);
    // B = {3, 4, 5}
    add(B, 3); add(B, 4); add(B, 5);
    
    // Union Operation: A U B = {1, 2, 3, 4, 5}
    intSet u = union_(A, B);
    char *u_str = toString(u);
    TEST_ASSERT("union_ matches reference string '{1,2,3,4,5}'", strcmp(u_str, "{1,2,3,4,5}") == 0);
    free(u_str);
    destroySet(u);
    
    // Intersection Operation: A n B = {3}
    intSet i = intersection(A, B);
    char *i_str = toString(i);
    TEST_ASSERT("intersection matches reference string '{3}'", strcmp(i_str, "{3}") == 0);
    free(i_str);
    destroySet(i);
    
    // Difference Operation: A - B = {1, 2}
    intSet d = diff(A, B);
    char *d_str = toString(d);
    TEST_ASSERT("diff (A - B) matches reference string '{1,2}'", strcmp(d_str, "{1,2}") == 0);
    free(d_str);
    destroySet(d);
    
    destroySet(A);
    destroySet(B);
}

// -------------------------------------------------------------
// Test Case 8: Memory Resetting (Clear)
// -------------------------------------------------------------
void test_clear_function() {
    printf("\n--- Running Clear Operations Tests ---\n");
    intSet s = createSet();
    add(s, 5); add(s, 10);
    
    clear(s);
    TEST_ASSERT("clear() resets tracking size to empty", isEmpty(s) == true);
    TEST_ASSERT("clear() reduces active item counter back to zero", card(s) == 0);
    
    char *str = toString(s);
    TEST_ASSERT("Cleared set converts back to standard empty string", strcmp(str, "{}") == 0);
    free(str);
    
    destroySet(s);
}

// -------------------------------------------------------------
// Test Case 9: Dynamic Resizing Expansion Verification
// -------------------------------------------------------------
void test_dynamic_growth() {
    printf("\n--- Running Dynamic Array Growth Verification ---\n");
    intSet s = createSet();
    
    // Insert 100 values to push beyond any small initial array capacity
    for (int i = 0; i < 100; i++) {
        add(s, i);
    }
    
    TEST_ASSERT("Set successfully grew dynamically to hold 100 items", card(s) == 100);
    TEST_ASSERT("Set safely preserves elements across capacity changes", contains(s, 50) == true);
    
    destroySet(s);
}

// -------------------------------------------------------------
// Executive Entry Point
// -------------------------------------------------------------
int main() {
    printf("====================================================\n");
    printf("      LAUNCHING INTSET MODULAR TEST SUITE          \n");
    printf("====================================================\n");
    
    test_initialization_and_lifecycle();
    test_add_and_ordering();
    test_membership_and_extremas();
    test_array_conversion();
    test_set_equality();
    test_removal();
    test_set_algebra();
    test_clear_function();
    test_dynamic_growth();
    
    printf("\n====================================================\n");
    printf("                  TESTING SUMMARY                   \n");
    printf("====================================================\n");
    printf("Total Assertions Evaluated: %d\n", tests_run);
    printf("Total Assertions Failed:    %d\n", tests_failed);
    
    if (tests_failed == 0) {
        printf("\nRESULT: SUCCESS! All targeted behaviors passed specs.\n");
        return EXIT_SUCCESS;
    } else {
        printf("\nRESULT: FAILURE. Regressions detected inside source logic.\n");
        return EXIT_FAILURE;
    }
}
