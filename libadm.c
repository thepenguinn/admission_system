#include <stdio.h>
#include <stdarg.h>

#include "libadm.h"

enum LogLevels {
	ERROR,
	WARN,
	INFO,
	DEBUG,
};

static void logger(int log_level, const char *fmt, ...);

static void logger(int log_level, const char *fmt, ...) {

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

int adm_load_database(const char *db_file_path) {

    logger(WARN, "%s", db_file_path);

}

int main() {
    adm_load_database(STUDENT_DATABASE_FILE);
    // printf("hello world\n");

    return 0;
}
