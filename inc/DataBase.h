#ifndef DATABASE_H_
#define DATABASE_H_

TYPE_OF_ERROR UpdateDataBase    (Akinator* akinator);
TYPE_OF_ERROR SetDataBase       (Akinator* akinator, int argc, char** argv);
TYPE_OF_ERROR ProcessFilenames  (int argc, char** argv, char** input_filename,
                                 char** output_filename);
TYPE_OF_ERROR ProcessFlag       (size_t number_of_flag, char** argv,
                                 char** input_filename, char** output_filename);
TYPE_OF_ERROR PrintDataBase     (FILE* data_base, TreeNode<char*>* node);
TYPE_OF_ERROR SetDefaultFilename(char** filename, const char* defult_filename);
TYPE_OF_ERROR ReadDataBase      (Akinator* akinator);
TYPE_OF_ERROR InstallDataBase   (Akinator* akinator);
TYPE_OF_ERROR ProcessBuffer     (Akinator* akinator, TreeNode<char*>* node, int side, char* begin, char* end);

#endif
