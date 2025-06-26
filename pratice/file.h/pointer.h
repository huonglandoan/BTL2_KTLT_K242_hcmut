#include<string>
int arr[] = {1, 2, 3, 4};
int k = 3;
int getValueAtIndex(int *ptr, int k){
    return *(ptr+k);
}
int a = 5; 
int b = 6;
void swap(int *ptr1, int *ptr2){
    int temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
}
int n = 1;

int *zero(int n){
if(n <= 0)  return nullptr;
int *arr = new int[n];
for(int i = 0; i < n; ++i)
    arr[i] = 0;
return arr;
}
