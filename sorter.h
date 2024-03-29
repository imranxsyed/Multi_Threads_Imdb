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
#include<pthread.h>


void* thread_dir_func(void *);
void get_output_name(char[], char[], char[],int );
void* thread_func(void *);
int find_csv_files(char*);
int check_csv_format(char*, char[]);
void dir_name(char* ,char *, char[], int);
int sort_file(char[],char[]);


/**File Where all the forking information will written to**/
FILE * fork_output;

/**output DIR Name**/
char output_dir_name[1048];

/**global variable to sort**/
char temp_sort[50];


/**file object where you will be putting the numbers of process**/
FILE* num_file ;

/**file object for heiarchy**/
FILE* extra_2;



/** Structure For Each Row **/
typedef struct movies Movie;
struct movies {

    int num_critic_for_reviews;
    int duration;
    int director_facebook_likes;
    int actor_3_facebook_likes;	
    int actor_1_facebook_likes;
    int gross;
    int num_voted_users;
    int cast_total_facebook_likes;
    int num_user_for_reviews;
    int facenumber_in_poster;
    int budget;
    int title_year;
    int actor_2_facebook_likes;
    int movie_facebook_likes;


    double imdb_score;
    double aspect_ratio;


    char director_name[50];
    char actor_2_name[50];
    char actor_3_name[50]; 
    char actor_1_name[50]; 
    char language [50];
    char country[50];
    char content_rating[50];


    char color[100];
    char genres[100];
    char movie_imdb_link [100]; 
   
    
    char movie_title[500]; 
    char plot_keywords [500];
   
    
};




/**global structs**/
struct names{

    char file[100];
    int index;
    



};



/**Global Variable**/


/**lock**/
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t merge_lock = PTHREAD_MUTEX_INITIALIZER;




/***global ArrayList for movies***/
Movie* mvs;
int target=2500;
int total_num_of_movies=0;
int check = 0;




/****ArrayList for Threads and Struts*****/
pthread_t * ts;//threads
struct names * sts; //structs
int ts_index=0;
int ts_limit = 5000;



//headers and sorter variable
char header[1000];
char sort_by[100];


/** method to compare 2 movies by determining factor**/
int compare_movie(Movie, Movie);

/** Tokenizer Function: personla tokenizer to tokenize each value  **/
int subTokenize(char* ,char*, int);


/** Function to print the results **/
void printMovies( Movie[], int, char[],char[]);


/** function to saperate null values . if the movie_title is the sorting factor then all the movies with Null movie title denoted as NUll values**/
int invalid_values(Movie[],Movie[], int,int);



/** function to put all the valid movies into the array called valid_movies**/
void valid_values(Movie[],Movie[],int);


/** TRIM Function  **/
char* trim (char*);





