/*GRUPO: NICOLAS JIRO HIGA TAKEMOTO; 
		GABRIEL ALVES DOS SANTOS
		VINICIUS EDUARDO PINHEIRO DE JESUS	 */
			 
//*RECOMENDA-SE DEIXAR O TERMINAL EM TELA CHEIA PARA UMA MELHOR VISUALIZAÇÃO DOS DADOS!*

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h> //Biblioteca para função sleep

#define AUTORES "Autores.dat"
#define CATEGORIAS "Categorias.dat"
#define EDITORAS "Editoras.dat"
#define LIVROS "Livros.dat"

struct reg_autores{
	int cod;
	char nome[35];
	char sobrenome[15];
};
struct reg_categorias{
	int cod;
	char descricao[20];
};
struct reg_editoras{
	int cod;
	char nomeEditora[35];
	char nomeContato[35];
	char fone[14];
	char email[35];
};
struct reg_livros{
	int cod;
	char titulo[30];
	float preco;
	int autor1, autor2, autor3, autor4;
	int categoria, editora, edicao, ano, qnt;
};

//Função buscar Autor para cadastro do livro
int buscarAutor(int i, int escolha){
	FILE *fpautores;
	struct reg_autores autores;
	int achou, cod;
	char opc;
				
	do{	
		fpautores = fopen(AUTORES, "rb");
		achou = 0;			
		fflush(stdin); scanf("%i", &cod);
		if(cod == -1){ //Se o usuario quiser sair
			printf("\nOPERACAO CANCELADA!!!");
			Sleep(1500);
			system("cls");
			break;
		} else if(cod != 0) {
				while((achou == 0) && (fread(&autores, sizeof(autores), 1,  fpautores))){
					if(autores.cod == cod){
						printf("\nNome: %s %s", autores.nome,  autores.sobrenome); //Imprime nome do autor encontrado
						achou = 1;
						
						if(achou == 1){
							printf("\nConfirmar autor(S/N)? "); //Pede confirmação
							fflush(stdin); scanf("%c", &opc);
							if((opc == 'n') || (opc == 'N')){
								printf("\n*Tente novamente ou digite -1 para sair*");
								printf("\n*--------------------------------------*");
								if(escolha == 0){
									printf("\nAutor %i: ", i); //Imprime para função de cadastrar
								} else{
									printf("\nDigite o codigo do autor que procura: "); //Imprime no relatório de livros de um autor
								}
							}
						}
					}
				}
				if (achou == 0){ //Caso não ache nada:
					printf("\n*Autor nao encontrado! Tente novamente ou digite -1 para sair*");
					printf("\n*------------------------------------------------------------*");
					if(escolha == 0){
						printf("\nAutor %i: ", i); //Imprime para função de cadastrar
					} else{
						printf("\nDigite o codigo do autor que procura: "); //Imprime no relatório de livros de um autor
					}
					opc = 'N'; //Automaticamente opc se torna NÃO para refazer o processo
				}
		}
		fclose(fpautores);
	}while((opc == 'N') || (opc == 'n'));
	
	return cod;
}
//Função de imprimir confirmação de voltar ao menu
void retornarMenu(){
	int voltar;
	
	do{
		printf("\n\n\n*Digite 0 para voltar: ");
		fflush(stdin); scanf("%i", &voltar);
		if(voltar == 0){
			system("cls");
			return;
			}
		}while(voltar != 0); //Opcao de retornar ao menu
}
//Buscar Categoria
int buscarCategoria(){
	FILE *fpcategorias;
	struct reg_categorias categorias;
	int cod, achou;
	char opc;
	
	do{
		fpcategorias = fopen(CATEGORIAS, "rb");
		printf("\nCodigo da categoria: "); //Entrada dos dados
		fflush(stdin); scanf("%i", &cod);
		if(cod == -1){ //Caso cancele:
			printf("\nOPERACAO CANCELADA!!!");
			Sleep(1500);
			system("cls");
			return cod;
		}
		achou = 0;
		while((achou == 0) && (fread(&categorias, sizeof(categorias), 1, fpcategorias))){
			if(categorias.cod == cod){
				printf("\nCategoria %s", categorias.descricao);
				achou = 1;
				printf("\nConfirmar categoria(S/N)?"); //Confirmação pelo usuário
				fflush(stdin); scanf("%c", &opc);
				if((opc == 'n') || (opc == 'N')){
						printf("\n*Tente novamente ou digite -1 para sair*");
						printf("\n*--------------------------------------*");
				}
			}
		}
		if(achou == 0){ //Caso nada seja encontrado:
				printf("\n*Categoria nao encontrado! Tente novamente ou digite -1 para sair*");
				printf("\n*----------------------------------------------------------------*");
		}
		fclose(fpcategorias);	
	}while((opc == 'n')||(opc == 'N'));
	
	return cod;
}
//Cabeçalho para listagem de livros
void cabecalhoLivros(){
	printf("\n\n*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*");
	printf("\n|                                                                                  LIVROS                                                                                                   |");
	printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
	printf("\n|CODIGO | TITULO                         | PRECO  | AUTORES                                             | CATEGORIA            | EDITORA                             | ANO  | EDICAO | QNT  |");
	printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
}
void cabecalhoAutores(){
	printf("*------------------------------------------------------------*");
	printf("\n|                        AUTORES                             |");
	printf("\n+------------------------------------------------------------+");
	printf("\n|CODIGO | NOME COMPLETO                                      |");
	printf("\n+------------------------------------------------------------+");
}
//Função para listar livros
void listarLivros(struct reg_livros *livros){
	int achou;
	struct reg_categorias categorias;
	struct reg_autores autores;
	struct reg_editoras editoras;
	FILE *fpautores, *fpeditoras, *fpcategorias;
	
	//Procura categoria	
	achou = 0;
	fpcategorias = fopen(CATEGORIAS,  "rb");
	while((achou == 0)&&(fread(&categorias, sizeof(categorias), 1, fpcategorias) == 1)){
		if(categorias.cod == livros->categoria){
			achou = 1;
		}
	}
	//Procura editora
	achou = 0;
	fpeditoras = fopen(EDITORAS,  "rb");
	while((achou == 0)&&(fread(&editoras, sizeof(editoras), 1, fpeditoras) == 1)){
		if(editoras.cod == livros->editora){
			achou = 1;
		}
	}
	//Procura autores
	achou = 0; //Autor 1
	char autor1[51]="", autor2[51]="", autor3[51]="", autor4[51]="";
	fpautores = fopen(AUTORES,  "rb");
	while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
		if(autores.cod == livros->autor1){
			strcat(strcat(strcat(autor1, autores.nome), " "), autores.sobrenome);//Salva nome completo do autor em uma string nova
			achou = 1;
		}
	}
	//Verifica se possui mais autores
	if(livros->autor2 != 0){//Autor 2
		achou = 0;
		fpautores = fopen(AUTORES,  "rb");
		while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
			if(autores.cod == livros->autor2){
				strcat(strcat(strcat(autor2, autores.nome), " "), autores.sobrenome);
				achou = 1;
			}
		}
		if(livros->autor3 != 0){//Autor 3
			achou = 0;
			fpautores = fopen(AUTORES,  "rb");
			while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
				if(autores.cod == livros->autor3){
				strcat(strcat(strcat(autor3, autores.nome), " "), autores.sobrenome);
				achou = 1;
				}
			}
			if(livros->autor4 != 0){//Autor 4
				achou = 0;
				fpautores = fopen(AUTORES,  "rb");
				while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){	
					if(autores.cod == livros->autor4){
					strcat(strcat(strcat(autor4, autores.nome), " "), autores.sobrenome);
					achou = 1;
					}
				}
			}
		}
	}
	
	//Imprime informações do livro de acordo com a qnt de autores
	if(livros->autor2 == 0){
		printf("\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|", livros->cod, livros->titulo, livros->preco, autor1, categorias.descricao, editoras.nomeEditora, livros->ano, livros->edicao, livros->qnt);
		printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
	} else if(livros->autor3 == 0){
		printf("\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|", livros->cod, livros->titulo, livros->preco, autor1, categorias.descricao, editoras.nomeEditora, livros->ano, livros->edicao, livros->qnt);
		printf("\n|                                                 | %-51s |                                    ", autor2);
		printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
	} else if(livros->autor4 == 0){
		printf("\n|                                                 | %-51s |                                    ", autor1);
		printf("\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|", livros->cod, livros->titulo, livros->preco, autor2, categorias.descricao, editoras.nomeEditora,livros->ano, livros->edicao, livros->qnt);
		printf("\n|                                                 | %-51s |                                    ", autor3);
		printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
	} else{
		printf("\n|                                                 | %-51s |                                    ", autor1);
		printf("\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|", livros->cod, livros->titulo, livros->preco, autor2, categorias.descricao, editoras.nomeEditora,livros->ano, livros->edicao, livros->qnt);
		printf("\n|                                                 | %-51s |                                    ", autor3);
		printf("\n|                                                 | %-51s |                                    ", autor4);
		printf("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+");
	}
	fclose(fpcategorias);
	fclose(fpeditoras);
}

