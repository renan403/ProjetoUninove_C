#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <conio.h>//para utilizar o getch()
#include <ctype.h>//para utilizar o isdigit()

char nome[20][50], endereco[20][100], email[20][100], cpfgamb[20][15], telefonegamb[20][10];
int telefone[20], pedido[20][4], i, cm;
long long cpf[20];
int numcadastro, continua=0, numcadastroreal=0, opcao, numcadastroexistentes;
char digitado[50];//armazena o que foi digitado pelo usuário
char c;

FILE*numcadastros;
FILE*cadastros;
FILE*pedidos;

void menu()
{
	//subrotina que imprime o menu
	printf("\n\n\tPasteis:\t\t\t\t\t Bebidas:"); 	
	printf("\n1- Pastel de Frango - R$5,00\t\t\t 9- Água (500ml) - R$2,00");
	printf("\n2- Pastel de Carne  - R$5,00\t\t\t10- Sprite (350ml) - R$4,00");
	printf("\n3- Pastel de Pizza  - R$8,00\t\t\t11- Guaraná (350ml) - R$5,50");
	printf("\n4- Pastel de Bauru  - R$5,00\t\t\t12- Coca-Cola (350ml) - R$6,00");
	printf("\n5- Pastel de Queijo - R$5,00\t\t\t13- Caldo de Cana (500ml) - R$6,00");
	printf("\n6- Pastel de Calabresa - R$5,00\t\t\t14- Suco Natural (350ml) - R$5,00");
	printf("\n7- Pastel de Carne com Queijo - R$8,00\t\t{Laranja / Limão / Manga");
	printf("\n8- Pastel de Frango com Queijo - R$8,00\t\t Acerola / Maracujá}");
	printf("\n0- NÃO DESEJA (PARA PASTEL OU BEBIDA)");
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
	printf("\n0- NÃO DESEJA");
}

void informacoescliente()
{
	//subrotina que imprime as informações do cliente
	system("cls");
	printf("Nome: %s",nome[numcadastro]);
	printf("\nCPF: %s", cpfgamb[numcadastro]);
	printf("\nE-Mail: %s", email[numcadastro]);
	printf("\nEndereço: %s",endereco[numcadastro]);
	printf("\nTelefone: %s",telefonegamb[numcadastro]);
}

void numcad()
{
	numcadastros=fopen("numcadastros.txt", "r+");	//abre o arquivo numcadastros.txt em modo de leitura e gravação para os seguintes processos:
	fscanf(numcadastros,"%d", &numcadastro); 		//faz a leitura do dado inteiro no numcadastros.txt e o atribui a variavel numcadastro
	fclose(numcadastros);  							//fecha e salva o arquivo numcadastros.txt corretamente 
	numcadastro++;									//incrementa 1 na variavel numcadastro para continuar a partir do ultimo numero de cadastro sem repeti-lo
}

void escritadados()
{
	numcadastros=fopen("numcadastros.txt", "w+");	//abre o arquivo numcadastros.txt em modo de escrita e leitura para os seguintes processos:
	if (numcadastros == NULL)
	{
		//caso o arquivo numcadastros.txt não seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
		perror("Erro: Arquivo de cadastros não encontrado.");
		getchar();
		exit(1);    
	}
	fprintf(numcadastros,"%d", numcadastro);							 //escreve o valor atual de numcadastro no arquivo numcadastros.txt
	fclose(numcadastros);   											 //fecha e salva o arquivo numcadastros.txt corretament
	//escreve as informações de cadastro do cliente no arquivo numcadastros.txt   
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
	//requisita e só permite a inserção de números (também remove caracteres especiais)
	do
    {
	    c=getch();//captura o caractere digitado pelo usuário
	    	if (isdigit(c)!=0)//se for um número
	        {  digitado[i] = c;//armazena no vetor de caracteres
	            i++;//incrementa o índice do vetor de caracteres
	            printf ("%c", c);//exibe o caractere digitado  
			}
			else if(c==8&&i)//se for pressionada a tecla BACKSPACE e houver caracteres já digitados
	        {
			    digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
			    i--;//o índice do vetor de caracteres é decrementado
			    printf("\b \b");//o caractere digitado é apagado da tela
	        }
    } while(c!=13);//o loop vai ser executado até que a tecla pressionada seja o ENTER (código 13 na tabela ASCII)
   
		digitado[i]='\0';//o índice atual do vetor de caracteres recebe a terminação da string
		i=0;
} 


