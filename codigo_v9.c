#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>//para utilizar o getch()
#include <ctype.h>//para utilizar o isdigit()

char nome[20][50], endereco[20][100], email[20][100], cpfgamb[20][15], telefonegamb[20][10];
int telefone[20], pedido[20][4], i, cm;
long long cpf[20];
int numcadastro, continua=0, numcadastroreal=0, opcao, numcadastroexistentes;
char digitado[50];//armazena o que foi digitado pelo usu�rio
char c;

FILE*numcadastros;
FILE*cadastros;
FILE*pedidos;

void menu()
{
	//subrotina que imprime o menu
	printf("\n\n\tPasteis:\t\t\t\t\t Bebidas:"); 	
	printf("\n1- Pastel de Frango - R$5,00\t\t\t 9- �gua (500ml) - R$2,00");
	printf("\n2- Pastel de Carne  - R$5,00\t\t\t10- Sprite (350ml) - R$4,00");
	printf("\n3- Pastel de Pizza  - R$8,00\t\t\t11- Guaran� (350ml) - R$5,50");
	printf("\n4- Pastel de Bauru  - R$5,00\t\t\t12- Coca-Cola (350ml) - R$6,00");
	printf("\n5- Pastel de Queijo - R$5,00\t\t\t13- Caldo de Cana (500ml) - R$6,00");
	printf("\n6- Pastel de Calabresa - R$5,00\t\t\t14- Suco Natural (350ml) - R$5,00");
	printf("\n7- Pastel de Carne com Queijo - R$8,00\t\t{Laranja / Lim�o / Manga");
	printf("\n8- Pastel de Frango com Queijo - R$8,00\t\t Acerola / Maracuj�}");
	printf("\n0- N�O DESEJA (PARA PASTEL OU BEBIDA)");
}

void menuacompanhamentos()
{
	//subrotina que imprime o menuacompanhamentos
	printf("\n\nAcompanhamentos:"); 	
	printf("\n15- Ketchup");
	printf("\n16- Mostarda");
	printf("\n17- Maionese");
	printf("\n18- Vinagrete");
	printf("\n19- Molho verde");
	printf("\n20- Molho de alho");
	printf("\n0- N�O DESEJA");
}

void informacoescliente()
{
	//subrotina que imprime as informa��es do cliente
	system("cls");
	printf("Nome: %s",nome[numcadastro]);
	printf("\nCPF: %s", cpfgamb[numcadastro]);
	printf("\nE-Mail: %s", email[numcadastro]);
	printf("\nEndere�o: %s",endereco[numcadastro]);
	printf("\nTelefone: %s",telefonegamb[numcadastro]);
}

void numcad()
{
	numcadastros=fopen("numcadastros.txt", "r+");	//abre o arquivo numcadastros.txt em modo de leitura e grava��o para os seguintes processos:
	fscanf(numcadastros,"%d", &numcadastro); 		//faz a leitura do dado inteiro no numcadastros.txt e o atribui a variavel numcadastro
	fclose(numcadastros);  							//fecha e salva o arquivo numcadastros.txt corretamente 
	numcadastro++;									//incrementa 1 na variavel numcadastro para continuar a partir do ultimo numero de cadastro sem repeti-lo
}

void escritadados()
{
	numcadastros=fopen("numcadastros.txt", "w+");	//abre o arquivo numcadastros.txt em modo de escrita e leitura para os seguintes processos:
	if (numcadastros == NULL)
	{
		//caso o arquivo numcadastros.txt n�o seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
		perror("Erro: Arquivo de cadastros n�o encontrado.");
		getchar();
		exit(1);    
	}
	fprintf(numcadastros,"%d", numcadastro);							 //escreve o valor atual de numcadastro no arquivo numcadastros.txt
	fclose(numcadastros);   											 //fecha e salva o arquivo numcadastros.txt corretament
	//escreve as informa��es de cadastro do cliente no arquivo numcadastros.txt   
	cadastros=fopen("cadastros.txt", "a");
	fprintf(cadastros,"%d\n%s\n%lld\n%s\n%s\n%d\n", numcadastro, nome[numcadastro], cpf[numcadastro], email[numcadastro], endereco[numcadastro], telefone[numcadastro]); 
	fclose(cadastros);  
		if(pedido[numcadastro][1]!=0 || pedido[numcadastro][2]!=0)
		{												 //fecha e salva o arquivo cadastros.txt corretament
	//escreve o numcadastro e o pedido referente a este no arquivo numcadastros.txt
			fprintf(pedidos,"CADASTRO:%d PASTEL:%d BEBIDA:%d ACOMPANHAMENTO:%d\n", numcadastro, pedido[numcadastro][1], pedido[numcadastro][2], pedido[numcadastro][3]);  	 
			fclose(pedidos);   													 //fecha e salva o arquivo pedidos.txt corretamente 
		}
}

