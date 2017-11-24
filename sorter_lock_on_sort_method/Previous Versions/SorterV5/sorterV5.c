#include "sorter.h"
#include "mergesort.c"





/*******************************************************
Pary:2
->Added reallocation.
->Everything tuned
->Used Recursion for dirs
->uses lock on the entire method (sort_file())
->put all the global variables inside the sorter.h file

**********************************************************/

void* thread_func(void *);
void* thread_func(void * ptr){


    struct names * na  = (struct names *) ptr;
   
   // printf("file is: %s\n dir is: %s\n sort by is: %s\n",na->file, na->dir, na->sort);

    char input_file[100],output_file[100],sort[50];
    strcpy(input_file,na->file);
    strcpy(output_file,na->dir);
   


    sort_file(input_file,output_file);

    pthread_exit(NULL);
}



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



int main(int argc, char * argv[]){

    
	/**name for initial director**/
    char initial_dir_name[1048];

   
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


	/**chekcing if the output dir exists**/
	DIR* check = opendir(output_dir_name);
	if (!check && strcmp(output_dir_name,"NONE")!=0){

		printf("WRONG PARMETER. OUTPUT FILE IS NOT CORRECT\n");
		exit(0);

	}
	

	strcpy(temp_sort,argv[2]);
	strcpy(sort_by, argv[2]);

	strcpy(header, "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes,\n");




	/**initializing the movies arrays**/
	mvs= (Movie*) malloc(sizeof(Movie)*target);


	/**initializing threads and structs**/
	ts = (pthread_t *)malloc(sizeof(pthread_t)*ts_limit);
	sts = (struct names * ) malloc (sizeof(struct names)*ts_limit);


	/** call the recursive method
		->print parent pid
		-> wiht dir name
	**/

	
	//printf("main thread id is: %d\n", pthread_self());

	

	/**calling recursive function**/
	printf("\tExecuting....\n");
	
	find_csv_files(initial_dir_name);

	//printf("returnes\n");
	int i;

	for (i=0; i< ts_index; i++){


		pthread_join(ts[i], NULL);

	}


	
	//printf("let us see this shit: %d\n", total_num_of_movies);
	int null_values=0, non_null_values=0;

//reallocating to the numbers of movies
mvs = realloc(mvs, sizeof(Movie)*(total_num_of_movies));


Movie* invalid_movies;
invalid_movies = (Movie*)malloc(sizeof(Movie)*total_num_of_movies);
null_values = invalid_values(mvs, invalid_movies, null_values , total_num_of_movies);

//printf("invalid_values: %d\n",null_values);
/**no need to valid and invalid arrays**/

if (null_values <=0){



free(invalid_movies);


mergeSort(mvs,total_num_of_movies);
printf("called for null values\n");
printMovies(mvs,total_num_of_movies, "w","sorted_file.csv");

return 0;
}

/**saperate the array**/

//putting the null values first
//printf("259\n");
printMovies(invalid_movies,null_values, "w","sorted_file.csv");

//getting the non null values 
non_null_values = (total_num_of_movies) - (null_values);



valid_values(mvs, invalid_movies,total_num_of_movies);

mergeSort(invalid_movies, non_null_values);

//printf("THE OUTPUT FILE NAM EIS: %s\n", output_file_name);
//printf("272\n");
printMovies(invalid_movies, non_null_values,"a","sorted_file.csv");

free(invalid_movies);

	
	
	
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
	//char header[1000] = "color,director_name,num_critic_for_reviews,duration,director_facebook_likes,actor_3_facebook_likes,actor_2_name,actor_1_facebook_likes,gross,genres,actor_1_name,movie_title,num_voted_users,cast_total_facebook_likes,actor_3_name,facenumber_in_poster,plot_keywords,movie_imdb_link,num_user_for_reviews,language,country,content_rating,budget,title_year,actor_2_facebook_likes,imdb_score,aspect_ratio,movie_facebook_likes,\n";



    //openning the file checking its header contents to make sure it is the right format inside csv file
    /*FILE * file = fopen(path,"r");

    //if could not open the file
    if (file == NULL){

        printf("Unable to open csv file: %s\n", name);
        return -1;
    }
    fclose(file);
    return 0;
*/
    /**we have the file open now
        ->get header
        ->check header
    
    char line[1000];
    fgets(line,1000,file);

    //not the right header
    if (strcasecmp(line,header)!=0){
        printf("incorrect header in the csv file: %s\n", name);
	fclose(file);
        return -1;
    }**/
    

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

	
        /**variable that will serve for a path name**/
        char path[1048];


       /**making a DIR variable and opening the Directory**/
       DIR *director;
       director = opendir(directory_name);

       /**making direct and stat for name checking**/
	   struct dirent *each_dir;
	   struct stat info;


	   /**error checking for the initial directory**/
	   if (!director){ return -1;}



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

            /**if its a sub dir we fork it**/
                
            if (S_ISDIR(info.st_mode)){

                    find_csv_files(path);
                    

            }
		else{


                
                if (check_csv_format(each_dir->d_name,path)==0){

                  
			
                        //printf("CSV_FILE: %s\nThe Path is: %s\n\n", each_dir->d_name,path);
		
			/**name of the file to output the sorted results to **/
			char output_file[500];output_file[0]='\0';
		
			get_output_name(output_dir_name, each_dir->d_name, output_file,  strcmp("NONE",output_dir_name)==0? 0: 1);
			

			struct names st;

           		strcpy(st.file, path);
          	        strcpy(st.dir,output_file);
                       
			
			
			
			/**reallocating the arraylist**/
			if(ts_index == ts_limit){
				pthread_mutex_lock(&lock);
				//printf("lock acquired\n");
				ts_limit  = ts_limit *2;
				sts = realloc (sts, sizeof(struct names) * ts_limit);
				ts  = realloc (ts, sizeof(pthread_t) * ts_limit);
				//printf("reallocated to : %d\n", ts_limit);
				pthread_mutex_unlock(&lock);
				
			}


			sts[ts_index] = st;

			pthread_create(&ts[ts_index],NULL,thread_func,&sts[ts_index]);
			
			ts_index +=1;


			
                       
			

                    
			
                	}
                
            	}


	}

}
       		/*int i;
		for (i=0; i<ts_index_2 ; ts_index_2++){

			pthread_join(ts_2[i],NULL);

		}*/
		return 1;


	}

























