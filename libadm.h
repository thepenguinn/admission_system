#define STUDENT_DATABASE_FILE "/home/daniel/.local/share/adm/database.csv"

#define STUDENT_NAME_MAX_LEN 512
#define STUDENT_PHONE_MAX_LEN 11

#define STUDENT_DATABASE_LINE_MAX_LEN (STUDENT_NAME_MAX_LEN + STUDENT_PHONE_MAX_LEN + 128)

struct Student;

struct Student {

    int roll;
    char name[STUDENT_NAME_MAX_LEN];
    char phone[STUDENT_PHONE_MAX_LEN];
    struct Student *next;

};

int adm_load_database(const char *db_file_path);
int adm_deload_database(const char *db_file_path);

int adm_write_database(const char *db_file_path);
int adm_append_database(const int roll, const char *name, const char *phone);
