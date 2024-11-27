#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

#include "custom_asserts.h"
#include "tree.h"
#include "akinator.h"
#include "DataBase.h"
#include "debug_macros.h"

static const char defult_filename[] = "DataBase/default.json";


TYPE_OF_ERROR SetDataBase(Akinator* akinator, int argc, char** argv) {
    check_expression(akinator, POINTER_IS_NULL);

    system("mkdir -p DataBase");

    ProcessFilenames(argc, argv, &(akinator->input_data_base), &(akinator->output_data_base));

    return SUCCESS;
}


TYPE_OF_ERROR ProcessFilenames(int argc, char** argv, char** input_filename,
                             char** output_filename) {
    check_expression(input_filename,  POINTER_IS_NULL);
    check_expression(output_filename, POINTER_IS_NULL);

    if(argc == 3)
    {
        ProcessFlag(1, argv, input_filename, output_filename);
    }
    else if(argc == 5)
    {
        ProcessFlag(1, argv, input_filename, output_filename);
        ProcessFlag(3, argv, input_filename, output_filename);
    }
    if(*input_filename == NULL)
    {
        SetDefaultFilename(input_filename, defult_filename);
    }
    if(*output_filename == NULL)
    {
        SetDefaultFilename(output_filename, defult_filename);
    }

    return SUCCESS;
}

TYPE_OF_ERROR ProcessFlag(size_t number_of_flag, char** argv,
                           char** input_filename, char** output_filename) {
    if(strcmp(argv[number_of_flag], "--input") == 0)
    {
        size_t size_of_filename = strlen(argv[number_of_flag + 1]);
        *input_filename         = (char*)calloc(size_of_filename, sizeof(char));

        warning(*input_filename, CALLOC_ERROR);

        strcpy(*input_filename, argv[number_of_flag + 1]);
    }
    else if(strcmp(argv[number_of_flag], "--output") == 0) //TODO Consts
    {
        size_t size_of_filename = strlen(argv[number_of_flag + 1]);
        *output_filename        = (char*)calloc(size_of_filename, sizeof(char));

        warning(*output_filename, CALLOC_ERROR);

        strcpy(*output_filename, argv[number_of_flag + 1]);
    }

    return SUCCESS;
}

TYPE_OF_ERROR SetDefaultFilename(char** filename, const char* defult_filename) {
    size_t size_of_filename = strlen(defult_filename);
    *filename               = (char*)calloc(size_of_filename + 1, sizeof(char));

    warning(*filename, CALLOC_ERROR);

    strcpy(*filename, defult_filename);
    // strcat(*filename, "\0");

    return SUCCESS;
}

TYPE_OF_ERROR InstallDataBase(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    FILE* input_file              = NULL;
    char filename[MAX_VALUE_SIZE] = "";

    printf("Из какого файла считать базу?\n");
    scanf("%s", filename);
    input_file = fopen(filename, "r");
    while(!input_file) {
        printf("Такого файла нет, попробуй ещё раз:\n");
        scanf("%s", filename);
        input_file = fopen(filename, "r");
    };
    fclose(input_file);

    size_t size_of_filename   = strlen(filename);
    memset(akinator->input_data_base, 0, strlen(akinator->input_data_base));
    akinator->input_data_base = (char*)realloc(akinator->input_data_base, size_of_filename * sizeof(char));

    warning(akinator->input_data_base, CALLOC_ERROR);

    strcpy(akinator->input_data_base, filename);

    ReadDataBase(akinator);

    return SUCCESS;
}

TYPE_OF_ERROR UpdateDataBase(Akinator* akinator) {
    check_expression(akinator, POINTER_IS_NULL);

    FILE* data_base = fopen(akinator->output_data_base, "w");
    warning(data_base, FILE_OPEN_ERROR);

    PrintDataBase(data_base, akinator->tree->root);

    fclose(data_base);

    return SUCCESS;
}

TYPE_OF_ERROR PrintDataBase(FILE* data_base, TreeNode<char*>* node) {
    if(!node) return SUCCESS;

    fprintf(data_base, "{\"%s\"", node->value);
    if(node->left ) PrintDataBase(data_base, node->left);
    if(node->right) PrintDataBase(data_base, node->right);

    fprintf(data_base, "}");

    return SUCCESS;
}

TYPE_OF_ERROR ReadDataBase(Akinator* akinator) {

    FILE* input_file = fopen(akinator->input_data_base, "r");
    warning(input_file, FILE_OPEN_ERROR);

    struct stat buf = {};
    int stat_value_check = stat(akinator->input_data_base, &buf);
    size_t size_of_buffer = (size_t)buf.st_size;

    char* buffer = (char*)calloc(size_of_buffer + 1, sizeof(char));
    warning(buffer, CALLOC_ERROR);

    fread(buffer, sizeof(char), size_of_buffer, input_file);

    fclose(input_file);

    char* begin = buffer;
    char* end = NULL;
    begin = strchr(begin, '"') + 1;
    end   = strchr(begin, '}');
    *(strchr(begin, '"')) = '\0';
    TreeInit(akinator->tree, begin);

    begin = strchr(strchr(begin, '\0') + 1, '{');

    ProcessBuffer(akinator, akinator->tree->root, LEFT_SIDE, begin, end);

    TreeDump(akinator->tree);

    return SUCCESS;
}

TYPE_OF_ERROR ProcessBuffer(Akinator* akinator, TreeNode<char*>* node, int side, char* begin, char* end) {
    check_expression(akinator, POINTER_IS_NULL);
    if(!node ) return          POINTER_IS_NULL;
    if(!begin) return          POINTER_IS_NULL;
    if(!end  ) return          POINTER_IS_NULL;

    if((end > (strchr(begin, '"') + 1)) && (strchr(begin, '"') != NULL)) {
        begin = strchr(begin, '"') + 1;
        if(*strchr(begin, '"')) {
            *(strchr(begin, '"')) = '\0';
        }
        AddNode(node, begin, side);
        begin = strchr(begin, '\0') + 1;
        if(node->right) {
            ProcessBuffer(akinator, node->right, LEFT_SIDE, begin, end);
            return SUCCESS;
        }
        else {
            ProcessBuffer(akinator, node->left, LEFT_SIDE, begin, end);
            return SUCCESS;
        }
    }
    end = strchr(end + 1, '}');

    ProcessBuffer(akinator, node->parent, RIGHT_SIDE, begin, end);

    return SUCCESS;
}
