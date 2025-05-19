#include  <stdio.h>

int main(){

    int dia,mes,ano;
    int invalida = 0 ;
    int bisex = 0;
    
    
    int test;

    scanf("%d %d %d", &dia, &mes, &ano);
    
    //printf("%d", ano);
    //checa se o mes é valido
    if (mes <= 12){
        switch (mes){
        case 1:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 2:
            if((ano%4 == 0 && ano%100 != 0) || ano%400 == 0 ){
                bisex = 1;
            };
            if(dia <= 29){
                if(bisex == 0 && dia == 29){
                    invalida =1;
            };
            break;
        case 3:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 4:
            if (dia > 30){
                invalida = 1;
            };
            break;
        case 5:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 6:
            if (dia > 30){
                invalida = 1;
            };
            break;
        case 7:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 8:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 9:
            if (dia > 30){
                invalida = 1;
            };
            break;
        case 10:
            if (dia > 31){
                invalida = 1;
            };
            break;
        case 11:
            if (dia > 30){
                invalida = 1;
            };
            break;
        case 12:
            if (dia > 31){
                invalida = 1;
            };
            break;
        default:
            break;
        }
    }
    }else{
        invalida = 1;
    };
    
    if(ano < 0 || mes < 0 || dia < 0){
        invalida = 1;
    };
    
    
        
    if(invalida > 0){
        printf("invalida");
    }else{
        printf("valida");
    };

    return 0;

}