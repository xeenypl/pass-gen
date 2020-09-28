#include <ctype.h>
#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

static const char* prog_name;

static bool        include_upper_case = false;
static bool        include_lower_case = false;
static bool        include_special = false;
static bool        include_digits = false;

static int         password_length = 30;
static int         password_count = 1;
static const char* password_set;

static bool charIsInSet(char c);
static void passGen(void);
static void usage(void);
static void help(void);

static bool charIsInSet(char c) {
    size_t len = strlen(password_set);
    for (size_t i = 0; i < len; i++) {
        if (password_set[i] == c) {
            return true;
        }
    }
    return false;
}

static void passGen(void) {
    for (int i = 0; i < password_length; i++) {
        char output;
        do {
            output = (rand() % 256);
        } while (!(
            (include_upper_case && isupper(output)) ||
            (include_lower_case && islower(output)) || 
            (include_special && ispunct(output)) || 
            (include_digits && isdigit(output)) || 
            (password_set && charIsInSet(output))
        ));
        printf("%c", output);
    }
    printf("\n");
}

static void usage(void) {
    fprintf(
        stderr,
        "usage:\n"
        "\t%s [options] [character-set]\n",
        prog_name
    );
    exit(EXIT_FAILURE);
}

static void help(void) {
    fprintf(
        stdout,
        "usage:\n"
        "\t%s [options] [character-set]\n"
        "option:\n"
        "\t-c --count <nunber>       How many password grnerate\n"
        "\t-l --length <nunber>      How long password should be\n"
        "\t-a --include-lower-case   Include all lower case letter [a-z]\n"
        "\t-A --include-upper-case   Include all upper case letter [A-Z]\n"
        "\t-s --include-special      Include special character like `!@#$.`\n"
        "\t-d --include-digits       Include all digits [0-9]\n"
        "\t-h --help                 Prints this mesage\n",
        prog_name
    );
    exit(EXIT_SUCCESS);
}

int main(int argc, char** argv) {
    prog_name = argv[0];
    static struct option long_opt[] = {
        {"count",               required_argument, NULL, 'c' },
        {"length",              required_argument, NULL, 'l' },
        {"include-lower-case",  no_argument,       NULL, 'a' },
        {"include-upper-case",  no_argument,       NULL, 'A' },
        {"include-special",     no_argument,       NULL, 's' },
        {"include-digits",      no_argument,       NULL, 'd' },
        {"help",                no_argument,       NULL, 'h' },
        {NULL,                  0,                 NULL, 0   },
    };

    while (true) {
        int opt = getopt_long(argc, argv, "c:l:aAsdh", long_opt, NULL);
        if (opt == -1) {
            break;
        }

        switch (opt) {
        case 'c':
            password_count = atoi(optarg);
            break;
        case 'l':
            password_length = atoi(optarg);
            break;
        case 'A':
            include_upper_case = true;
            break;
        case 'a':
            include_lower_case = true;
            break;
        case 's':
            include_special = true;
            break;
        case 'd':
            include_digits = true;
            break;
        case 'h':
            help();
            break;
        default:
            usage();
        }
    }

    argc -= optind;
    argv += optind;

    srand(time(NULL));

    if (argc > 1) {
        usage();
    }

    if (argc == 1) {
        password_set = argv[0];
    }

    if (
        !include_upper_case &&
        !include_lower_case &&
        !include_special &&
        !include_digits &&
        password_set == NULL
    ) {
        fprintf(stderr, "No specified character\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < password_count; i++) {
        passGen();
    }

    return EXIT_SUCCESS;
}
