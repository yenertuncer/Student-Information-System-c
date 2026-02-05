// utils.h - Yardýmcý Fonksiyonlar (FINAL VERSION)

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// String iþlemleri
void remove_newline(char *str);
int split_csv_line(char *line, char *tokens[], int max_tokens);
void trim_whitespace(char *str);

// Validasyon fonksiyonlarý
int is_numeric(const char *str);
int validate_email(const char *email);
int validate_phone(const char *phone);
int validate_gpa(float gpa);
int validate_positive_int(int value);
int validate_year(int year);

// Girdi alma fonksiyonlarý
void get_string_input(const char *prompt, char *buffer, int max_len);
int get_int_input(const char *prompt);
float get_float_input(const char *prompt);
int get_validated_id(const char *prompt);

// Tarih fonksiyonlarý
void get_current_date(char *buffer);
int validate_date(const char *date);

#endif // UTILS_H
