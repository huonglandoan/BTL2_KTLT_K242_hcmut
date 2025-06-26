int ascendingRows(int arr[][1000], int row, int col){
    int count = 0;
    for(int i = 0; i < row; ++i){
        bool check = true;
        for(int j = 0; j < col - 1; ++j){
            if(arr[i][j] > arr[i][j+1]) 
                check = false;
        }
        if(check) count++;
    }
    return count;
}

bool isPrime(int n){
    if(n < 2)   return false;

    for(int i = 2; i * i <= n; ++i){
        if(n % i == 0)   return false;
    }
    return true;
}
int primeColumns(int arr[][1000], int row, int col){
    int count = 0;
    for(int i = 0; i < col; ++i){
        int sum = 0;
        for(int j = 0; j < row; ++j){
            sum += arr[j][i];
        }
        if(isPrime(sum))    count++;
    }
    return count;
}