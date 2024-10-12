#include<iostream>

void copyArray(int *original, int *copy,int size){
    for (int i=0; i< size; i++) copy[i]=original[i];
}

void MergeSort(int * array, int size){
   if (size==1) return;
   int newsize=size/2;

   int *latterhalf = array+newsize;

   MergeSort(array, newsize);
   MergeSort(latterhalf, size - newsize);

   int * firsthalf = new int[newsize];
   copyArray(array,firsthalf,newsize);

   int i=0, j=0; 
   while(j<newsize && latterhalf<array+size){
        if(*latterhalf < *(firsthalf+j)) array[i]= *(latterhalf++);
        else array[i]= *(firsthalf + j++);
        i++;
   }
   while(j<newsize) array[i++]=firsthalf[j++];
   
   delete[] firsthalf;
}


int main(){
    int arrsize, i; 

    std::cout<< "Enter array size: ";
    std::cin>>arrsize;

    int * arr = new int[arrsize];

    std::cout<<"Enter numbers: ";
    for (i=0;i<arrsize;i++) std::cin>>arr[i];

    MergeSort(arr,arrsize);

    std::cout<<"\nSorted array: ";
    for(i=0;i<arrsize;i++) std::cout<<arr[i]<<" ";
    std::cout<<std::endl;
    
    return 0;
}