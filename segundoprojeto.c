#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#define R     "\x1b[31m"
#define B     "\e[0;37m"
int cont = 0;

typedef struct user user;
struct user
{
    char *usuario;
    char *senha;
    int saldo;
    user *next;
    user *prev;
};

void printarLista(user *lista);
void checarCedulas(int *valor);
void checarTexto(char *v);
void checarValor(int *valor);
user *checarLogin(user *estrutura);
user *buscaPosicao(user *admin, char *username);
user *procurarCadastro(char *username, user *admin);
void receberCliente(user *admin, int *notas, int *loop);
user *cadastraCliente(user *admin);
void menuCliente(int *notas, user *cliente);
void msgOperacao(int *notas, user *cliente);
void receberCedulas(int *notas);
void printarCedulas(int *notas);
void reabastecer(int *notas);
int depositar(int *notas, int saldo);
int sacar(int *notas, int saldo);
void liberar(user *admin);

int main()
{
    user *admin = malloc(sizeof(user));
    admin->usuario = "admin";
    admin->senha = "admin";
    admin->next = NULL;
    admin->prev = NULL;
    int notas[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int loop = 1;
    /*printf("Este caixa eletronico acabou de ser iniciado.\n");
    printf("Nao ha cedulas na maquina, acesse o usuario administrador para reabastecer.\n");
    admin = checarLogin(admin);
    reabastecer(notas);
    printf("Caixa reabastecido, segue as quantidades.\n");
    printarCedulas(notas);
    printf("Encerrando sessao do administrador.\n");*/
    while (loop)
        receberCliente(admin, notas, &loop);
    printf("\n|---------------------------|\n");
    printf("|    PROGRAMA ENCERRADO!    |\n");
    printf("|---------------------------|\n");
    liberar(admin);

    return 0;
}

void checarCedulas(int *valor)
{
    if (*valor >= 0)
        return;
    else
    {
        printf("A quantidade de cedulas deve ser maior ou igual a 0, digite novamente: ");
        scanf("%d", valor);
        checarCedulas(valor);
    }
}

void checarTexto(char *v)
{
    char s[] = "sim", n[] = "nao";
    if (strcmp(v, s) == 0 || strcmp(v, n) == 0)
        return;
    else
    {
        printf("Comando invalido! Digite novamente. [sim/nao] ");
        scanf(" %s", v);
        checarTexto(v);
    }
}

void checarValor(int *valor)
{
    if (*valor >= 0)
        return;
    else
    {
        printf("O valor deve ser maior ou igual a zero. Digite novamente: ");
        scanf("%s", &valor);
        checarValor(valor);
    }
}

user *checarLogin(user *estrutura)
{
    printf(R"checarLogin entrou \n"B);
    char username[15], password[15];
    printf("Usuario: ");
    scanf(" %15s", &username);
    printf("Senha: ");
    scanf(" %15s", &password);
    user *posicao = procurarCadastro(username, estrutura);
    if (posicao == NULL)
    {
        cont++;
        if (cont == 3) 
        {
            printf("Usuario inexistente. Finalizando operacao!\n");
            cont = 0;
    
            printf(R"checarLogin saiu \n"B);
            return posicao; //RETURN TA DANDO SEGMENTATION FAULT
        }
        printf("Usuario nao encontrado, por favor, tente novamente.\n");
        checarLogin(estrutura);
    }
    else if (strcmp(password, posicao->senha) != 0)
    {
        cont++;
        if (cont == 3)
        {
            printf("Limite de tentativas excedido, voce deve alterar a senha.\n");
            printf("Confirme seu username: ");
            scanf(" %15s", &username);
            while (strcmp(username, posicao->usuario) != 0)
            {
                printf("O usuario digitado nao coincide, tente novamente.\n");
                scanf(" %15s", &username);
            }
            printf("Digite a nova senha: ");
            scanf(" %15s", posicao->senha);
            printf("Senha alterada com sucesso!\nEfetue o login.\n");
        }
        else
            printf("Senha invalida, por favor, tente novamente.\n");
        checarLogin(estrutura);
    }
    cont = 0;
    printf("Bem vindo, %s!\n", posicao->usuario);
    printf(R"checarLogin saiu \n"B);
    return posicao;
}

user *buscaPosicao(user *admin, char *username)
{
    printf(R"buscaPosicao entrou \n"B);
    user *posicao = admin;
    while (posicao != NULL)
    {
        if (strcmp(username, posicao->usuario) < 0)
        {
            printf(R"buscaPosicao saiu \n"B);
            return posicao;
        }
        else
        {
            posicao = posicao->next;
        }
    }
    printf(R"buscaPosicao saiu \n"B);
    return posicao;
}

user *procurarCadastro(char *username, user *admin)
{
    printf(R"procurarCadastro entrou \n");
    user *posicao = admin;
    if (strcmp(username, "admin") == 0) {

        printf(R"procurarCadastro saiu \n"B);
        return admin;
    }
    while (posicao != NULL)
    {
        if (strcmp(username, posicao->usuario) == 0) {
            printf(R"procurarCadastro saiu \n"B);
            return posicao;
        }
        posicao = posicao->next;
    }
    return posicao;
}

void receberCliente(user *admin, int *notas, int *loop)
{
    printf(R"receberCliente entrou \n"B);
    char res[3];
    printf("Bem vindo ao Banco do Programador!\n");
    printf("Deseja efetuar operacoes de administrador? [sim/nao] ");
    scanf(" %s", &res);
    checarTexto(res);
    if (strcmp(res, "sim") == 0)
    {
        admin = checarLogin(admin);
        printf("Deseja desligar a maquina? [sim/nao] ");
        scanf(" %s", &res);
        if (strcmp(res, "sim") == 0)
        {
            *loop = 0;
    
            printf(R"receberCliente saiu \n"B);
            return;
        }
        else
        {
            printf("Iniciando operacao de reabastecimento.\n");
            reabastecer(notas);
            printf("Caixa reabastecido, segue as quantidades.\n");
            printarCedulas(notas);
        }
        printf("Encerrando sessao do administrador.\n");
    }
    else
    {
        printf("Voce ja eh cliente? [sim/nao] ");
        scanf(" %s", &res);
        checarTexto(res);
        if (strcmp(res, "sim") == 0)
            menuCliente(notas, checarLogin(admin));
        else
        {
            printf("Deseja criar uma conta em nosso banco? [sim/nao] ");
            scanf(" %s", &res);
            checarTexto(res);
            if (strcmp(res, "sim") == 0)
            {
                admin = cadastraCliente(admin);
                printf("Seu cadastro foi realizado com sucesso!\n");
                printf("Efetue o login para prosseguir ao menu do cliente.\n");
                menuCliente(notas, checarLogin(admin));
            }
            else
                printf("OK! Obrigada, tenha um otimo dia.\n");
        }
    }
    printf(R"receberCliente saiu \n"B);
}

user *cadastraCliente(user *admin) {
    if(admin == NULL) {
        user *novo = malloc(sizeof(user));
        novo->saldo = 0;
        printf("Crie seu nome de usuario: ");
        scanf(" %15s", novo->usuario);
        printf("Digite uma senha: ");
        scanf(" %15s", novo->senha);
        novo->prev = NULL;
        novo->next = NULL;
        return novo;
    }
    else {
        admin->next = cadastraCliente(admin->next);
        admin->next->prev = admin;
        return admin;
    }
}

/*user *ordenaCliente(user *admin) { Ha algum erro aqui
    user *inicio = admin, *lista = admin;
    user *atual = malloc(sizeof(user));
    while(inicio) {
        strcpy(atual->usuario, inicio->usuario);
        strcpy(atual->senha, inicio->senha);
        atual->saldo = inicio->saldo;
        if(inicio->prev = NULL)
            lista = inicio->prev;
        while(lista != NULL && strcmp(atual->usuario, lista->usuario) < 0) {
            strcpy(lista->next->usuario, lista->usuario);
            strcpy(lista->usuario, atual->usuario);
            strcpy(lista->next->senha, lista->senha);
            strcpy(lista->senha, atual->senha);
            lista->next->saldo = lista->saldo;
            lista->saldo = atual->saldo;
            if(lista->prev == NULL) 
                break;
            lista = lista->prev;
        }
        inicio = inicio->next;
    }
    return inicio;
}*/

void menuCliente(int *notas, user *cliente)
{
    printf(R"menuCliente entrou \n"B);
    if (!cliente) {

        printf(R"menuCliente saiu \n"B);
        return;
    }
    char res[3];
    printf("Voce possui um saldo de R$ %d,00.\n", cliente->saldo);
    if (cliente->saldo == 0)
    {
        printf("Com esse saldo voce apenas pode realizar depositos.\n");
        printf("Deseja realizar um deposito agora? [sim/nao] ");
        scanf(" %s", &res);
        checarTexto(res);
        if (strcmp(res, "nao") == 0)
            printf("Encerrando sessao.\nObrigado, volte sempre!\n");
        else
        {
            cliente->saldo = depositar(notas, cliente->saldo);
            msgOperacao(notas, cliente);
        }
    }
    else
    {
        int rets, retd;
        char v[8], s[] = "saque", d[] = "deposito";
        printf("Digite a operacao que deseja realizar: [saque/deposito] ");
        scanf(" %s", &v);
        rets = strncmp(v, s, 5);
        retd = strncmp(v, d, 8);
        while (rets != 0 && retd != 0)
        {
            printf("Comando invalido!\n");
            printf("Digite a operacao que deseja realizar: [saque/deposito] ");
            scanf(" %s", &v);
            rets = strncmp(v, s, 5);
            retd = strncmp(v, d, 8);
        }
        if (retd == 0)
        {
            cliente->saldo = depositar(notas, cliente->saldo);
            msgOperacao(notas, cliente);
        }
        else
        {
            if (notas[7] == 0)
            {
                printf("Não ha dinheiro disponivel para saque nesse momento.\nAguarde um administrador realizar o reabastecimento.\n");
                return;
            }
            cliente->saldo = sacar(notas, cliente->saldo);
            msgOperacao(notas, cliente);
        }
    }
    printf(R"menuCliente saiu \n"B);
}

void msgOperacao(int *notas, user *cliente)
{
    printf(R"msgOperacao entrou \n"B);
    char res[3];
    printf("Deseja realizar outra operacao? [sim/nao] ");
    scanf(" %s", &res);
    checarTexto(res);
    if (strcmp(res, "nao") == 0)
    {
        printf("O seu saldo atual eh de R$ %d,00.\n", cliente->saldo);
        printf("Encerrando sessao.\nObrigado, volte sempre!\n");
    }
    else
        menuCliente(notas, cliente);
    printf(R"msgOperacao saiu \n"B);
}

void receberCedulas(int *notas)
{
    printf(R"receberCedulas entrou \n"B);
    int v[] = {200, 100, 50, 20, 10, 5, 2}, i;
    for(i = 0; i < 7; i++)
    {
        printf("Insira a quantidade de cedulas de R$ %d,00: ", v[i]);
        scanf("%d", &notas[i]);
        checarCedulas(&notas[i]);
    }
    printf(R"receberCedulas saiu \n"B);
}

void printarCedulas(int *notas)
{
    int v[] = {200, 100, 50, 20, 10, 05, 02}, i;
    printf("\n|-----------CAIXA-----------|\n");
    printf("   Valor  | Qtd. de cedulas \n");
    printf("|---------------------------|\n");
    for(i = 0; i < 7; i++)
        if(notas[i] > 0)
        {
            if(v[i] >= 100)
                printf("   %d,00 |      %d \n", v[i], notas[i]);
            else if(v[i] >= 10)
                printf("    %d,00 |      %d \n", v[i], notas[i]);
            else
                printf("    0%d,00 |      %d \n", v[i], notas[i]);
        }
    printf("|---------------------------|\n");
    printf("   Total  |   R$ %d,00 \n", notas[7]);
    printf("|---------------------------|\n\n");
}

void reabastecer(int *notas)
{
    int rnotas[7], v[] = {200, 100, 50, 20, 10, 5, 2}, i;
    receberCedulas(rnotas);
    for (i = 0; i < 7; i++)
    {
        notas[i] += rnotas[i];
        notas[7] += notas[i] * v[i];
    }
}

int depositar(int *notas, int saldo)
{
    int valor, dep[] = {0, 0, 0, 0, 0, 0, 0}, v[] = {200, 100, 50, 20, 10, 5, 2}, soma = 0, i;
    char res[3];
    printf("Digite o valor que deseja depositar: ");
    scanf("%d", &valor);
    checarValor(&valor);
    receberCedulas(dep);
    for (i = 0; i < 7; i++)
        soma += dep[i] * v[i];
    while (soma != valor)
    {
        printf("O valor a ser depositado nao corresponde com as cedulas inseridas.\n");
        printf("Voce inseriu R$ %d,00. Deseja depositar essa quantia? [sim/nao] ", soma);
        scanf(" %s", &res);
        checarTexto(res);
        v[0] = 200;
        if (strcmp(res, "sim") == 0)
        {
            for (i = 0; i < 7; i++)
                notas[i] += dep[i];
            notas[7] += soma;
            printf("Operacao realizada com sucesso!\n");
            printf("O seu novo saldo eh de R$ %d,00.\n", saldo + soma);
            return (saldo + soma);
        }
        else
        {
            printf("Insira novamente as cedulas, o valor a ser depositado eh de R$ %d,00.\n", valor);
            receberCedulas(dep);
            for (soma = 0, i = 0; i < 7; i++) {
                soma += dep[i] * v[i];
            }
        }
    }
    for (i = 0; i < 7; i++)
        notas[i] += dep[i];
    notas[7] += soma;
    printf("Operacao realizada com sucesso!\n");
    printf("O seu novo saldo eh de R$ %d,00.\n", saldo + soma);
    return (saldo + soma);
}

int sacar(int *notas, int saldo)
{
    int i, valor, sac[7], v[] = {200, 100, 50, 20, 10, 5, 2}, checar = 0;
    for(i = 0; i < 7; i++)
        sac[i] = notas[i];
    printf("Digite o valor que deseja sacar: ");
    scanf("%d", &valor);
    checarValor(&valor);
    while (valor > saldo)
    {
        printf("O valor a ser sacado eh incompativel com o saldo da conta.\n");
        printf("O saque tem que ser menor ou igual a seu saldo: %.2f\n", saldo);
        printf("Por favor, digite o valor a ser sacado: ");
        scanf("%d", &valor);
    }
    while (valor > notas[7])
    {
        printf("O valor a ser sacado eh incompativel com o dinheiro disponivel na maquina.\n");
        printf("O saque tem que ser menor ou igual a R$ %d,00.\n", notas[7]);
        printf("Abaixo uma amostragem das cedulas disponiveis.\n");
        printarCedulas(notas);
        printf("Por favor, digite o valor a ser sacado: ");
        scanf("%d", &valor);
    }
    sac[7] = valor;
    for(i = 0; i < 7; i++)
    {
        while (sac[i] > 0 && (notas[7] - v[i]) >= 0 && checar < valor)
        {
            sac[i]--;
            notas[7] -= v[i];
            checar += v[i];
        }
    }
    if (checar != valor)
    {
        printf("Cedulas insuficientes para realizar a operacao!\n");
        printf("Abaixo uma amostragem das cedulas disponiveis.\n");
        printarCedulas(notas);
        return saldo;
    }
    else
    {
        printf("\n|-----------SAQUE-----------|\n");
        for(i = 0; i < 7; i++)
        {
            if (sac[i] != notas[i])
            {
                if (v[i] >= 100)
                    printf("    %d Notas de R$ %d,00    \n", (notas[i] - sac[i]), v[i]);
                else if(v[i] >= 10)
                    printf("    %d Notas de R$  %d,00    \n", (notas[i] - sac[i]), v[i]);
                else
                    printf("    %d Notas de R$  0%d,00    \n", (notas[i] - sac[i]), v[i]);
            }
        }
        printf("|---------------------------|\n");
        printf("   Total  |      %d,00 \n", valor);
        printf("|---------------------------|\n\n");

        for (i = 0; i < 7; i++)
        {
            notas[i] = notas[i] - (notas[i] - sac[i]);
            notas[7] = notas[i] * v[i];
        }
        return (saldo - valor);
    }
}

void liberar(user *admin) 
{
    if(admin->next == NULL)
        free(admin);
    liberar(admin->next);
    free(admin);
}

void printarLista(user *lista) {
    user *posicao = lista;
    while(posicao) {
        printf("%s ", posicao->usuario);
        posicao = posicao->next;
    }
    printf("\n");
}