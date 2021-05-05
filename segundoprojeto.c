#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
<<<<<<< HEAD
#include <conio.h>
#define R     "\x1b[31m"
#define B     "\e[0;37m"
int cont = 0;
=======
>>>>>>> parent of 29fa795... Versão final não testada.

typedef struct user user;
struct user
{
    char *usuario;
    char *senha;
    int saldo;
    user *next;
    user *prev;
};
<<<<<<< HEAD

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
=======
void menuCliente(int *notas, user *cliente);
>>>>>>> parent of 29fa795... Versão final não testada.

user *procurarCadastro(char *username, user *admin)
{
<<<<<<< HEAD
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
=======
    user *posicao = admin;
    if (username == "admin")
        return admin;
    while (posicao->next != NULL)
    {
        if (strcmp(username, posicao->usuario) == 0)
            return posicao;
        posicao = posicao->next;
    }
    return NULL;
>>>>>>> parent of 29fa795... Versão final não testada.
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

user *checarLogin(user *estrutura)
{
    printf(R"checarLogin entrou \n"B);
    char username[15], password[15];
    printf("Usuario: ");
    scanf("%s", username);
    printf("Senha: ");
    scanf("%s", password);
    user *posicao = procurarCadastro(username, estrutura);
    if (posicao == NULL || username != posicao->usuario || password != posicao->senha)
    {
<<<<<<< HEAD
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
=======
        printf("Usuario ou senha incorretos, por favor, tente novamente.\n");
        //PARADA PARA ESQUECIMENTO DE SENHA, OBRIGATORIAMENTE LOGAR
        checarLogin(estrutura);
    }
>>>>>>> parent of 29fa795... Versão final não testada.
    printf("Bem vindo, %s!\n", posicao->usuario);
    printf(R"checarLogin saiu \n"B);
    return posicao;
}

void checarCedulas(int *valor)
{
<<<<<<< HEAD
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
=======
    if (*valor >= 0)
        return;
    else
    {
        printf("A quantidade de cedulas deve ser maior ou igual a 0, digite novamente: ");
        scanf("%d", valor);
        checarCedulas(valor);
    }
>>>>>>> parent of 29fa795... Versão final não testada.
}

void receberCedulas(int *notas)
{
<<<<<<< HEAD
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
=======
    printf("Insira a quantidade de cedulas de R$ 200,00: ");
    scanf("%d", notas[0]);
    checarCedulas(&notas[0]);

    printf("Insira a quantidade de cedulas de R$ 100,00: ");
    scanf("%d", notas[1]);
    checarCedulas(&notas[1]);

    printf("Insira a quantidade de cedulas de R$ 50,00: ");
    scanf("%d", notas[2]);
    checarCedulas(&notas[2]);

    printf("Insira a quantidade de cedulas de R$ 20,00: ");
    scanf("%d", notas[3]);
    checarCedulas(&notas[3]);

    printf("Insira a quantidade de cedulas de R$ 10,00: ");
    scanf("%d", notas[4]);
    checarCedulas(&notas[4]);

    printf("Insira a quantidade de cedulas de R$ 5,00: ");
    scanf("%d", notas[5]);
    checarCedulas(&notas[5]);

    printf("Insira a quantidade de cedulas de R$ 2,00: ");
    scanf("%d", notas[6]);
    checarCedulas(&notas[6]);
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
>>>>>>> parent of 29fa795... Versão final não testada.
}

void printarCedulas(int *notas)
{
<<<<<<< HEAD
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
=======
    printf("\n|-----------CAIXA-----------|\n");
    printf("   Valor  | Qtd. de cedulas \n");
    printf("|---------------------------|\n");
    printf("   200,00 |      %d \n", notas[0]);
    printf("   100,00 |      %d \n", notas[1]);
    printf("   50,00  |      %d \n", notas[2]);
    printf("   20,00  |      %d \n", notas[3]);
    printf("   10,00  |      %d \n", notas[4]);
    printf("   05,00  |      %d \n", notas[5]);
    printf("   02,00  |      %d \n", notas[6]);
    printf("|---------------------------|\n");
    printf("   Total  |      %d,00 \n", notas[7]);
    printf("|---------------------------|\n\n");
}

user *buscaPosicao(user *admin, char *username)
{
    user *posicao = admin;
    while (posicao->next != NULL)
    {
        if (strcmp(username, posicao->usuario) < 0)
>>>>>>> parent of 29fa795... Versão final não testada.
        {
            return posicao;
        }
<<<<<<< HEAD
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
=======
        else
        {
            posicao = posicao->next;
        }
    }
    return posicao;
>>>>>>> parent of 29fa795... Versão final não testada.
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

<<<<<<< HEAD
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

=======
>>>>>>> parent of 29fa795... Versão final não testada.
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
<<<<<<< HEAD
        printf("Voce inseriu R$ %d,00. Deseja depositar essa quantia? [sim/nao] ", soma);
        scanf(" %s", &res);
=======
        printf("Voce inseriu R$%d,00. Deseja depositar essa quantia? [sim/nao] ");
        scanf("%3s", &res);
>>>>>>> parent of 29fa795... Versão final não testada.
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
<<<<<<< HEAD
            printf("Insira novamente as cedulas, o valor a ser depositado eh de R$ %d,00.\n", valor);
=======
            printf("Insira novamente as cedulas, o valor a ser depositado é de R$%d,00.\n", valor);
>>>>>>> parent of 29fa795... Versão final não testada.
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
    while (sac[0] > 0 && (notas[7] - 200) >= 0 && checar < valor)
    {
        sac[0]--;
        notas[7] -= 200;
        checar += 200;
    }
    while (sac[1] > 0 && (notas[7] - 100) >= 0 && checar < valor)
    {
        sac[1]--;
        notas[7] -= 100;
        checar += 100;
    }
    while (sac[2] > 0 && (notas[7] - 50) >= 0 && checar < valor)
    {
        sac[2]--;
        notas[7] -= 50;
        checar += 50;
    }
    while (sac[3] > 0 && (notas[7] - 20) >= 0 && checar < valor)
    {
        sac[3]--;
        notas[7] -= 20;
        checar += 20;
    }
    while (sac[4] > 0 && (notas[7] - 10) >= 0 && checar < valor)
    {
        sac[4]--;
        notas[7] -= 10;
        checar += 10;
    }
    while (sac[5] > 0 && (notas[7] - 5) >= 0 && checar < valor)
    {
        sac[5]--;
        notas[7] -= 5;
        checar += 5;
    }
    while (sac[6] > 0 && (notas[7] - 2) >= 0 && checar < valor)
    {
        sac[6]--;
        notas[7] -= 2;
        checar += 2;
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
        if (sac[0] != notas[0])
            printf("    %d Notas de R$ 200,00    \n", (notas[0] - sac[0]));
        if (sac[1] != notas[1])
            printf("    %d Notas de R$ 100,00    \n", (notas[1] - sac[1]));
        if (sac[2] != notas[2])
            printf("    %d Notas de R$  50,00    \n", (notas[2] - sac[2]));
        if (sac[3] != notas[3])
            printf("    %d Notas de R$  20,00    \n", (notas[3] - sac[3]));
        if (sac[4] != notas[4])
            printf("    %d Notas de R$  10,00    \n", (notas[4] - sac[4]));
        if (sac[5] != notas[5])
            printf("    %d Notas de R$   5,00    \n", (notas[5] - sac[5]));
        if (sac[6] != notas[6])
            printf("    %d Notas de R$   2,00    \n", (notas[6] - sac[6]));
        printf("|---------------------------|\n\n");

        for (i = 0; i < 7; i++)
        {
            notas[i] = notas[i] - (notas[i] - sac[i]);
            notas[7] = notas[i] * v[i];
        }
        return (saldo - valor);
    }
}

<<<<<<< HEAD
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
=======
void msgOperacao(int notas, user *cliente)
{
    char res[3];
    printf("Deseja realizar outra operacao? [sim/nao] ");
    scanf("%3s", &res);
    checarTexto(res);
    if (res == "nao")
    {
        printf("O seu novo saldo é de R$%d,00.\n", cliente->saldo);
        printf("Encerrando sessao.\nObrigado, volte sempre!");
    }
    else
        menuCliente(notas, cliente);
}

void menuCliente(int *notas, user *cliente)
{
    char res[3];
    printf("Voce possui um saldo de R$%.2f.\n", cliente->saldo);
    if (cliente->saldo == 0)
    {
        printf("Com esse saldo você apenas pode realizar depositos.\n");
        printf("Deseja realizar um deposito agora? [sim/nao] ");
        scanf("%3s", &res);
        checarTexto(res);
        if (res == "nao")
            printf("Encerrando sessao.\nObrigado, volte sempre!");
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
        scanf(" %8s", &v);
        rets = strncmp(v, s, 5);
        retd = strncmp(v, d, 8);
        while (rets != 0 && retd != 0)
        {
            printf("Comando invalido!\n");
            printf("Digite a operacao que deseja realizar: [saque/deposito] ");
            scanf(" %8s", &v);
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
}

void receberCliente(user *admin, int *notas, int *loop)
{
    char res[3];
    printf("Bem vindo ao Banco do Programador!\n");
    printf("Deseja efetuar operacoes de administrador? [sim/nao] ");
    scanf("%s", res);
    checarTexto(res);
    if (res == "sim")
    {
        admin = checarLogin(admin);
        printf("Deseja desligar a maquina? [sim/nao] ");
        scanf("%s", res);
        if (res == "sim")
        {
            *loop = 0;
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
        scanf("%s", res);
        checarTexto(res);
        if (res == "sim")
            menuCliente(notas, checarLogin(admin));
        else
        {
            printf("Deseja criar uma conta em nosso banco? [sim/nao] ");
            scanf("%s", res);
            checarTexto(res);
            if (res == "sim")
            {
                cadastraCliente(admin);
            }
            else
                printf("OK! Obrigada, tenha um otimo dia.\n");
        }
    }
}

int main()
{
    user *admin = malloc(sizeof(user));
    admin->usuario = "admin";
    admin->senha = "admin";
    admin->next = NULL;
    admin->prev = NULL;
    int notas[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int loop = 1;
    printf("Este caixa eletronico acabou de ser iniciado.\n");
    printf("Nao ha cedulas na maquina, acesse o usuario administrador para reabastecer.\n");
    admin = checarLogin(admin);
    reabastecer(notas);
    printf("Caixa reabastecido, segue as quantidades.\n");
    printarCedulas(notas);
    printf("Encerrando sessao do administrador.\n");
    while (loop)
    {
        receberCliente(admin, notas, &loop);
    }
}
>>>>>>> parent of 29fa795... Versão final não testada.
