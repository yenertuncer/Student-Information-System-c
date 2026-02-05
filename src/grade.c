// grade.c - Not Modülü (TAMAMLANMIÞ)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "grade.h"
#include "utils.h"
#include "course.h"

// ===============================================
// LETTER GRADE CONVERSION (OTOMATÝK HARF HESAPLAMA)
// ===============================================

/**
 * Converts a numeric score (0-100) into a standard letter grade.
 * Sayýsal bir puaný (0-100) standart bir harf notuna dönüþtürür.
 * * @param numeric - The numeric score to be converted
 * @param numeric - Dönüþtürülecek sayýsal puan
 * @param letter_buffer - Buffer to store the resulting letter grade (e.g., "AA")
 * @param letter_buffer - Sonuç harf notunun saklanacaðý alan (örn. "AA")
 */
void numeric_to_letter(float numeric, char *letter_buffer) {
    if (numeric >= 90.0) {
        strcpy(letter_buffer, "AA");
    } else if (numeric >= 85.0) {
        strcpy(letter_buffer, "BA");
    } else if (numeric >= 80.0) {
        strcpy(letter_buffer, "BB");
    } else if (numeric >= 75.0) {
        strcpy(letter_buffer, "CB");
    } else if (numeric >= 70.0) {
        strcpy(letter_buffer, "CC");
    } else if (numeric >= 65.0) {
        strcpy(letter_buffer, "DC");
    } else if (numeric >= 60.0) {
        strcpy(letter_buffer, "DD");
    } else if (numeric >= 50.0) {
        strcpy(letter_buffer, "FD");
    } else {
        strcpy(letter_buffer, "FF");
    }
}

/**
 * Converts a letter grade to its corresponding 4.0 scale points.
 * Bir harf notunu 4.0'lýk sistemdeki karþýlýk gelen puanýna dönüþtürür.
 * * @param letter - The letter grade string (e.g., "AA", "BA")
 * @param letter - Harf notu dizgisi (örn. "AA", "BA")
 * @return Point value of the grade (0 to 4)
 * @return Notun puan karþýlýðý (0 ile 4 arasý)
 */
int letter_to_points(const char *letter) {
    if (strcmp(letter, "AA") == 0) return 4;
    if (strcmp(letter, "BA") == 0) return 3;
    if (strcmp(letter, "BB") == 0) return 3;
    if (strcmp(letter, "CB") == 0) return 2;
    if (strcmp(letter, "CC") == 0) return 2;
    if (strcmp(letter, "DC") == 0) return 1;
    if (strcmp(letter, "DD") == 0) return 1;
    return 0;  // FF, FD
}

// ===============================================
// CRUD - CREATE
// ===============================================

/**
 * Adds a new grade record to the list and automatically calculates the letter grade.
 * Listeye yeni bir not kaydý ekler ve harf notunu otomatik olarak hesaplar.
 * * @param head_ptr - Double pointer to the head of the grade list
 * @param head_ptr - Not listesinin baþýna iþaret eden çift kademeli pointer
 * @param new_data - Pointer to the structure containing new grade data
 * @param new_data - Yeni not verilerini içeren yapýya iþaret eden pointer
 * @return 1 if successful, 0 if validation fails or ID already exists
 * @return Baþarýlýysa 1, doðrulama baþarýsýzsa veya ID zaten varsa 0 döner
 */
