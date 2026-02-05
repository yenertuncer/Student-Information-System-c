// professor.c - Profesör Modülü (TAMAMLANMIÞ)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "professor.h"
#include "utils.h"
#include "enrollment.h"
#include "course.h"

/**
 * Adds a new professor to the system after validating ID and email.
 * ID ve e-posta doðrulamasýndan sonra sisteme yeni bir profesör ekler.
 * * @param head_ptr - Double pointer to the head of the professor list
 * @param head_ptr - Profesör listesinin baþýna iþaret eden çift kademeli pointer
 * @param new_data - Pointer to the structure containing new professor data
 * @param new_data - Yeni profesör verilerini içeren yapýya iþaret eden pointer
 * @return 1 if successful, 0 if validation fails or ID already exists
 * @return Baþarýlýysa 1, doðrulama baþarýsýzsa veya ID zaten varsa 0 döner
 */
int add_professor(Professor **head_ptr, const Professor *new_data) {
    if (new_data == NULL) {
        printf("Error: Invalid professor data!\n");
        return 0;
    }
    
    // Validasyon
    if (!validate_positive_int(new_data->id)) {
        printf("Error: Professor ID must be positive!\n");
        return 0;
    }
    
    if (!validate_email(new_data->email)) {
        printf("Error: Invalid email format!\n");
        return 0;
    }
    
    // Ayný ID var mý
    if (find_professor_by_id(*head_ptr, new_data->id) != NULL) {
        printf("Error: Professor with ID %d already exists!\n", new_data->id);
        return 0;
    }
    
    // Yeni node
    Professor *new_node = (Professor *)malloc(sizeof(Professor));
    if (new_node == NULL) {
        printf("Error: Memory allocation failed!\n");
        return 0;
    }
    
    // Verileri kopyala
    new_node->id = new_data->id;
    strcpy(new_node->first_name, new_data->first_name);
    strcpy(new_node->last_name, new_data->last_name);
    strcpy(new_node->email, new_data->email);
    strcpy(new_node->phone, new_data->phone);
    strcpy(new_node->department, new_data->department);
    strcpy(new_node->title, new_data->title);
    strcpy(new_node->office, new_data->office);
    new_node->next = NULL;
    
    // Listeye ekle
    if (*head_ptr == NULL) {
        *head_ptr = new_node;
    } else {
        Professor *current = *head_ptr;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    
    printf("Success: Professor '%s %s' added successfully!\n", 
           new_data->first_name, new_data->last_name);
    return 1;
}

/**
 * Searches for a professor in the linked list by their unique ID.
 * Benzersiz ID numarasýna göre profesörü baðlý listede arar.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 * @param id - Unique identifier of the professor
 * @param id - Profesörün benzersiz tanýmlayýcýsý
 * @return Pointer to the professor node if found, NULL otherwise
 * @return Profesör düðümü bulunursa adresi, aksi takdirde NULL döner
 */
Professor* find_professor_by_id(Professor *head, int id) {
    Professor *current = head;
    
    while (current != NULL) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Searches for a professor by matching both first and last names.
 * Hem isim hem de soyisim eþleþmesine göre profesör aramasý yapar.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 * @param first_name - First name string to search
 * @param first_name - Aranan isim dizgisi
 * @param last_name - Last name string to search
 * @param last_name - Aranan soyisim dizgisi
 * @return Pointer to the matched professor or NULL
 * @return Eþleþen profesörün adresi veya NULL döner
 */
Professor* find_professor_by_name(Professor *head, const char *first_name, const char *last_name) {
    Professor *current = head;
    
    while (current != NULL) {
        if (strcmp(current->first_name, first_name) == 0 && 
            strcmp(current->last_name, last_name) == 0) {
            return current;
        }
        current = current->next;
    }
    
    return NULL;
}

/**
 * Updates an existing professor's details with new validated data.
 * Mevcut bir profesörün bilgilerini doðrulanmýþ yeni verilerle günceller.
 * * @param prof_to_update - Pointer to the professor node to update
 * @param prof_to_update - Güncellenecek profesör düðümüne iþaret eden pointer
 * @param new_data - Structure containing updated information
 * @param new_data - Güncellenmiþ bilgileri içeren yapý
 * @return 1 if successful, 0 if validation fails
 * @return Baþarýlýysa 1, doðrulama baþarýsýzsa 0 döner
 */
int update_professor(Professor *prof_to_update, const Professor *new_data) {
    if (prof_to_update == NULL || new_data == NULL) {
        printf("Error: Invalid parameters!\n");
        return 0;
    }
    
    // Validasyon
    if (!validate_email(new_data->email)) {
        printf("Error: Invalid email format!\n");
        return 0;
    }
    
    // Güncelle (ID hariç)
    strcpy(prof_to_update->first_name, new_data->first_name);
    strcpy(prof_to_update->last_name, new_data->last_name);
    strcpy(prof_to_update->email, new_data->email);
    strcpy(prof_to_update->phone, new_data->phone);
    strcpy(prof_to_update->department, new_data->department);
    strcpy(prof_to_update->title, new_data->title);
    strcpy(prof_to_update->office, new_data->office);
    
    printf("Success: Professor information updated!\n");
    return 1;
}

/**
 * Removes a professor from the list by ID and frees allocated memory.
 * Bir profesörü ID'sine göre listeden kaldýrýr ve ayrýlan belleði serbest býrakýr.
 * * @param head_ptr - Double pointer to the head of the professor list
 * @param head_ptr - Profesör listesinin baþýna iþaret eden çift kademeli pointer
 * @param id - Unique ID of the professor to delete
 * @param id - Silinecek profesörün benzersiz ID'si
 * @return 1 if deletion is successful, 0 if professor not found
 * @return Silme baþarýlýysa 1, profesör bulunamazsa 0 döner
 */
int delete_professor(Professor **head_ptr, int id) {
    Professor *current = *head_ptr;
    Professor *prev = NULL;
    
    if (current == NULL) {
        printf("Error: Professor list is empty!\n");
        return 0;
    }
    
    // Ýlk node
    if (current->id == id) {
        *head_ptr = current->next;
        printf("Success: Professor with ID %d deleted.\n", id);
        free(current);
        return 1;
    }
    
    // Ortada/sonda
    while (current != NULL && current->id != id) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Error: Professor with ID %d not found!\n", id);
        return 0;
    }
    
    prev->next = current->next;
    printf("Success: Professor with ID %d deleted.\n", id);
    free(current);
    return 1;
}

/**
 * Loads professor data from a CSV file into the linked list.
 * CSV dosyasýndaki profesör verilerini baðlý listeye yükler.
 * * @param head_ptr - Double pointer to receive the head of the loaded list
 * @param head_ptr - Yüklenen listenin baþýný alacak çift kademeli pointer
 * @return 1 if loading is successful, 0 if file cannot be opened
 * @return Yükleme baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int load_professors_from_csv(Professor **head_ptr) {
    const char *filename = "data/professors.csv";
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
    	filename = "professors.csv";
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Warning: Could not open professors.csv. Starting empty.\n");
            return 0;
        }
    }
    
    char line[512];
    char *tokens[10];
    int count = 0;
    
    fgets(line, sizeof(line), file);
    
    while (fgets(line, sizeof(line), file)) {
        remove_newline(line);
        
        int token_count = split_csv_line(line, tokens, 8);
        
        if (token_count >= 8) {
            Professor temp;
            
            temp.id = atoi(tokens[0]);
            strcpy(temp.first_name, tokens[1]);
            strcpy(temp.last_name, tokens[2]);
            strcpy(temp.email, tokens[3]);
            strcpy(temp.phone, tokens[4]);
            strcpy(temp.department, tokens[5]);
            strcpy(temp.title, tokens[6]);
            strcpy(temp.office, tokens[7]);
            
            Professor *new_node = (Professor *)malloc(sizeof(Professor));
            if (new_node) {
                *new_node = temp;
                new_node->next = NULL;
                
                if (*head_ptr == NULL) {
                    *head_ptr = new_node;
                } else {
                    Professor *curr = *head_ptr;
                    while (curr->next != NULL) curr = curr->next;
                    curr->next = new_node;
                }
                count++;
            }
        }
    }
    
    fclose(file);
    printf("Success: Loaded %d professors from CSV.\n", count);
    return 1;
}

/**
 * Saves all professor records from the linked list to a CSV file.
 * Baðlý listedeki tüm profesör kayýtlarýný bir CSV dosyasýna kaydeder.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 * @param filename - Destination file path string
 * @param filename - Hedef dosya yolu dizgisi
 * @return 1 if successful, 0 if file cannot be opened
 * @return Baþarýlýysa 1, dosya açýlamazsa 0 döner
 */
int save_professors_to_csv(Professor *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Could not open file for writing!\n");
        return 0;
    }
    
    fprintf(file, "professor_id,first_name,last_name,email,phone,department,title,office\n");
    
    Professor *current = head;
    int count = 0;
    
    while (current != NULL) {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s\n",
                current->id,
                current->first_name,
                current->last_name,
                current->email,
                current->phone,
                current->department,
                current->title,
                current->office);
        current = current->next;
        count++;
    }
    
    fclose(file);
    printf("Success: Saved %d professors to CSV.\n", count);
    return 1;
}

