#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define  MAX_NAME 256
#define TABLE_SIZE 1

typedef struct person{
    char name[MAX_NAME];
    int age;
    struct person * next;
    // ..other stuff
} person;

person * hash_table[TABLE_SIZE];

void init_hash_table(){
    for(int i = 0;i < TABLE_SIZE;i++){
        hash_table[i] = NULL;
    }
}
void print_hash_table(){
    person * actual_node;
    person * next_node;
    puts("----------------------------------");
    for(int i = 0 ; i<TABLE_SIZE ; i++){
            actual_node = hash_table[i];
            if(actual_node == NULL){
                printf("\t %i\t---\n",i);
            }
            else{
                printf("\t %i \t %s ---",i,actual_node -> name);
                next_node = actual_node -> next;
                while(next_node != NULL){
                printf("%s---",next_node -> name);
                next_node = next_node -> next;
            }
            puts("\n");
            }
      }
    puts("----------------------------------");
}

unsigned int hash(char *name){
    int length = strnlen(name,MAX_NAME);
    unsigned int hash_value = 0;
    for(int i = 0 ; i < MAX_NAME ; i++){
       hash_value += name[i];
       hash_value = hash_value * name[i] % TABLE_SIZE; }
    return hash_value;
}

bool insert_hash_table(person * p){
    if (p == NULL ) return false;
    int index = hash(p->name);
    person * actual_node = hash_table[index];
    printf("%s add:%p\n",hash_table[index] -> name ,hash_table[index]);
    p -> next = actual_node;
    hash_table[index] = p;
    return true;
}

person* search_hash_table(char* name){
    if(name ==  NULL) return NULL;
    int index = hash(name);
    person * actual_node = hash_table[index];
    while(actual_node != NULL){
        if(strcmp(actual_node -> name,name) == 0 ) return actual_node;
        actual_node = actual_node -> next;
    };
    return NULL;
}

person* delete_item_hash_table(char* name){
    if(name == NULL) return NULL;
    int index = hash(name);
    person * actual_node = hash_table[index];
    person * next_node = hash_table[index]-> next;
    person * prev_node = NULL;
    while(actual_node != NULL){
        if(strcmp(actual_node -> name ,name) == 0){
            person * eliminated_node = actual_node;
            if(prev_node  == NULL){
                actual_node = next_node;
                return eliminated_node;
            }
            prev_node -> next = next_node;
            return eliminated_node;
        }
    }
    return NULL;
}

int main (){
  init_hash_table();
  print_hash_table();
  person jhon = {.name="Jhon",.age=49};
  person matilda  = {.name="Matilda",.age=20};
  person matilda1 = {.name="Matilda1",.age=20};
  person matilda2 = {.name="Matilda2",.age=20};
  person matilda3 = {.name="Matilda3",.age=20};
  person matilda4 = {.name="Fuck",.age=20};
  //insert_hash_table(NULL);
  insert_hash_table(&matilda);
  insert_hash_table(&matilda1);
  insert_hash_table(&matilda3);
  insert_hash_table(&jhon);
  insert_hash_table(&matilda2);
  insert_hash_table(&matilda4);
  print_hash_table();
  person* a = search_hash_table("Jhon");
  printf("persona found %s",a ->name);
  return 10;
}
