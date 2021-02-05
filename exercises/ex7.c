#include <stdio.h>

int main(int argc, char *argv[])
{
  int bugs = 100;
  double bug_rate = 1.2;

  printf("You have %d bugs at an imaginary rate of %f.\n", bugs, bug_rate);

  long universe_of_defect = 1L * 1024L * 1024L * 1024L * 1024L * 1024L * 1024L;
  printf("The entire universe has %ld bugs.\n", universe_of_defect);

  double expected_bugs = bugs * bug_rate;
  printf("You are expected to have %f bugs..\n", expected_bugs);

  double part_of_the_universe = expected_bugs / universe_of_defect;
  printf("This is only %e portion of the universe.\n", part_of_the_universe);

  char nul_byte = '\0';
  int care_percentage = bugs * nul_byte;
  printf("Which means you should care %d%%.\n", care_percentage);

  // printf("\nnul_byte: %%c -> %c; %%d -> %d; %%s -> %s\n", nul_byte, nul_byte, nul_byte);

  return 0;
}