/**
 * @file tail.cc
 * @author Karel Hajek 
 * @login xhajek48 (VUT FIT)
 * @version 0.1
 * @date 2019-04-02
 * 
 * g++ -std=c++11 -pedantic -Wall priklad.cc
 */
#include <iostream>
#include <fstream>
#include <vector>   // vector
#include <stdarg.h> 
#include <cstring>

// Default line count to print
#define DEFAULT_COUNT 10

const char *USAGE = "Usage: tail [OPTION] [FILE]\n";

/**
 * @brief Variadic function that prints
 *        a message and exits the program
 *
 * @param exitCode
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
 * @brief Loads all lines from a file into a vector
 * 
 * @param file 
 * @return std::vector<std::string> 
 */
std::vector<std::string> load_lines(std::istream &file) {
    std::vector<std::string> text;
    std::string line;

	while (std::getline(file, line)) {
        line.append("\n");
        text.push_back(line);
    }
    return text;
}

/**
 * @brief Prints last N lines from text
 * 
 * @param text 
 * @param n    Number of lines to print
 */
void print_tail_lines(std::vector<std::string> text, const size_t n) {
    // if there isn't enough lines, print them all
    size_t totalCount = text.size();

    if (totalCount < n) {
        for (size_t i = 0; i < totalCount; i++) {
            std::cout << text[i];
        }
    } else {
        for (size_t i = totalCount - n; i < totalCount; i++) {
            std::cout << text[i];
        }
    }
}

/**
 * @brief Converts string to uint, if error - exits program
 * @param str String to convert
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
    std::ifstream file;
    // Argument parsing
    // Too many arguments
    std::vector<std::string> text;
    switch (argc){
        case 1:
        {
		    text = load_lines(std::cin);
            print_tail_lines(text, DEFAULT_COUNT);
            break;
        }
        case 2:
        {
            if (strcmp(argv[1], "-n") == 0)
            die(-1, "Wrong arguments, %s", USAGE);

            file.open(argv[1], std::fstream::in);
            if (!file)
              die(-1, "Couldn't open the file.\n");

            std::vector<std::string> text = load_lines(file);
            print_tail_lines(text, DEFAULT_COUNT);
            break;
        }

        case 3:
        {
            if (strcmp(argv[1], "-n") != 0)
            die(-1, "Wrong arguments, %s", USAGE);

            size_t lineArgument = string_to_uint(argv[2]);
            std::vector<std::string> text = load_lines(std::cin);
            if (argv[2][0] == '+') {
                if (text.size() < lineArgument)
                    die(-1, "Wrong arguments, %s", USAGE);
                print_tail_lines(text, text.size() - lineArgument);
            } else
            print_tail_lines(text, lineArgument);
            
            break;
        }

        case 4:
        {
            if (strcmp(argv[1], "-n") != 0)
            die(-1, "Wrong arguments, %s", USAGE);

            file.open(argv[3], std::fstream::in);
            if (!file)
                die(-1, "Couldn't open the file.\n");

            size_t lineArgument = string_to_uint(argv[2]);
            std::vector<std::string> text = load_lines(file);

            if (argv[2][0] == '+') {
                if (text.size() < lineArgument)
                    die(-1, "Wrong arguments, %s", USAGE);
                print_tail_lines(text, text.size() - lineArgument);
            } else
                print_tail_lines(text, lineArgument);
            
            break;
        }

        default:
            die(-1, "Incorrect arguments, %s", USAGE);
    }
    file.close();
    return 0;
}
