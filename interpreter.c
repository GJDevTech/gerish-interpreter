#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct Variable{
    
    int value;
    struct Variable *next_variable;
}Variable;

typedef struct Token{

    char *token;
    struct Token *next_token;
}Token;

typedef struct Line{

    struct Line *prev_line;
    int line_num;
    Token *tokens;
    struct Line *next_line;
}Line;

Token *tokenize(char *line){

}

void addLine(Line **lines, char *line){

    printf("%s\n", line);

    // Line *newLine = (Line*) malloc(sizeof(Line));

    // if ((*lines) == NULL){
    //     newLine->prev_line = NULL;
    //     newLine->line_num = 0;
    //     newLine->tokens = tokenize(line);
    //     newLine->next_line = (*lines);
    // }

}

void setLines(Line **lines, char *script){

    int buffer_size = 128;
    char *line = (char*) malloc(buffer_size * sizeof(char));
    int j = 0;

    for (int i = 0; script[i] != '\0'; i++){

        if (script[i] == '\n' || script[i] == ';' || script[i] == '{'){

            if (j > 0) {
                line[j] = '\0';
                addLine(lines, line);
            }
            free(line);
            buffer_size = 128;
            line = (char*) malloc(buffer_size * sizeof(char));
            j = 0;            
        }
        else {
            if (j >= buffer_size - 1) {
                buffer_size *= 2;
                line = (char*) realloc(line, buffer_size * sizeof(char));
            }
            line[j] = script[i];
            j++;
        }
    }

    if (j > 0) {
        line[j] = '\0';
        addLine(lines, line);
    }

    free(line);
}

char *readFile(char *file){

    FILE *f = fopen(file, "r");

    if (f == NULL){
        perror("Error opening file");
        return NULL;
    }

    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    char *string = malloc(fsize + 1);
    fread(string, fsize, 1, f);
    fclose(f);

    string[fsize] = 0;

    return string;
}

int main(int argc, char* argv[]){

    char *script = readFile(argv[1]);

    if (script == NULL){
        return 1;
    }
    
    printf("%s\n\n", script);

    Line *lines;
    
    setLines(&lines, script);

    free(script);

    return 0;
}