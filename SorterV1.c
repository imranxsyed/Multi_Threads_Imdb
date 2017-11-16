#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<ctype.h>
#include<math.h>
#include <sys/types.h>
#include<sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include "sorter.c"


/**
version:1
->this file basically is checking the structure of recursive function and parametrs checking.
-> given the directory it prints out the file names inside the files

**/


/**header for recursive method**/
int find_csv_files(char*);

/**header for checking the method**/
int check_csv_format(char*, char[]);

/**header and implementation for the dir_name**/
void dir_name(char* ,char *, char[], int);
void dir_name(char* directory, char* name, char path[], int check){

	
    path[0] = '\0';
    strcat(path, directory);
    strcat(path, "/");
	
	if (check==0){
		
		 strcat(path, name);
	}
	else{
		/**we need to come back here**/
		strcat(name, "-");
	}
   
}

/**File Where all the forking information will written to**/
FILE * fork_output;

/**output DIR Name**/
char output_dir_name[1048];

/**global variable to sort**/
char temp_sort[50];


/**file object where you will be putting the numbers of process**/
FILE* num_file ;



int main(int argc, char * argv[]){

    
	/**name for initial director**/
    char initial_dir_name[1048];

   /* getcwd(initial_dir_name,1048);
    printf("initial dir: %s\n", initial_dir_name);
    return 0;*/

	/**parameters checking
		->making sure got the right parameters
		->initial directoy name
		->initial_dir = fopen(argv[x], "W")
	**/


	if (argc<3){


        printf("NOT ENOUGH PARAMTERS\n");
        exit(0);
	}

	/**at least the directory is given**/
	if (argc>=7){



        if(strcasecmp(argv[3], "-d") ==0 ){

        strcpy(initial_dir_name, argv[4]);
        }
        else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }



        if(strcasecmp(argv[5], "-o") ==0 ){

            strcpy(output_dir_name,argv[6]);
        }else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }


	}
	else if (argc>=5){



        if(strcasecmp(argv[3], "-d") ==0 ){

        strcpy(initial_dir_name, argv[4]);
        strcpy(output_dir_name, "NONE");
        }



        else if(strcasecmp(argv[3], "-o") ==0 ){

            strcpy(output_dir_name, argv[4]);
            getcwd(initial_dir_name,1048);
        }

        else{

            printf("WRONG PARAMETERS\n");
            exit(0);
        }


	}

	else{

        getcwd(initial_dir_name,1048);
        strcpy(output_dir_name, "NONE");

	}

	strcpy(temp_sort,argv[2]);



	/**initalizing the file where program will printin its number of process**/
	num_file = fopen("child_process", "w");

    	if(num_file==NULL){

		printf("CHILD PROCESS FILE FAILED TO OPEN\n");

	}



	/** call the recursive method
		->print parent pid
		-> wiht dir name

	**/
	/**printing parent ID**/
	printf("Parent PID: %d\n",getpid());
	int parent_pid = getpid();

	/**calling recursive function**/
	find_csv_files(initial_dir_name);

	/** if the child process returned we simply retrun back
	 ->else: if it a main parent: we proceed below**/
	if (getpid() !=parent_pid){return 0 ;}



	/**anything beyond this point only happens once in the main parent**/

	fclose(num_file);




	/**now we read the total number of process written to child_process file**/
	num_file = fopen("child_process", "r");
	char line[5];
	int num_process=1;

	/**adding all the numbers to num_process variable**/
	while ((fgets(line,5,num_file))){

		num_process += atoi(line);

	}
	printf("Total number of processes: %d\n",num_process);
	

	fclose(num_file);
}	









int check_csv_format(char *name, char path[]){

    int name_length = strlen(name);

    /**it CANNOT have .csv file**/
    if (name_length < 4){

        return -1;

    }
    char format[5];
    format[0] = '\0';
    int i= 0 ;


    int start_index = name_length -4;

    while (start_index<name_length){

        format[i]  = name[start_index];

        start_index++;
        i++;
    }
    format[i] = '\0';

    if (strcasecmp(format, ".csv")!=0){

         //printf("NON_CSV_FILE: %s\nPath is: %s\n\n",name, path);
        return -1;
    }
    /** at this time we know we have a file with a csv format
        -> no we need to check for contents inside**/
	char header[1000] = "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes,\n";



    /**openning the file checking its header contents to make sure it is the right format inside csv file**/
    FILE * file = fopen(path,"r");

    /**if could not open the file**/
    if (file == NULL){

        printf("Unable to open csv file: %s\n", name);
        return -1;
    }

    /**we have the file open now
        ->get header
        ->check header
    **/
    char line[1000];
    fgets(line,1000,file);

    /**not the right header**/
    if (strcasecmp(line,header)!=0){
        printf("incorrect header in the csv file: %s\n", name);
	fclose(file);
        return -1;
    }
    fclose(file);
    return 0;

}



