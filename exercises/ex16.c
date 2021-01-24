#include <stdio.h> // include the standard input/output library
#include <assert.h> // include the assert function for debugging
#include <stdlib.h>
#include <string.h>

struct Person { // create a Person struct
  char *name; // property name string
  int age; // property age int
  int height; // property height int
  int weight; // property height int
};

struct Person *Person_create(char *name, int age, int height, int weight){ //Person_create funtion
  struct Person *who = malloc(sizeof(struct Person)); // create memory space for person
  assert(who != NULL); // make sure who is valid memory space
  who->name = strdup(name); // duplicate the string for name and add it to the structure
  // to make sure the structure actually owns it
  who->age = age;  // add the age to the structure
  who->height = height; // add the height to the structure
  who->weight = weight; // add the weight to the stucture

  return who; // return the address to the structure
}

void Person_destroy(struct Person *who){ // function to destroy person struct i.e cleanup from memory
  assert(who != NULL); // ensure who is a defined pointer
  free(who->name); // free the memory created for name using the strdup()
  free(who); // free the memory created for the struct using malloc()
}
void Person_print(struct Person *who){ // display the details of person
  printf("Name: %s\n", who->name); // print the name
  printf("\tAge: %d\n", who->age); // print the age
  printf("\tHeight: %d\n", who->height); // print the height
  printf("\tWeight: %d\n", who->weight); // print the weight
}

int main(int argc, char *argv[]){
  // make two people structures
  struct Person *joe = Person_create("Joe Alex", 32,64,140); // create a person struct joe
  struct Person *frank = Person_create("Frank Blank",20,72,180); // create a person struct frank

  printf("Joe is at memory location %p\n", joe); // print the memory location of joe
  Person_print(joe); // print the properties of joe
  printf("Frank is at memory location %p\n", frank); // print the memory location of frank
  Person_print(frank); // print the properties of frank

  // make everyone 20 years and print them again
  joe->age += 20;
  joe->height -= 2;
  joe->weight += 40;
  Person_print(joe);

  frank->age += 20;
  frank->weight += 20;
  Person_print(frank);

  //destroy both of them so we clean up
  Person_destroy(joe);
  Person_destroy(frank);

  return 0;
}
