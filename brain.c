#include <stdio.h>
#include <unistd.h>

//translate the brainfuck code to c
void translate(FILE * fp){
  FILE * fpc;
  int c;
  fpc = fopen("out.c", "w");
  fputs("#include <stdio.h>\n", fpc);
  fputs("int main(){\n", fpc);
  fputs("char array[9000] = {0};\n", fpc);
  fputs("char *ptr=array;\n", fpc);
  while((c =fgetc(fp))!= EOF){
    switch(c){
      case '>': fputs("++ptr;\n", fpc);
                break;
      case '<': fputs("--ptr;\n", fpc);
                break;
      case '+': fputs("++*ptr;\n", fpc);
                break;
      case '-': fputs("--*ptr;\n", fpc);
                break;
      case '.': fputs("putchar(*ptr);\n", fpc);
                break;
      case ',': fputs("*ptr=getchar();\n", fpc);
                break;
      case '[': fputs("while(*ptr){\n", fpc);
                break;
      case ']': fputs("}\n", fpc);
                break;
      default :
                break;
    }
  }
  fputs("}", fpc);
  fclose(fpc);
  fclose(fp);
}

//executes the c compiler with the translated c file
void compile(char * filename){
  char * args[3];
  args[0] = "gcc";
  args[1] = filename;
  args[2] = NULL;
  pid_t pid = fork();
  if(pid == 0)
    execvp(args[0], args);
}

int main(int argc, char * argv[]){
  if(argc < 2){
    printf("Usage: %s [filename]\n", argv[0]);
    return -1;
  }
  FILE * fp;
  fp = fopen(argv[1], "r");
  translate(fp);
  compile("out.c");
  return 0;
}
