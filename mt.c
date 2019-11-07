#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(){
    char binNumber[] = {" 11"};
    printf("Valor Actual: %s\n", binNumber);
    // char x = binNumber[1];
    // printf("%c\n", x);
    // if(x == '0')
    //     printf("simon\n");
    
    
    int estado = 0;
    int i = 0;
    int limit = strlen(binNumber);
    while(i <= limit){
        //printf("%d\n",i);
        char x = binNumber[i];
        
        if(estado == 0){
                if(x == '1' || x == '0'||x == ' '){
                    estado = 0;
                    i++;
                }else if(x == '\0'){
                    estado = 1;
                    
                }
        }
        else if(estado == 1){
                if(i == limit)
                    i--;
                //printf("n: %d\n",i);
                if (x == '1' ){
                    binNumber[i] = '0'; 
                    i--;
                }else if(x == '0' || x==' '){
                    binNumber[i] = '1';
                    break;
                }
        }

    }
    printf("Nuevo valor: %s\n", binNumber);
    return 0;   
}