void cadastrocliente()
{
	//subrotina que realiza o cadastro do cliente
	printf("Cadastro: %d",numcadastro);			//num_cadastro
	printf("\nDigite o nome do cliente: ");		//nome_cliente
	scanf(" %[^\n]s",nome[numcadastro]); 		//espaço antes do % limpa o buffer do teclado
	printf("Informe o CPF: ");					//cpf_cliente
	scanf("%lld",&cpf[numcadastro]);
		//validacao, cpj tem que possuir 11 digitos
		while(cpf[numcadastro]<=10000000001 || cpf[numcadastro]>99999999999)
		{
			printf("\nCPF inválido, insira o CPF novamente:\n");
			scanf("%lld",&cpf[numcadastro]);
		}
	printf("Insira o e-mail: ");				//email_cliente
	scanf(" %[^\n]s",email[numcadastro]); 		//espaço antes do % limpa o buffer do teclado
	printf("Informe o endereço: ");				//endereco_cliente
	scanf(" %[^\n]s",endereco[numcadastro]); 	//espaço antes do % limpa o buffer do teclado
	printf("Insira um número de celular: ");	//telefone_cliente
	validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
	telefone[numcadastro] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "telefone[numcadastro]" como um: telefone[numcadastro];
		//validacao, numero de telefone menor que 99999999 ou maior que 999999999 ou que possua digito inicial diferente de 9 (já que é um celular) é invalido
		while(telefone[numcadastro]<=99999999 || telefone[numcadastro]>999999999 || telefone[numcadastro]/100000000!=9)
		{
			printf("\nNúmero de celular inválido, insira um número de 9 digitos com inicio em 9:\n");
			validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
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
			//caso o arquivo cadastros.txt não seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
			perror("Erro: Arquivo de cadastros não encontrado.");
			getchar();
			exit(1);    
		} 
		fclose(cadastros);
		
		pedidos=fopen("pedidos.txt", "a");
		if (pedidos == NULL)
		{
			//caso o arquivo pedidos.txt não seja encontrado ou seja impossivel de acessa-lo, encerra o programa ser prossegui-lo
			perror("Erro: Arquivo de cadastros não encontrado.");
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
    		printf("\n\nDeseja realizar qual operação?		1-Cadastro		2-Verificação		3-Realizar Pedido\n");
    		validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
			opcao = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "opcao" como um: scanf("%d",&opcao);
    		//estrutura de seleção multipla escolha:
			//caso 1 = cadastro de cliente novo + realização de pedido, caso 2 = verificação de cadastro, caso 3 = realização de outro pedido (cadastro ja feito)
		      	switch(opcao)
				{
				 	case 1:
				  		//cadastro de clientes + realização primeiro pedido
				  		system("cls");
				  		numcad();								//subrotina que inicia o numcadastro
					  	cadastrocliente();  					//subrotina que realiza o cadastro do cliente
					    menu(); 								//subrotina que imprime o menu
				    		printf("\n\nPastel desejado: ");
				    		validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
							pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
			    				//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
					  			while(pedido[numcadastro][1]<0 || pedido[numcadastro][1]>8)
					  			{
					  				printf("\nNúmero de pedido inválido, insira um número de 1 a 8 ou 0:\n");
					  				validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
									pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
								}
							printf("\n\nBebida desejada: ");
							validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
								if(pedido[numcadastro][2]==0)
								pedido[numcadastro][2]==0;
								else
								{
				    				//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
						  			while(pedido[numcadastro][2]<9 || pedido[numcadastro][2]>14)
						  			{
						  				printf("\nNúmero de pedido inválido, insira um número de 9 a 14 ou 0:\n");
						  				validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
										pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
									}
								}
								//acompanhamento:
									if (pedido[numcadastro][1]>=1 && pedido[numcadastro][1]<=8)
									{
										menuacompanhamentos();
										printf("\n\nAcompanhamento desejado: ");
										validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
										pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
						    				if(pedido[numcadastro][3]==0)
											pedido[numcadastro][3]==0;
											else
											{
												//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
								  				while(pedido[numcadastro][3]<15 || pedido[numcadastro][3]>20)
								  				{
								  					printf("\nNúmero de acompanhamento inválido, insira um número de 15 a 20 ou 0:\n");
								  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
													pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
												}
											}
									}
							escritadados();		
				  		break; 
				  	case 2:
				  		//verificaçao ou checagem de cadastros ja existentes
				  		system("cls");
				  		numcadastroreal=numcadastro;	
			  			printf("Digite o numero do cadastro que deseja visualizar: ");
						//requisita o numero de cadastro (numcadastro) que o funcionario deseja buscar informações...
						validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
						numcadastro = atoi(digitado); 	//atribui os numeros inseridos antes na variavel pedido[numcadastro][3] como um: scanf("%d",&pedido[numcadastro][3]);
							//validação (não existe numero de cadastro menor que 1)
			  				while(numcadastro<1)
			  				{
			  					printf("\nValor de cadastro inválido, insira outro número de cadastro:\n");
			  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
								numcadastro = atoi(digitado); 	//atribui os numeros inseridos antes na variavel pedido[numcadastro][3] como um: scanf("%d",&pedido[numcadastro][3]);
							} 
								//busca se o cadastro procurado ja foi realizado
								if(numcadastro<=numcadastroexistentes)
								{
									//se há confirmação de que esse numero de cadastro ja foi cadastrado:
						  			informacoescliente(); 			//subrotina que imprime as informações do cliente
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
					    		}
					    		else
					    		{
					    			system("cls");
					    			printf("Esse número de cadastro (%d) ainda não foi realizado.\n", numcadastro);
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
								}
				  		break;
				  	case 3:
				  		//realizar pedido ja com cadastro
				  		system("cls");
				  		printf("Insira o número do cadastro para realizar um pedido: ");
				  		numcadastroreal=numcadastro;		//armazena o atual numero de cadastro (numcadastro) em outra variavel (numcadastroreal) para recupera-la posteriormente	
						validacaonumeros(); 				//requisita e só permite a inserção de números (também remove caracteres especiais)
	    				numcadastro = atoi(digitado);		//atribui os numeros inseridos antes na variavel "numcadastro" como um: scanf("%d",&numcadastro);	
			  				//validação (não existe numero de cadastro menor que 1)
			  				while(numcadastro<1)
			  				{
			  					printf("\nValor de cadastro inválido, insira outro número de cadastro:\n");	
			  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais)
	    						numcadastro = atoi(digitado);			//atribui os numeros inseridos antes na variavel "numcadastro" como um: scanf("%d",&numcadastro);		
							}
								//busca se o cadastro procurado ja foi realizado
					  			if (numcadastro<=numcadastroexistentes)
								{
									//se há confirmação de que esse numero de cadastro ja foi cadastrado:
									informacoescliente();  					//subrotina que imprime as informações do cliente
						  			menu();									//subrotina que imprime o menu
					    			printf("\n\nPastel desejado: ");
							    	validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais)
			    					pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
					    				//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
							  				while(pedido[numcadastro][1]<0 || pedido[numcadastro][1]>8)
							  				{
							  					printf("\nNúmero de pedido inválido, insira um número de 1 a 8 ou 0:\n");
							  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
				    							pedido[numcadastro][1] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][1]" como um: scanf("%d",&pedido[numcadastro][1]);
											}
									printf("\n\nBebida desejada: ");
				    				validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais)
	    							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
				    					if(pedido[numcadastro][2]==0)
										pedido[numcadastro][2]==0;
										else
										{
										//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
							  				while(pedido[numcadastro][2]<9 || pedido[numcadastro][2]>14)
							  				{
							  					printf("\nNúmero de pedido inválido, insira um número de 9 a 14 ou 0:\n");
							  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
				    							pedido[numcadastro][2] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][2]" como um: scanf("%d",&pedido[numcadastro][2]);
											}
										}
										//acompanhamentos
											if (pedido[numcadastro][1]>=1 && pedido[numcadastro][1]<=8)
											{
												menuacompanhamentos();
												printf("\n\nAcompanhamento desejado: ");
								    			validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais)
					    						pedido[numcadastro][3] = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "pedido[numcadastro][3]" como um: scanf("%d",&pedido[numcadastro][3]);
								    				if(pedido[numcadastro][3]==0)
													pedido[numcadastro][3]==0;
													else
													{
														//validação (remove opção de inserir pedidos inferiores ou maiores do que a opção do menu)
										  				while(pedido[numcadastro][3]<15 || pedido[numcadastro][3]>20)
										  				{
										  					printf("\nNúmero de acompanhamento inválido, insira um número de 15 a 20 ou 0:\n");
										  					validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
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
					    			printf("É preciso realizar um cadastro nesse número (%d) antes de realizar um pedido.\n", numcadastro);
					    			numcadastro=numcadastroreal; 	//retorna o atual numero de cadastros(numcadastroreal) a sua variavel oficial(numcadastro)
								}
			    		break;
				  	default:
				  		printf("\nValor inválido.");
				  		break; 
				}
			printf("\n\nDeseja realizar outro processo?		1-Sim		2-Não\n");
			validacaonumeros(); 					//requisita e só permite a inserção de números (também remove caracteres especiais).
			continua = atoi(digitado); 	//atribui os numeros inseridos antes na variavel "continua" como um: scanf("%d",&continua);
   }	while(continua!=2);
   
system("cls");
printf("\n\t\t\t\t\tAgradeçemos a preferencia!.\n");
printf("\t\t\t\tObrigado por utilizar nossos serviços!!!\n\n\n\n\n\n");
system("pause");
}
