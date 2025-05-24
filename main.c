#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/types.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef enum { PREPARE_SUCCESS, PREPARE_UNRECOGNIZED_STATEMENT } PrepareResult;
typedef enum { STATEMENT_INSERT, STATEMENT_SELECT } StatementType;
typedef enum { META_COMMAND_SUCCESS, META_COMMAND_UNRECOGNIZED_COMMAND } MetaCommandResult;

typedef struct{
  char * buffer;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

typedef struct {
  StatementType type;
} Statement;

void print_prompt() {
  printf("db > "); 
}

void close_input_buffer(InputBuffer * input_buffer){
  free(input_buffer->buffer);
  free(input_buffer);
}
InputBuffer * new_input_buffer(){
  InputBuffer * input_buffer = (InputBuffer *)malloc(sizeof(InputBuffer));
  input_buffer->buffer_length = 0;
  input_buffer->input_length = 0;
  char * buffer = NULL;
  return input_buffer;
}

InputBuffer * read_input(){
  InputBuffer* input_buffer = new_input_buffer();
  ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    
    if(bytes_read <= 0){
      perror("Error Reading input\n");
      exit(EXIT_FAILURE);
    }
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;

    return input_buffer;
}


void execute_statement(Statement* statement) {
  FILE* file;
  switch (statement->type) {
    case (STATEMENT_INSERT):
      file = fopen("./data/data.txt", "a");
      fputs("wrote to the database!\n", file);
      printf("Check database!");
      break;
    case (STATEMENT_SELECT):
      file = fopen("./data/data.txt", "r");
      char * buffer = (char*)malloc(255);
      fgets(buffer, 255, file);
    size_t bytes_written = fwrite(buffer, 1, strlen(buffer), stdout);
      break;
  }
    fclose(file);
}

PrepareResult prepare_statement(InputBuffer* input_buffer, Statement* statement) {
 if (strncmp(input_buffer->buffer, "insert", 6) == 0) {
    statement->type = STATEMENT_INSERT;
    return PREPARE_SUCCESS;
  }
  if (strcmp(input_buffer->buffer, "select") == 0) {
    statement->type = STATEMENT_SELECT;
    return PREPARE_SUCCESS;
  }

  return PREPARE_UNRECOGNIZED_STATEMENT;
}

MetaCommandResult do_meta_command(InputBuffer* input_buffer) {
  if (strcmp(input_buffer->buffer, ".exit") == 0) {
    exit(EXIT_SUCCESS);
  } else {
    return META_COMMAND_UNRECOGNIZED_COMMAND;
  }
}

void excute_command(InputBuffer * input_buffer){

}


int main(int argc, char** argv){
  while(TRUE){
    print_prompt();
    InputBuffer * input_buffer = read_input();

    if (input_buffer->buffer[0] == '.') {
      switch (do_meta_command(input_buffer)) {
              case (META_COMMAND_SUCCESS):
            continue;
          case (META_COMMAND_UNRECOGNIZED_COMMAND):
            printf("Unrecognized command '%s'\n", input_buffer->buffer);
            continue;
        }
      }

    Statement statement;
    switch (prepare_statement(input_buffer, &statement)) {
      case (PREPARE_SUCCESS):
        break;
      case (PREPARE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized keyword at start of '%s'.\n",
                input_buffer->buffer);
        continue;
    }

    execute_statement(&statement);
  }
}