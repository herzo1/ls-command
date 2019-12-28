#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>

int main(int argc, char **argv){

	struct dirent **namelist;
	int n;
	struct stat s;

	if(argc < 1){
		exit(EXIT_FAILURE);
	} else if(argc==1){
		n=scandir(".", &namelist, NULL, alphasort);
	} else {
		// printf("%s\n", argv[1]);
		n=scandir(argv[1], &namelist, NULL, alphasort);
	}
	if(n<0){
		// perror("scandir");
		// exit(EXIT_FAILURE);
		printf("%s\n", argv[1]);
	} else {
		for(int i=0; i<n; i++){
			stat(namelist[i]->d_name, &s);
			if(s.st_mode & S_IFREG){
				// perror("stat");
				// exit(EXIT_FAILURE);
				printf("%s\n", namelist[i]->d_name);
			} else switch (s.st_mode & S_IFMT){
				case S_IFDIR:
					if(namelist[i]->d_name[0] != '.'){
						printf("%s/\n", namelist[i]->d_name);
					}
					break;
				case S_IFREG:
					if(namelist[i]->d_name[0] != '.'){
						if((s.st_mode & S_IEXEC) != 0){
							printf("%s*\n", namelist[i]->d_name);
						}else{
							printf("%s\n", namelist[i]->d_name);
						}
					}
					break;
			}
			free(namelist[i]);
		}
		free(namelist);
	}
	return EXIT_SUCCESS;
}
