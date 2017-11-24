



void sort(Movie[], Movie[],Movie[], int);
void sort(Movie first[], Movie second[],Movie output[], int size) {



int i, j, n = 0;
j = 0;
i = 0;
while (i < (size/2) && j < (size-(size/2))) {

if (compare_movie(first[i], second[j])>=0) {
output[n] = first[i];
n++;
i++;

} else {

output[n] = second[j];
j++;
n++;

}
if (i > (size/2) - 1 || j > ((size - (size/2)) - 1)) {

if (j > ((size - (size/2)) - 1)) {

while (i < (size/2)) {

output[n] = first[i];
n++;
i++;
}
} else {

while (j < (size-(size/2))) {

output[n] = second[j];
n++;
j++;
}

}
}
}
/*
i=0;
printf("[");
while (i<n){

printf("%s |", output[i].movie_title);

i++;

}
printf("]\n\n");

*/
return;

}


void copy(Movie[],Movie[],int ,int );
void copy(Movie input[],Movie output[], int start, int end) {



if (start == end) {
output[0] = input[end - 1];
return ;
}

int i = 0;




while (start < end) {

output[i] = input[start];
start++;
i++;
}
return;
}







void mergeSort(Movie[], int);
void mergeSort(Movie input[],int size ) {




if (size <= 1) {


return ;
}



int start=0, mid= (size/2),end = size -(size/2);



/**sending left sub**/
Movie* left;
left = (Movie*) malloc(sizeof(Movie)*mid);
copy(input,left, start, mid);


        /**sending right sub**/
Movie *right;
right = (Movie*) malloc(sizeof(Movie)*end);
copy(input , right, mid , size);


 mergeSort(left,mid);
          mergeSort(right,end);





sort(left, right,input, size);
free(left);
free(right);



return;



}

