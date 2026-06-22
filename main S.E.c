<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    char nome[50];
    int quantidade;
    int codigo;
} Produto;


//Função para limpar a tela, se o programa for rodado no Windows vai rodar o código system("cls"), se for rodado no Linux ou MacOS vai rodar o código
//system("clear")
void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Função para verificar se já existe um produto com o mesmo código no estoque
int verifica_codigo(Produto *p,int codigo, int n){

    for(int i = 0; i < n; i++){
        if(codigo == p[i].codigo){
            return 1;
        }
    }
    return 0;
}

//Função para verificar se já o produto no estoque
int verifica_nome(Produto *p, char nome[], int n){

    for(int i = 0; i < n; i++){
        if(strcmp(nome, p[i]. nome) == 0){
            return 1;
        }
    }
    return 0;
}

//Função para cadastrar o produto
void cadastrar_produtos(Produto *p, int *n){

    //Verifica se o limite de produtos foi aingido
    if(*n >= 100){
        printf("NUMERO LIMITE DE PRODUTOS ATINGIDO!");
        return;
    }
    printf("========== CADASTRANDO PRODUTO ==========\n\n");
    int existe_codigo, existe_nome;

    char nome_temp[50];

    //Verifica e armazena o nome do produto digitado pelo usuário
    printf("Digite o nome do produto: ");
    getchar();
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = '\0';

    existe_nome = verifica_nome(p, nome_temp, *n);
    if(existe_nome == 1){
        printf("O produto já existe no cadastro, cadastro cancelado!\n\n");
        system("PAUSE");
        return;
    }
    strcpy(p[*n].nome, nome_temp);

    //Armazena a quantidade do produto
    printf("Digite a quantidade do produto no estoque: ");
    scanf("%d", &p[*n].quantidade);


    //Verifica e armazena o código do produto digitado pelo usuário
    printf("Digite o código do produto: ");
    int codigo_temp;
    scanf("%d", &codigo_temp);
    existe_codigo = verifica_codigo(p, codigo_temp, *n);

    if(existe_codigo == 1){
        printf("Já existe outro produto com o mesmo código no cadastro, cadastro cancelado!\n\n");
        system("PAUSE");
        return;
    }

    p[*n].codigo = codigo_temp;

    *n += 1;
    limparTela();
    printf("PRODUTO CADASTRADO COM SUCESSO!\n\n");
    system("PAUSE");
}

//Função para listar todos os produtos
void listar_produtos(Produto *p, int *n){
    if (*n == 0) {
        printf("Nenhum produto cadastrado no sistema!\n\n");
        system("PAUSE");
        return;
    }

    printf("========== LISTA DE PRODUTO ==========\n\n");
    for(int i = 0; i < *n; i++){
        printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
    }
    printf("\n");
    system("PAUSE");
}


//Função para buscar um produto no estoque através do código
void buscar_produto_codigo(Produto *p, int *n){
    printf("========== BUSCANDO PRODUTO ==========\n\n");
    int codigo;
    printf("Digite o código do produto que deseja buscar: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            system("PAUSE");
            return;
        }
    }
    printf("Não existe produto com esse código no sistema!\n\n");
    system("PAUSE");
}

//Função para buscar um produto no estoque através do nome
void buscar_produto_nome(Produto *p, int *n){
    printf("========== BUSCANDO PRODUTO ==========\n\n");
    char nome[50];
    printf("Digite o nome do produto que deseja buscar: ");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < *n; i++){
        if(strcmp(nome, p[i].nome) == 0){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            system("PAUSE");
            return;
        }
    }

    printf("Não existe produto com esse nome no sistema!\n");
    system("PAUSE");

}

