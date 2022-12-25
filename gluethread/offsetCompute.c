#include <stdio.h>

typedef struct emp_ {
	char name[30];//30 bytes //offset = 0
	unsigned int salary;//4 bytes //offset = 30
	char designation[30];//30 bytes //offset = 34
	unsigned int emp_id;//4 bytes //offset = 64
}emp_t;

#define offset(struct_name, field_name) ((unsigned int)&(((struct_name *)0)->field_name))
//zero is casted to the type of the structure. i.e., 0 is the address of the structure variable

int main() {
	//Write a C macro which computes the offset of a given field in a given C structure?
	printf("0 = %d\n30 = %d\n34 = %d\n64 = %d\n",offset(emp_t, name),offset(emp_t, salary),offset(emp_t, designation),offset(emp_t, emp_id));
}
