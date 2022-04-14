#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/stat.h>




int makeChild(int flags,char * buffer,int byte);//create the child process and run the flip function
int main(int argc,char * argv[]){
	char buffer[8100];
	int check;
	int byte;	
	while((byte = read(STDIN_FILENO,buffer,8100)) != 0){//read in the user input
	//loop 3 times to create 3 child process that will use the flip program
		for(int i = 0; i < 3; i++){
			check = makeChild(i,buffer,byte);
			if(check == 0){
				write(STDERR_FILENO,"Error in making a child.\n",25);
			}
		}
	}	
	return 1;
}
/**
 *makeChild() - create child process and run flip program
 *
 *The function will create a pipe first for the parent process and the child process
 *then it will check for the flags to know which option to run the flip program.
 *Once it done with calling the flip program then it will close all the pipe and wait for the child
 *process to finish before returning.
 *
 *
 * @param flags - the option for the flip program for lower,upper and lowerUpper case
 * @param buffer - the output of the parent program
 * @param byte - number of byte that the parent is outputing from buffer.
 *
 */
int makeChild(int flags,char * buffer,int byte){
	//creating a pipe before the fork() and check if the pipe is properly be make
	int pipeline[2],status,file_check;
	pid_t pid;
	if(pipe(pipeline) < 0)
		return 0;
	if((pid = fork()) < 0)
		return 0;
	//if parent process
	else if(pid > 0){	
		close(pipeline[0]);	
		if(byte <= 0){
			exit(0);
		}
		if(write(pipeline[1],buffer,byte) <= 0){
			exit(0);
		}
		close(pipeline[1]);
	}
	//if child process
	else{
		//if the flag is 0 then it lower
		//close the child STDOUT and it write Pipe line.
		//then create and open the file then redirect the output to the file	
		if(flags == 0){
			close(STDOUT_FILENO);
			close(pipeline[1]);
			file_check = open("toLower.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
			if(file_check < 0){
				printf("fail to open file.\n");
			}
			dup2(pipeline[0],STDIN_FILENO);
			char * arg[3];
			arg[0] = "./flip";
			arg[1] = "-l";
			arg[2] = NULL;
			execvp(arg[0],arg);
			return 1;
		}
		//if the flag is 1 then it upper
		//close the child STDOUT and it write Pipe line.
		//then create and open the file then redirect the output to the file	
		else if(flags == 1){
			close(STDOUT_FILENO);
			close(pipeline[1]);
			file_check = open("toUpper.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRWXU);
			if(file_check < 0){
				printf("fail to open file.\n");
			}
			dup2(pipeline[0],STDIN_FILENO);
			char * arg[3];
			arg[0] = "./flip";
			arg[1] = "-u";
			arg[2] = NULL;
			execvp(arg[0],arg);
			return 1;
		}
		//if the flag is 2 then it lowerUpper
		//close the child STDOUT and it write Pipe line.
		//then create and open the file then redirect the output to the file	
		else if(flags == 2){	
			close(pipeline[1]);
			char * arg[3];
			dup2(pipeline[0],STDIN_FILENO);
			arg[0] = "./flip";
			arg[1] = "-lu";
			arg[2] = NULL;
			execvp(arg[0],arg);
			return 1;
		}	
	}	
	//close the pipe and wait for the child process then return.
	close(pipeline[0]);
	close(pipeline[1]);	
	waitpid(-1,&status,0);	
	return 1;
}









