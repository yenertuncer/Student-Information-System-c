// tests/test_course.c
void run_course_tests() {
    printf("\n--- Running Course Module Tests ---\n");
    Course *head = NULL;

    // 1. Add Course
    Course c1; 
    c1.id = 101; strcpy(c1.code, "CS101"); strcpy(c1.name, "Intro to C");
    c1.credits = 4; c1.capacity = 50; strcpy(c1.department, "CS");
    strcpy(c1.prerequisites, "None"); c1.next = NULL;

    int res = add_course(&head, &c1);
    TEST_ASSERT(res == 1, "Add Course Successfully");

    // 2. Find Course
    Course *found = find_course_by_code(head, "CS101");
    TEST_ASSERT(found != NULL, "Find Course by Code");

    // 3. Delete Course
    res = delete_course(&head, 101);
    TEST_ASSERT(res == 1, "Delete Course");
    TEST_ASSERT(head == NULL, "List Empty after Delete");

    free_all_courses(&head);
}
