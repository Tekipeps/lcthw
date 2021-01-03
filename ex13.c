#include <stdio.h>

int main(int argc, char *argv[]){
  if(argc < 2){
    printf("ERROR: You need at least one argument .\n");
    return 1;
  }
  for(unsigned int j = 1; j < argc; j++){
    char letter;
    for(unsigned int i = 0; letter = argv[j][i], argv[j][i] != '\0'; i++){
      if(letter > 64 && letter < 91){
        letter += 32;
      }
      if(letter == 'a'){
          printf("%d: 'A'\n", i);
      } else if (letter == 'e') {
          printf("%d: 'E'\n", i);
      } else if (letter == 'i') {
          printf("%d: 'I'\n", i);
      } else if (letter == 'o') {
          printf("%d: 'O'\n", i);
      } else if (letter == 'u') {
          printf("%d: 'U'\n", i);
      } else if (letter == 'y') {
          if(i > 2) {
            // it's only sometimes Y
            printf("%d: 'Y'\n", i);
          }
      } else {
          printf("%d: %c is not a vowel\n", i, letter);
      }
    }
    printf("\t...\t\n");
  }
  return 0;
}