//Função para excluir um produto do estoque
 void excluir_produto(Produto *p, int *n){
    printf("========== EXCLUINDO PRODUTO ==========\n\n");
    int codigo, simNao, posicao = -1;
    printf("Digite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            printf("Este é o produto que deseja excluir(0 - Não || 1 - Sim)? ");
            scanf("%d", &simNao);

            if(simNao == 0){
                printf("Exclusão cancelada!\n");
                system("PAUSE");
                return;
            }
            posicao = i;
        }
    }

    if(posicao == -1){
        printf("Código do produto não encontrado!\n");
        system("PAUSE");
        return;
    }

    for(int i = posicao; i < *n - 1; i++){
        strcpy(p[i].nome, p[i+1].nome);
        p[i].quantidade = p[i+1].quantidade;
        p[i].codigo = p[i+1].codigo;
    }

    *n -= 1;
    printf("Produto excluido com sucesso!\n");
    system("PAUSE");
}

//Função para alterar as informações de um produto do estoque
void alterar_produto(Produto *p, int *n){
    printf("========== ALTERANDO PRODUTO ==========\n\n");
    int codigo, simNao, pos = -1;
    printf("Digite o código do produto que deseja alterar: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            printf("Este é o produto que deseja alterar(0 - Não || 1 - Sim)? ");
            scanf("%d", &simNao);

            if(simNao == 0){
                printf("Alteração cancelada!\n");
                system("PAUSE");
                return;
            }
            pos = i;
            limparTela();
            printf("Alterando produto:\n");

            printf("Digite o nome do produto: ");
            getchar();
            fgets(p[pos].nome, sizeof(p[pos].nome), stdin);
            p[pos].nome[strcspn(p[pos].nome, "\n")] = '\0';
            printf("Digite a quantidade do produto no estoque: ");
            scanf("%d", &p[pos].quantidade);
            printf("Digite o código do produto: ");
            scanf("%d", &p[pos].codigo);
            return;
        }
    }
    printf("Não existe produto com esse código no sistema!\n\n");
    system("PAUSE");
}


int main()
{
    setlocale(LC_ALL, "portuguese");
    int escolha;
    int qntd = 0;
    Produto *p;
    p = (Produto *) malloc(100 * sizeof(Produto));

    if(p == NULL){
        printf("** Erro: Memório Insuficiente **");
        exit(1);
    }

    //MENU
    printf("===============================\nBEM VINDO AO SISTEMA DE ESTOQUE\n===============================\n\n");
    int l = 1;
    do{

        printf("Escolha uma opção abaixo:\n1 - Cadastrar Produto\n2 - Listar todos os produtos\n3 - Buscar produtos por código\n4 - Buscar produto por nome\n5 - Excluir produto\n6 - Alterar produto\n7 - Sair do sistema\n\n");
        printf("OBS: O nome do produto no cadastro e na busca deve ser feito em minúsculo!\n\n");
        scanf("%d", &escolha);
        limparTela();
        switch(escolha){
        case 1:
            limparTela();
            cadastrar_produtos(p, &qntd);
            limparTela();
            break;
        case 2:
            limparTela();
            listar_produtos(p, &qntd);
            limparTela();
            break;
        case 3:
            limparTela();
            buscar_produto_codigo(p, &qntd);
            limparTela();
            break;
        case 4:
            limparTela();
            buscar_produto_nome(p, &qntd);
            limparTela();
            break;
        case 5:
            limparTela();
            excluir_produto(p, &qntd);
            limparTela();
            break;
        case 6:
            limparTela();
            alterar_produto(p, &qntd);
            limparTela();
            break;
        case 7:
            l = 0;
            break;
        default:
            l = 0;
            break;
        }
    }while(l == 1);

    free(p);
    printf("PROGRAMA FECHADO!\n\n");
    system("PAUSE");
    return 0;
}
=======
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
    char nome[50];
    int quantidade;
    int codigo;
} Produto;


//Função para limpar a tela, se o programa for rodado no Windows vai rodar o código system("cls"), se for rodado no Linux ou MacOS vai rodar o código
//system("clear")
void limparTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

