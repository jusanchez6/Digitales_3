/** 
 * @file main.c
 * @date 14/8/2024
 * @author: Maria Del Mar Arbelaez Sandoval
 * @author: Julian Mauricio Sanchez Ceballos
 * @brief This is a simple program that prints "Hello world, this is suffering" to the console.
 * @brief It also performs some bitwise operations and some simple math operations.
*/


#include <stdio.h>

#define PI (3.1416)

int x = 5;	//0000 0101

int a = 4;	//0000 0100
int b = 5;  //0000 0101


int func1 (int, float);
float func2 (int, float);


int main (void) {
	printf("Hello world, this is suffering \n");
	printf("the entire value is: %d \n", func1(x, PI));
	printf("the entire float is: %f \n \n \n", func2(x, PI));

	printf("bitwise operations \n \n");
	printf("AND between a and b is: %d \n", a&b);
	printf("OR between a and b is: %d \n", a|b);
	printf("XOR between a and b is: %d \n", a^b);
	printf("NOT of a is: %d \n", ~a);
	printf("left shift of a is: %d \n", a<<1);
	printf("right shift of a is: %d \n", a>>1);


	return 0;

}

int func1 (int a, float b){
	return a*(int)b;
}

float func2 (int a, float b){
	return (float)a*b;
}