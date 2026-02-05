// tests/test_professor.c
void run_professor_tests() {
    printf("\n--- Running Professor Module Tests ---\n");
    Professor *head = NULL;

    Professor p1;
    p1.id = 5001; strcpy(p1.first_name, "John"); strcpy(p1.last_name, "Nash");
    strcpy(p1.email, "nash@univ.edu"); strcpy(p1.phone, "555-9999");
    strcpy(p1.department, "Math"); strcpy(p1.title, "Prof"); 
    strcpy(p1.office, "A-101"); p1.next = NULL;

    int res = add_professor(&head, &p1);
    TEST_ASSERT(res == 1, "Add Professor");

    Professor *found = find_professor_by_id(head, 5001);
    TEST_ASSERT(found != NULL, "Find Professor by ID");

    free_all_professors(&head);
}
