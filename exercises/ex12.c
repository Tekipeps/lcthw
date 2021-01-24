#include <stdio.h>

int main(int argc, char *argv[]){
  int i = 0;
  if(argc == 1) {
    printf("%s\n", "You have only no arguement. You suck.");
  } else if(argc == 2){
    printf("%s\n", "You have only one argument, You suck.");
  } else if (argc > 1 && argc < 4){
    printf("Here's your arguements:\n");
    for(i = 1; i < argc; i++){
      printf("%s ", argv[i]);
    }
    puts("");
  } else {
    printf("%s\n", "You have too many arguements. You suck. \n");
  }

  return 0;
}
