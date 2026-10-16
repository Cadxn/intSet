#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>
#include "intSet.c"

// Helper function to print test status
void print_test_result(const char *test_name, bool success) {
    if (success) {
        printf("[PASS] %s\n", test_name);
    } else {
        printf("[FAIL] %s\n", test_name);
    }
}

int main() {
    printf("Starting intSet Comprehensive Tests...\n\n");

    // -------------------------------------------------------------
    // Test 1: Creation and Initial State
    // -------------------------------------------------------------
    intSet s1 = createSet();
    assert(s1 != NULL);
    print_test_result("createSet - set is not NULL", true);
    
    print_test_result("isEmpty - new set is empty", isEmpty(s1) == true);
    print_test_result("card - new set cardinality is 0", card(s1) == 0);
    
    char *s1_str = toString(s1);
    print_test_result("toString - empty set is '{}'", strcmp(s1_str, "{}") == 0);
    free(s1_str);

    // -------------------------------------------------------------
    // Test 2: Adding items and Set properties (Ascending Order verification)
    // -------------------------------------------------------------
    add(s1, 9);
    add(s1, -52);
    add(s1, 17);
    
    print_test_result("card - after 3 inserts is 3", card(s1) == 3);
    print_test_result("isEmpty - after inserts is false", isEmpty(s1) == false);
    
    // Test duplicate addition (should do nothing)
    add(s1, 9);
    print_test_result("add - duplicate insertion ignored", card(s1) == 3);

    // Verify ordering in toString
    s1_str = toString(s1);
    print_test_result("toString - sorted representation matches benchmark", 
                      strcmp(s1_str, "{-52,9,17}") == 0);
    free(s1_str);

    // -------------------------------------------------------------
    // Test 3: Extremas and Contains
    // -------------------------------------------------------------
    print_test_result("smallest - finds correct minimum (-52)", smallest(s1) == -52);
    print_test_result("largest - finds correct maximum (17)", largest(s1) == 17);
    
    print_test_result("contains - element present", contains(s1, 9) == true);
    print_test_result("contains - element absent", contains(s1, 100) == false);

    // -------------------------------------------------------------
    // Test 4: toArray functionality
    // -------------------------------------------------------------
    int *arr = toArray(s1);
    bool array_ok = (arr[0] == -52 && arr[1] == 9 && arr[2] == 17);
    print_test_result("toArray - matches sorted order elements", array_ok);
    free(arr);

    // -------------------------------------------------------------
    // Test 5: Equality
    // -------------------------------------------------------------
    intSet s2 = createSet();
    add(s2, 17);
    add(s2, -52);
    add(s2, 9);
    
    print_test_result("equals - identical sets with different insertion order match", equals(s1, s2) == true);
    
    add(s2, 100);
    print_test_result("equals - differing sets do not match", equals(s1, s2) == false);
    destroySet(s2);

    // -------------------------------------------------------------
    // Test 6: Removal functionality
    // -------------------------------------------------------------
    remove_(s1, 9);
    print_test_result("remove_ - removing element decreases cardinality", card(s1) == 2);
    print_test_result("contains - removed element missing", contains(s1, 9) == false);
    
    // Remove non-existent element (should do nothing)
    remove_(s1, 999);
    print_test_result("remove_ - removing non-existent element safe", card(s1) == 2);

    // -------------------------------------------------------------
    // Test 7: Set Operations (Union, Intersect, Difference)
    // -------------------------------------------------------------
    intSet A = createSet();
    intSet B = createSet();
    
    // A = {1, 2, 3}
    add(A, 1); add(A, 2); add(A, 3);
    // B = {3, 4, 5}
    add(B, 3); add(B, 4); add(B, 5);

    // Union: A U B = {1, 2, 3, 4, 5}
    intSet u_set = union_(A, B);
    char *u_str = toString(u_set);
    print_test_result("union_ - matches {1,2,3,4,5}", strcmp(u_str, "{1,2,3,4,5}") == 0);
    free(u_str);
    destroySet(u_set);

    // Intersection: A n B = {3}
    intSet i_set = intersect(A, B);
    char *i_str = toString(i_set);
    print_test_result("intersect - matches {3}", strcmp(i_str, "{3}") == 0);
    free(i_str);
    destroySet(i_set);

    // Difference: A - B = {1, 2}
    intSet d_set = diff(A, B);
    char *d_str = toString(d_set);
    print_test_result("diff - A - B matches {1,2}", strcmp(d_str, "{1,2}") == 0);
    free(d_str);
    destroySet(d_set);

    destroySet(A);
    destroySet(B);

    // -------------------------------------------------------------
    // Test 8: Memory Clearing
    // -------------------------------------------------------------
    clear(s1);
    print_test_result("clear - set becomes empty", isEmpty(s1) == true);
    print_test_result("clear - cardinality resets to 0", card(s1) == 0);

    // Clean up remaining setup memory
    destroySet(s1);
    print_test_result("destroySet - successfully executed", true);

    // -------------------------------------------------------------
    // Test 9: Expected Error Triggering (Manual Validation)
    // -------------------------------------------------------------
    printf("\n[Manual Check] Testing empty set errors. The program should print a message containing 'error' and exit:\n");
    intSet empty_set = createSet();
    
    // Uncomment one of the lines below to manually test the crash/error exit property
    // smallest(empty_set); 
    // largest(empty_set);
    
    destroySet(empty_set);

    printf("\nAll structured assertions complete.\n");
    return 0;
}
