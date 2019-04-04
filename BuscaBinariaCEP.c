//Código escrito em colaboração por Leonardo Izaú e Mariana Fortes.
#include <stdio.h>
#include <string.h>
#include <locale.h>                                                      //para imprimir os endereços com acento

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

typedef struct _Endereco Endereco;

int main(int argc, char**argv)
{
  	FILE *f;
	Endereco e;
	int i = 0;
	long posicao, inicio, fim, meio;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}
	f = fopen("cep_ordenado.dat","r");                               //abre arquivo
        fseek(f,0,SEEK_END);
	posicao = ftell(f);
	rewind(f);

 	inicio = 0;
  	fim = (posicao/sizeof(Endereco))-1;                              //calcula o numero do ultimo registro
	while(inicio <= fim)
	{
		i++;
		meio = (inicio+fim)/2;
		fseek(f, meio * sizeof(Endereco), SEEK_SET);
		fread(&e,sizeof(Endereco),1,f);                          //le
		if(strncmp(argv[1],e.cep,8) == 0)                        //compara com o cep pesquisado
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep, setlocale (LC_ALL, "portuguese"));                     //caso 1: achou
			break;
		}
		else
			if(strncmp(argv[1],e.cep,8) > 0)                 //caso 2:
				inicio = meio + 1;
			else                                             //caso 3:
	    		fim = meio - 1;

	}
	printf("\nTotal de enderecos lidos: %d", i);
	fclose(f);
	return 0;
}
