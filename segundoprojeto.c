#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <windows.h>
int cont = 0;

typedef struct user user;
struct user
{
    char *usuario;
    char *senha;
    int saldo;
    user *next;
};

void checarCedulas(int *valor);
void checarTexto(char *v);
void checarValor(int *valor);
user *checarLogin(user *estrutura);
user *procurarCadastro(char *username, user *admin);
void receberCliente(user *admin, int *notas, int *loop);
void *cadastraCliente(user *admin);
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
    admin->saldo = 0;
    admin->next = NULL;
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
        receberCliente(admin, notas, &loop);
    printf("\n|---------------------------|\n");
    printf("|    PROGRAMA ENCERRADO!    |\n");
    printf("|---------------------------|\n");

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
    char username[15], password[15];
    printf("Usuario: ");
    scanf(" %15s", &username);
    printf("Senha: ");
    scanf(" %15s", &password);
    user *posicao = procurarCadastro(username, estrutura);
    if (posicao == NULL)
    {
        while (posicao == NULL && cont < 3)
        {
            printf("Usuario nao encontrado, por favor, tente novamente. (%d tentativas restantes)\n", (3 - cont));
            printf("Usuario: ");
            scanf(" %15s", &username);
            printf("Senha: ");
            scanf(" %15s", &password);
            posicao = procurarCadastro(username, estrutura);
            cont++;
        }
        if (cont == 3)
        {
            printf("Usuario inexistente. Finalizando operacao!\n");
            cont = 0;
            return posicao;
        }
        cont = 0;
    }
    else if (strcmp(password, posicao->senha) != 0)
    {
        while (strcmp(password, posicao->senha) != 0 && cont < 3)
        {
            printf("Senha invalida, por favor, tente novamente. (%d tentativas restantes)\n", (3 - cont));
            printf("Usuario: ");
            scanf(" %15s", &username);
            printf("Senha: ");
            scanf(" %15s", &password);
            posicao = procurarCadastro(username, estrutura);
            cont++;
        }
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
            printf("Usuario confirmado.\nDigite a nova senha: ");
            scanf(" %15s", &password);
            posicao->senha = password;
            printf("Senha alterada com sucesso!\nEfetue o login.\n");
            return (posicao = checarLogin(estrutura));
        }
    }
    cont = 0;
    printf("Bem vindo, %s!\n", posicao->usuario);
    return posicao;
}

user *procurarCadastro(char *username, user *admin)
{
    user *posicao = admin;
    if (strcmp(username, "admin") == 0)
        return admin;
    while (posicao)
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
                cadastraCliente(admin);
                printf("Seu cadastro foi realizado com sucesso!\n");
                printf("Efetue o login para prosseguir ao menu do cliente.\n");
                menuCliente(notas, checarLogin(admin));
            }
            else
                printf("OK! Obrigada, tenha um otimo dia.\n");
        }
    }
}

void *cadastraCliente(user *admin)
{
    user *novo = malloc(sizeof(user));
    novo->usuario = malloc(sizeof(char) * 15);
    novo->senha = malloc(sizeof(char) * 15);
    printf("Crie seu nome de usuario: ");
    scanf("%s", novo->usuario);
    printf("Digite uma senha: ");
    scanf("%s", novo->senha);
    novo->saldo = 0;
    novo->next = NULL;
    if (procurarCadastro(novo->usuario, admin))
    {
        printf("Usuario ja existente, tente novamente.\n");
        free(novo->usuario);
        free(novo->senha);
        free(novo);
        cadastraCliente(admin);
    }
    else{
        if (admin == NULL)
            admin = novo;
        else
        {
            user *posicao = admin;
            while (posicao->next != NULL)
                posicao = posicao->next;
            posicao->next = novo;
        }
    }
}

    void menuCliente(int *notas, user *cliente)
    {
        if (cliente == NULL)
        {
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
    }

    void msgOperacao(int *notas, user *cliente)
    {
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
    }

    void receberCedulas(int *notas)
    {
        int v[] = {200, 100, 50, 20, 10, 5, 2}, i;
        for (i = 0; i < 7; i++)
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
        for (i = 0; i < 7; i++)
            if (notas[i] > 0)
            {
                if (v[i] >= 100)
                    printf("   %d,00 |      %d \n", v[i], notas[i]);
                else if (v[i] >= 10)
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
        for (notas[7] = 0, i = 0; i < 7; i++)
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
        for (notas[7] = 0, i = 0; i < 7; i++)
        {
            soma += dep[i] * v[i];
            notas[7] += notas[i] * v[i];
        }
        while (soma != valor)
        {
            printf("O valor a ser depositado nao corresponde com as cedulas inseridas.\n");
            printf("Voce inseriu R$ %d,00. Deseja depositar essa quantia? [sim/nao] ", soma);
            scanf(" %s", &res);
            checarTexto(res);
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
                for (soma = 0, i = 0; i < 7; i++)
                {
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
        int i, valor, sac[8], v[] = {200, 100, 50, 20, 10, 5, 2};
        for (notas[7] = 0, i = 0; i < 7; i++)
        {
            sac[i] = notas[i];
            notas[7] += notas[i] * v[i];
        }
        printf("Digite o valor que deseja sacar: ");
        scanf("%d", &valor);
        checarValor(&valor);
        while (valor > saldo)
        {
            printf("O valor a ser sacado eh incompativel com o saldo da conta.\n");
            printf("O saque tem que ser menor ou igual a seu saldo: %d\n", saldo);
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
        for (i = 0; i < 7; i++)
        {
            while (sac[i] > 0 && (sac[7] - v[i]) >= 0)
            {
                sac[i]--;
                sac[7] -= v[i];
            }
        }
        if (sac[7] != 0)
        {
            printf("Cedulas insuficientes para realizar a operacao!\n");
            printf("Abaixo uma amostragem das cedulas disponiveis.\n");
            printarCedulas(notas);
            return saldo;
        }
        else
        {
            printf("\n|-----------SAQUE-----------|\n");
            for (i = 0; i < 7; i++)
            {
                if (sac[i] != notas[i])
                {
                    if (v[i] >= 100)
                        printf("    %d Notas de R$ %d,00    \n", (notas[i] - sac[i]), v[i]);
                    else if (v[i] >= 10)
                        printf("    %d Notas de R$  %d,00    \n", (notas[i] - sac[i]), v[i]);
                    else
                        printf("    %d Notas de R$  0%d,00    \n", (notas[i] - sac[i]), v[i]);
                }
            }
            printf("|---------------------------|\n");
            printf("   Total  |      %d,00 \n", valor);
            printf("|---------------------------|\n\n");

            for (notas[7] = 0, i = 0; i < 7; i++)
            {
                notas[i] = notas[i] - (notas[i] - sac[i]);
                notas[7] += notas[i] * v[i];
            }
            return (saldo - valor);
        }
    }

    void liberar(user * admin)
    {
        if (admin->next == NULL)
            free(admin);
        liberar(admin->next);
    }