/**
 * Prints all professor information in a formatted table.
 * Tüm profesör bilgilerini formatlý bir tabloda yazdýrýr.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 */
void display_all_professors(Professor *head) {
    Professor *current;
    int count = 0;
    
    if (head == NULL) {
        printf("\nNo professors to display.\n");
        return;
    }
    
    printf("\n====================================================================================\n");
    printf("                               PROFESSOR LIST                                       \n");
    printf("====================================================================================\n");
    printf("%-5s %-12s %-15s %-28s %-20s %-23s %-8s\n", 
           "ID", "First", "Last", "Email", "Department", "Title", "Office");
    printf("------------------------------------------------------------------------------------\n");
    
    current = head;
    
    while (current != NULL) {
        printf("%-5d %-12.12s %-15.15s %-28.28s %-20.20s %-23.23s %-8.8s\n",
               current->id,
               current->first_name,
               current->last_name,
               current->email,
               current->department,
               current->title,
               current->office);
        current = current->next;
        count++;
    }
    
    printf("====================================================================================\n");
    printf("Total Professors: %d\n", count);
    printf("====================================================================================\n");
}

/**
 * Displays detailed information about a single professor.
 * Tek bir profesör hakkýndaki detaylý bilgileri görüntüler.
 * * @param professor - Pointer to the professor structure
 * @param professor - Profesör yapýsýna iþaret eden pointer
 */
