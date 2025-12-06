#include <stdio.h>

int main () {
    int n = 0 ;
    if(scanf("%d",&n)!=1){
        return 1 ;
    } else {
        for(int i = 1 ; i <=n ; i++){
            printf("[%d] Hello world\n",i) ;
        }
    }
    return 0 ;
}