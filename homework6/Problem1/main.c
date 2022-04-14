#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<pthread.h>


/**
*print_threadID() - print out the ID of the thread
*
*This function will print out the ID of the Thread
*
*@param Var - main processer ID
*/
void*print_threadID(void * var){
	int id = pthread_self();
	printf("This thread #%ld ID is #%u \n",(long)var,id);
	pthread_exit(NULL);
	return NULL;
}
int main(int argc, char * argv[]){
	//check the arguement to see if it correct
	if(argc <= 1){
		printf("too little arguement. \n");
		return 0;
	}
	else if(argc >= 3){
		printf("too many arguement. \n");
		return 0;
	}
	//set the number thread
	int number_childs = atoi(argv[1]);
	if(number_childs > 8 || number_childs < 1){
		printf("Invalid number. \n");
		return 0;	
	}	
	//create the thread array
	pthread_t my_thread[number_childs];
	//loop through the array and then have the thread call the print_threadID function.
	for(int i = 0; i < number_childs; i++){
		int ret = pthread_create(&my_thread[i],NULL,print_threadID,&i);
		if(ret != 0){
			printf("Error: pthread() has failed.\n");
			exit(0);
		}
	}
	pthread_exit(NULL);
	return 0;
}




