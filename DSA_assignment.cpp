#include<iostream>
#include<cstdlib>
#include<ctime>
#include<chrono>
using namespace std;
using namespace chrono;

void generateRandomNumbers(int arr[],int n){
    srand(time(0));
    for(int i=0;i<n;i++){
        arr[i]=rand()%1000;
    }
}

void displayArray(int arr[],int n){
    for(int i=0;i<n;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void selectionSort(int arr[],int n){//O(n^2)
    for(int i=0;i<n-1;i++){
        int smallestIdx=i;//unsorted part starting
        for(int j=i+1;j<n;j++){
            if(arr[j]<arr[smallestIdx]){
                smallestIdx=j;
            }
        }
        swap(arr[i],arr[smallestIdx]);
    }
}

void merge(int arr[],int st,int mid,int end){
    int temp[end-st+1];//temporary array to store the merged result
    int i=st,j=mid+1,idx=0;
    
    //merge two halves of the array into temp
    while(i<=mid && j<=end){
        if(arr[i]<=arr[j]){
            temp[idx]=arr[i];
            i++;
   }else{
            temp[idx]=arr[j];
            j++;
        }
        idx++;
        }
        
        //copy the remaining element of the left half
        while(i<=mid){
            temp[idx]=arr[i];
            i++; 
            idx++;
        }
        
        //copy the remaining element of the right half
        while(j<=end){
            temp[idx]=arr[j];
            j++;
            idx++;
        }
        //copy the sorted elements back into the original array
        for(int i=0;i<(end-st+1);i++){
            arr[st +i]=temp[i];
            
        }
}

void mergeSort(int arr[],int st,int end){
    if(st<end){
    int mid=st+(end-st)/2;//find the middle point
    mergeSort(arr,st,mid);//sort the left half
    mergeSort(arr,mid+1,end);//sort the right half
    merge(arr,st,mid,end);//merge the sorted halves
}
}

int binarySearch(int arr[],int size,int tar){
    int st=0,end=size-1;
    while(st<=end){
        int mid=(st+end)/2;
        if(tar>arr[mid]){
            st=mid+1;
        }else if(tar<arr[mid]){
            end=mid-1;
        }else{
            return mid;
        }
 }
    return -1;
}
        
int interpolationSearch(int arr[], int n, int el) {
    int start = 0, end = n - 1;

    while (start <= end && el >= arr[start] && el <= arr[end]) {
       
        if (arr[start] == arr[end]) {
            if (arr[start] == el) {
                return start; 
            } else {
                return -1; 
            }
        }

        int pos = start + (((double)(end - start) / (arr[end] - arr[start])) * (el - arr[start]));

        if (arr[pos] == el) {
            return pos;
        }

      
        if (arr[pos] < el) {
            start = pos + 1; 
        } else {
            end = pos - 1; 
        }
    }

    return -1; 
}

int main(){
    int n, target;
    cout << "Enter the number of random integers to generate: ";
    cin >> n;
    int arr[n];
 if (n <= 0) {
        cout << "Please enter a positive number." << endl;
        return 1;
    }
    generateRandomNumbers(arr, n);
    cout << "Generated numbers: ";
    displayArray(arr,n);
    
    int numbersForMergeSort[n];
    int numbersForSelectionSort[n];
    for (int i = 0; i < n; i++) {
        numbersForMergeSort[i] = arr[i];
        numbersForSelectionSort[i] = arr[i];
    }

    // Merge Sort
    auto start = high_resolution_clock::now();
    mergeSort(numbersForMergeSort, 0, n - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start);
    cout << "Merge sort sorted numbers: ";
    displayArray(numbersForMergeSort, n);
    cout << "Time taken by MergeSort: " << duration.count() << " nanoseconds" << endl;

    // Selection Sort
    start = high_resolution_clock::now();
    selectionSort(numbersForSelectionSort, n);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    cout << "SelectionSort sorted numbers: ";
    displayArray(numbersForSelectionSort, n);
    cout << "Time taken by SelectionSort: " << duration.count() << " nanoseconds" << endl;

    // Search Operations
    cout << "Enter a number to search: ";
    cin >> target;

    // Binary Search
    start = high_resolution_clock::now();
      int binaryResult = binarySearch(numbersForMergeSort, n, target);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    if (binaryResult != -1) {
        cout << "Number found at index " << binaryResult << " using binary search" << endl;
    } else {
        cout << "Binary search: Number not found." << endl;
    }
    cout << "Time taken by BinarySearch: " << duration.count() << " nanoseconds" << endl;

    // Interpolation Search
    start = high_resolution_clock::now();
    int interpolationResult = interpolationSearch(numbersForMergeSort, n, target);
    stop = high_resolution_clock::now();
    duration = duration_cast<nanoseconds>(stop - start);
    if (interpolationResult != -1) {
        cout << "Number found at index " << interpolationResult << " using interpolation search" << endl;
    } else {
        cout << "Interpolation search: Number not found." << endl;
    }
    cout << "Time taken by InterpolationSearch: " << duration.count() << " nanoseconds" << endl;

 return 0;
}