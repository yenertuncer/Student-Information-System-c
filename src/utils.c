// utils.c - Yardýmcý Fonksiyonlar (FINAL VERSION)
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"
#include <stdlib.h>
#include <time.h>

/**
 * Sanitizes input string by replacing Turkish characters with ASCII equivalents.
 * Girdi dizisindeki Türkçe karakterleri ASCII karþýlýklarýyla deðiþtirerek temizler.
 * @param str - The string to be sanitized / Temizlenecek dizgi
 */
static void sanitize_input(char *str) {
	if (str == NULL) return;
    int i;
	for ( i = 0; str[i] != '\0'; i++) {
        switch (str[i]) {
            case 'þ': str[i] = 's'; break;
            case 'Þ': str[i] = 'S'; break;
            case 'ý': str[i] = 'i'; break;
            case 'Ý': str[i] = 'I'; break;
            case 'ð': str[i] = 'g'; break;
            case 'Ð': str[i] = 'G'; break;
            case 'ü': str[i] = 'u'; break;
            case 'Ü': str[i] = 'U'; break;
            case 'ö': str[i] = 'o'; break;
            case 'Ö': str[i] = 'O'; break;
            case 'ç': str[i] = 'c'; break;
            case 'Ç': str[i] = 'C'; break;
        }
    }
}

/**
 * Removes newline and carriage return characters from the end of a string.
 * Bir dizginin sonundaki satýr baþý ve yeni satýr karakterlerini kaldýrýr.
 * @param str - Target string / Hedef dizgi
 */
void remove_newline(char *str) {
    if (str == NULL) return;
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
    if (len > 1 && str[len - 2] == '\r') {
        str[len - 2] = '\0';
    }
}

/**
 * Splits a CSV line into tokens using comma as a delimiter.
 * Bir CSV satýrýný virgül ayýracý kullanarak parçalara (token) ayýrýr.
 * @param line - The raw CSV line / Ham CSV satýrý
 * @param tokens - Array to store split tokens / Parçalarýn saklanacaðý dizi
 * @param max_tokens - Maximum number of tokens allowed / Ýzin verilen maks. parça sayýsý
 * @return Number of tokens found / Bulunan parça sayýsý
 */
int split_csv_line(char *line, char *tokens[], int max_tokens) {
    int count = 0;
    char *token = strtok(line, ",");
    while (token != NULL && count < max_tokens) {
        tokens[count++] = token;
        token = strtok(NULL, ",");
    }
    return count;
}

/**
 * Removes leading and trailing whitespace from a string.
 * Bir dizginin baþýndaki ve sonundaki boþluklarý temizler.
 * @param str - The string to be trimmed / Temizlenecek dizgi
 */
void trim_whitespace(char *str) {
    if (str == NULL) return;
    char *start = str;
    while (*start && isspace(*start)) start++;
    char *end = str + strlen(str) - 1;
    while (end > start && isspace(*end)) end--;
    size_t len = end - start + 1;
    memmove(str, start, len);
    str[len] = '\0';
}

/**
 * Validates if a string contains only numeric characters.
 * Bir dizginin sadece sayýsal karakterler içerip içermediðini doðrular.
 * @param str - The string to check / Kontrol edilecek dizgi
 * @return 1 if numeric, 0 otherwise / Sayýsalsa 1, aksi halde 0 döner
 */
int is_numeric(const char *str) {
    if (str == NULL || *str == '\0') return 0;
    if (*str == '-' || *str == '+') str++;
    while (*str) {
        if (!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}

/**
 * Validates the format of an email address.
 * Bir e-posta adresinin formatýný doðrular.
 * @param email - Email string / E-posta dizgisi
 * @return 1 if valid, 0 otherwise / Geçerliyse 1, aksi halde 0 döner
 */
int validate_email(const char *email) {
    if (email == NULL || strlen(email) < 5) return 0;
    const char *at = strchr(email, '@');
    if (at == NULL) return 0;
    const char *dot = strchr(at, '.');
    if (dot == NULL || dot <= at + 1) return 0;
    if (at == email) return 0;
    return 1;
}

/**
 * Ensures a phone number contains at least 7 digits.
 * Bir telefon numarasýnýn en az 7 rakam içerdiðinden emin olur.
 * @param phone - Phone number string / Telefon numarasý dizgisi
 * @return 1 if valid, 0 otherwise / Geçerliyse 1, aksi halde 0 döner
 */
int validate_phone(const char *phone) {
    if (phone == NULL || strlen(phone) < 7) return 0;
    int i, digit_count = 0;
    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit(phone[i])) digit_count++;
    }
    return digit_count >= 7;
}

