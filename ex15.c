#include <stdio.h>

int main(int argc, char *argv[]){
  // create two arrays
  int ages[] = {23, 43, 12, 89, 2};
  char *names[] = {"Alan", "Frank", "Tekipeps", "Lisa", "John"};
  // safely get the size of ages
  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  // using indexing
  for (i =0; i < count; i++){
    printf("%s has %d years to live. \n", names[i], ages[i]);
  }
  printf("---\n");

  //setup the pointer to the start of the array
  int *cur_age = ages;
  int **cur_name = names;

  for(i = 0; i < count; i++){
    printf("%s is %d years old. \n", *(cur_name+i), *(cur_age+i));
  }
  printf("---\n");

  // third way, pointer are just arrays
  for (i = 0; i < count; i++){
    printf("%s is %d years old again .\n", cur_name[i], cur_age[i]);
  }
  printf("---\n");

  // fourth way with pointer in a stupid complex way
  for(cur_name=names, cur_age=ages; (cur_age-ages) < count; cur_name++, cur_age++){
    printf("%s lived %d years so far.\n", *cur_name, *cur_age);
  }
  return 0;
}
