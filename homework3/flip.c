#include<unistd.h>
#include<stdio.h>
#include<string.h>


int getInput(int option);//get the input from the user
int lowercase(char array[],int size);//make all the char to lower
int uppercase(char array[],int size);//make all the char to upper
int lowerUpper(char array[],int size);//if the char is lower then make it upper and it upper then make it lower


int main(int argc,char * argv[]){
	//check for valid arguement then call the input function to start asking the user for input
	if(argc <= 1){
		write(STDERR_FILENO,"Not enough arguement.\n",22);
		return 0;
	}
	else{
		if(argc > 2){	
			if(strcmp(argv[1],"-l") == 0 && strcmp(argv[2],"-u") == 0){
				int temp = getInput(2);
				if(temp == 1)
					return 1;
			}
			else if(strcmp(argv[1],"-u") == 0 && strcmp(argv[2],"-l") == 0){
				int temp = getInput(2);
				if(temp == 1)
					return 1;
			}
			else{
				write(STDERR_FILENO,"Invalid Option.\n",17);
				return 0;
			}			
		}
		else{
			if(strcmp(argv[1],"-l") == 0){
				int temp = getInput(0);
				if(temp == 1)
					return 1;
			}
			else if(strcmp(argv[1],"-u") == 0){
				int temp = getInput(1);
				if(temp == 1)
					return 1;
			}
			else if(strcmp(argv[1],"-lu") == 0 || strcmp(argv[1],"-ul") == 0 || strcmp(argv[1],"-l-u") == 0){
				int temp = getInput(2);
				if(temp == 1)
					return 1;
			}
			else{
				write(STDERR_FILENO,"Invalid Flag.\n",14);
				return 0;
			}
		}	
	}
	return 1;	
}
/*
 *getInput() - get the input from the user
 *
 *The function will get the input from the user then call the right function
 *that will perform the task the user want. 0 for lower, 1 for upper and 2 for both lower/upper.
 *
 *@param option - the option that the user pick
 *
 */ 

int getInput(int option){
	int conti = 1;
	while(conti == 1){
		char buffer[100];
		int nbyte = read(STDIN_FILENO,buffer,100);
		if(nbyte == 0){
			conti = 1;
			write(STDOUT_FILENO,"\n",1);
			return 1;
		}
		int size = strlen(buffer);	
		if(option == 0){
			lowercase(buffer,size);
			write(STDOUT_FILENO,buffer,nbyte);
			write(STDOUT_FILENO,"\n",1); 
		}
		else if(option == 1){
			uppercase(buffer,size);
			write(STDOUT_FILENO,buffer,nbyte);
			write(STDOUT_FILENO,"\n",1);
		}
		else if(option == 2){
			lowerUpper(buffer,size);
			write(STDOUT_FILENO,buffer,nbyte);
			write(STDOUT_FILENO,"\n",1);	
		}
		else{
			write(STDERR_FILENO,"Invalid option.\n",17);
		}
	}
	return 1;
}
/*
 *lowercase() - make string all lower case.
 *
 *This function will loop through the array and then +32 to each of the array element 
 *to convert it all to lower case.
 *
 *@param array[] - the string that is need to be make lower
 *@param size - the size of the array
 */ 
int lowercase(char array[],int size){
	for(int i = 0; i < size;i++){
		if((array[i] > 64 ) && (array[i] < 91))
			array[i] = array[i] + 32;
	}	
	return 1;
}
/*
 *uppercase() - make string all upper case.
 *
 *This function will loop through the array and then -32 to each of the array element 
 *to convert it all to upper case.
 *
 *@param array[] - the string that is need to be make lower
 *@param size - the size of the array
 */ 

int uppercase(char array[],int size){
	for(int i = 0; i < size;i++){
		if((array[i] > 96) && (array[i] < 123))
			array[i] = array[i] - 32;
	}
	return 1;
}
/*
 *lowerUpper() - flip the case of all the element.
 *
 *This function will loop through the array and then +32 or -32 depend on the array element.
 *If the array element is a lower then it will -32 to make it a upper else if it an upper element 
 *then it will +32 to make it lower.
 *
 *@param array[] - the string that is need to be make lower
 *@param size - the size of the array
 */ 

int lowerUpper(char array[],int size){
	for(int i = 0; i < size;i++){
		if((array[i] > 64) && (array[i] < 91))
			array[i] = array[i] + 32;
		else if((array[i] > 96) && (array[i] < 123))
			array[i] = array[i] - 32;
	
	}	
	return 1;
} 






