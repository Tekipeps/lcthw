#include <stdio.h>

int main(int argc, char *argv[]) {
  int numbers[4] = {0};
  char name[4] = {'a'};

  // first print them out raw
  printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2],
         numbers[3]);
  printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
  printf("name: %s\n", name);

  numbers[1] = 1; /* setup numbers */
  numbers[2] = 2;
  numbers[3] = 3;

  name[0] = 'T'; /* setup numbers */
  name[1] = 'k';
  name[2] = 'S';

  // print them out initialized
  printf("numbers: %d %d %d %d\n", numbers[0], numbers[1], numbers[2],
         numbers[3]);
  printf("name each: %c %c %c %c\n", name[0], name[1], name[2], name[3]);
  printf("name: %s\n", name); /* print name as a string */

  // another way to use name
  char *anotherName = "Tks";
  printf("Another name: %s\n", anotherName);
  printf("Another name each: %c %c %c %c\n", anotherName[0], anotherName[1],
         anotherName[2], anotherName[3]);
  return 0;
}