int add_grade(Grade **head_ptr, const Grade *new_data) {
    if (new_data == NULL) {
        printf("Error: Invalid grade data!\n");
        return 0;
    }
    
    // Validasyon
    if (!validate_positive_int(new_data->id)) {
        printf("Error: Grade ID must be positive!\n");
        return 0;
    }
    
    if (new_data->numeric_grade < 0.0 || new_data->numeric_grade > 100.0) {
        printf("Error: Numeric grade must be between 0 and 100!\n");
        return 0;
    }
    
    // Ayný ID var mý
    if (find_grade_by_id(*head_ptr, new_data->id) != NULL) {
        printf("Error: Grade with ID %d already exists!\n", new_data->id);
        return 0;
    }
    
    // Yeni node
    Grade *new_node = (Grade *)malloc(sizeof(Grade));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 0;
    }
    
    // Verileri kopyala
    new_node->id = new_data->id;
    new_node->enrollment_id = new_data->enrollment_id;
    new_node->student_id = new_data->student_id;
    new_node->course_id = new_data->course_id;
    new_node->numeric_grade = new_data->numeric_grade;
    strcpy(new_node->semester, new_data->semester);
    
    // Harf notunu otomatik hesapla
    numeric_to_letter(new_data->numeric_grade, new_node->letter_grade);
    
    new_node->next = NULL;
    
    // Listeye ekle
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        Grade *current = *head_ptr;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    printf("Success: Grade added (%.2f -> %s)!\n", 
           new_data->numeric_grade, new_node->letter_grade);
    return 1;
}

// ===============================================
// CRUD - READ
// ===============================================

/**
 * Finds a specific grade record using its unique ID.
 * Benzersiz ID'sini kullanarak belirli bir not kaydýný bulur.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param id - The unique identifier of the grade to find
 * @param id - Bulunacak notun benzersiz tanýmlayýcýsý
 * @return Pointer to the grade node if found, NULL otherwise
 * @return Not düðümü bulunursa adresi, aksi takdirde NULL döner
 */