//Funções de cadastrar
void cadastrarAutores(){
	struct reg_autores autores;
	FILE *fpautores;
	char opc;
	
	printf("Codigo do autor: "); //Recebe dados do autor
	fflush(stdin); scanf("%i", &autores.cod);
	printf("\nSobrenome: ");
	fflush(stdin); gets(autores.sobrenome);
	printf("\nNome: ");
	fflush(stdin); gets(autores.nome);
	
	printf("\nGravar Autor(S/N)? "); //Confirma cadastro
	fflush(stdin); scanf("%c", &opc);
	if((opc == 'n') || (opc == 'N')){ //Retorna caso cancelado
		printf("\nOperacacao cancelada!\n\n");
		Sleep(1500);
		system("cls");
		return;
	}
	
	fpautores = fopen(AUTORES, "ab");
	fwrite(&autores, sizeof(autores), 1, fpautores); //Salva os dados
	fclose(fpautores);
	printf("\nAutor gravado com sucesso!\n\n");
	Sleep(1500);
	system("cls");
}

void cadastrarCategorias(){
	struct reg_categorias categorias;
	FILE *fpcategorias;
	char opc;
	
	printf("Codigo da categoria: "); //Entrada de dados
	fflush(stdin); scanf("%i", &categorias.cod);
	printf("\nDescricao: ");
	fflush(stdin); gets(categorias.descricao);
	
	printf("\nGravar Categoria(S/N)? "); //Confirmação 
	fflush(stdin); scanf("%c", &opc);
	if((opc == 'n') || (opc == 'N')){ //Caso cancele:
		printf("\nOperacacao cancelada!\n\n");
		Sleep(1500);
		system("cls");
		return;
	}
	
	fpcategorias = fopen(CATEGORIAS, "ab");
	fwrite(&categorias, sizeof(categorias), 1, fpcategorias); //Salva os dados
	fclose(fpcategorias);
	printf("\nCategoria gravada com sucesso!\n\n");
	Sleep(1500);
	system("cls");
}