/*****************************************************************

Part:0
->sorts the CSV FILE
->WRITE THE CSV FILE TO THE THE GIVEN DIRECTORY

******************************************************************/
int compareString(char*,char*,int, int);
int compareString(char* first, char* second, int len_1, int len_2){
	int output = 0;
	int fix_len= len_2>=len_1 ? len_1 : len_2;
	int iter=0;
	
		while(iter<=fix_len){
			if(first[iter]!=second[iter]){
				if(first[iter]>second[iter]){
					output = -1;
					break;
				}else{
					output = 1;
					break;
				}
			}
			iter++;
		}
		
		if(iter==fix_len){
			if(iter<len_1){
				output = -1;
			}else if(iter<len_2){
				output = 1;
			}else{
				output = 0;
				}
		}
		
	return output;
}
int compare_movie(Movie movie1,Movie movie2){

	int output;

	if (strcmp(sort_by,"color")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[2];
		first[0] = movie1.color[0] == '"' ? movie1.color[1] : movie1.color[0];
		first[1] = '\0';

		//for movie 2
		char second[2];
		second[0] = movie2.color[0]=='"'? movie2.color[1] : movie2.color[0];
		second[1] = '\0';
		

		output = strcasecmp(second,first);

		//output = strcasecmp(movie2.color,movie1.color);
	
	}

	else if (strcmp(sort_by,"director_name")==0){

		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.director_name);i++){
			if(movie1.director_name[i]=='"'){continue;}
			first[num]=movie1.director_name[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.director_name);i++){
			if(movie2.director_name[i]=='"'){continue;}
			second[num]=movie2.director_name[i];
			num++;
		}

		

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

 		//output = strcasecmp(movie2.director_name,movie1.director_name);
	}


	else if (strcmp(sort_by,"num_critic_for_reviews")==0){

 		output = movie1.num_critic_for_reviews >= movie2.num_critic_for_reviews? -1: 1;
	}
	

	else if (strcmp(sort_by,"duration")==0){

 		output = movie1.duration >= movie2.duration? -1: 1;
	}



	else if (strcmp(sort_by,"director_facebook_likes")==0){

 		output = movie1.director_facebook_likes >= movie2.director_facebook_likes? -1: 1;
	}


	else if (strcmp(sort_by,"actor_3_facebook_likes")==0){

 		output = movie1.actor_3_facebook_likes >= movie2.actor_3_facebook_likes? -1: 1;
	}


	else if (strcmp(sort_by,"actor_2_name")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.actor_2_name);i++){
			if(movie1.actor_2_name[i]=='"'){continue;}
			first[num]=movie1.actor_2_name[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.actor_2_name);i++){
			if(movie2.actor_2_name[i]=='"'){continue;}
			second[num]=movie2.actor_2_name[i];
			num++;
		}

		

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);


	}

	else if (strcmp(sort_by,"actor_1_facebook_likes")==0){

 		output = movie1.actor_1_facebook_likes>= movie2.actor_1_facebook_likes? -1: 1;
	}


	else if (strcmp(sort_by,"gross")==0){

 		output = movie1.gross>= movie2.gross? -1: 1;
	}



	else if (strcmp(sort_by,"genres")==0){

		/** Quotation marks checking**/
		//for movies 1
		char first[100];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.genres);i++){
			if(movie1.genres[i]=='"'){continue;}
			first[num]=movie1.genres[i];
			num++;
		}
		
		//for movie 2
		char second[100];
		num=0;
		
		for(i=0; i<=strlen(movie2.genres);i++){
			if(movie2.genres[i]=='"'){continue;}
			second[num]=movie2.genres[i];
			num++;
		}

		

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);
	

	}


	else if (strcmp(sort_by,"actor_1_name")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.actor_1_name);i++){
			if(movie1.actor_1_name[i]=='"'){continue;}
			first[num]=movie1.actor_1_name[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.actor_1_name);i++){
			if(movie2.actor_1_name[i]=='"'){continue;}
			second[num]=movie2.actor_1_name[i];
			num++;
		}

		

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}

	else if (strcmp(sort_by,"movie_title")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.movie_title);i++){
			if(movie1.movie_title[i]=='"'){continue;}
			first[num]=movie1.movie_title[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.movie_title);i++){
			if(movie2.movie_title[i]=='"'){continue;}
			second[num]=movie2.movie_title[i];
			num++;
		}
		/*
		if(isdigit(first[0]) && isdigit(second[0])){
			int j =0;
			int num1=0;
			int num2=0;
			while(isdigit(first[j])||first[j]==','){
				
				if(first[j]==','){
					j++;
					continue;
				}
				num1 *=10;
				num1 += first[j] - '0';
				j++;
			}
			
			int p=0;
			while(isdigit(second[p])||second[p]==','){
				
				if(second[p]==','){
					p++;
					continue;
				}
				num2 *=10;
				num2 += second[p] - '0';
				p++;
			}
			
			if(num1>num2){
				output = -1;
			}else if (num1<num2){
				output = 1;
			}else{
				char first_sub[50];
				char second_sub[50];
				int count;
				int ptr = 0;
				for(count = j;count<=strlen(first);count++){
					first_sub[ptr] = first[count];
					ptr++;
				}
				ptr=0;
				for(count = p;count<strlen(second);count++){
					second_sub[ptr] = second[count];
					ptr++;
				}
				int len_1 = strlen(first_sub);
				int len_2 = strlen(second_sub);
				output = compareString(first_sub,second_sub,len_1,len_2);
			}
		}else{
			int len_1 = strlen(first);
			int len_2 = strlen(second);
			output = compareString(first,second,len_1,len_2);
			
		}*/
			int len_1 = strlen(first);
			int len_2 = strlen(second);
			output = compareString(first,second,len_1,len_2);
			
	}

	

	else if (strcmp(sort_by,"num_voted_users")==0){

 		output = movie1.num_voted_users >= movie2.num_voted_users ? -1: 1;
	}



	else if (strcmp(sort_by,"cast_total_facebook_likes")==0){

 		output = movie1.cast_total_facebook_likes >= movie2.cast_total_facebook_likes ? -1: 1;
	}



	else if (strcmp(sort_by,"actor_3_name")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.actor_3_name);i++){
			if(movie1.actor_3_name[i]=='"'){continue;}
			first[num]=movie1.actor_3_name[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.actor_3_name);i++){
			if(movie2.actor_3_name[i]=='"'){continue;}
			second[num]=movie2.actor_3_name[i];
			num++;
		}
		
		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);
	}

	
	else if (strcmp(sort_by,"facenumber_in_poster")==0){

 		output = movie1.facenumber_in_poster >= movie2.facenumber_in_poster ? -1: 1;
	}




	else if (strcmp(sort_by,"plot_keywords")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[500];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.plot_keywords);i++){
			if(movie1.plot_keywords[i]=='"'){continue;}
			first[num]=movie1.plot_keywords[i];
			num++;
		}
		
		//for movie 2
		char second[500];
		num=0;
		
		for(i=0; i<=strlen(movie2.plot_keywords);i++){
			if(movie2.plot_keywords[i]=='"'){continue;}
			second[num]=movie2.plot_keywords[i];
			num++;
		}

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}

	else if (strcmp(sort_by,"movie_imdb_link")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[100];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.movie_imdb_link);i++){
			if(movie1.movie_imdb_link[i]=='"'){continue;}
			first[num]=movie1.movie_imdb_link[i];
			num++;
		}
		
		//for movie 2
		char second[100];
		num=0;
		
		for(i=0; i<=strlen(movie2.movie_imdb_link);i++){
			if(movie2.movie_imdb_link[i]=='"'){continue;}
			second[num]=movie2.movie_imdb_link[i];
			num++;
		}
		

		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}


	
	else if (strcmp(sort_by,"num_user_for_reviews")==0){

		

 		output = movie1.num_user_for_reviews >= movie2.num_user_for_reviews ? -1: 1;
	}



	else if (strcmp(sort_by,"language")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.language);i++){
			if(movie1.language[i]=='"'){continue;}
			first[num]=movie1.language[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.language);i++){
			if(movie2.language[i]=='"'){continue;}
			second[num]=movie2.language[i];
			num++;
		}
		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}


	else if (strcmp(sort_by,"country")==0){
		
		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.country);i++){
			if(movie1.country[i]=='"'){continue;}
			first[num]=movie1.country[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.country);i++){
			if(movie2.country[i]=='"'){continue;}
			second[num]=movie2.country[i];
			num++;
		}
		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}

	else if (strcmp(sort_by,"content_rating")==0){

		/** Quotation marks checking**/
		
		//for movies 1
		char first[50];
		int i;
		int num=0;	
		for(i=0; i<=strlen(movie1.content_rating);i++){
			if(movie1.content_rating[i]=='"'){continue;}
			first[num]=movie1.content_rating[i];
			num++;
		}
		
		//for movie 2
		char second[50];
		num=0;
		
		for(i=0; i<=strlen(movie2.content_rating);i++){
			if(movie2.content_rating[i]=='"'){continue;}
			second[num]=movie2.content_rating[i];
			num++;
		}
		int len_1 = strlen(first);
		int len_2 = strlen(second);
		output = compareString(first,second,len_1,len_2);

	}

	else if (strcmp(sort_by,"budget")==0){

 		output = movie1.budget >= movie2.budget ? -1: 1;
	}
	

	else if (strcmp(sort_by,"title_year")==0){

 		output = movie1.title_year >= movie2.title_year ? -1: 1;
	}
	

	else if (strcmp(sort_by,"actor_2_facebook_likes")==0){

 		output = movie1.actor_2_facebook_likes >= movie2.actor_2_facebook_likes ? -1: 1;
	}
	

	else if (strcmp(sort_by,"imdb_score")==0){

 		output = movie1.imdb_score >= movie2.imdb_score ? -1: 1;
	}
	

	else if (strcmp(sort_by,"aspect_ratio")==0){

 		output = movie1.aspect_ratio >= movie2.aspect_ratio ? -1: 1;
	}


	else if (strcmp(sort_by,"movie_facebook_likes")==0){

 		output = movie1.movie_facebook_likes >= movie2.movie_facebook_likes ? -1: 1;
	}

	else{


	printf("Wrong Parameter\n");
	return 0;

	}


	return output;
	


}