Grade* find_grade_by_id(Grade *head, int id) {
    Grade *current = head;
    
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Searches for a grade record associated with a specific enrollment.
 * Belirli bir kayýtla (enrollment) iliþkili not kaydýný arar.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param enrollment_id - The ID of the enrollment record
 * @param enrollment_id - Kayýt (enrollment) kaydýnýn ID'si
 * @return Pointer to the grade node or NULL
 * @return Not düðümü adresi veya NULL döner
 */
Grade* find_grade_by_enrollment(Grade *head, int enrollment_id) {
    Grade *current = head;
    
    while (current != NULL) {
        if (current->enrollment_id == enrollment_id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Retrieves the grade for a specific student in a specific course.
 * Belirli bir öðrencinin belirli bir kurstaki notunu getirir.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param student_id - ID of the student
 * @param student_id - Öðrencinin ID'si
 * @param course_id - ID of the course
 * @param course_id - Kursun ID'si
 * @return Pointer to the matched grade or NULL
 * @return Eþleþen notun adresi veya NULL döner
 */
Grade* find_student_course_grade(Grade *head, int student_id, int course_id) {
    Grade *current = head;
    
    while (current != NULL) {
        if (current->student_id == student_id && current->course_id == course_id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

// ===============================================
// CRUD - UPDATE
// ===============================================

/**
 * Updates the numeric and letter grade of an existing record.
 * Mevcut bir kaydýn sayýsal ve harf notunu günceller.
 * * @param grade_to_update - Pointer to the grade node to modify
 * @param grade_to_update - Deðiþtirilecek not düðümüne iþaret eden pointer
 * @param new_numeric - The new numeric grade value
 * @param new_numeric - Yeni sayýsal not deðeri
 * @param new_letter - Optional new letter grade (if NULL, it's auto-calculated)
 * @param new_letter - Ýsteðe baðlý yeni harf notu (NULL ise otomatik hesaplanýr)
 * @return 1 if successful, 0 otherwise
 * @return Baþarýlýysa 1, aksi takdirde 0 döner
 */
int update_grade(Grade *grade_to_update, float new_numeric, const char *new_letter) {
    if (grade_to_update == NULL) {
        printf("Error: Invalid grade!\n");
        return 0;
    }
    
    if (new_numeric < 0.0 || new_numeric > 100.0) {
        printf("Error: Numeric grade must be between 0 and 100!\n");
        return 0;
    }
    
    grade_to_update->numeric_grade = new_numeric;
    
    // Eðer harf notu verilmediyse otomatik hesapla
    if (new_letter == NULL || strlen(new_letter) == 0) {
        numeric_to_letter(new_numeric, grade_to_update->letter_grade);
    } else {
        strcpy(grade_to_update->letter_grade, new_letter);
    }
    
    printf("Success: Grade updated to %.2f (%s)!\n", 
           new_numeric, grade_to_update->letter_grade);
    return 1;
}

// ===============================================
// CRUD - DELETE
// ===============================================

/**
 * Removes a grade record from the list by its ID.
 * Bir not kaydýný ID'sine göre listeden kaldýrýr.
 * * @param head_ptr - Double pointer to the head of the grade list
 * @param head_ptr - Not listesinin baþýna iþaret eden çift kademeli pointer
 * @param id - The unique ID of the grade to delete
 * @param id - Silinecek notun benzersiz ID'si
 * @return 1 if successfully deleted, 0 if not found
 * @return Baþarýyla silindiyse 1, bulunamadýysa 0 döner
 */
int delete_grade(Grade **head_ptr, int id) {
    Grade *current = *head_ptr;
    Grade *prev = NULL;
    
    if (current == NULL) {
        printf("Error: Grade list is empty!\n");
        return 0;
    }
    
    // Ýlk node
    if (current->id == id) {
        *head_ptr = current->next;
        printf("Success: Grade with ID %d deleted.\n", id);
        free(current);
        return 1;
    }
    
    // Ortada/sonda
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Grade with ID %d not found!\n", id);
        return 0;
    }
    
    prev->next = current->next;
    printf("Success: Grade with ID %d deleted.\n", id);
    free(current);
    return 1;
}

// ===============================================
// FILE OPERATIONS
// ===============================================

/**
 * Loads grade data from the CSV file into the linked list.
 * CSV dosyasýndaki not verilerini baðlý listeye yükler.
 * * @param head_ptr - Double pointer to receive the head of the list
 * @param head_ptr - Listenin baþýný alacak çift kademeli pointer
 * @return 1 if successful, 0 if file cannot be opened
 * @return Baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int load_grades_from_csv(Grade **head_ptr) {
    const char *filename = "data/grades.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
    	filename = "grades.csv";
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Warning: Could not open grades.csv. Starting empty.\n");
            return 0;
        }
    }
    
    char line[512];
    char *tokens[10];
    int count = 0;
    
    fgets(line, sizeof(line), file);
    
    while (fgets(line, sizeof(line), file)) {
        remove_newline(line);
        
        int token_count = split_csv_line(line, tokens, 7);
        
        if (token_count >= 7) {
            Grade temp;
            
            temp.id = atoi(tokens[0]);
            temp.enrollment_id = atoi(tokens[1]);
            temp.student_id = atoi(tokens[2]);
            temp.course_id = atoi(tokens[3]);
            strcpy(temp.letter_grade, tokens[4]);
            temp.numeric_grade = atof(tokens[5]);
            strcpy(temp.semester, tokens[6]);
            
            Grade *new_node = (Grade *)malloc(sizeof(Grade));
            if (new_node) {
                *new_node = temp;
                new_node->next = NULL;
                
                if (*head_ptr == NULL) {
                    *head_ptr = new_node;
                } else {
                    Grade *curr = *head_ptr;
                    while (curr->next != NULL) curr = curr->next;
                    curr->next = new_node;
                }
                count++;
            }
        }
    }
    
    fclose(file);
    printf("Success: Loaded %d grades from CSV.\n", count);
    return 1;
}

/**
 * Saves all current grade records to a specified CSV file.
 * Mevcut tüm not kayýtlarýný belirtilen bir CSV dosyasýna kaydeder.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param filename - String containing the destination file path
 * @param filename - Hedef dosya yolunu içeren dizgi
 * @return 1 if successful, 0 otherwise
 * @return Baþarýlýysa 1, aksi takdirde 0 döner
 */
int save_grades_to_csv(Grade *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing!\n");
        return 0;
    }
    
    fprintf(file, "grade_id,enrollment_id,student_id,course_id,letter_grade,numeric_grade,semester\n");
    
    Grade *current = head;
    int count = 0;
    
    while (current != NULL) {
        fprintf(file, "%d,%d,%d,%d,%s,%.2f,%s\n",
                current->id,
                current->enrollment_id,
                current->student_id,
                current->course_id,
                current->letter_grade,
                current->numeric_grade,
                current->semester);
        current = current->next;
        count++;
    }
    
    fclose(file);
    printf("Success: Saved %d grades to CSV.\n", count);
    return 1;
}

// ===============================================
// DISPLAY OPERATIONS
// ===============================================

/**
 * Prints all grades and the numeric average for a specific student.
 * Belirli bir öðrenci için tüm notlarý ve sayýsal ortalamayý yazdýrýr.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param student_id - ID of the student
 * @param student_id - Öðrencinin ID'si
 */
void display_student_grades(Grade *head, int student_id) {
    printf("\n============================================================================\n");
    printf("  Grades for Student ID: %d\n", student_id);
    printf("============================================================================\n");
    printf("%-10s %-10s %-10s %-10s %-15s\n", 
           "GradeID", "CourseID", "Letter", "Numeric", "Semester");
    printf("----------------------------------------------------------------------------\n");
    
    Grade *current = head;
    int found = 0;
    float sum = 0;
    int count = 0;
    
    while (current != NULL) {
        if (current->student_id == student_id) {
            printf("%-10d %-10d %-10s %-10.2f %-15s\n",
                   current->id,
                   current->course_id,
                   current->letter_grade,
                   current->numeric_grade,
                   current->semester);
            sum += current->numeric_grade;
            count++;
            found = 1;
        }
        current = current->next;
    }
    
    printf("============================================================================\n");
    if (found) {
        printf("Average Numeric Grade: %.2f\n", sum / count);
    } else {
        printf("No grades found for this student.\n");
    }
    printf("============================================================================\n");
}

/**
 * Lists all student grades recorded for a specific course.
 * Belirli bir kurs için kaydedilmiþ tüm öðrenci notlarýný listeler.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param course_id - ID of the course
 * @param course_id - Kursun ID'si
 */
void display_course_grades(Grade *head, int course_id) {
    printf("\n============================================================================\n");
    printf("  Grade Distribution for Course ID: %d\n", course_id);
    printf("============================================================================\n");
    printf("%-10s %-10s %-10s %-15s\n", 
           "StudentID", "Letter", "Numeric", "Semester");
    printf("----------------------------------------------------------------------------\n");
    
    Grade *current = head;
    int found = 0;
    
    while (current != NULL) {
        if (current->course_id == course_id) {
            printf("%-10d %-10s %-10.2f %-15s\n",
                   current->student_id,
                   current->letter_grade,
                   current->numeric_grade,
                   current->semester);
            found = 1;
        }
        current = current->next;
    }
    
    if (!found) {
        printf("No grades found for this course.\n");
    }
    
    printf("============================================================================\n");
}

/**
 * Prints a complete table of all grades currently in the system memory.
 * Sistem belleðindeki tüm notlarýn tam bir tablosunu yazdýrýr.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 */
void display_all_grades(Grade *head) {
    Grade *current;
    int count = 0;
    
    if (head == NULL) {
        printf("\nNo grades to display.\n");
        return;
    }
    
    printf("\n=====================================================================\n");
    printf("                           GRADE LIST                                \n");
    printf("=====================================================================\n");
    printf("%-6s %-6s %-8s %-8s %-6s %-7s %-12s\n", 
           "GrdID", "EnrID", "StudID", "CrsID", "Letter", "Numeric", "Semester");
    printf("---------------------------------------------------------------------\n");
    
    current = head;
    
    while (current != NULL) {
        printf("%-6d %-6d %-8d %-8d %-6.6s %-7.2f %-12.12s\n",
               current->id,
               current->enrollment_id,
               current->student_id,
               current->course_id,
               current->letter_grade,
               current->numeric_grade,
               current->semester);
        current = current->next;
        count++;
    }
    
    printf("=====================================================================\n");
    printf("Total Grades: %d\n", count);
    printf("=====================================================================\n");
}

// ===============================================
// STATISTICS
// ===============================================

/**
 * Calculates the mean numeric grade for all students in a course.
 * Bir kurstaki tüm öðrenciler için ortalama sayýsal notu hesaplar.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param course_id - ID of the course
 * @param course_id - Kursun ID'si
 * @return The average numeric score
 * @return Ortalama sayýsal puan
 */
float calculate_course_average(Grade *head, int course_id) {
    float sum = 0;
    int count = 0;
    
    Grade *current = head;
    while (current != NULL) {
        if (current->course_id == course_id) {
            sum += current->numeric_grade;
            count++;
        }
        current = current->next;
    }
    
    if (count == 0) return 0.0;
    return sum / count;
}

/**
 * Shows comprehensive statistics including average, min, max, and grade distribution.
 * Ortalama, min, max ve not daðýlýmý dahil kapsamlý istatistikleri gösterir.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @param course_id - ID of the course
 * @param course_id - Kursun ID'si
 */
void display_grade_statistics(Grade *head, int course_id) {
    float sum = 0, min = 100, max = 0;
    int count = 0;
    
    // Sayaçlarý sýfýrla
    int count_AA = 0, count_BA = 0, count_BB = 0, count_CB = 0;
    int count_CC = 0, count_DC = 0, count_DD = 0, count_FD = 0, count_FF = 0;

    Grade *curr = head;

    printf("\n========================================\n");
    printf("   Grade Statistics for Course %d\n", course_id);
    printf("========================================\n");

    while (curr != NULL) {
        if (curr->course_id == course_id) {
            float score = curr->numeric_grade; // Sayýsal notu al
            
            // 1. Genel Ýstatistikler
            if (score < min) min = score;
            if (score > max) max = score;
            sum += score;
            count++;

            // 2. Daðýlýmý SAYISAL nota göre yap
            if (score >= 90) count_AA++;
            else if (score >= 85) count_BA++;
            else if (score >= 80) count_BB++;
            else if (score >= 75) count_CB++;
            else if (score >= 70) count_CC++;
            else if (score >= 60) count_DC++;
            else if (score >= 50) count_DD++;
            else if (score >= 40) count_FD++;
            else count_FF++;
        }
        curr = curr->next;
    }

    if (count > 0) {
        printf("Total Students: %d\n", count);
        printf("Average:        %.2f\n", sum / count);
        printf("Minimum:        %.2f\n", min);
        printf("Maximum:        %.2f\n", max);
        printf("----------------------------------------\n");
        printf("GRADE DISTRIBUTION:\n");
        printf("AA: %-4d  BA: %-4d  BB: %-4d  CB: %-4d\n", count_AA, count_BA, count_BB, count_CB);
        printf("CC: %-4d  DC: %-4d  DD: %-4d  FD: %-4d\n", count_CC, count_DC, count_DD, count_FD);
        printf("FF: %-4d\n", count_FF);
    } else {
        printf("No grades recorded for this course.\n");
    }
    printf("========================================\n");
}

// ===============================================
// UTILITY
// ===============================================

/**
 * Frees all memory allocated for the grade linked list.
 * Not baðlý listesi için ayrýlan tüm belleði serbest býrakýr.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 */
void free_all_grades(Grade *head) {
    Grade *temp;
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    printf("Memory for grades cleared.\n");
}

/**
 * Counts the total number of grade records in the linked list.
 * Baðlý listedeki toplam not kaydý sayýsýný hesaplar.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @return Total record count
 * @return Toplam kayýt sayýsý
 */
int count_grades(Grade *head) {
    int count = 0;
    Grade *current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}

/**
 * Determines the next sequential unique ID for a new grade entry.
 * Yeni bir not giriþi için bir sonraki sýralý benzersiz ID'yi belirler.
 * * @param head - Pointer to the head of the grade list
 * @param head - Not listesinin baþýna iþaret eden pointer
 * @return The next available integer ID
 * @return Mevcut bir sonraki tam sayý ID
 */
int get_next_grade_id(Grade *head) {
    int max_id = 0;
    Grade *current = head;
    
    while (current != NULL) {
        if (current->id > max_id) {
            max_id = current->id;
        }
        current = current->next;
    }
    
    return max_id + 1;
}
