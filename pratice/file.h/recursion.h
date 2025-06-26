int calculate_power(int n, int e){
    if(e == 0)  return 1;
    return n * calculate_power(n, e - 1);
}
int gcdRecursion(int p, int q){
   if(q == 0)   return p;
   return gcdRecursion(q, p%q);
}
int gcdInteration(int p, int q){
   while(q != 0){
    int temp = q;
    q = p % q;
    p = temp;
   }
   return p;
}
int strLen(char *str){
    if(*str == '\0')    return 0;
    return 1 + strLen(str+1);
}