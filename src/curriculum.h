#ifndef CURRICULUM_H
#define CURRICULUM_H

#include "student.h"
#include "course.h"
#include "grade.h"

// Müfredat ve Mezuniyet Kontrolü Fonksiyonu
void check_graduation_status(int student_id, Student *s_head, Grade *g_head, Course *c_head);

#endif
