#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* str = (char*)calloc(100, 1);

    FILE* file = fopen("DataBase/default.json", "r");

    struct stat buf = {};

    int stat_value_check = stat("DataBase/default.json", &buf);

    size_t size_of_buffer = (size_t)buf.st_size;

    printf("%lu\n", size_of_buffer);

    fread(str, 1, size_of_buffer, file);
    printf("%s\n", str + 12);
    str[12] = '\0';
    str = strchr(str, '"') + 1;
    printf("%p\n", str);
    str = strchr(str, '"') + 1;
    printf("%p\n", str);
    str = strchr(str, '"') + 1;
    printf("%p\n", str);
}
