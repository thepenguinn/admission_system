#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include "libadm.h"

enum LogLevels {
	ERROR,
	WARN,
	INFO,
	DEBUG,
};

static struct Student *First_Student = NULL;
static struct Student *Last_Student = NULL;

static void adm_logger(int log_level, const char *fmt, ...);
static void adm_parse_line(struct Student *student, char *line);

static void adm_logger(int log_level, const char *fmt, ...) {

	va_list ap;

	if (log_level == ERROR)
		fprintf(stdout, "ERROR: ");
	else if (log_level == WARN)
		fprintf(stdout, "WARN:  ");
	else if (log_level == INFO)
		fprintf(stdout, "INFO:  ");
	else if (log_level == DEBUG)
		fprintf(stdout, "DEBUG: ");

	va_start(ap, fmt);
	vfprintf(stdout, fmt, ap);
	va_end(ap);

	fprintf(stdout, "\n");

	fflush(stdout);
}

static void adm_parse_line(struct Student *student, char *line) {

    char *roll;
    char *name;
    char *phone;

    roll = line;

    while (*line != '\0' && *line != ',') {
        line++;
    }

    *line = '\0';
    line++;

    name = line;

    while (*line != '\0' && *line != ',') {
        line++;
    }

    *line = '\0';
    line++;

    phone = line;

    student->roll = atoi(roll);

    student->name[STUDENT_NAME_MAX_LEN - 1] = '\0';
    student->phone[STUDENT_PHONE_MAX_LEN - 1] = '\0';

    strncpy(student->name, name, STUDENT_NAME_MAX_LEN - 1);
    strncpy(student->phone, phone, STUDENT_PHONE_MAX_LEN - 1);

}


int adm_load_database(const char *db_file_path) {

    FILE *file;
    char line[STUDENT_DATABASE_LINE_MAX_LEN];
    struct Student *student;

    // adm_logger(WARN, "%s", db_file_path);

    if (access(db_file_path, F_OK) != 0) {
        adm_logger(INFO, "File doesn't exists, creating it: %s", db_file_path);
        file = fopen(db_file_path, "w+");
    } else {
        file = fopen(db_file_path, "r+");
    }

    if (file == NULL) {
        adm_logger(ERROR, "fopen() returned NULL");
        return 1;
    }

    while ((fgets(line, STUDENT_DATABASE_LINE_MAX_LEN, file)) != NULL) {
        adm_logger(INFO, "Read line: %s", line);
        student = malloc(sizeof(struct Student));
        if (student == NULL) {
            adm_logger(ERROR, "malloc() returned NULL");
            return -1;
        }

        adm_parse_line(student, line);

        student->next = NULL;

        if (First_Student == NULL) {
            First_Student = student;
        } else {
            Last_Student->next = student;
        }
        Last_Student = student;

    }

    return 0;

}

int adm_append_database(const int roll, const char *name, const char *phone) {

    struct Student *student;

    student = malloc(sizeof(struct Student));
    if (student == NULL) {
        adm_logger(ERROR, "malloc() returned NULL");
        return -1;
    }

    student->name[STUDENT_NAME_MAX_LEN - 1] = '\0';
    student->phone[STUDENT_PHONE_MAX_LEN - 1] = '\0';

    strncpy(student->name, name, STUDENT_NAME_MAX_LEN - 1);
    strncpy(student->phone, phone, STUDENT_PHONE_MAX_LEN - 1);

    student->roll = roll;

    student->next = NULL;

    if (First_Student == NULL) {
        First_Student = student;
    } else {
        Last_Student->next = student;
    }
    Last_Student = student;

    return 0;
}

// int adm_write_database(const char *db_file_path) {
// }

int main() {

    adm_load_database(STUDENT_DATABASE_FILE);

    struct Student *student;

    adm_append_database(23, "Daniel V Mathew", "1111111111");

    for (student = First_Student; student; student = student->next) {
        printf("%p\n", student);
        printf("%d\n", student->roll);
        printf("%s\n", student->name);
        printf("%s\n", student->phone);

        printf("\n");
    }

    return 0;
}
