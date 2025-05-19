#include <stdio.h>


int main() {

    int N,A,B;

    scanf("%d\n%d %d", &N, &A, &B);


    int sum_total = N * (N+1) / 2;

    // a soma de todos numeros multiplos de A
    long long ka = N/A;
    int sum_A = A*ka*(ka + 1)/2;
    // a soma de todos numeros multiplos de B
    long long kb = N/B;
    int sum_B = B*kb*(kb + 1)/2;

    int soma_final = sum_total - sum_A - sum_B;

    printf("%d\n", soma_final);
    if (soma_final % 2 == 0){
        printf("Lá ele!!!");
    }else{
        printf("Opa xupenio AULAS...");
    }

    
    
    return 0;
}