//Função para verificar se já existe um produto com o mesmo código no estoque
int verifica_codigo(Produto *p,int codigo, int n){

    for(int i = 0; i < n; i++){
        if(codigo == p[i].codigo){
            return 1;
        }
    }
    return 0;
}

//Função para verificar se já o produto no estoque
int verifica_nome(Produto *p, char nome[], int n){

    for(int i = 0; i < n; i++){
        if(strcmp(nome, p[i]. nome) == 0){
            return 1;
        }
    }
    return 0;
}

//Função para cadastrar o produto
void cadastrar_produtos(Produto *p, int *n){

    //Verifica se o limite de produtos foi aingido
    if(*n >= 100){
        printf("NUMERO LIMITE DE PRODUTOS ATINGIDO!");
        return;
    }
    printf("========== CADASTRANDO PRODUTO ==========\n\n");
    int existe_codigo, existe_nome;

    char nome_temp[50];

    //Verifica e armazena o nome do produto digitado pelo usuário
    printf("Digite o nome do produto: ");
    getchar();
    fgets(nome_temp, sizeof(nome_temp), stdin);
    nome_temp[strcspn(nome_temp, "\n")] = '\0';

    existe_nome = verifica_nome(p, nome_temp, *n);
    if(existe_nome == 1){
        printf("O produto já existe no cadastro, cadastro cancelado!\n\n");
        system("PAUSE");
        return;
    }
    strcpy(p[*n].nome, nome_temp);

    //Armazena a quantidade do produto
    printf("Digite a quantidade do produto no estoque: ");
    scanf("%d", &p[*n].quantidade);


    //Verifica e armazena o código do produto digitado pelo usuário
    printf("Digite o código do produto: ");
    int codigo_temp;
    scanf("%d", &codigo_temp);
    existe_codigo = verifica_codigo(p, codigo_temp, *n);

    if(existe_codigo == 1){
        printf("Já existe outro produto com o mesmo código no cadastro, cadastro cancelado!\n\n");
        system("PAUSE");
        return;
    }

    p[*n].codigo = codigo_temp;

    *n += 1;
    limparTela();
    printf("PRODUTO CADASTRADO COM SUCESSO!\n\n");
    system("PAUSE");
}

//Função para listar todos os produtos
void listar_produtos(Produto *p, int *n){
    if (*n == 0) {
        printf("Nenhum produto cadastrado no sistema!\n\n");
        system("PAUSE");
        return;
    }

    printf("========== LISTA DE PRODUTO ==========\n\n");
    for(int i = 0; i < *n; i++){
        printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
    }
    printf("\n");
    system("PAUSE");
}


//Função para buscar um produto no estoque através do código
void buscar_produto_codigo(Produto *p, int *n){
    printf("========== BUSCANDO PRODUTO ==========\n\n");
    int codigo;
    printf("Digite o código do produto que deseja buscar: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            system("PAUSE");
            return;
        }
    }
    printf("Não existe produto com esse código no sistema!\n\n");
    system("PAUSE");
}

//Função para buscar um produto no estoque através do nome
void buscar_produto_nome(Produto *p, int *n){
    printf("========== BUSCANDO PRODUTO ==========\n\n");
    char nome[50];
    printf("Digite o nome do produto que deseja buscar: ");
    getchar();
    fgets(nome, sizeof(nome), stdin);
    nome[strcspn(nome, "\n")] = '\0';

    for(int i = 0; i < *n; i++){
        if(strcmp(nome, p[i].nome) == 0){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            system("PAUSE");
            return;
        }
    }

    printf("Não existe produto com esse nome no sistema!\n");
    system("PAUSE");

}

