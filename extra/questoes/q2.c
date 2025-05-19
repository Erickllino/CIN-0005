#include <stdio.h>

int main() {

    int total,h1,h2,h3;
    scanf("%d\n%d\n%d\n%d", &total, &h1, &h2, &h3);

    float H1,H2,H3;

    H1 = h1*total/100.00;
    H2 = h2*total/100.00;
    H3 = h3*total/100.00;

    int resto = total - (H1 + H2 + H3);
    int porcentagem = h1 + h2 + h3;
    int investido = 0;
    int possivel = 1;
    
    int check = ((int)H1 != H1) || ((int)H2 != H2) || ((int)H3 != H3);
    
    
    if (((int)H1 != H1) || ((int)H2 != H2) || ((int)H3 != H3)){
        
        total += 1;
        H1 = h1*total/100.00;
        H2 = h2*total/100.00;
        H3 = h3*total/100.00;
        resto = total - (H1 + H2 + H3);
        investido += 1;
        if (((int)H1 != H1) || ((int)H2 != H2) || ((int)H3 != H3)){
            total += 1;
            H1 = h1*total/100.00;
            H2 = h2*total/100.00;
            H3 = h3*total/100.00;
            resto = total - (H1 + H2 + H3);
            investido += 1;
            if (((int)H1 != H1) || ((int)H2 != H2) || ((int)H3 != H3)){
                total += 1;
                H1 = h1*total/100.00;
                H2 = h2*total/100.00;
                H3 = h3*total/100.00;
                resto = total - (H1 + H2 + H3);
                investido += 1;
                if (((int)H1 != H1) || ((int)H2 != H2) || ((int)H3 != H3)){
                    possivel = 0;
                };
            };
        };

    };
    
    if (possivel == 1){
            
        printf("Cada homem ficou com %.f, %.f e %.f reais, respectivamente\n", H1, H2, H3);
        
        if (resto >= 0){
            if (investido == 2){
                char A,B,C;
                scanf(" %c %c %c", &A, &B, &C);
                int soma = A+B+C - 96*3;
                
                printf("%d\n", soma);
            }else if (investido == 3){
                int idade1, idade2, idade3;
                scanf("%d %d %d", &idade1, &idade2, &idade3);
                int parcelas = 0;
                if (idade1%3 == 0){
                    parcelas += idade1/3;
                }
                if (idade2%3 == 0){
                    parcelas += idade2/3;
                }
                if (idade3%3 == 0){
                    parcelas += idade3/3;
                }
                if (parcelas > 0){
                    printf("%d\n", parcelas);
                }
            };

            

            int money_rbk = resto + 3-investido;
            if (money_rbk >= 7){
                printf("Ela conseguiu! Rebeka voltou para casa e apanhou da mae por sumir noite passada!\n");
            }else{
                printf("E parece que Rebeka vai ter que voltar andando...");
            }
    };
    }else{
        printf("Nao foi dessa vez que Rebeka pode ajudar...\n");
        printf("E parece que Rebeka vai ter que voltar andando...");
    };
    
}