void cadastrarEditoras(){
	struct reg_editoras editoras;
	FILE *fpeditoras;
	char opc;
	//Entrada dos dados:
	printf("Codigo da editora: ");
	fflush(stdin); scanf("%i", &editoras.cod);
	printf("\nNome da editora: ");
	fflush(stdin); gets(editoras.nomeEditora);
	printf("\nNome de contato: ");
	fflush(stdin); gets(editoras.nomeContato);
	printf("\nTelefone de contato (sem espacos): ");
	fflush(stdin); scanf("%s", &editoras.fone);
	printf("\nEmail da editora: ");
	fflush(stdin); scanf("%s", &editoras.email);
	
	printf("\nGravar Editora(S/N)? "); //Confirmação
	fflush(stdin); scanf("%c", &opc);
	if((opc == 'n') || (opc == 'N')){ //Caso cancele:
		printf("\nOperacacao cancelada!\n\n");
		Sleep(1500);
		system("cls");
		return;
	}
	
	fpeditoras = fopen(EDITORAS, "ab");
	fwrite(&editoras, sizeof(editoras), 1, fpeditoras); //Salva os dados
	fclose(fpeditoras);
	printf("\nEditora gravada com sucesso!\n\n");
	Sleep(1500);
	system("cls");
}

void cadastrarLivros(){
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras;
	char opc;
	int cod, achou, escolha = 0; //Escolha = 0 para aparecer a mensagem designada a essa função, ao ser passada como parametro
	//Entrada de dados
	printf("Codigo do livro: ");
	fflush(stdin); scanf("%i", &livros.cod);
	printf("\nTitulo: ");
	fflush(stdin); gets(livros.titulo);
	printf("\nPreco: ");
	fflush(stdin); scanf("%f", &livros.preco);
	
	//Cadastrar autores do livro
	printf("\nCodigo dos autores (Digite 0 para quando NAO houver):");
	for(int i = 1; i <= 4; i++){
		printf("\nAutor %i: ", i);
		//Chama a função para buscar o autor
		cod = buscarAutor(i, escolha);
		if(cod == -1){
			return; //Volta ao menu, caso tenha cancelado
		} else {
			if(i == 1){
				livros.autor1 = cod;
			} else if(i == 2){
				if(cod == 0){ //Confirma se existe
					livros.autor2 = 0; livros.autor3 = 0; livros.autor4 = 0; //Adiciona zero para todos os outros
					break;
				} else {
					livros.autor2 = cod;
				}
			} else if(i == 3){
				if(cod == 0){ //Confirma se existe
					livros.autor3 = 0; livros.autor4 = 0; //Adiciona zero para todos os outros
					break;
				} else {
					livros.autor3 = cod;
				}
			} else if(i == 4){
				livros.autor4 = cod;
			}
		}
	}
	
	//Cadastrar categoria do livro
	cod = buscarCategoria();
	if(cod != -1){
		livros.categoria = cod;
	} else {
		return;
	}
		
	//Cadastrar editora do livro
	do{
		fpeditoras = fopen(EDITORAS, "rb");
		printf("\nCodigo da editora: ");
		fflush(stdin); scanf("%i", &cod);
		if(cod == -1){
				printf("\nOPERACAO CANCELADA!!!");
				Sleep(1500);
				system("cls");
				return;
		}
		achou = 0;
		while((achou ==  0) && (fread(&editoras, sizeof(editoras), 1, fpeditoras))){
			if(editoras.cod == cod){
				printf("\nEditora %s?", editoras.nomeEditora);
				achou = 1;
				printf("\nConfirmar editora(S/N)?");
					fflush(stdin); scanf("%c", &opc);
					if((opc == 'n') || (opc == 'N')){
							printf("\n*Tente novamente ou digite -1 para sair*");
							printf("\n*--------------------------------------*");
					}else{
						livros.editora = cod;
					}
			}
		}
		if(achou == 0){
				printf("\n*Editora nao encontrada! Tente novamente ou digite -1 para sair*");
				printf("\n*----------------------------------------------------------------*");
		}
		fclose(fpeditoras);
	}while((opc == 'n')||(opc == 'N'));
	
	//Cadastro das informações restantes
	printf("\nEdicao: ");
	fflush(stdin); scanf("%i", &livros.edicao);
	printf("\nAno: ");
	fflush(stdin); scanf("%i", &livros.ano);
	printf("\nQuantidade disponivel: ");
	fflush(stdin); scanf("%i", &livros.qnt);
	
	//Confirmar cadastro do livro
	printf("\nGravar Livro(S/N)? ");
	fflush(stdin); scanf("%c", &opc);
	if((opc == 'n') || (opc == 'N')){
		printf("\nOperacacao cancelada!\n\n");
		Sleep(1500);
		system("cls");
		return;
	}
	//Gravar os dados
	fplivros = fopen(LIVROS, "ab");
    fwrite(&livros, sizeof(livros), 1, fplivros);
    fclose(fplivros);
    printf("\nLivro gravado com sucesso!\n");
    Sleep(1500);
    system("cls");
    return;
}

