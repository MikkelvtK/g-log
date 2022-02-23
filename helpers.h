#include <stdbool.h>
#include <getopt.h>

#define DATE_SIZE 20
#define USAGE "Use --help to look up valid commands\n"

void format_date(char *d, int s);
void print_table_header();
void print_table_footer();
bool validate_arguments(int argc, struct option options[], int opt_i, int optind);