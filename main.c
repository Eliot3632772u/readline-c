#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

// Color codes for output
#define GREEN "\033[0;32m"
#define RED "\033[0;31m"
#define BLUE "\033[0;34m"
#define YELLOW "\033[0;33m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define RESET "\033[0m"

void print_header(const char *test_name)
{
    printf("\n" BLUE "╔════════════════════════════════════════════════╗\n");
    printf("║  %-44s  ║\n", test_name);
    printf("╚════════════════════════════════════════════════╝" RESET "\n");
}

void print_test(const char *description)
{
    printf(CYAN "\n▶ %s\n" RESET, description);
}

void print_line(int line_num, char *line)
{
    if (line)
        printf(GREEN "  [Line %d]: %s" RESET, line_num, line);
    else
        printf(YELLOW "  [Line %d]: NULL\n" RESET, line_num);
}

void print_result(int passed)
{
    if (passed)
        printf(GREEN "  ✓ PASS\n" RESET);
    else
        printf(RED "  ✗ FAIL\n" RESET);
}

// Helper function to create test files
void create_test_file(const char *filename, const char *content)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd != -1)
    {
        write(fd, content, strlen(content));
        close(fd);
    }
}

// Test 1: Simple file with multiple lines
void test_basic_file(void)
{
    print_header("TEST 1: Basic File Reading");
    
    create_test_file("test1.txt", "Line 1\nLine 2\nLine 3\n");
    
    print_test("Reading 3 lines from a simple file");
    
    int fd = open("test1.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line;
    int i = 1;
    int success = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        print_line(i, line);
        if (i == 1 && strcmp(line, "Line 1\n") != 0)
            success = 0;
        if (i == 2 && strcmp(line, "Line 2\n") != 0)
            success = 0;
        if (i == 3 && strcmp(line, "Line 3\n") != 0)
            success = 0;
        free(line);
        i++;
    }
    
    print_result(success && i == 4);
    close(fd);
}

// Test 2: File without trailing newline
void test_no_trailing_newline(void)
{
    print_header("TEST 2: No Trailing Newline");
    
    create_test_file("test2.txt", "Line 1\nLine 2\nLine 3");
    
    print_test("Last line should not have \\n");
    
    int fd = open("test2.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line;
    int i = 1;
    int success = 1;
    char *last_line = NULL;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        print_line(i, line);
        if (last_line)
            free(last_line);
        last_line = line;
        i++;
    }
    
    if (last_line)
    {
        success = (strcmp(last_line, "Line 3") == 0);
        free(last_line);
    }
    
    print_result(success);
    close(fd);
}

