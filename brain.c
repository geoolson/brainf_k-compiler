#include <stdio.h>

void foo(FILE * fp){
  FILE * fpc;
  int c;
  fpc = fopen("brains.c", "w");
  fputs("#include <stdio.h>\n", fpc);
  fputs("int main(){\n", fpc);
  fputs("char array[9000] = {0};\n", fpc);
  fputs("char *ptr=array;\n", fpc);
  while((c =fgetc(fp))!= EOF){
    switch(c){
      case '>': fputs("++ptr;", fpc);
                break;
      case '<': fputs("--ptr;", fpc);
                break;
      case '+': fputs("++*ptr;", fpc);
                break;
      case '-': fputs("--*ptr;", fpc);
                break;
      case '.': fputs("putchar(*ptr);", fpc);
                break;
      case ',': fputs("*ptr=getchar();", fpc);
                break;
      case '[': fputs("while(*ptr){", fpc);
                break;
      case ']': fputs("}", fpc);
                break;
      default :
                break;
    }
  }
  fputs("}", fpc);
}

int main(int argc, char * argv[]){
  if(argc < 2){
    printf("Usage: %s [filename]\n", argv[0]);
    return -1;
  }
  FILE * fp;
  fp = fopen(argv[1], "r");
  foo(fp);
  return 0;
}