//Funções de Listar
void listarTodosLivros(){
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras;
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	int voltar, achou = 0;
	
	fplivros = fopen(LIVROS, "rb");
	cabecalhoLivros();
	while(fread(&livros, sizeof(livros), 1, fplivros) == 1){ //Le arquivo livros.dat	
		listarLivros(&livros); //Chama função de listar, passando o local atual da struct como parametro
	}
	fclose(fplivros);
	retornarMenu();
}

void listarAutores(){
	FILE *fpautores;
	struct reg_autores autores;
	int voltar;
	
	fpautores = fopen(AUTORES, "rb");
	cabecalhoAutores();//Chama cabeçalho da lista Autores
	
	while(fread(&autores, sizeof(autores), 1, fpautores) == 1) { //Le arquivo autores.dat
		char nome[51] = ""; //Variavel pra copiar o nome completo
		strcat(strcat(strcat(nome, autores.nome), " "), autores.sobrenome);//Junta o nome inteiro do autor numa variavel só, facilitando printar dentro de um tamanho de espaço específico
		printf("\n|   %i   | %-51s|", autores.cod, nome);
	}
	printf("\n*------------------------------------------------------------*"); //Fecha lista
	fclose(fpautores);
	
	retornarMenu();
}	

void listarCategorias(){
	FILE *fpcategorias;
	struct reg_categorias categorias;
	int voltar;
	
	fpcategorias = fopen(CATEGORIAS, "rb");
	printf("*-----------------------------*");
	printf("\n|         CATEGORIAS          |");
	printf("\n+-----------------------------+");
	printf("\n|CODIGO | DESCRICAO           |");
	printf("\n+-----------------------------+");
	
	while(fread(&categorias, sizeof(categorias), 1, fpcategorias) == 1) { //Le arquivo categorias.dat
		printf("\n|   %i   | %-20s|", categorias.cod, categorias.descricao);
	}
	printf("\n*-----------------------------*"); //Fecha lista
	fclose(fpcategorias);
	
	retornarMenu();
}
		
void listarEditoras(){
	FILE *fpeditoras;
	struct reg_editoras editoras;
	int voltar;
	
	fpeditoras = fopen(EDITORAS, "rb");
	printf("*-----------------------------------------------------------------------------------------------------------------------------------------*");
	printf("\n|                                                           EDITORAS                                                                      |");
	printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------+");
	printf("\n|CODIGO | EDITORA                             | NOME DE CONTATO                     | TELEFONE       | EMAIL                              |");
	printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------+");
	
	while(fread(&editoras, sizeof(editoras), 1, fpeditoras) == 1) { //Le arquivo editoras.dat
		printf("\n|   %i   | %-35s | %-35s | %-14s | %-35s|", editoras.cod, editoras.nomeEditora, editoras.nomeContato, editoras.fone, editoras.email);
	}
	printf("\n+-----------------------------------------------------------------------------------------------------------------------------------------+"); //Fecha lista
	fclose(fpeditoras);
	
	retornarMenu();
}