/**takes a file name and a directory name to:
    ->merge them
    ->ex. file.csv ---> file-movie_title.csv
**/
void get_output_name(char[], char[], char[],int );
void get_output_name(char directory[], char name[],char output[],int check ){

    output[0]= '\0';
    int index=0;
    int lenght = strlen(name)-4;

    if (check!=0){

        strcpy(output,directory);
        strcat(output, "/");

       // printf("String is: %s\n", output);

        index = strlen(output);
    }

    /**
        ->we first get the name before the
        ->file.csv will produce file
    **/


        int i;
        for (i=0; i<lenght; i++){

            output[index] = name[i];
            index++;
        }

        output[index]= '\0';
        strcat(output, "-sorted-");
        index+=8;
        output[index]= '\0';



        /**we have the file name without extention
        ->now we add the temp_sort + .csv
        **/
        lenght = strlen(temp_sort);

         i;

        for (i=0; i<lenght; i++){

           output[index] = temp_sort[i];
           index++;
        }
        /**now we have the correct format**/
        output[index] = '\0';
        strcat(output,".csv");

}










/** Function that finds the csv files and SORTS them, and if encountered with sub Directoris it calls itself**/
int find_csv_files(char *directory_name){


	/**this is our arraylist strucutre where we add all pids of the parent children**/
	int track=0,limit=20;
	int* pids;
	pids = (int*)malloc(sizeof(int)*limit);


	




        /**variable that will serve for a path name**/
        char path[1048];


       /**making a DIR variable and opening the Directory**/
       DIR *director;
       director = opendir(directory_name);

       /**making direct and stat for name checking**/
	   struct dirent *each_dir;
	   struct stat info;


	   /**error checking for the initial directory**/
	   if (!director){ return;}



	/**runs a loop until no files left in the dir**/
	while ((each_dir = readdir(director))!=NULL){


        /**checking if it is its own dir. (dot) .**/
        if (each_dir->d_name[0]== '.'){ /** do nothing**/}


        /**DIRorFILE is not its own file. (dot) .**/
        else{

            /** getting a path name**/
            dir_name(directory_name,each_dir->d_name, path,0);


            /** setting a info stat**/
            stat(path, &info);

            /**if its a sub dir we fork it
                ->if CHILD: call the recursive function
                ->if Parent: wait for the child**/
            if (S_ISDIR(info.st_mode)){

                int id= fork();
                //int id= 0 ;
                /**if child calls the recursive function with new sub dir**/
                if(id==0){

                    find_csv_files(path);
                    //fork_output.write(getPID())
                    //printf("SUB_DIR: %s\nThe Path is: %s\n\n", each_dir->d_name,path);
		    return 0;

                }else{

                    /**if parent: add the pid of the children to the arraylist**/
                   	if (track == limit){

				/**need to realloc**/
				limit = limit*2;
				pids = realloc(pids,sizeof(int)*limit);
			}

			/**add the pid of the children**/
			pids[track] = id;
			track++;


                }

            }else{


                //check if the file is .csv file by calling the functin check_csv_format() and check if the contens inside the file is corrent : meaning : MOVIE,DIRECTOR_NAME, ....etc

                if (check_csv_format(each_dir->d_name,path)==0){

                    /**we fork() to :
                        -> child process could sort
                        ->parent process could wait for the child process
                    **/
                    int id =fork();

                   // int id =0;


                    /**If its a child, call the sorter function**/
                    if (id==0){

                        //printf("CSV_FILE: %s\nThe Path is: %s\n\n", each_dir->d_name,path);
		
			/**name of the file to output the sorted results to **/
			char output_file[500];output_file[0]='\0';
		
			get_output_name(output_dir_name,each_dir->d_name,output_file, strcmp("NONE",output_dir_name)==0? 0: 1);
			
                        sort_file(path, output_file, temp_sort);
                        //fork_output.write(getPID())

			return 0;


                    }else{

                        /**if parent: add the pid of the children to the arraylist**/
                   	if (track == limit){

				/**need to realloc**/
				limit = limit*2;
				pids = realloc(pids,sizeof(int)*limit);
			}

			/**add the pid of the children**/
			pids[track] = id;
			track++;


                    }



                }
                else{


                    /**meaning the file is not of the csv format..
                        -> JUST IGNORE
                    **/


                }
            }


		}

	}
        /**when all files done.
	->wait for all child process
	-> return the function**/
	int i=0;
	for (i=0; i<track; i++){

		wait(NULL);
		printf("%d\n", pids[i]);

	}
	fprintf(num_file,"%d\n",track);

	/**freeing allocated memroy**/
	free(pids);
		
		return 1;


	}















