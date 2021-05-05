#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
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

void checarCedulas(int *valor);
void checarTexto(char *v);
void checarValor(int *valor);
user *checarLogin(user *estrutura);
user *buscaPosicao(user *admin, char *username);
user *procurarCadastro(char *username, user *admin);
void receberCliente(user *admin, int *notas, int *loop);
void cadastraCliente(user *admin);
void menuCliente(int *notas, user *cliente);
void msgOperacao(int notas, user *cliente);
void receberCedulas(int *notas);
void printarCedulas(int *notas);
void reabastecer(int *notas);
int depositar(int *notas, int saldo);
int sacar(int *notas, int saldo);

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
        scanf("%s", &v);
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
    char username[15], password[15];
    printf("Usuario: ");
    scanf(" %15s", &username);
    printf("Senha: ");
    scanf(" %15s", &password);
    user *posicao = procurarCadastro(username, estrutura);
    if (posicao == NULL)
    {
        printf("Usuario nao encontrado, por favor, tente novamente.\n");
        checarLogin(estrutura);
    }
    else if (password != posicao->senha)
    {
        cont++;
        if (cont == 3)
        {
            printf("Limite de tentativas excedido, voce deve alterar a senha.\n");
            printf("Confirme seu username: ");
            scanf(" %15s", &username);
            while (username != posicao->usuario)
            {
                printf("O usuario digitado nao coincide, tente novamente.\n");
                scanf(" %15s", &username);
            }
            printf("Digite a nova senha: ");
            scanf(" %15s", &(posicao->senha));
            printf("Senha alterada com sucesso!\nEfetue o login.\n");
        }
        else
            printf("Senha invalida, por favor, tente novamente.\n");
        checarLogin(estrutura);
    }
    cont = 0;
    printf("Bem vindo, %s!\n", posicao->usuario);
    return posicao;
}

user *buscaPosicao(user *admin, char *username)
{
    user *posicao = admin;
    while (posicao->next != NULL)
    {
        if (strcmp(username, posicao->usuario) < 0)
        {
            return posicao;
        }
        else
        {
            posicao = posicao->next;
        }
    }
    return posicao;
}

user *procurarCadastro(char *username, user *admin)
{
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

void cadastraCliente(user *admin)
{
    user *novo = malloc(sizeof(user));
    novo->saldo = 0;
    printf("Crie seu nome de usuario: ");
    scanf("%s", novo->usuario);
    printf("Digite uma senha: ");
    scanf("%s", novo->senha);
    if (admin->next == NULL)
    {
        admin->next = novo;
        novo->prev = admin;
        novo->next = NULL;
    }
    else
    {
        user *posicao = buscaPosicao(admin, novo->usuario);
        if (posicao->next == NULL)
        {
            posicao->next = novo;
            novo->prev = posicao;
            novo->next = NULL;
        }
        else
        {
            novo->next = posicao->next;
            novo->prev = posicao;
            posicao->next = novo;
            novo->next->prev = novo;
        }
    }
}

void menuCliente(int *notas, user *cliente)
{
    char res[3];
    printf("Voce possui um saldo de R$ %.2f.\n", cliente->saldo);
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

void msgOperacao(int notas, user *cliente)
{
    char res[3];
    printf("Deseja realizar outra operacao? [sim/nao] ");
    scanf("%3s", &res);
    checarTexto(res);
    if (res == "nao")
    {
        printf("O seu novo saldo é de R$ %d,00.\n", cliente->saldo);
        printf("Encerrando sessao.\nObrigado, volte sempre!");
    }
    else
        menuCliente(notas, cliente);
}

void receberCedulas(int *notas)
{
    int v[] = {200, 100, 50, 20, 10, 5, 2}, i;
    for(i = 0; i < 7; i++)
    {
        printf("Insira a quantidade de cedulas de R$ %d,00: ", v[i]);
        scanf("%d", &notas[i]);
        checarCedulas(&notas[i]);
    }
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
                printf("   %d,00 |      %d \n", v[i], notas[i]);
            else
                printf("   0%d,00  |      %d \n", v[i], notas[i]);
        }
    printf("|---------------------------|\n");
    printf("   Total  |      %d,00 \n", notas[7]);
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
    int valor, dep[] = {0, 0, 0, 0, 0, 0, 0}, v[] = {200, 100, 50, 20, 10, 5, 2}, soma, i;
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
        printf("Voce inseriu R$ %d,00. Deseja depositar essa quantia? [sim/nao] ");
        scanf("%3s", &res);
        checarTexto(res);
        if (res == "sim")
        {
            for (i = 0; i < 7; i++)
                notas[i] += dep[i];
            notas[7] += soma;
            return (saldo + soma);
        }
        else
        {
            printf("Insira novamente as cedulas, o valor a ser depositado é de R$ %d,00.\n", valor);
            receberCedulas(dep);
            for (i = 0; i < 7; i++)
                soma += dep[i] * v[i];
        }
    }
    for (i = 0; i < 7; i++)
        notas[i] += dep[i];
    notas[7] += soma;
    return (saldo + soma);
}

int sacar(int *notas, int saldo)
{
    int valor, sac[] = notas, v[] = {200, 100, 50, 20, 10, 5, 2}, checar = 0, i;
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