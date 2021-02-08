#include <stdio.h>
#include <stdlib.h>

void linear_search(int len, int *arr, int num) {
  for (int i = 0; i < len; i++) {
    if (arr[i] == num) {
      printf("%d is found at position %d\n", num, i + 1);
    }
  }
}

int main(int argc, char *argv[]) {
  int arr[argc - 1];

  printf("[ ");
  for (int i = 0; i < argc - 1; i++) {
    arr[i] = atoi(argv[i + 1]);
    printf("%d ", arr[i]);
  }
  printf("]");

  printf("\nEnter the number you want to search: ");
  int num;
  scanf("%d", &num);

  linear_search((argc - 1), arr, num);

  return 0;
}