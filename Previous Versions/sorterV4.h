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



/**header for recursive method**/
int find_csv_files(char*);

/**header for checking the method**/
int check_csv_format(char*, char[]);

/**header and implementation for the dir_name**/
void dir_name(char* ,char *, char[], int);


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

    char color[100];
    char director_name[50];
    int num_critic_for_reviews;
    int duration;
    int director_facebook_likes;
    int actor_3_facebook_likes;
    char actor_2_name[50];
    int actor_1_facebook_likes;
    int gross;
    char genres[100];
    char actor_1_name[50];
    char movie_title[500];
    int num_voted_users;
    int cast_total_facebook_likes;
    char actor_3_name[50];
    int facenumber_in_poster;
    char plot_keywords [500];
    char movie_imdb_link [100];
    int num_user_for_reviews;
    char language [50];
    char country[50];
    char content_rating[50];
    int budget;
    int title_year;
    int actor_2_facebook_likes;
    double imdb_score;
    double aspect_ratio;
    int movie_facebook_likes;


};




/**Global Variable**/

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