//Funções de Consultas
void consultarPalavraTitulo(){
	FILE *fplivros, *fpcategorias, *fpautores, *fpeditoras;
    struct reg_livros livros;
    struct reg_categorias categorias;
    struct reg_autores autores;
    struct reg_editoras editoras;
    int achou = 0, achouPalavra = 0, voltar;
    char palavra[20], titulo[30];
    
    fplivros = fopen(LIVROS, "rb");
	printf("\nDigite a palavra-chave: ");
	fflush(stdin); gets(palavra);
	strupr(palavra); //Deixa a palavra toda em maiuscula         
    
    while(fread(&livros, sizeof(livros), 1, fplivros) == 1){
    	strupr(strcpy(titulo, livros.titulo)); //copia o titulo para uma nova variavel e deixa tudo em maiúsculo
        if(strstr(titulo, palavra) != NULL){ //Verifica se uma palavra esta contida no titulo
        	cabecalhoLivros(); //Chama função do cabeçalho
			listarLivros(&livros); //Chama funnção de listar
			achouPalavra = 1;
    	}
    }
    fclose(fplivros);
    if(achouPalavra == 0) { //Caso não encontre nada
        printf("\n\n**Nenhum livro contem a palavra '%s' no titulo.", palavra);
        printf("\n**Retornando ao menu...");
        Sleep(6000);
    	system("cls");
    	return;
    }else{
		retornarMenu();
	}
}

void consultarInicialAutor(){
	FILE *fpautores;
    struct reg_autores autores;
    int achou = 0, voltar;
    char palavra[15], nome[35];
    
    fpautores = fopen(AUTORES, "rb");
    printf("\nDigite a inicial do nome que procura: ");
    fflush(stdin); strupr(gets(palavra)); //Entrada de dados
    while(fread(&autores, sizeof(autores), 1, fpautores) == 1){
    	strupr(strcpy(nome, autores.nome)); //Copia nome do autor e transforma tudo em maiusculo
        if(strncmp(nome, palavra, strlen(palavra)) == 0){
            cabecalhoAutores(); //Chama cabeçalho da lista Autores
			char nome[51] = "";
			strcat(strcat(strcat(nome, autores.nome), " "), autores.sobrenome); //Junta o nome inteiro do autor numa variavel só, facilitando printar dentro de um tamanho de espaço específico
			printf("\n|   %i   | %-51s|", autores.cod, nome);
            achou++;
        }
	}
	printf("\n*------------------------------------------------------------*");
	if (achou == 0) { //Caso não encontre nenhum autor com o nome digitado
		printf("\n\n**Nenhum autor comtem '%s' no inicio do nome.\n", palavra);
		printf("\n**Retornando ao menu...");
		Sleep(6000);
		system("cls");
		return;
	}
	fclose(fpautores);
	retornarMenu();
}

//Funções de Relatorios
void relatorioLivrosCat(){
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras;
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	int voltar, achou, cod;
	char opc;
	//Receber categoria desejada
	cod = buscarCategoria();
	if(cod == -1){
		return;  
	}
	//Imprimir livros com a categoria escolhida
	fplivros = fopen(LIVROS, "rb");
	cabecalhoLivros(); //Chama função do cabeçalho
    while(fread(&livros, sizeof(livros), 1, fplivros) == 1){
        if(livros.categoria == cod){ //Verifica se uma palavra esta contida no titulo
            listarLivros(&livros);
    	}
    }
    fclose(fplivros);
    
    retornarMenu();
}

void relatorioLivrosAutor(){
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras;
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	int voltar, achou, cod, escolha = 1, i =1; //Escolha = 1 passado como parametro na função de buscar autor
	char opc;
	
	printf("\nDigite o codigo do autor que procura: ");
	cod = buscarAutor(i, escolha);
	//Imprimir livros com o autor escolhido
	fplivros = fopen(LIVROS, "rb");
	cabecalhoLivros(); //Chama função do cabeçalho
    while(fread(&livros, sizeof(livros), 1, fplivros) == 1){
        if((livros.autor1 == cod)||(livros.autor2 == cod)||(livros.autor3 == cod)||(livros.autor4 == cod)){ //Verifica se uma palavra esta contida no titulo
            listarLivros(&livros); //Chama função de listar
    	}
    }
    fclose(fplivros);
    
    retornarMenu();
}