int subTokenize(char first[],char second[], int index){
    int i=0 ;

    if (first[index] =='"'){

		
	    second[i] = '"'; //putting " for the first character
	    i++;
            index++; // getting after "

            while (first[index]!='"'&& first[index]!= '\0'&& first[index]!= '\n'){ //until the next one comes

                second[i]= first[index];
                index++;
                i++;
            }
            second[i]= '"'; // putting " in the last character
	     second[i+1] = '\0';

	index = index+2;
        return index;
    }
    else{

        while (first[index]!= ','&& first[index]!= '\0'&& first[index]!= '\n'){

            second[i] = first[index];
            index++;
            i++;

        }
        second[i] = '\0';
	index = index+1;
        return index;
    }
}




void printMovies(Movie  movies[], int total_movies, char command[],char output_name[]){

	FILE* outputName = fopen(output_name, command);
	//printf("file name is: %s\ncommad is: %s\n",output_name,command);
	
	if (outputName == NULL){

		printf("PRINTMOVIES..COULD NOT OPEN THE FILE: %s\n",output_name);
		return ;
	}
	
	if (strcmp(command,"w")==0){
	fprintf(outputName, "%s",header);
	//printf("%s",header);
	}
	

	int i= 0 ;
	Movie movie;

	for (i=0 ; i< total_movies ; i++){

	movie = movies[i]; // getting the movie at index i
	//printContent(movie); // printing the content of the movie at index i
	//printf("line number: %d\n", i);


	fprintf(outputName,"%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%f,%f,%d\n" , movie.color, movie.director_name,movie.num_critic_for_reviews,movie.duration,movie.director_facebook_likes,
movie.actor_3_facebook_likes,movie.actor_2_name,movie.actor_1_facebook_likes,movie.gross,movie.genres,
movie.actor_1_name,movie.movie_title,movie.num_voted_users,movie.cast_total_facebook_likes,movie.actor_3_name,movie.facenumber_in_poster,
movie.plot_keywords,movie.movie_imdb_link,movie.num_user_for_reviews,movie.language,movie.country,movie.content_rating,movie.budget,
movie.title_year,
movie.actor_2_facebook_likes,movie.imdb_score,movie.aspect_ratio,movie.movie_facebook_likes);


	/*printf("%s,%s,%d,%d,%d,%d,%s,%d,%d,%s,%s,%s,%d,%d,%s,%d,%s,%s,%d,%s,%s,%s,%d,%d,%d,%f,%f,%d\n" , movie.color, movie.director_name,movie.num_critic_for_reviews,movie.duration,movie.director_facebook_likes,
movie.actor_3_facebook_likes,movie.actor_2_name,movie.actor_1_facebook_likes,movie.gross,movie.genres,
movie.actor_1_name,movie.movie_title,movie.num_voted_users,movie.cast_total_facebook_likes,movie.actor_3_name,movie.facenumber_in_poster,
movie.plot_keywords,movie.movie_imdb_link,movie.num_user_for_reviews,movie.language,movie.country,movie.content_rating,movie.budget,
movie.title_year,
movie.actor_2_facebook_likes,movie.imdb_score,movie.aspect_ratio,movie.movie_facebook_likes);*/

	

	}

fclose(outputName);


}






