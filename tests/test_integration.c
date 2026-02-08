// tests/test_integration.c
void run_integration_tests() {
    printf("\n--- Running Integration Tests (Enrollment & Grade) ---\n");

    // Tüm listeleri sıfırdan oluşturuyoryz
    Student *s_head = NULL;
    Course *c_head = NULL;
    Enrollment *e_head = NULL;
    Grade *g_head = NULL;

    // 1. Hazırlık: Öðrenci ve Ders Ekle
    Student s; s.id = 2024001; strcpy(s.first_name,"Test"); strcpy(s.last_name,"Stud");
    strcpy(s.email,"t@t.com"); strcpy(s.phone,"555"); s.enrollment_year=2024;
    strcpy(s.major,"CS"); s.gpa=0; s.next=NULL;
    add_student(&s_head, &s);

    Course c; c.id = 3001; strcpy(c.code,"CS101"); strcpy(c.name,"Coding");
    c.credits=4; c.capacity=30; strcpy(c.department,"CS"); 
    strcpy(c.prerequisites,""); c.next=NULL;
    add_course(&c_head, &c);

    // 2. Test: Kayıt Olma (Enrollment)
    Enrollment e; e.student_id = 2024001; e.course_id = 3001;
    e.professor_id = 0; strcpy(e.semester, "2024-FALL"); 
    strcpy(e.date, "2024-09-01"); strcpy(e.status, "Enrolled");
    e.id = 1; e.next = NULL;

    // check_prerequisites fonksiyonunu manuel test ediyoruz
    int can_take = check_prerequisites(s.id, &c, g_head, e_head);
    TEST_ASSERT(can_take == 1, "Prerequisite Check Passed (No prereqs)");

    int res = add_enrollment(&e_head, &e);
    TEST_ASSERT(res == 1, "Student Enrolled Successfully");

    // 3. Test: Çift Kayıt Engelleme
    int is_enrolled = is_student_enrolled(e_head, 2024001, 3001);
    TEST_ASSERT(is_enrolled == 1, "is_student_enrolled returns True");

    // 4. Test: Not Verme (Grade)
    Grade g; g.id = 1; g.student_id = 2024001; g.course_id = 3001;
    g.enrollment_id = 1; g.numeric_grade = 90.0; 
    strcpy(g.semester, "2024-FALL"); g.next = NULL;
    
    res = add_grade(&g_head, &g);
    TEST_ASSERT(res == 1, "Grade Assigned");

    // 5. Test: GPA Hesaplama
    // Grade eklendiği için GPA değişmeli (Þu an hesapla fonksiyonunu çağırıyoruz)
    float gpa = calculate_student_gpa(2024001, g_head, c_head);
    TEST_ASSERT(gpa > 0.0, "GPA Calculated > 0.0");

    // Temizlik
    free_all_students(&s_head);
    free_all_courses(&c_head);
    free_all_enrollments(&e_head);
    free_all_grades(&g_head);
}

