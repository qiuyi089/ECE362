#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

//Protrotype
int search_data(char * argv[],int line_num);//search for the line that the user want to see in the file and display it
int input_check(char * input);//check if the user input is valid

int main(int argc, char * argv[]){
	//check for if the arguement are valid if there too much or too little arguement
	if(argc < 2){
		write(STDERR_FILENO,"Too little arguement. \n",23);
		return 0;
	}
	else if(argc >= 3){
		write(STDERR_FILENO,"Too much arguement. \n",21);
		return 0;
	}
	//check if the is exist if it not exist then print out error
	int check_file = open(argv[1],O_RDONLY,0777);
	if(check_file < 0){
		write(STDERR_FILENO,"File don't exist.\n",18);
		return 0;
	}
	int conti = 0;
	//ask the user for the line in the text file they want to display
	while(conti == 0){
		char temp[100];
		write(STDOUT_FILENO,"What line do you want to search: ",33);
		int line = read(STDIN_FILENO,temp,100);
		if(line <= 1){
			conti = 1;
			return 0;
		}
		int num = input_check(temp);
		if(num == 0){
			write(STDERR_FILENO,"Invalid input. \n",16);
		}
		else{
			search_data(argv,num);
		}
	}
	return 1;
}
/*
 *search_data() - search for the line that the user want from the text file and display it to the user.
 *
 *
 *The function will take in the user input and then go through the file and search for the key line that the 
 *user want to see. Then it will print out the line for the user otherwise it will prompt an error message.
 *
 *@param argv[] - the file name to open the correct file.
 *@param line_num - the line number that the user want to see.
 *
 *
 */
int search_data(char * argv[],int line_num){
	int file = open(argv[1],O_RDONLY,0777);
	char buffer[8000];
	int length;
	int count = 0;
	length = read(file,buffer,8000);
	if(line_num > 1){
		count = 1;
		for(int i = 0;i < (length - 1);i++){
			if(buffer[i] == '\n'){
				count += 1;
			}
			if(count == line_num){
				count = i + 1;
				i = length;
			}
		}
	}
	if(buffer[count] == '\n' || buffer[count] == '\0'){
		write(STDOUT_FILENO,"The line doesn't exist in the file.\n",36);
		return 0;
	}
	while(buffer[count] != '\n'){
		write(STDOUT_FILENO,&buffer[count],1);
		count+=1;
	}
	write(STDOUT_FILENO,"\n",1);
	return 1;
}
/*
 *input_check() - check if the user input is valid and if it is then convert the input to int and return that number back.
 *
 *The function will convert the user input to number and check to see if it valid or not. If it not valid then it will 
 *return back an error else it will return back the number.
 *
 *@param input - the user input that need to be check if it valid
 */
int input_check(char * input){
	int num_convert;
	char * ptr;
	num_convert = strtol(input,&ptr,10);
	if(ptr[0] == '\n'){}
	else{
		return 0;
	}
	return num_convert;
}
