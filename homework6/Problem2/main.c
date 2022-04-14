#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>


int MAX_SIZE = 64000;//Maximum size of the array
int NTHREAD;//number of thread
int intialize_array(int array[]);//Randomlize assign each element of the array
int printArray(int array[]);//Print out the array
int check_arg(char * array[]);//Check argv to make sure that it correct
void * bubble_sort(void * array);//do the Bubble sort
int check_sort(int array[]);//Check if the sorting is done correctly
void sort(int array[]);//Sort the array again after all the thread have sort

int main(int argc, char * argv[]){
	//Check for if there enough arguement and check if the arguement is valid
	if(argc == 1){
		printf("Missing arguement. \n");
		return 0;
	}
	else if(argc >= 4){
		printf("Too many arguement. \n");
		return 0;
	}
	int error_check = check_arg(argv);
	if(error_check == 0){
		return 0;
	}
//////////////////////////////////////////
//	create the Srand() seed for rand() to be use
//	initialize the array with the initialize_array()
//	create the array of thread then start up the clock to keep track of how long it take the threads to sort
//  create nth thread that the user enter in and then join them back
//  after that go through the sort again to join back all the partition array 
	int temp = atoi(argv[2]);
	NTHREAD = temp;
	srand(temp);
	int integer_array[MAX_SIZE];	
	intialize_array(integer_array);
	pthread_t threadArray[temp];	
	int rc;
	clock_t t;
	t = clock();
	int offset = MAX_SIZE / temp;
	for(int i = 0;i < temp;i++){
		rc = pthread_create(&threadArray[i],NULL,&bubble_sort,(void*)(integer_array + (offset * i)));
		if(rc != 0){
			printf("Error in creating Thread #%d. \n",i);	
		}
	}	
	for(int j = 0;j < temp;j++){
		rc = pthread_join(threadArray[j],NULL);
		if(rc  != 0){
			printf("Error in joining Thread #%d. \n",j);
		}
	}
	sort(integer_array);		
	t = clock() - t;
	double time_taken = ((double)t)/CLOCKS_PER_SEC;
//  go through the array to make sure that the array have been sort
	int check = check_sort(integer_array);
	if(check == 1){
		printf("Sorted complete.\n");
	}
	else{
		printf("error in sorting.\n");
	}
	printf("It take %f s to sort. \n",time_taken);
	return 0;
}
/**
*sort() - sort through the array 
*
*This function will go through the array that already been sort by the thread and it will resort it again
*to make sure that nothing wrong with the array. It will perform bubble sort again.
*
*@param array[] - the integer array
*
*
**/
void sort(int array[]){
	int size = MAX_SIZE;
	int temp;
	for(int i = 0; i < size - 1;i++){
		for(int j = 0;j < size - i - 1;j++){
			if(array[j] > array[j + 1]){
				temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
} 
/**
*check_sort() - check to see if the array is sort
*
*This function will go through the array to check to see if the array have 
*been sort correctly. It will return a 1 if all the element have been sort and 
*0 if there an element at index i + 1 is bigger at the current index.
*
*@param array[] - the array that hold the integer
*
**/
int check_sort(int array[]){
	for(int i = 0;i < MAX_SIZE - 1;i++){	
		if(array[i] > array[i + 1])
			return 0;
	}
	return 1;
}
/**
*initialize_array() - randomlize all the element in the array
*
*This function will loop through each of the array element and then 
*randomly assign a random number to the element.
*
*@param array[] - the array that hold the integer
*
**/
int intialize_array(int array[]){
	for(int i = 0; i < MAX_SIZE;i++){
		array[i] = rand() % 200;
	}
	return 1;
}
/**
*printArray() - print out the array element
*
*This function will go loop through the array and print out the element that is in the 
*array
*
*@param array[] - the array that hold the integer
*
**/
int printArray(int array[]){
	for(int i = 0; i < MAX_SIZE;i+=5){
		printf("%d, %d, %d, %d, %d \n",array[i], array[i + 1], array[i + 2],  array[i + 3],array[i + 4]);
	}
	return 1;
}
/**
*check_arg() - check the arguement
*
*This function will check the arguement to see if the user have enter in
*a valid arguement before running the program
*
*@param array[] - The array that hold the integer
**/
int check_arg(char * array[]){
	char * ptr1;
	char * ptr2;
	int ret = strtol(array[1],&ptr1,10);
	int ret2 = strtol(array[2],&ptr2,10);
	if(*ptr1 != '\0'){
		printf("Error in the first arguement, receive %s .\n",array[1]);
		return 0;
	}	
	if(*ptr2 != '\0'){
		printf("Error in the second arguement, receive %s .\n",array[2]);
		return 0;
	}
	return ret + ret2;
}
/**
*bubble_sort() - bubble sort function that will sort the data with bubble sort method
*
*This function will perform the bubble sort method and it going to be use by
*the thread that going to be create by the program.
*
*@param array - the pointer to the array of integer
*
**/
void * bubble_sort(void * array){
	int size = MAX_SIZE/NTHREAD;
	int temp;
	int * arr = (int*) array;
	for(int i = 0; i < size - 1;i++){
		for(int j = 0;j < size - i - 1;j++){
			if(arr[j] > arr[j + 1]){
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
	return NULL;
}





















