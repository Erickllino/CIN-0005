#include <stdio.h>

int main() {

    int titulos_nau = 24, titulos_spo = 45, titulos_san = 29, titulos_sal = 1;
    int t1, t2, t3, t4;
    char c1, c2, c3, c4;
    
    scanf("%d %c", &t1, &c1);
    scanf("%d %c", &t2, &c2);
    scanf("%d %c", &t3, &c3);
    scanf("%d %c", &t4, &c4);
    
    if (c1 == 'A') {
        if (t1 > titulos_nau){
            printf("Se contar direitinho ainda tá faltando uns títulos para o Timba...\n");
        }else if (t1 < titulos_nau){
            printf("Isso deve ser coisa do Sport, querem ganhar no tapetão que nem em 87!\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_nau = t1;
    } else if (c1 == 'B') {
        if (t1 > titulos_spo){
            printf("Se antes já era grande a diferença, imagine agora...\n");
        }else if(t1 < titulos_spo){
            printf("Capaz de recorrerem no STJD e recuperarem os títulos no tapetão.\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_spo = t1;
    } else if (c1 == 'C') {
        if (t1 > titulos_sal) {
            printf("Finalmente teve justiça sobre que aconteceu em 2017!\n");
        }else if (t1 < titulos_sal) {
            printf("Foi roubado em 2017 e agora em 2025, existe isso não...\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_sal = t1;
    } else if (c1 == 'D') {
        if (t1 > titulos_san) {
            printf("O Santa é gigante e esse ano vai sair da série D\n");
        }else if (t1 < titulos_san) {
            printf("É muito azar, nem com a SAF as coisas dão certo.\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_san = t1;
    }
    
    if (c2 == 'A') {
        if (t2 > titulos_nau){
            printf("Se contar direitinho ainda tá faltando uns títulos para o Timba...\n");
        }else if (t2 < titulos_nau){
            printf("Isso deve ser coisa do Sport, querem ganhar no tapetão que nem em 87!\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_nau = t2;
    } else if (c2 == 'B') {
        if (t2 > titulos_spo){
            printf("Se antes já era grande a diferença, imagine agora...\n");
        }else if(t2 < titulos_spo){
            printf("Capaz de recorrerem no STJD e recuperarem os títulos no tapetão.\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_spo = t2;
    } else if (c2 == 'C') {
        if (t2 > titulos_sal) {
            printf("Finalmente teve justiça sobre que aconteceu em 2017!\n");
        }else if (t2 < titulos_sal) {
            printf("Foi roubado em 2017 e agora em 2025, existe isso não...\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_sal = t2;
    } else if (c2 == 'D') {
        if (t2 > titulos_san) {
            printf("O Santa é gigante e esse ano vai sair da série D\n");
        }else if (t2 < titulos_san) {
            printf("É muito azar, nem com a SAF as coisas dão certo.\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_san = t2;
    }
    
    if (c3 == 'A') {
        if (t3 > titulos_nau){
            printf("Se contar direitinho ainda tá faltando uns títulos para o Timba...\n");
        }else if (t3 < titulos_nau){
            printf("Isso deve ser coisa do Sport, querem ganhar no tapetão que nem em 87!\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_nau = t3;
    } else if (c3 == 'B') {
        if (t3 > titulos_spo){
            printf("Se antes já era grande a diferença, imagine agora...\n");
        }else if(t3 < titulos_spo){
            printf("Capaz de recorrerem no STJD e recuperarem os títulos no tapetão.\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_spo = t3;
    } else if (c3 == 'C') {
        if (t3 > titulos_sal) {
            printf("Finalmente teve justiça sobre que aconteceu em 2017!\n");
        }else if (t3 < titulos_sal) {
            printf("Foi roubado em 2017 e agora em 2025, existe isso não...\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_sal = t3;
    } else if (c3 == 'D') {
        if (t3 > titulos_san) {
            printf("O Santa é gigante e esse ano vai sair da série D\n");
        }else if (t3 < titulos_san) {
            printf("É muito azar, nem com a SAF as coisas dão certo.\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_san = t3;
    }
    
    if (c4 == 'A') {
        if (t4 > titulos_nau){
            printf("Se contar direitinho ainda tá faltando uns títulos para o Timba...\n");
        }else if (t4 < titulos_nau){
            printf("Isso deve ser coisa do Sport, querem ganhar no tapetão que nem em 87!\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_nau = t4;
    } else if (c4 == 'B') {
        if (t4 > titulos_spo){
            printf("Se antes já era grande a diferença, imagine agora...\n");
        }else if(t4 < titulos_spo){
            printf("Capaz de recorrerem no STJD e recuperarem os títulos no tapetão.\n");
        }else{
            printf("Tem algo estranho aqui...\n");
        }titulos_spo = t4;
    } else if (c4 == 'C') {
        if (t4 > titulos_sal) {
            printf("Finalmente teve justiça sobre que aconteceu em 2017!\n");
        }else if (t4 < titulos_sal) {
            printf("Foi roubado em 2017 e agora em 2025, existe isso não...\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_sal = t4;
    } else if (c4 == 'D') {
        if (t4 > titulos_san) {
            printf("O Santa é gigante e esse ano vai sair da série D\n");
        }else if (t4 < titulos_san) {
            printf("É muito azar, nem com a SAF as coisas dão certo.\n");
        }else {
            printf("Tem algo estranho aqui...\n");
        }titulos_san = t4;
    }
    
    printf("\n");
    
    if (titulos_spo > titulos_nau && titulos_spo > titulos_san && titulos_spo > titulos_sal) {
        printf("1º - Sport - %d - títulos\n", titulos_spo);
        if (titulos_san > titulos_nau && titulos_san > titulos_sal) {
            printf("2º - Santa Cruz - %d - títulos\n", titulos_san);
            if (titulos_nau > titulos_sal) {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            } else {
                printf("3º - Salgueiro - %d - títulos\n", titulos_sal);
            }
        } else if (titulos_nau > titulos_san && titulos_nau > titulos_sal) {
            printf("2º - Náutico - %d - títulos\n", titulos_nau);
            if (titulos_san > titulos_sal) {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            } else {
                printf("3º - Salgueio - %d - títulos\n", titulos_sal);
            }
        } else {
            printf("2º - Salgueiro - %d - títulos\n", titulos_sal);
            if (titulos_san > titulos_nau) {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            } else {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            }
        }
    } else if (titulos_san > titulos_nau && titulos_san > titulos_sal) {
        printf("1º - Santa Cruz - %d - títulos\n", titulos_san);
        if (titulos_spo > titulos_nau && titulos_spo > titulos_sal) {
            printf("2º - Sport - %d - títulos\n", titulos_spo);
            if (titulos_nau > titulos_sal) {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            } else {
                printf("3º - Salgueiro - %d - títulos\n", titulos_sal);
            }
        } else if (titulos_nau > titulos_spo && titulos_nau > titulos_sal) {
            printf("2º - Náutico - %d - títulos\n", titulos_nau);
            if (titulos_spo > titulos_sal) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Salgueiro - %d - títulos\n", titulos_sal);
            }
        } else {
            printf("2º - Salgueiro - %d - títulos\n", titulos_sal);
            if (titulos_spo > titulos_nau) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            }
        }
    } else if (titulos_nau > titulos_sal) {
        printf("1º - Náutico - %d - títulos\n", titulos_nau);
        if (titulos_spo > titulos_san && titulos_spo > titulos_sal) {
            printf("2º - Sport - %d - títulos\n", titulos_spo);
            if (titulos_san > titulos_sal) {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            } else {
                printf("3º - Salgueiro - %d - títulos\n", titulos_sal);
            }
        } else if (titulos_san > titulos_spo && titulos_san > titulos_sal) {
            printf("2º - Santa Cruz - %d - títulos\n", titulos_san);
            if (titulos_spo > titulos_sal) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Salgueiro - %d - títulos\n", titulos_sal);
            }
        } else {
            printf("2º - Salgueiro - %d - títulos\n", titulos_sal);
            if (titulos_spo > titulos_san) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            }
        }
    } else {
        printf("1º - Salgueiro - %d - títulos\n", titulos_sal);
        if (titulos_spo > titulos_san && titulos_spo > titulos_nau) {
            printf("2º - Sport - %d - títulos\n", titulos_spo);
            if (titulos_san > titulos_nau) {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            } else {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            }
        } else if (titulos_san > titulos_spo && titulos_san > titulos_nau) {
            printf("2º - Santa Cruz - %d - títulos\n", titulos_san);
            if (titulos_spo > titulos_nau) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Náutico - %d - títulos\n", titulos_nau);
            }
        } else {
            printf("2º - Náutico - %d - títulos\n", titulos_nau);
            if (titulos_spo > titulos_san) {
                printf("3º - Sport - %d - títulos\n", titulos_spo);
            } else {
                printf("3º - Santa Cruz - %d - títulos\n", titulos_san);
            }
        }
    }
    
    printf("\n");
    
    if (titulos_spo > titulos_nau && titulos_spo > titulos_san && titulos_spo > titulos_sal) {
        printf("Deu o óbvio, o papai da cidade é o Leão!\n");
    } else if (titulos_san > titulos_nau && titulos_san > titulos_sal) {
        printf("É o terror do Nordeste, sempre soube!\n");
    } else if (titulos_nau > titulos_sal) {
        printf("A justiça foi feita, o Timba é o maior do estado, não tem jeito!\n");
    } else {
        printf("Já era o maior do interior, agora é o maior do estado!\n");
    }
    
    return 0;
}