void relatorioArqTxt(){
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras, *fptr;
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	int voltar, achou, qnt;
	char opc, mensagem[49], lista[956], cabecalho[965];
	
	//Entra qnt de estoque desejada pelo usuário
	printf("\nLivros com quantidade de estoque abaixo de: ");
	fflush(stdin); scanf("%i", &qnt);
	//Imprime os livros encontrados no arquivo.txt
	fptr = fopen("RelatorioLivrosQnt.txt", "a"); //Abre arquivo.txt
	sprintf(mensagem,"##Livros com estoque abaixo de %i unidades##\n", qnt);
	fputs(mensagem, fptr);
	
	//Imprimir livros com a quantidade escolhida
	fplivros = fopen(LIVROS, "rb");
	//Unico metodo para imprimir ocabeçalho que não apresentou erro:
	fputs("\n*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*\n|                                                                                  LIVROS                                                                                                   |\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+\n|CODIGO | TITULO                         | PRECO  | AUTORES                                             | CATEGORIA            | EDITORA                             | ANO  | EDICAO | QNT  |\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+", fptr);

    while(fread(&livros, sizeof(livros), 1, fplivros) == 1){
        if(livros.qnt <= qnt){
            //Procura categoria	
            achou = 0;
			fpcategorias = fopen(CATEGORIAS,  "rb");
			while((achou == 0)&&(fread(&categorias, sizeof(categorias), 1, fpcategorias) == 1)){
				if(categorias.cod == livros.categoria){
					achou = 1;
				}
			}
			//Procura editora
			achou = 0;
			fpeditoras = fopen(EDITORAS,  "rb");
			while((achou == 0)&&(fread(&editoras, sizeof(editoras), 1, fpeditoras) == 1)){
				if(editoras.cod == livros.editora){
					achou = 1;
				}
			}
			//Procura autores
			achou = 0; //Autor 1
			char autor1[51]="", autor2[51]="", autor3[51]="", autor4[51]="";
			fpautores = fopen(AUTORES,  "rb");
			while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
				if(autores.cod == livros.autor1){
					strcat(strcat(strcat(autor1, autores.nome), " "), autores.sobrenome);//Salva nome completo do autor em uma string nova
					achou = 1;
				}
			}
			//Verifica se possui mais autores
			if(livros.autor2 != 0){//Autor 2
				achou = 0;
				fpautores = fopen(AUTORES,  "rb");
				while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
					if(autores.cod == livros.autor2){
						strcat(strcat(strcat(autor2, autores.nome), " "), autores.sobrenome);
						achou = 1;
					}
				}
				if(livros.autor3 != 0){//Autor 3
					achou = 0;
					fpautores = fopen(AUTORES,  "rb");
					while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){
						if(autores.cod == livros.autor3){
						strcat(strcat(strcat(autor3, autores.nome), " "), autores.sobrenome);
						achou = 1;
						}
					}
					if(livros.autor4 != 0){//Autor 4
						achou = 0;
						fpautores = fopen(AUTORES,  "rb");
						while((achou == 0)&&(fread(&autores, sizeof(autores), 1, fpautores) == 1)){	
							if(autores.cod == livros.autor4){
							strcat(strcat(strcat(autor4, autores.nome), " "), autores.sobrenome);
							achou = 1;
							}
						}
					}
				}
			}
			
			//Imprime informações do livro em um arquivo.txt de acordo com a qnt de autores
			if(livros.autor2 == 0){
				sprintf(lista, "\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|", livros.cod, livros.titulo, livros.preco, autor1, categorias.descricao, editoras.nomeEditora, livros.ano, livros.edicao, livros.qnt);
				fputs(lista, fptr);
				fputs("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+", fptr);
			} else if(livros.autor3 == 0){
				sprintf(lista, "\n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|\n|                                                 | %-51s |                                    ", livros.cod, livros.titulo, livros.preco, autor1, categorias.descricao, editoras.nomeEditora, livros.ano, livros.edicao, livros.qnt, autor2);
				fputs(lista, fptr);
				fputs("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+", fptr);
			} else if(livros.autor4 == 0){
				sprintf(lista, "\n|                                                 | %-51s |                                    \n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|\n|                                                 | %-51s |                                    ", autor1, livros.cod, livros.titulo, livros.preco, autor2, categorias.descricao, editoras.nomeEditora,livros.ano, livros.edicao, livros.qnt, autor3);
				fputs(lista, fptr);
				fputs("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+", fptr);
			} else{
				sprintf(lista, "\n|                                                 | %-51s |                                    \n|   %i   | %-30s | %-6.2f | %-51s | %-20s | %-35s | %-4i | %-4i   | %-5i|\n|                                                 | %-51s |                                    \n|                                                 | %-51s |                                    ", autor1, livros.cod, livros.titulo, livros.preco, autor2, categorias.descricao, editoras.nomeEditora,livros.ano, livros.edicao, livros.qnt, autor3, autor4);
				fputs(lista, fptr);
				fputs("\n+-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+", fptr);
			}
			fclose(fpcategorias);
			fclose(fpeditoras);
    	}
    }
    fclose(fplivros);
    fclose(fptr); //Fecha arquivo.txt
    printf("\nArquivo criado com sucesso!");
    retornarMenu();
}

