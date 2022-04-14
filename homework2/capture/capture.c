#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<stdio.h>
//Function prototype
int read_to_file(char * argv[]);//read and write the data into the file
int display_file_data(char * argv[]);//display all the data in the file

int main(int argc, char * argv[]){
	//check for if the arguement is valid otherwise print out the error
	if(argc < 2){
		write(STDERR_FILENO,"Too little arguement. \n",23);
		return 1;
	}
	else if(argc >= 3){
		write(STDERR_FILENO,"Too much arguement. \n",21);
		return 1;
	}
	//if there is no problem with the arguement then read and write into the file
	//then display the data in the file
	read_to_file(argv);
	write(STDOUT_FILENO,"Displaying file content.\n",25);
	display_file_data(argv);	
}
/**
 *read_to_file() - read and write the user input into the file
 *
 *This function will create and open a file that the user want if the file
 *have not been create then it will open a read/write file. If the file already exist then
 *it will not open another file and sent a warning to the user and exit the program.
 *Once the file have been open and set to read/write, the program will prompt the user to enter
 *the data they want to write to the file and then it will save the data in the file.
 *
 *@param argv[] - the file name
 *
 *@return 1 for success operation and 0 for error.
 *
 */
int read_to_file(char * argv[]){
	write(STDOUT_FILENO,"Press enter with no input to end the program.\n",56);
	int file = open(argv[1],O_RDWR | O_EXCL | O_CREAT,0777);
	if(file == -1){
		write(STDERR_FILENO,"The file already exist.\n",24);
		return 0;
	}
	int condition = 0;
	while(condition == 0){
		write(STDOUT_FILENO,"Enter: ",7);
		char buffer[100];
		int check1 = read(STDIN_FILENO,buffer,100);
		if(check1 <= 1){
			if(close(file) < 0){
				write(STDERR_FILENO,"Fail to close file.\n",20);
				return 0;
			}
			condition = 1;
			write(STDOUT_FILENO,"File is close.\n",15);
			return 1;
		}
		else{
			write(file,buffer,check1);
			write(STDOUT_FILENO,"What your have put in the file: ",32);
			write(STDOUT_FILENO,buffer,check1);
			write(STDOUT_FILENO,"\n",1);
		}
	}
	return 1;
}
/**
 *display_file_data() - display the content of the file
 *
 *The function will open up the file for read and then it will display all
 *the data in the file to the user until it hit end of the file
 *
 *@param argv[] - the file name that is need to open
 *@return 1 for success run and 0 for error.
 */

int display_file_data(char * argv[]){
	write(STDOUT_FILENO,"\n",1);
	int file = open(argv[1],O_RDONLY,0777);
	char buffer[100];
	if(file < 0){
		write(STDERR_FILENO,"Can't open file.\n",17);
		return 0;
	}
	else{
		int length;
		while((length = read(file,buffer,100)) > 0){
			write(1,buffer,length);
		}	
		close(file);
		return 1;
	}
	return 1;
}