//Função para excluir um produto do estoque
 void excluir_produto(Produto *p, int *n){
    printf("========== EXCLUINDO PRODUTO ==========\n\n");
    int codigo, simNao, posicao = -1;
    printf("Digite o código do produto que deseja excluir: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            printf("Este é o produto que deseja excluir(0 - Não || 1 - Sim)? ");
            scanf("%d", &simNao);

            if(simNao == 0){
                printf("Exclusão cancelada!\n");
                system("PAUSE");
                return;
            }
            posicao = i;
        }
    }

    if(posicao == -1){
        printf("Código do produto não encontrado!\n");
        system("PAUSE");
        return;
    }

    for(int i = posicao; i < *n - 1; i++){
        strcpy(p[i].nome, p[i+1].nome);
        p[i].quantidade = p[i+1].quantidade;
        p[i].codigo = p[i+1].codigo;
    }

    *n -= 1;
    printf("Produto excluido com sucesso!\n");
    system("PAUSE");
}

//Função para alterar as informações de um produto do estoque
void alterar_produto(Produto *p, int *n){
    printf("========== ALTERANDO PRODUTO ==========\n\n");
    int codigo, simNao, pos = -1;
    printf("Digite o código do produto que deseja alterar: ");
    scanf("%d", &codigo);

    for(int i = 0; i < *n; i++){
        if(codigo == p[i].codigo){
            printf("%da - Nome: %s  ||  Quantidade: %d  ||  Código: %d\n\n",i + 1, p[i].nome, p[i].quantidade, p[i].codigo);
            printf("Este é o produto que deseja alterar(0 - Não || 1 - Sim)? ");
            scanf("%d", &simNao);

            if(simNao == 0){
                printf("Alteração cancelada!\n");
                system("PAUSE");
                return;
            }
            pos = i;
            limparTela();
            printf("Alterando produto:\n");

            printf("Digite o nome do produto: ");
            getchar();
            fgets(p[pos].nome, sizeof(p[pos].nome), stdin);
            p[pos].nome[strcspn(p[pos].nome, "\n")] = '\0';
            printf("Digite a quantidade do produto no estoque: ");
            scanf("%d", &p[pos].quantidade);
            printf("Digite o código do produto: ");
            scanf("%d", &p[pos].codigo);
            return;
        }
    }
    printf("Não existe produto com esse código no sistema!\n\n");
    system("PAUSE");
}


int main()
{
    setlocale(LC_ALL, "portuguese");
    int escolha;
    int qntd = 0;
    Produto *p;
    p = (Produto *) malloc(100 * sizeof(Produto));

    if(p == NULL){
        printf("** Erro: Memório Insuficiente **");
        exit(1);
    }

    //MENU
    printf("===============================\nBEM VINDO AO SISTEMA DE ESTOQUE\n===============================\n\n");
    int l = 1;
    do{

        printf("Escolha uma opção abaixo:\n1 - Cadastrar Produto\n2 - Listar todos os produtos\n3 - Buscar produtos por código\n4 - Buscar produto por nome\n5 - Excluir produto\n6 - Alterar produto\n7 - Sair do sistema\n\n");
        printf("OBS: O nome do produto no cadastro e na busca deve ser feito em minúsculo!\n\n");
        scanf("%d", &escolha);
        limparTela();
        switch(escolha){
        case 1:
            limparTela();
            cadastrar_produtos(p, &qntd);
            limparTela();
            break;
        case 2:
            limparTela();
            listar_produtos(p, &qntd);
            limparTela();
            break;
        case 3:
            limparTela();
            buscar_produto_codigo(p, &qntd);
            limparTela();
            break;
        case 4:
            limparTela();
            buscar_produto_nome(p, &qntd);
            limparTela();
            break;
        case 5:
            limparTela();
            excluir_produto(p, &qntd);
            limparTela();
            break;
        case 6:
            limparTela();
            alterar_produto(p, &qntd);
            limparTela();
            break;
        case 7:
            l = 0;
            break;
        default:
            l = 0;
            break;
        }
    }while(l == 1);

    free(p);
    printf("PROGRAMA FECHADO!\n\n");
    system("PAUSE");
    return 0;
}
>>>>>>> master