void relatorioLivroCaro(){
	FILE *fplivros, *fpautores, *fpcategorias, *fpeditoras;
	struct reg_livros livros;
	struct reg_autores autores;
	struct reg_categorias categorias;
	struct reg_editoras editoras;
	int voltar, achou, cod;
	char opc;
	float maiorPreco = 0;
	//Receber categoria desejada
	printf("|| Livro mais caro de uma categoria ||\n");
	cod = buscarCategoria();
	if(cod == -1){ //Caso o usuário tenha cancelado a operação:
		return;  
	}
	//Registra o maior valor de um livro na categoria escolhida:        
	fplivros = fopen(LIVROS, "rb");      
	while(fread(&livros, sizeof(livros), 1, fplivros) == 1){                                      
		if(livros.categoria == cod){                
		 	if(livros.preco > maiorPreco){
					maiorPreco = livros.preco;
			}
		}
	}
	fclose(fplivros);
	printf("\n##PRECO MAIS CARO: R$%.2f", maiorPreco); //Exibe preco mais caro encontrado
	
	//Imprimir livros com a categoria escolhida
	fplivros = fopen(LIVROS, "rb");
	cabecalhoLivros(); //Chama função do cabeçalho
    while(fread(&livros, sizeof(livros), 1, fplivros) == 1){
    	if(livros.categoria == cod){ 
	        if(livros.preco == maiorPreco){ //Verifica se uma palavra esta contida no titulo
	            listarLivros(&livros);
	    	}
		}
    }
    fclose(fplivros);
	retornarMenu();
}

//Menu de Cadastros
void cadastrar() {
	int op;
	
	do {
		printf("|#-----------------------------------#|");
		printf("\n||            Cadastrar              ||");
		printf("\n|#-----------------------------------#|");
		printf("\n|| 1) Livro                          ||");
		printf("\n|| 2) Autores                        ||");
		printf("\n|| 3) Categorias                     ||");
		printf("\n|| 4) Editoras                       ||");
		printf("\n|| 0) Voltar ao menu principal       ||");
		printf("\n||                                   ||");
		printf("\n|| Opcao -> ");
		fflush(stdin); scanf("%i", &op);
		switch(op) {
			case 1: //Cadastrar Livro
				system("cls");
				cadastrarLivros();
				break;
			case 2: //Cadastrar Autores
				system("cls");
				cadastrarAutores();
				break;
			case 3: //Cadastrar Categoria
				system("cls");
				cadastrarCategorias();
				break;
			case 4: //Cadastrar Editoras
				system("cls");
				cadastrarEditoras();
				break;
			case 0: //Voltar ao menu
				system("cls");
				return;
			default: //Opções invalidas
				printf("\nComando invalido! Tente novamente.");
				Sleep(1000);
				system("cls");
				break;
		}
	} while((op != 0)&&(op != 1)&&(op != 2)&&(op != 3)&&(op != 4));
	
	system("cls");
	return;
}
//Menu de Listar
void listar() {
	int op;
	
	do {
		printf("|#-----------------------------------#|");
		printf("\n||              Listar               ||");
		printf("\n|#-----------------------------------#|");
		printf("\n|| 1) Livros                         ||");
		printf("\n|| 2) Autores                        ||");
		printf("\n|| 3) Categorias                     ||");
		printf("\n|| 4) Editoras                       ||");
		printf("\n|| 0) Voltar ao menu principal       ||");
		printf("\n||                                   ||");
		printf("\n|| Opcao -> ");
		fflush(stdin); scanf("%i", &op);
		
		switch(op){
			case 1: //Listar livros
				system("cls");
				listarTodosLivros();
				break;
			case 2: //Listar autores
				system("cls");
				listarAutores();
				break;
			case 3: //Listar categorias
				system("cls");
				listarCategorias();
				break;
			case 4: //Listar editoras
				system("cls");
				listarEditoras();
				break;
			case 0: //Voltar ao menu
				system("cls");
				return;
			default: //Opções invalidas
				printf("\nComando invalido! Tente novamente.");
				Sleep(1000);
				system("cls");
				break;
		}
	} while((op != 0)&&(op != 1)&&(op != 2)&&(op != 3)&&(op != 4));
	
	system("cls");
	return;
}
//Menu de Consultas
void consultar() {
	int op;
	
	do {
		printf("|#----------------------------------------#|");
		printf("\n||             Consultar                 ||");
		printf("\n|#---------------------------------------#|");
		printf("\n|| 1) Livro por palavra-chave no titulo  ||");
		printf("\n|| 2) Autores por inical do nome         ||");
		printf("\n|| 0) Voltar ao menu principal           ||");
		printf("\n||                                       ||");
		printf("\n|| Opcao -> ");
		fflush(stdin); scanf("%i", &op);
		
		switch(op){
			case 1: //Buscar livro por palavra-chave
				system("cls");
				consultarPalavraTitulo();
				break;
			case 2: //Buscar autor por inicial do nome
				system("cls");
				consultarInicialAutor();
				break;
			case 0: //Voltar ao menu
				system("cls");
				return;
			default: //Opção invalida
				printf("\nComando invalido! Tente novamente.");
				Sleep(1000);
				system("cls");
				break;
		}
	} while((op != 0)&&(op != 1)&&(op != 2));
	
	system("cls");
	return;
}
//Menu de Relatórios
void relatorios() {
int op;
	
	do {
		printf("|#--------------------------------------------#|");
		printf("\n||                  Relatorios                ||");
		printf("\n|#--------------------------------------------#|");
		printf("\n|| 1) Livro por categoria                     ||");
		printf("\n|| 2) Livros de um autor                      ||");
		printf("\n|| 3) Livros com estoque baixo (arquivo txt)  ||");
		printf("\n|| 4) Livro mais caro de uma categoria        ||");
		printf("\n|| 0) Voltar ao menu principal                ||");
		printf("\n||                                            ||");
		printf("\n|| Opcao -> ");
		fflush(stdin); scanf("%i", &op);
		
		switch(op){
			case 1: //Livro por categoria
				system("cls");
				relatorioLivrosCat();
				break;
			case 2: //Livros de um autor
				system("cls");
				relatorioLivrosAutor();
				break;
			case 3: //Livros com estoque abaixo de uma certa quantidade
				system("cls");
				relatorioArqTxt();
				break;
			case 4: //Livro mais caro de uma categoria
				system("cls");
				relatorioLivroCaro();
				break;
			case 0: //Voltar ao menu
				system("cls");
				return;
			default: //Outras opções inválidas
				printf("\nComando invalido! Tente novamente.");
				Sleep(1000);
				system("cls");
				break;
				
		}
	} while((op != 0)&&(op != 1)&&(op != 2)&&(op != 3)&&(op != 4)); //Se for diferente das opções fornecidas, o processo é refeito
	
	system("cls");
	return;
}

