/**
 * @file tail.c
 * @author Karel Hajek 
 * @login xhajek48 (VUT FIT)
 * @version 0.1
 * @date 2019-04-03
 * 
 * Compiled with: gcc -std=c99 -pedantic -Wall -Wextra
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

// Default line count to print
#define DEFAULT_COUNT 10
// Default string length
#define LINE_LENGTH 1024

const char *USAGE = "Usage: tail [OPTION] [FILE]\n";

struct string {
    size_t length;
    size_t capacity;
    char *s;
};

/**
 * @brief Allocates and initializes string struct
 *
 * @return pointer to allocated string
 */
struct string *string_ctor() {
	struct string *str = malloc(sizeof(struct string));
    if (str == NULL)
        return NULL;
    str->length = 0;
    str->s = malloc(LINE_LENGTH);
    if (str->s == NULL) {
        free(str);
        return NULL;
    }
    str->capacity = LINE_LENGTH;
    return str;
}

/**
 * @brief Reallocates the string for double the capacity
 * @param s Ptr to string to change
 * @return int 0 success, -1 reallocation failed
 */
int string_resize(struct string *s) {
    size_t size = s->capacity * 2;  // double the size needed
    char *foo = realloc(s->s, size);
    if (foo == NULL)
        return -1;
    s->capacity = s->capacity * 2;
    s->s = foo;
    return 0;
}

/**
 * @brief Adds a char to the end of the s
 *        Potentially increasing String capacity
 *        if needed
 *
 * @param str String to append
 * @param c   Char to append
 * @return int 0 success, -1 reallocation failed
 */
int string_append(struct string *str, const char c) {
    if (str->capacity <= str->length + 1) {
        if (string_resize(str) == -1)
            return -1;
    }
    str->s[str->length] = c;
    str->length++;
    return 0;
}

/**
 * @brief Variadic function that prints
 *        a message and exits the program
 *
 * @param exitCode Code to exit program with
 * @param fms  Format string
 * @param ...  Optional arguments
 */
void die(int exitCode, const char *fms, ...) {
    va_list argPtr;
    va_start(argPtr, fms);
    fprintf(stderr, "Error: ");
    vfprintf(stderr, fms, argPtr);
    va_end(argPtr);
    exit(exitCode);
}

/**
 * @brief Gets the number of lines in
 *        a given string
 *
 * @param file
 * @return size_t Number of lines in a file
 */ 
size_t line_count(struct string *string) {
    size_t lineCount = 0;
    for(size_t i = 0; string->s[i] != '\0'; i++) {
        if(string->s[i] == 0xa) lineCount++;
    }
    // If it's not proper unix text file, each line terminated with newline
    // if(string->s[string->length-2] != 0xa) lineCount++;
    return lineCount;
}

/**
 * @brief Deallocates sring
 * 
 * @param text string to free
 */
void string_free(struct string *text) {
    free(text->s);
    free(text);
}

/**
 * @brief Loads content of a file to string
 *
 * @param file  File to load text from
 * @return string* string with file content or NULL if error
 */
struct string *load_lines(FILE *file) {
    struct string *text = string_ctor();
    if(!text) return NULL;
    int c = 0;
    while ((c = fgetc(file)) != EOF) {
        if(string_append(text, c) != 0){
            string_free(text);
            return NULL;
        }
    }
    if(string_append(text, '\0') != 0) {
        string_free(text);
        return NULL;
    }
    return text;
}

/**
 * @brief Prints last N lines from string
 *
 * @param text string
 * @param totalCount Number of lines in string
 * @param n Number of lines to print
 */
void print_tail_lines(struct string *text, const size_t lineCount, const size_t linesToPrint) {
    // if there isn't enough lines, print them all
    if (lineCount < linesToPrint) {
		printf("%s", text->s);
    } else { // skip N number of lines where N = lineCount - linesToPrint
        size_t j = 0; // amount of chars to skip
		for (size_t i = 0; i < lineCount - linesToPrint; ) {
            if(text->s[j++] == 0xa) i++;
        }
        // prints all chars after first 'j' chars
        printf("%s", text->s+j);
    }
}
/**
 * @brief Converts string to uint
 * 
 * @param str 
 * @return size_t 
 */
size_t string_to_uint(const char *str) {
    unsigned int offset = 0;
    if (str[0] == '-') offset++; // negative numbers will be positive
    char *endptr = 0;
    size_t num = strtoul(str + offset, &endptr, 10);
    errno = 0;

    if (str + offset == endptr || errno != 0 || *endptr != 0)
        die(-1, "Couldn't convert number argument, %s", USAGE);
    return num;
}

int main(const int argc, char const *argv[]) {
    FILE *file = stdin;
    // Argument parsing
    // Too many arguments
    struct string *text = NULL;
    size_t lineCount = 0;
    
    switch (argc){
        case 1:
        {
			text = load_lines(file);
            if(!text){
                die(-1, "Error: allocation failed\n");
            }
            lineCount = line_count(text);
            print_tail_lines(text, lineCount, DEFAULT_COUNT);
            break;
        }
        case 2:
        {
            if (strcmp(argv[1], "-n") == 0)
                die(-1, "Wrong arguments, %s", USAGE);

            file = fopen(argv[1], "r");
            if (!file)
                die(-1, "Couldn't open the file.\n");

            text = load_lines(file);
            if(!text){
                die(-1, "Error: allocation failed\n");
            }
            lineCount = line_count(text);
            print_tail_lines(text, lineCount, DEFAULT_COUNT);
            break;
        }
        case 3:
        {
            if (strcmp(argv[1], "-n") != 0)
                die(-1, "Wrong arguments, %s", USAGE);

            size_t lineArgument = string_to_uint(argv[2]);
            text = load_lines(file);
            if(!text){
                die(-1, "Error: allocation failed");
            }
            lineCount = line_count(text);

            if (argv[2][0] == '+') {
                if (lineCount < lineArgument) {
                    string_free(text);
                    die(-1, "File doesn't have enough lines %s", USAGE);
                }
                print_tail_lines(text, lineCount, lineCount - lineArgument+1);
            } else
                print_tail_lines(text, lineCount, lineArgument);
        }
        break;

        case 4:
        {
            if (strcmp(argv[1], "-n") != 0)
                 die(-1, "Wrong arguments, %s", USAGE);

            file = fopen(argv[3], "r");
            if (!file)
                die(-1, "Couldn't open the file.\n");

            size_t lineArgument = string_to_uint(argv[2]);
            text = load_lines(file);
            if(!text){
                die(-1, "Error: allocation failed");
            }
            lineCount = line_count(text);

            if (argv[2][0] == '+') {
                if (lineCount < lineArgument)
                    die(-1, "Wrong arguments, %s", USAGE);
                print_tail_lines(text, lineCount, lineCount - lineArgument+1);
            } else
                print_tail_lines(text, lineCount, lineArgument);
        }
        break;

        default:
            die(-1, "Incorrect arguments, %s", USAGE);
    }

    string_free(text);
    fclose(file);
    return 0;
}