/**
 * Checks if a GPA value is within the 0.0 to 4.0 range.
 * Bir GPA deðerinin 0.0 ile 4.0 aralýðýnda olup olmadýðýný kontrol eder.
 * @param gpa - Floating point GPA value / Ondalýklý GPA deðeri
 * @return 1 if in range, 0 otherwise / Aralýktaysa 1, aksi halde 0 döner
 */
int validate_gpa(float gpa) {
    return (gpa >= 0.0 && gpa <= 4.0);
}

/**
 * Validates if an integer is greater than zero.
 * Bir tam sayýnýn sýfýrdan büyük olduðunu doðrular.
 * @param value - Integer value / Tam sayý deðeri
 * @return 1 if positive, 0 otherwise / Pozitifse 1, aksi halde 0 döner
 */
int validate_positive_int(int value) {
    return (value > 0);
}

/**
 * Ensures a year value is within a logical range (1900-2100).
 * Bir yýl deðerinin mantýklý bir aralýkta (1900-2100) olmasýný saðlar.
 * @param year - Year value / Yýl deðeri
 * @return 1 if in range, 0 otherwise / Aralýktaysa 1, aksi halde 0 döner
 */
int validate_year(int year) {
    return (year >= 1900 && year <= 2100);
}

/**
 * Safely reads a string from user input, cleans it, and handles Turkish characters.
 * Kullanýcýdan güvenli bir þekilde dizgi alýr, temizler ve Türkçe karakterleri iþler.
 * @param prompt - Text to display to user / Kullanýcýya gösterilecek metin
 * @param buffer - Storage for input string / Girdi dizgisinin saklanacaðý yer
 * @param max_len - Maximum buffer length / Maksimum tampon uzunluðu
 */
void get_string_input(const char *prompt, char *buffer, int max_len) {
   if (prompt != NULL && strlen(prompt) > 0) printf("%s", prompt);
    if (fgets(buffer, max_len, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
    sanitize_input(buffer);
    trim_whitespace(buffer);
}

/**
 * Reads an integer from user input with error checking and numeric validation.
 * Hata kontrolü ve sayýsal doðrulama ile kullanýcýdan bir tam sayý okur.
 * @param prompt - Instruction for the user / Kullanýcý için talimat
 * @return Validated integer value / Doðrulanmýþ tam sayý deðeri
 */
int get_int_input(const char *prompt) {
    int value;
    char input[50];
    while (1) {
        if (strlen(prompt) > 0) printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) continue;
        remove_newline(input);
        trim_whitespace(input);
        if (strlen(input) == 0) continue;
        if (is_numeric(input)) {
            value = atoi(input);
            return value;
        } else printf("Error: Please enter a valid number!\n");
    }
}

/**
 * Reads a float from user input and handles parsing errors.
 * Kullanýcýdan bir ondalýklý sayý okur ve ayrýþtýrma hatalarýný iþler.
 * @param prompt - Instruction for the user / Kullanýcý için talimat
 * @return Validated float value / Doðrulanmýþ ondalýklý sayý deðeri
 */
float get_float_input(const char *prompt) {
    float value;
    char input[50];
    while (1) {
        if (strlen(prompt) > 0) printf("%s", prompt);
        if (fgets(input, sizeof(input), stdin) == NULL) continue;
        remove_newline(input);
        trim_whitespace(input);
        if (strlen(input) == 0) continue;
        if (sscanf(input, "%f", &value) == 1) return value;
        else printf("Error: Please enter a valid number!\n");
    }
}

/**
 * Prompts user for an ID and ensures it is a positive integer.
 * Kullanýcýdan bir ID ister ve bunun pozitif bir tam sayý olmasýný saðlar.
 * @param prompt - Message for the user / Kullanýcý mesajý
 * @return Validated positive ID / Doðrulanmýþ pozitif ID
 */
int get_validated_id(const char *prompt) {
    int id;
    do {
        id = get_int_input(prompt);
        if (!validate_positive_int(id)) printf("Error: ID must be a positive number!\n");
    } while (!validate_positive_int(id));
    return id;
}

/**
 * Retrieves the current system date in YYYY-MM-DD format.
 * Mevcut sistem tarihini YYYY-MM-DD formatýnda alýr.
 * @param buffer - Storage for the date string / Tarih dizgisinin saklanacaðý yer
 */
void get_current_date(char *buffer) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, 20, "%Y-%m-%d", tm_info);
}

/**
 * Validates if a date string follows the YYYY-MM-DD format.
 * Bir tarih dizgisinin YYYY-MM-DD formatýna uyup uymadýðýný doðrular.
 * @param date - Date string to check / Kontrol edilecek tarih dizgisi
 * @return 1 if format is valid, 0 otherwise / Format geçerliyse 1, aksi halde 0 döner
 */
int validate_date(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[4] != '-' || date[7] != '-') return 0;
    int i;
    for (i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!isdigit(date[i])) return 0;
    }
    return 1;
}