// Test 3: Empty file
void test_empty_file(void)
{
    print_header("TEST 3: Empty File");
    
    create_test_file("test3.txt", "");
    
    print_test("Should return NULL immediately");
    
    int fd = open("test3.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line = get_next_line(fd);
    print_line(1, line);
    
    print_result(line == NULL);
    close(fd);
}

// Test 4: Single character per line
void test_single_char_lines(void)
{
    print_header("TEST 4: Single Character Lines");
    
    create_test_file("test4.txt", "a\nb\nc\n");
    
    print_test("Each line has only one character plus \\n");
    
    int fd = open("test4.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line;
    int i = 1;
    int success = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        print_line(i, line);
        if (strlen(line) != 2)
            success = 0;
        free(line);
        i++;
    }
    
    print_result(success && i == 4);
    close(fd);
}

// Test 5: Only newlines
void test_only_newlines(void)
{
    print_header("TEST 5: Only Newlines");
    
    create_test_file("test5.txt", "\n\n\n");
    
    print_test("File contains only newline characters");
    
    int fd = open("test5.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line;
    int i = 1;
    int success = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        print_line(i, line);
        if (strcmp(line, "\n") != 0)
            success = 0;
        free(line);
        i++;
    }
    
    print_result(success && i == 4);
    close(fd);
}

// Test 6: Very long line
void test_long_line(void)
{
    print_header("TEST 6: Very Long Line");
    
    char long_str[1001];
    memset(long_str, 'A', 1000);
    long_str[1000] = '\0';
    
    create_test_file("test6.txt", long_str);
    
    print_test("Line with 1000 characters (no newline)");
    
    int fd = open("test6.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line = get_next_line(fd);
    
    printf(GREEN "  [Line 1]: [1000 'A' characters]\n" RESET);
    
    int success = (line != NULL && strlen(line) == 1000);
    print_result(success);
    
    free(line);
    close(fd);
}

// Test 7: Multiple files simultaneously
void test_multiple_fds(void)
{
    print_header("TEST 7: Multiple File Descriptors");
    
    create_test_file("test7a.txt", "File A - Line 1\nFile A - Line 2\n");
    create_test_file("test7b.txt", "File B - Line 1\nFile B - Line 2\n");
    
    print_test("Reading from two files alternately");
    
    int fd1 = open("test7a.txt", O_RDONLY);
    int fd2 = open("test7b.txt", O_RDONLY);
    
    if (fd1 == -1 || fd2 == -1)
    {
        printf(RED "  Error opening files\n" RESET);
        return;
    }
    
    char *line1, *line2;
    int success = 1;
    
    line1 = get_next_line(fd1);
    print_line(1, line1);
    if (!line1 || strcmp(line1, "File A - Line 1\n") != 0)
        success = 0;
    free(line1);
    
    line2 = get_next_line(fd2);
    print_line(2, line2);
    if (!line2 || strcmp(line2, "File B - Line 1\n") != 0)
        success = 0;
    free(line2);
    
    line1 = get_next_line(fd1);
    print_line(3, line1);
    if (!line1 || strcmp(line1, "File A - Line 2\n") != 0)
        success = 0;
    free(line1);
    
    line2 = get_next_line(fd2);
    print_line(4, line2);
    if (!line2 || strcmp(line2, "File B - Line 2\n") != 0)
        success = 0;
    free(line2);
    
    print_result(success);
    
    close(fd1);
    close(fd2);
}

// Test 8: Invalid file descriptor
void test_invalid_fd(void)
{
    print_header("TEST 8: Invalid File Descriptor");
    
    print_test("Reading from fd = -1");
    
    char *line = get_next_line(-1);
    print_line(1, line);
    
    print_result(line == NULL);
}

// Test 9: Stdin simulation (manual test)
void test_stdin_info(void)
{
    print_header("TEST 9: Standard Input (Manual Test)");
    
    printf(YELLOW "\nTo test stdin, run this program manually:\n");
    printf("  echo \"Line 1\\nLine 2\" | ./test_gnl\n");
    printf("Or uncomment the stdin test in main() and type input.\n" RESET);
}

// Test 10: Mixed empty and non-empty lines
void test_mixed_lines(void)
{
    print_header("TEST 10: Mixed Empty and Non-Empty Lines");
    
    create_test_file("test10.txt", "First\n\nThird\n\nFifth\n");
    
    print_test("Alternating empty and non-empty lines");
    
    int fd = open("test10.txt", O_RDONLY);
    if (fd == -1)
    {
        printf(RED "  Error opening file\n" RESET);
        return;
    }
    
    char *line;
    int i = 1;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        print_line(i, line);
        free(line);
        i++;
    }
    
    print_result(i == 6);
    close(fd);
}

int main(void)
{
    printf(MAGENTA "\n");
    printf("╔══════════════════════════════════════════════════════╗\n");
    printf("║                                                      ║\n");
    printf("║         GET_NEXT_LINE COMPREHENSIVE TESTS           ║\n");
    printf("║                                                      ║\n");
    printf("║              Buffer Size: %-4d                      ║\n", BUFFER_SIZE);
    printf("║                                                      ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n");
    printf(RESET);
    
    test_basic_file();
    test_no_trailing_newline();
    test_empty_file();
    test_single_char_lines();
    test_only_newlines();
    test_long_line();
    // test_multiple_fds();
    test_invalid_fd();
    test_mixed_lines();
    test_stdin_info();
    
    printf(MAGENTA "\n╔══════════════════════════════════════════════════════╗\n");
    printf("║                 ALL TESTS COMPLETED!                 ║\n");
    printf("╚══════════════════════════════════════════════════════╝\n" RESET);
    
    printf(YELLOW "\n💡 Tips:\n");
    printf("   - Test with different BUFFER_SIZE values (1, 42, 1000, etc.)\n");
    printf("   - Check for memory leaks with valgrind\n");
    printf("   - Test reading from stdin manually\n");
    printf("   - Verify all test files are created properly\n" RESET);
    
    printf(CYAN "\n📝 To test with different buffer sizes:\n");
    printf("   cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 main.c get_next_line.c get_next_line_utils.c\n");
    printf("   cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 main.c get_next_line.c get_next_line_utils.c\n" RESET);
    
    return 0;
}

/* UNCOMMENT TO TEST STDIN
void test_stdin_real(void)
{
    print_header("TEST: Reading from Standard Input");
    
    printf(YELLOW "Type some lines (Ctrl+D to finish):\n" RESET);
    
    char *line;
    int i = 1;
    
    while ((line = get_next_line(0)) != NULL)
    {
        print_line(i, line);
        free(line);
        i++;
    }
    
    printf(GREEN "\nFinished reading from stdin\n" RESET);
}

// Add test_stdin_real() to main() to test
*/