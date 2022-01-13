#include <stdio.h>
#include <stdlib.h>

void hamming(int *palavra);

void hamming(int *palavra){
	int soma = 0;
	int saida[16], bit_rec[5];

	for (int i = 0; i < 16; i++){
		saida[i] = palavra [i];
	}

	// Descobrindo a paridade dos bits recebidos
	for (int i = 0; i < 5; i++){
		switch(i){
			case 0: // bit 1
				bit_rec[i] = palavra[0]^palavra[2]^palavra[4]^
							palavra[5]^palavra[7]^palavra[9]^
							palavra[11]^palavra[12]^palavra[14]^
							palavra[15];

				break;

			case 1: // bit 2
				bit_rec[i] = palavra[2]^palavra[3]^palavra[5]^
							palavra[6]^palavra[9]^palavra[10]^
							palavra[12]^palavra[13]^palavra[15];

				break;

			case 2:// bit 4
				bit_rec[i] = palavra[0]^palavra[1]^palavra[5]^
							palavra[6]^palavra[7]^palavra[8]^
							palavra[12]^palavra[13]^palavra[14];

				break;

			case 3:// bit 8
				bit_rec[i] = palavra[5]^palavra[6]^palavra[7]^
							palavra[8]^palavra[9]^palavra[10]^
							palavra[11];

				break;

			case 4:// bit 16
				bit_rec[i] = palavra[0]^palavra[1]^palavra[2]^
							palavra[3]^palavra[4];

				break;
		}

	}

	// Comparacao das paridades recebidas com os valores certos
	for (int i = 0; i < 5; ++i){
		switch(i){
			case 0: // bit 1
				if(bit_rec[i] != palavra[20])
					soma += 1;
				break;
			case 1: // bit 2
				if(bit_rec[i] != palavra[19])
					soma += 2;
				break;

			case 2:// bit 4
				if(bit_rec[i] != palavra[18])
					soma += 4;
				break;

			case 3:// bit 8
				if(bit_rec[i] != palavra[17])
					soma += 8;
				break;

			case 4:// bit 16
				if(bit_rec[i] != palavra[16])
					soma += 16;
				break;
		}
	}

	// Inversao do valor do bit com erro
	switch(soma){
		case 3: 
			saida[15] = !saida[15];
			break;
		case 5: 
			saida[14] = !saida[14];
			break;
		case 6: 
			saida[13] = !saida[13];
			break;
		case 7:
			saida[12] = !saida[12];
			break;
		case 9: 
			saida[11] = !saida[11];
			break;		
		case 10:
			saida[10] = !saida[10];
			break; 
		case 11: 
			saida[9] = !saida[9];
			break;
		case 12: 
			saida[8] = !saida[8];
			break;
		case 13: 
			saida[7] = !saida[7];
			break;
		case 14:
			saida[6] = !saida[6];
			break;
		case 15:
			saida[5] = !saida[5];
			break;
		case 17:
			saida[4] = !saida[4];
			break;
		case 18:
			saida[3] = !saida[3];
			break;
		case 19:
			saida[2] = !saida[2];
			break;
		case 20:
			saida[1] = !saida[1];
			break;
		case 21:
			saida[0] = !saida[0];
			break;
	}

	//Exibicao da palavra recebida corrigida
	for (int i = 0; i < 16; ++i){
		printf("%d", saida[i]);
	}

	printf("\n");

}

int main(int argc, char *argv[]){
	int qtd;
	int **palavras;
	FILE *arq = fopen(argv[1], "r");
    while (!feof(arq)) {
        fscanf(arq, "%d\n", &qtd);  
        palavras = (int **)malloc(qtd * sizeof(int *)); // aloca quantidade de linhas

	    for (int j = 0; j < qtd; j++){
	    	char extra;
	    	palavras[j] = (int *)malloc(21 * sizeof(int)); // aloca quantidade de colunas

			for(int i = 0; i < 21; i++){
				char aux;
		        fscanf(arq, "%c", &aux);
		        palavras[j][i] = atoi(&aux); // transforma em char em int
	       	}  
	       	fscanf(arq, "%c", &extra); // exclui o caracter fim de linha
		}
    }

    fclose(arq);

	printf("\nPalavras de entrada: \n");

    for (int i = 0; i < qtd; ++i){
    	for (int j = 0; j < 21; ++j)
    	{
    		printf("%d", palavras[i][j]);
    	}
    	printf("\n");
    }

    printf("\nPalavras de saida: \n");
    for (int i = 0; i < qtd; i++){
    	hamming(palavras[i]);
    }
	    
    return 0;
}