void validacaonumeros()
{
	//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
	do
    {
	    c=getch();//captura o caractere digitado pelo usu�rio
	    	if (isdigit(c)!=0)//se for um n�mero
	        {  digitado[i] = c;//armazena no vetor de caracteres
	            i++;//incrementa o �ndice do vetor de caracteres
	            printf ("%c", c);//exibe o caractere digitado  
			}
			else if(c==8&&i)//se for pressionada a tecla BACKSPACE e houver caracteres j� digitados
	        {
			    digitado[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string
			    i--;//o �ndice do vetor de caracteres � decrementado
			    printf("\b \b");//o caractere digitado � apagado da tela
	        }
    } while(c!=13);//o loop vai ser executado at� que a tecla pressionada seja o ENTER (c�digo 13 na tabela ASCII)
   
		digitado[i]='\0';//o �ndice atual do vetor de caracteres recebe a termina��o da string
		i=0;
} 


void cadastrocliente()
{
	//subrotina que realiza o cadastro do cliente
	printf("Cadastro: %d",numcadastro);			//num_cadastro
	printf("\nDigite o nome do cliente: ");		//nome_cliente
	scanf(" %[^\n]s",nome[numcadastro]); 		//espa�o antes do % limpa o buffer do teclado
	printf("Informe o CPF: ");					//cpf_cliente
	scanf("%lld",&cpf[numcadastro]);
		//validacao, cpj tem que possuir 11 digitos
		while(cpf[numcadastro]<=10000000001 || cpf[numcadastro]>99999999999)
		{
			printf("\nCPF inv�lido, insira o CPF novamente:\n");
			scanf("%lld",&cpf[numcadastro]);
		}
	printf("Insira o e-mail: ");				//email_cliente
	scanf(" %[^\n]s",email[numcadastro]); 		//espa�o antes do % limpa o buffer do teclado
	printf("Informe o endere�o: ");				//endereco_cliente
	scanf(" %[^\n]s",endereco[numcadastro]); 	//espa�o antes do % limpa o buffer do teclado
	printf("Insira um n�mero de celular: ");	//telefone_cliente
	validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
	telefone[numcadastro] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "telefone[numcadastro]" como um: telefone[numcadastro];
		//validacao, numero de telefone menor que 99999999 ou maior que 999999999 ou que possua digito inicial diferente de 9 (j� que � um celular) � invalido
		while(telefone[numcadastro]<=99999999 || telefone[numcadastro]>999999999 || telefone[numcadastro]/100000000!=9)
		{
			printf("\nN�mero de celular inv�lido, insira um n�mero de 9 digitos com inicio em 9:\n");
			validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
			telefone[numcadastro] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "telefone[numcadastro]" como um: telefone[numcadastro];
		}
}

main()
{	

setlocale(LC_ALL,"Portuguese");

    do
    {
    	cadastros=fopen("cadastros.txt", "a");
		if (cadastros == NULL)
		{
			//caso o arquivo cadastros.txt n�o seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
			perror("Erro: Arquivo de cadastros n�o encontrado.");
			getchar();
			exit(1);    
		} 
		fclose(cadastros);
		
		pedidos=fopen("pedidos.txt", "a");
		if (pedidos == NULL)
		{
			//caso o arquivo pedidos.txt n�o seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
			perror("Erro: Arquivo de cadastros n�o encontrado.");
			getchar();
			exit(1);    
		}
		
			numcadastros=fopen("numcadastros.txt", "r+");
			fscanf(numcadastros,"%d", &numcadastroexistentes);
			fclose(numcadastros);  
			cadastros=fopen("cadastros.txt", "r+");	
				for(cm=0;cm<numcadastroexistentes;cm++)
				{			
					fscanf(cadastros, "%d", &numcadastro);
					fscanf(cadastros, "\n%[^\n]s", &nome[numcadastro]);
					fscanf(cadastros, "\n%[^\n]s", cpfgamb[numcadastro]);
					fscanf(cadastros, "\n%[^\n]s", email[numcadastro]);
					fscanf(cadastros, "\n%[^\n]s", endereco[numcadastro]);
					fscanf(cadastros, "\n%[^\n]s", telefonegamb[numcadastro]);  
				} 
			fclose(cadastros);
    		system("cls");
    		printf("\n\t\t\t\t\tBem vindo ao 'La Casa de Pastell'");	  	
			menu(); //subrotina que imprime o menu
    		printf("\n\nDeseja realizar qual opera��o?		1-Cadastro		2-Verifica��o		3-Realizar Pedido\n");
    		validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
			opcao = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "opcao" como um: scanf("%d",&opcao);
    		//estrutura de sele��o multipla escolha:
			//caso 1 = cadastro de cliente novo + realiza��o de pedido, caso 2 = verifica��o de cadastro, caso 3 = realiza��o de outro pedido (cadastro ja feito)
		      	switch(opcao)
				{
				 	case 1:
				  		//cadastro de clientes + realiza��o primeiro pedido
				  		system("cls");
				  		numcad();								//subrotina que inicia o numcadastro
					  	cadastrocliente();  					//subrotina que realiza o cadastro do cliente
					    menu(); 								//subrotina que imprime o menu
				    		printf("\n\nPastel desejado: ");
				    		validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
							pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
			    				//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
					  			while(pedido[numcadastro][1]<0 || pedido[numcadastro][1]>8)
					  			{
					  				printf("\nN�mero de pedido inv�lido, insira um n�mero de 1 a 8 ou 0:\n");
					  				validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
									pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
								}
							printf("\n\nBebida desejada: ");
							validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
								if(pedido[numcadastro][2]==0)
								pedido[numcadastro][2]==0;
								else
								{
				    				//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
						  			while(pedido[numcadastro][2]<9 || pedido[numcadastro][2]>14)
						  			{
						  				printf("\nN�mero de pedido inv�lido, insira um n�mero de 9 a 14 ou 0:\n");
						  				validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
										pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
									}
								}
								//acompanhamento:
									if (pedido[numcadastro][1]>=1 && pedido[numcadastro][1]<=8)
									{
										menuacompanhamentos();
										printf("\n\nAcompanhamento desejado: ");
										validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
										pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
						    				if(pedido[numcadastro][3]==0)
											pedido[numcadastro][3]==0;
											else
											{
												//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
								  				while(pedido[numcadastro][3]<15 || pedido[numcadastro][3]>20)
								  				{
								  					printf("\nN�mero de acompanhamento inv�lido, insira um n�mero de 15 a 20 ou 0:\n");
								  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
													pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
												}
											}
									}
							escritadados();		
				  		break; 
				  	case 2:
				  		//verifica�ao ou checagem de cadastros ja existentes
				  		system("cls");
				  		numcadastroreal=numcadastro;	
			  			printf("Digite o numero do cadastro que deseja visualizar: ");
						//requisita o numero de cadastro (numcadastro) que o funcionario deseja buscar informa��es...
						validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
						numcadastro = atoi(digitado); 	//atribui os numeros inseridos antes na variavel pedido[numcadastro][3] como um: scanf("%d",&pedido[numcadastro][3]);
							//valida��o (n�o existe numero de cadastro menor que 1)
			  				while(numcadastro<1)
			  				{
			  					printf("\nValor de cadastro inv�lido, insira outro n�mero de cadastro:\n");
			  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
								numcadastro = atoi(digitado); 	//atribui os numeros inseridos antes na variavel pedido[numcadastro][3] como um: scanf("%d",&pedido[numcadastro][3]);
							} 
								//busca se o cadastro procurado ja foi realizado
								if(numcadastro<=numcadastroexistentes)
								{
									//se h� confirma��o de que esse numero de cadastro ja foi cadastrado:
						  			informacoescliente(); 			//subrotina que imprime as informa��es do cliente
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
					    		}
					    		else
					    		{
					    			system("cls");
					    			printf("Esse n�mero de cadastro (%d) ainda n�o foi realizado.\n", numcadastro);
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
								}
				  		break;
				  	case 3:
				  		//realizar pedido ja com cadastro
				  		system("cls");
				  		printf("Insira o n�mero do cadastro para realizar um pedido: ");
				  		numcadastroreal=numcadastro;		//armazena o atual numero de cadastro (numcadastro) em outra variavel (numcadastroreal) para recupera-la posteriormente	
						validacaonumeros(); 				//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
	    				numcadastro = atoi(digitado);		//atribui os numeros inseridos antes na variavel "numcadastro" como um: scanf("%d",&numcadastro);	
			  				//valida��o (n�o existe numero de cadastro menor que 1)
			  				while(numcadastro<1)
			  				{
			  					printf("\nValor de cadastro inv�lido, insira outro n�mero de cadastro:\n");	
			  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
	    						numcadastro = atoi(digitado);			//atribui os numeros inseridos antes na variavel "numcadastro" como um: scanf("%d",&numcadastro);		
							}
								//busca se o cadastro procurado ja foi realizado
					  			if (numcadastro<=numcadastroexistentes)
								{
									//se h� confirma��o de que esse numero de cadastro ja foi cadastrado:
									informacoescliente();  					//subrotina que imprime as informa��es do cliente
						  			menu();									//subrotina que imprime o menu
					    			printf("\n\nPastel desejado: ");
							    	validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
			    					pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
					    				//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
							  				while(pedido[numcadastro][1]<0 || pedido[numcadastro][1]>8)
							  				{
							  					printf("\nN�mero de pedido inv�lido, insira um n�mero de 1 a 8 ou 0:\n");
							  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
				    							pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
											}
									printf("\n\nBebida desejada: ");
				    				validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
	    							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
				    					if(pedido[numcadastro][2]==0)
										pedido[numcadastro][2]==0;
										else
										{
										//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
							  				while(pedido[numcadastro][2]<9 || pedido[numcadastro][2]>14)
							  				{
							  					printf("\nN�mero de pedido inv�lido, insira um n�mero de 9 a 14 ou 0:\n");
							  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
				    							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
											}
										}
										//acompanhamentos
											if (pedido[numcadastro][1]>=1 && pedido[numcadastro][1]<=8)
											{
												menuacompanhamentos();
												printf("\n\nAcompanhamento desejado: ");
								    			validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais)
					    						pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
								    				if(pedido[numcadastro][3]==0)
													pedido[numcadastro][3]==0;
													else
													{
														//valida��o (remove op��o de inserir pedidos inferiores ou maiores do que a op��o do menu)
										  				while(pedido[numcadastro][3]<15 || pedido[numcadastro][3]>20)
										  				{
										  					printf("\nN�mero de acompanhamento inv�lido, insira um n�mero de 15 a 20 ou 0:\n");
										  					validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
							    							pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
														}	
													}
											}
									if(pedido[numcadastro][1]!=0 || pedido[numcadastro][2]!=0)
									{
										pedidos=fopen("pedidos.txt", "a");	//fecha e salva o arquivo pedidos.txt corretamente 	
										fprintf(pedidos,"CADASTRO:%d PASTEL:%d BEBIDA:%d ACOMPANHAMENTO:%d\n", numcadastro, pedido[numcadastro][1], pedido[numcadastro][2], pedido[numcadastro][3]);  	//escreve o numcadastro e o acompanhamento referente a este no arquivo numcadastros.txt
										fclose(pedidos);
									}
									numcadastroreal=numcadastro;		//armazena o atual numero de cadastro (numcadastro) em outra variavel (numcadastroreal) para recupera-la posteriormente 							
					    		}
					    		else
					    		{
					    			system("cls");
					    			printf("� preciso realizar um cadastro nesse n�mero (%d) antes de realizar um pedido.\n", numcadastro);
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
								}
			    		break;
				  	default:
				  		printf("\nValor inv�lido.");
				  		break; 
				}
			printf("\n\nDeseja realizar outro processo?		1-Sim		2-N�o\n");
			validacaonumeros(); 					//requisita e s� permite a inser��o de n�meros (tamb�m remove caracteres especiais).
			continua = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "continua" como um: scanf("%d",&continua);
   }	while(continua!=2);
   
system("cls");
printf("\n\t\t\t\t\tAgrade�emos a preferencia!.\n");
printf("\t\t\t\tObrigado por utilizar nossos servi�os!!!\n\n\n\n\n\n");
system("pause");
}