int invalid_values(Movie  movies[], Movie  invalid_movies[],int null_values, int total_movies){

int i = 0;
Movie movie;




for (i=0 ; i< total_movies; i++){

movie = movies[i];




	if (strcmp(sort_by,"color")==0){

		if (strlen(movie.color)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"director_name")==0){

 		if (strlen(movie.director_name)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}
	}


	else if (strcmp(sort_by,"num_critic_for_reviews")==0){}
	else if (strcmp(sort_by,"duration")==0){}
	else if (strcmp(sort_by,"director_facebook_likes")==0){}
	else if (strcmp(sort_by,"actor_3_facebook_likes")==0){}
	else if (strcmp(sort_by,"actor_1_facebook_likes")==0){}
	else if (strcmp(sort_by,"gross")==0){}
	else if (strcmp(sort_by,"num_voted_users")==0){}
	else if (strcmp(sort_by,"cast_total_facebook_likes")==0){}
	else if (strcmp(sort_by,"facenumber_in_poster")==0){}
	else if (strcmp(sort_by,"num_user_for_reviews")==0){}
	else if (strcmp(sort_by,"budget")==0){}
	else if (strcmp(sort_by,"title_year")==0){}
	else if (strcmp(sort_by,"actor_2_facebook_likes")==0){}
	else if (strcmp(sort_by,"imdb_score")==0){}
	else if (strcmp(sort_by,"aspect_ratio")==0){}
	else if (strcmp(sort_by,"movie_facebook_likes")==0){}


	


	else if (strcmp(sort_by,"actor_2_name")==0){

 		if (strlen(movie.actor_2_name)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	



	else if (strcmp(sort_by,"genres")==0){

 		if (strlen(movie.genres)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}


	else if (strcmp(sort_by,"actor_1_name")==0){

 		if (strlen(movie.actor_1_name)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"movie_title")==0 ){

 		if (strlen(movie.movie_title)<1 ){


			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

		

	}

	



	else if (strcmp(sort_by,"actor_3_name")==0){

 		if (strlen(movie.actor_3_name)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	




	else if (strcmp(sort_by,"plot_keywords")==0){

 		if (strlen(movie.plot_keywords)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"movie_imdb_link")==0){

 		if (strlen(movie.movie_imdb_link)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}
	
	

	else if (strcmp(sort_by,"language")==0){

 		if (strlen(movie.language)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}


	else if (strcmp(sort_by,"country")==0){

 		if (strlen(movie.country)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"content_rating")==0){

 		if (strlen(movie.content_rating)<1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else{


	printf("Wrong Parameter\n");
	return 0;

	}
	




}

return null_values;

}






void valid_values(Movie  movies[], Movie  invalid_movies[], int total_movies){

int i = 0, null_values=0;
Movie movie;




for (i=0 ; i< total_movies; i++){

movie = movies[i];




	if (strcmp(sort_by,"color")==0){

		if (strlen(movie.color)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"director_name")==0){

 		if (strlen(movie.director_name)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}
	}

	else if (strcmp(sort_by,"num_critic_for_reviews")==0){}
	else if (strcmp(sort_by,"duration")==0){}
	else if (strcmp(sort_by,"director_facebook_likes")==0){}
	else if (strcmp(sort_by,"actor_3_facebook_likes")==0){}
	else if (strcmp(sort_by,"actor_1_facebook_likes")==0){}
	else if (strcmp(sort_by,"gross")==0){}
	else if (strcmp(sort_by,"num_voted_users")==0){}
	else if (strcmp(sort_by,"cast_total_facebook_likes")==0){}
	else if (strcmp(sort_by,"facenumber_in_poster")==0){}
	else if (strcmp(sort_by,"num_user_for_reviews")==0){}
	else if (strcmp(sort_by,"budget")==0){}
	else if (strcmp(sort_by,"title_year")==0){}
	else if (strcmp(sort_by,"actor_2_facebook_likes")==0){}
	else if (strcmp(sort_by,"imdb_score")==0){}
	else if (strcmp(sort_by,"aspect_ratio")==0){}
	else if (strcmp(sort_by,"movie_facebook_likes")==0){}


	else if (strcmp(sort_by,"num_critic_for_reviews")==0){

	}
	//
	//
	//


	else if (strcmp(sort_by,"actor_2_name")==0){

 		if (strlen(movie.actor_2_name)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	//
	//



	else if (strcmp(sort_by,"genres")==0){

 		if (strlen(movie.genres)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}


	else if (strcmp(sort_by,"actor_1_name")==0){

 		if (strlen(movie.actor_1_name)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"movie_title")==0){

 		if ((strlen(movie.movie_title)>=1)){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	//
	//



	else if (strcmp(sort_by,"actor_3_name")==0){

 		if (strlen(movie.actor_3_name)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	//



	else if (strcmp(sort_by,"plot_keywords")==0){

 		if (strlen(movie.plot_keywords)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"movie_imdb_link")==0){

 		if (strlen(movie.movie_imdb_link)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}
	
	//

	else if (strcmp(sort_by,"language")==0){

 		if (strlen(movie.language)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}


	else if (strcmp(sort_by,"country")==0){

 		if (strlen(movie.country)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	else if (strcmp(sort_by,"content_rating")==0){

 		if (strlen(movie.content_rating)>=1){

			invalid_movies[null_values]  = movie;
			null_values++;
			
		}

	}

	//
	//
	//
	//
	//
	//

	else{


	printf("Wrong Parameter\n");
	exit(0);

	}
	

	}

return;

}



   
char* trim (char* input){


    //checking if the input is Null or contains nothing
    //return: Null
    if (input == NULL || strlen(input)<1){

        return input;
    }

    //variable i starts with the last letter of the word and proceeds backwards until hit an actual letter
    int i, j=0;
    i= strlen(input) -1;

    //executes until it hits a valid letter
    while ((input[i]== ' '|| input[i]== '\n')&& i>=0){

        i--;
    }
    // no spaces found
    //return : input
    if (i == strlen(input)-1){
//input[strlen(input)+1] = '\0';
        return input;
    }
    input[i+1] = '\0';
    /** got rid of all the trailing zero at this time**/



     /** starting from the start of string and removing all the leading zero**/
     while (input[j]== ' ' ){


        j++;
     }

     if (!(j>0)){

        return input;
     }

     int index=0;

     while (j<=i){

        input[index] = input[j];
        j++;
        index++;
     }
     input[index] = '\0';


    return input;



}
















int sort_file(char input_file_name[],char output_file_name[]){


    //printf("function is called\n");
    //printf("iput file: %s\noutput: %s\nsort_by: %s\n",input_file_name,output_file_name,sort);

     Movie data;
  
     char append[2] = "a";
     char write[2] = "w";
     char token[500]; token[0]= '\0';
     char line[1000]; line[0]= '\0'; 



	/****locking the thread****/
     pthread_mutex_lock(&lock);

   // printf("lock is acquired\n");


    
   


      int track_tokenizer=0;
	
    
      FILE* file = fopen(input_file_name, "r");

	if (file == NULL){

		printf("SORT_FILE...COULD NOT OPEN THE FILE\n",output_file_name);
		fclose(file);
		pthread_mutex_unlock(&lock);
		return -1;
	}


	fgets(line,1000,file);//getting the header

	fgets(line,1000,file); //getting the first line




        while (strlen(line)>1){


	
	if(total_num_of_movies==target){ //need to realloc

		target = target*2;
		mvs = realloc(mvs, sizeof(Movie)*(target));
		//printf("new target %d\n", target);

	}


            //value of color, putting the value of color into the data
         track_tokenizer = subTokenize(line, token,track_tokenizer);
        data.color[0] = '\0';
	trim(token);
        strcpy(data.color, token);

        
              track_tokenizer = subTokenize(line, token,track_tokenizer);
        data.director_name[0] = '\0';
	trim(token);
        strcpy(data.director_name,token);

             // printf("%s\n", token);




            //num_critcs_for_reviews
            track_tokenizer = subTokenize(line, token,track_tokenizer);
	    trim(token);
            data.num_critic_for_reviews = atoi(token);
             //printf("%d\n", atoi(token));

            //duration
         track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
         data.duration = atoi(token);
         // printf("%d\n", atoi(token));

          //director_facebook_likes
        track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
        data.director_facebook_likes = atoi(token);

        // actor_3_facebook_liked
          track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
          data.actor_3_facebook_likes = atoi(token);
          //printf("%d\n", atoi(token));

        //actor_to_name
         track_tokenizer = subTokenize(line, token,track_tokenizer);
         data.actor_2_name[0] = '\0';
	trim(token);
         strcpy(data.actor_2_name, token);
        // printf("%s\n", token);


            //actor_1_facebook_likes
           track_tokenizer = subTokenize(line, token,track_tokenizer);
		trim(token);
           data.actor_1_facebook_likes = atoi(token);
          // printf("%d\n", atoi(token));

           //gross
           track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
           data.gross = atoi(token);
          // printf("%d\n", atoi(token));


        //genres
        track_tokenizer = subTokenize(line, token,track_tokenizer);
        data.genres[0]= '\0';
	trim(token);
        strcpy(data.genres, token);
        // printf("%s\n", token);



          //actor_1_name
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.actor_1_name[0] = '\0';
	trim(token);
          strcpy(data.actor_1_name, token);
         // printf("%s\n", token);


        //movie_title
        track_tokenizer = subTokenize(line, token,track_tokenizer);
        data.movie_title[0]= '\0';
	trim(token);
        strcpy(data.movie_title, token);
        //printf("%s\n", data.movie_title);


         //num_voted_users
        track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
        data.num_voted_users = atoi(token);

        //cast_total_Facebook_likes
       track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
       data.cast_total_facebook_likes = atoi(token);

           //actor_3_name
            track_tokenizer = subTokenize(line, token,track_tokenizer);
            data.actor_3_name[0]= '\0';
	trim(token);
            strcpy(data.actor_3_name, token);
           // printf("%s\n", token);


          //facenumber_in_poster
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.facenumber_in_poster = atoi(token);
	trim(token);
          // printf("%d\n", atoi(token));

         // plot keywords
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.plot_keywords[0] = '\0';
	trim(token);
          strcpy(data.plot_keywords, token);
         // printf("%s\n", token);


         // movie_imdb_link
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.movie_imdb_link[0] = '\0';
	trim(token);
          strcpy(data.movie_imdb_link, token);
         // printf("%s\n", token);


         // num_user_for_reviews
          track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
          data.num_user_for_reviews = atoi(token);
          //printf("%d\n", atoi(token));

         // language
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.language[0]= '\0';
	trim(token);
           strcpy(data.language, token);
          //printf("%s\n", token);


         // country
          track_tokenizer = subTokenize(line, token,track_tokenizer);
          data.country[0] = '\0';
	trim(token);
          strcpy(data.country, token);
          //printf("%s\n", token);


         // content_rating
         track_tokenizer = subTokenize(line, token,track_tokenizer);
         data.content_rating[0] = '\0';
	trim(token);
         strcpy(data.content_rating, token);
         // printf("%s\n", token);


            //budget
           track_tokenizer = subTokenize(line, token,track_tokenizer);
		trim(token);
           data.budget = atoi(token);
	
          // printf("%d\n", atoi(token));

           //title_year
           track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
           data.title_year =atoi( token);
          // printf("%d\n", atoi(token));

           // actor_2_facebook_likes
            track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
            data.actor_2_facebook_likes = atoi(token);
           // printf("%d\n", atoi(token));

            //imdb_score
            track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
            data.imdb_score = atof(token);
            // printf("%d\n", atoi(token));

             //aspect_ratio
            track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
            data.aspect_ratio = atof(token);
            // printf("%d\n", atoi(token));

            //movie facebook _like
            track_tokenizer = subTokenize(line, token,track_tokenizer);
	trim(token);
            data.movie_facebook_likes = atoi(token);
            // printf("%d\n", atoi(token));


            track_tokenizer= 0;
            line[0]= '\0';


            mvs[total_num_of_movies] = data;
            total_num_of_movies +=1;

	  // printf("the line number: %d\n", movie_number);

	fgets(line,1000,file);

		

            


}    //loop ends

fclose(file);



pthread_mutex_unlock(&lock);

//printf("The number of Movies: %d\nAllocated Space: %d\n", total_num_of_movies,target);

  return 0;
 }