//Função de excluir categoria
void excluirCategoria(){
	FILE *fpcategorias, *fpcategoriasnew;
    struct reg_categorias categorias;
    int achou = 0, cod;
    char op;
	//Entrada de dados
    printf("\nDigite o codigo da categoria a ser excluida: ");
            fflush(stdin); scanf("%i", &cod);

    fpcategorias = fopen(CATEGORIAS, "rb");
    while ((achou == 0) && (fread(&categorias, sizeof(categorias), 1, fpcategorias) == 1)) {
        if(categorias.cod == cod) { //Procura a categoria escolhida
        printf("\nCodigo: %i\nDescricao: %s\n", categorias.cod, categorias.descricao);
        achou = 1;
        }
    }

    fclose(fpcategorias);
	//Se nada for encontrado:
    if(achou == 0){
        printf("Nenhuma categoria com codigo %i foi encontrada!", cod);
        Sleep(4000);
		system("cls");
		return; //Retorna ao menu principal
    }

    //Se a categoria for localizada, confirma exclusão:
    printf("\nDeseja excluir categoria?(S/N)");
    fflush(stdin); scanf("%c", &op);
    if((op == 'N') || (op == 'n')){
        printf("\nOPERACAO CANCELADA!"); //Caso não deseje mais continuar
        Sleep(1500);
        system("cls");
        return;
    }
    //Se confirmou a exclusão:
    fpcategorias = fopen(CATEGORIAS, "rb");
    fpcategoriasnew = fopen("Categoriasnew.dat", "wb"); //Abre um novo arquivo

    while(fread(&categorias, sizeof(categorias), 1, fpcategorias) == 1) {
        if (categorias.cod != cod){
            fwrite(&categorias, sizeof(categorias), 1, fpcategoriasnew); //Copia os dados não excluidos
        }
    }
    fclose(fpcategorias);
    fclose(fpcategoriasnew);

    system("del Categorias.dat");//Excluindo o arquivo antigo
    system("ren Categoriasnew.dat Categorias.dat");//Renomeando o novo arquivo

    printf("\nCategoria excluida com sucesso!!!");
    Sleep(1500);
    system("cls");
    return;
}

//Função Principal
int main() {
	int op;
	
	do {
		printf("|#-----------------------------------#|");
		printf("\n||        Controle de Livraria       ||");
		printf("\n|#-----------------------------------#|");
		printf("\n|| 1) Cadastrar                      ||");
		printf("\n|| 2) Listar                         ||");
		printf("\n|| 3) Excluir Categoria              ||");
		printf("\n|| 4) Consultar                      ||");
		printf("\n|| 5) Relatorios                     ||");
		printf("\n|| 0) Sair                           ||");
		printf("\n||                                   ||");
		printf("\n|| Opcao -> ");
		fflush(stdin); scanf("%i", &op);
		
		switch(op) {
			case 1: //Cadastrar
				system("cls");
				cadastrar();
				break;
			case 2: //Listar
				system("cls");
				listar();
				break;
			case 3: //Excluir Categoria
				system("cls");
				excluirCategoria();
				break;
			case 4: //Consultar
				system("cls");
				consultar();
				break;
			case 5: //Relatorios
				system("cls");
				relatorios();
				break;	
			case 0: //Sair
				printf("\n\n||Ate logo!");
				Sleep(1500);
				break;
			default://Outra opção
				printf("\nComando invalido! Tente novamente.");
				Sleep(1000);
				system("cls");
				break;
		}
	} while(op != 0);
}