void display_professor_details(Professor *professor) {
    if (professor == NULL) {
        printf("Error: Professor not found!\n");
        return;
    }
    
    printf("\n========================================\n");
    printf("       PROFESSOR DETAILS                \n");
    printf("========================================\n");
    printf("ID:         %d\n", professor->id);
    printf("Name:       %s %s\n", professor->first_name, professor->last_name);
    printf("Email:      %s\n", professor->email);
    printf("Phone:      %s\n", professor->phone);
    printf("Department: %s\n", professor->department);
    printf("Title:      %s\n", professor->title);
    printf("Office:     %s\n", professor->office);
    printf("========================================\n");
}

/**
 * Lists all courses assigned to a specific professor using enrollment data.
 * Kayýt verilerini kullanarak belirli bir profesöre atanan tüm dersleri listeler.
 * * @param professor_id - ID of the professor to check
 * @param professor_id - Kontrol edilecek profesörün ID'si
 * @param enrollment_head_void - Generic pointer to the enrollment list head
 * @param enrollment_head_void - Kayýt listesinin baþýna iþaret eden genel pointer
 * @param course_head_void - Generic pointer to the course list head
 * @param course_head_void - Kurs listesinin baþýna iþaret eden genel pointer
 */
void display_professor_courses(int professor_id, void *enrollment_head_void, void *course_head_void) {
    Enrollment *enrollment_head = (Enrollment *)enrollment_head_void;
    Course *course_head = (Course *)course_head_void;
    
    printf("\n========================================\n");
    printf("  Courses taught by Professor ID: %d   \n", professor_id);
    printf("========================================\n");
    printf("%-10s %-40s %-15s\n", "Code", "Course Name", "Semester");
    printf("----------------------------------------\n");
    
    Enrollment *e = enrollment_head;
    int found = 0;
    
    while (e != NULL) {
        if (e->professor_id == professor_id) {
            Course *c = find_course_by_id(course_head, e->course_id);
            if (c != NULL) {
                printf("%-10s %-40s %-15s\n", c->code, c->name, e->semester);
                found = 1;
            }
        }
        e = e->next;
    }
    
    if (!found) {
        printf("No courses assigned yet.\n");
    }
    
    printf("========================================\n");
}

/**
 * Clears all professor nodes from memory at the end of the program.
 * Program sonunda tüm profesör düðümlerini bellekten temizler.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 */
void free_all_professors(Professor *head) {
    Professor *temp;
    
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
    
    printf("Memory for professors cleared.\n");
}

/**
 * Returns the total count of professors registered in the system.
 * Sistemde kayýtlý olan toplam profesör sayýsýný döndürür.
 * * @param head - Pointer to the head of the professor list
 * @param head - Profesör listesinin baþýna iþaret eden pointer
 * @return Integer representing total number of professors
 * @return Toplam profesör sayýsýný temsil eden tam sayý
 */
int count_professors(Professor *head) {
    int count = 0;
    Professor *current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }
    
    return count;
}
