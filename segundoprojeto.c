#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct user user;
struct user
{
    char *usuario;
    char *senha;
    int saldo;
    user *next;
    user *prev;
};
void menuCliente(int *notas, user *cliente);

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

void checarValor(int *valor) {
    if(*valor >= 0)
        return;
    else {
        printf("O valor deve ser maior ou igual a zero. Digite novamente: ");
        scanf("%s", &valor);
        checarvalor(valor);
    }
}

void checartexto(char *v)
{
    char s[] = "sim", n[] = "nao";
    if (strcmp(v, s) == 0 || strcmp(v, n) == 0)
        return;
    else
    {
        printf("Comando invalido! Digite novamente. [sim/nao] ");
        scanf("%s", &v);
        checartexto(v);
    }
}

user *checarLogin(user *estrutura)
{
    char username[15], password[15];
    printf("Usuario: ");
    scanf("%s", username);
    printf("Senha: ");
    scanf("%s", password);
    user *posicao = procurarCadastro(username, estrutura);
    if (posicao == NULL || username != posicao->usuario || password != posicao->senha)
    {
        printf("Usuario ou senha incorretos, por favor, tente novamente.\n");
        //PARADA PARA ESQUECIMENTO DE SENHA, OBRIGATORIAMENTE LOGAR
        checarLogin(estrutura);
    }
    printf("Bem vindo, %s!\n", posicao->usuario);
    return posicao;
}

void checarcedulas(int *valor)
{
    if (*valor >= 0)
        return;
    else
    {
        printf("A quantidade de cedulas deve ser maior ou igual a 0, digite novamente: ");
        scanf("%d", valor);
        checarcedulas(valor);
    }
}

void recebercedulas(int *notas)
{
    printf("Insira a quantidade de cedulas de R$ 200,00: ");
    scanf("%d", notas[0]);
    checarcedulas(&notas[0]);

    printf("Insira a quantidade de cedulas de R$ 100,00: ");
    scanf("%d", notas[1]);
    checarcedulas(&notas[1]);

    printf("Insira a quantidade de cedulas de R$ 50,00: ");
    scanf("%d", notas[2]);
    checarcedulas(&notas[2]);

    printf("Insira a quantidade de cedulas de R$ 20,00: ");
    scanf("%d", notas[3]);
    checarcedulas(&notas[3]);

    printf("Insira a quantidade de cedulas de R$ 10,00: ");
    scanf("%d", notas[4]);
    checarcedulas(&notas[4]);

    printf("Insira a quantidade de cedulas de R$ 5,00: ");
    scanf("%d", notas[5]);
    checarcedulas(&notas[5]);

    printf("Insira a quantidade de cedulas de R$ 2,00: ");
    scanf("%d", notas[6]);
    checarcedulas(&notas[6]);
}

void reabastecer(int *notas)
{
    int rnotas[6];

    recebercedulas(rnotas);
    notas[0] += rnotas[0];
    notas[1] += rnotas[1];
    notas[2] += rnotas[2];
    notas[3] += rnotas[3];
    notas[4] += rnotas[4];
    notas[5] += rnotas[5];
    notas[6] += rnotas[6];
    notas[7] = notas[0] * 200 + notas[1] * 100 + notas[2] * 50 + notas[3] * 20 + notas[4] * 10 + notas[5] * 5 + notas[6] * 2;
}

void printarcedulas(int *notas)
{
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

int depositar(int *notas, int saldo)
{   
    int valor, dep[] = {0, 0, 0, 0, 0, 0, 0}, soma, i;
    char res[3];
    printf("Digite o valor que deseja depositar: ");
    scanf("%d", &valor);
    checarValor(&valor);
    recebercedulas(dep);
    soma = dep[0] * 200 + dep[1] * 100 + dep[2] * 50 + dep[3] * 20 + dep[4] * 10 + dep[5] * 5 + dep[6] * 2;
    while (soma != valor)
    {
        printf("O valor a ser depositado nao corresponde com as cedulas inseridas.\n");
        printf("Voce inseriu R$%d,00. Deseja depositar essa quantia? [sim/nao] ");
        scanf("%3s", &res);
        checartexto(res);
        if(res == "sim")
        {
            for(i = 0; i < 7; i++)
                notas[i] += dep[i];
            notas[7] += soma;
            return (saldo + soma);
        }
        else
        {
            printf("Insira novamente as cedulas, o valor a ser depositado é de R$%d,00.\n", valor);
            recebercedulas(dep);
            soma = dep[0] * 200 + dep[1] * 100 + dep[2] * 50 + dep[3] * 20 + dep[4] * 10 + dep[5] * 5 + dep[6] * 2;
        }        
    }
    for(i = 0; i < 7; i++)
        notas[i] += dep[i];
    notas[7] += soma;
    return (saldo + soma);

}

int sacar(int *notas, int saldo)
{
    int valor, sac[] = notas, checar = 0;
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
        printarcedulas(notas);
        printf("Por favor, digite o valor a ser sacado: ");
        scanf("%d", &valor);
    }
    sac[7] = valor;
    while (sac[0] > 0 && (notas[7] - 200) >= 0 && checar < valor) {
        sac[0]--;
        notas[7] -= 200;
        checar += 200;
    }
    while (sac[1] > 0 && (notas[7] - 100) >= 0 && checar < valor) {
        sac[1]--;
        notas[7] -= 100;
        checar += 100;
    }
    while (sac[2] > 0 && (notas[7] - 50) >= 0 && checar < valor) {
        sac[2]--;
        notas[7] -= 50;
        checar += 50;
    }
    while (sac[3] > 0 && (notas[7] - 20) >= 0 && checar < valor) {
        sac[3]--;
        notas[7] -= 20;
        checar += 20;
    }
    while (sac[4] > 0 && (notas[7] - 10) >= 0 && checar < valor) {
        sac[4]--;
        notas[7] -= 10;
        checar += 10;
    }
    while (sac[5] > 0 && (notas[7] - 5) >= 0 && checar < valor) {
        sac[5]--;
        notas[7] -= 5;
        checar += 5;
    }
    while (sac[6] > 0 && (notas[7] - 2) >= 0 && checar < valor) {
        sac[6]--;
        notas[7] -= 2;
        checar += 2;
    }

    
}

void msgOperacao(int notas, user *cliente){
    char res[3];
    printf("Deseja realizar outra operacao? [sim/nao] ");
    scanf("%3s", &res);
    checartexto(res);
    if(res == "nao")
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
    if(cliente->saldo == 0)
    {
        printf("Com esse saldo você apenas pode realizar depositos.\n");
        printf("Deseja realizar um deposito agora? [sim/nao] ");
        scanf("%3s", &res);
        checartexto(res);
        if(res == "nao")
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
        while (rets != 0 && retd != 0) {
            printf("Comando invalido!\n");
            printf("Digite a operacao que deseja realizar: [saque/deposito] ");
            scanf(" %8s", &v);
            rets = strncmp(v, s, 5);
            retd = strncmp(v, d, 8);
        }
        if(retd == 0){
            cliente->saldo = depositar(notas, cliente->saldo);
            msgOperacao(notas, cliente);
        }
        else
        {
            if(notas[7] == 0)
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
    checartexto(res);
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
            printarcedulas(notas);
        }
        printf("Encerrando sessao do administrador.\n");
    }
    else
    {
        printf("Voce ja eh cliente? [sim/nao] ");
        scanf("%s", res);
        checartexto(res);
        if (res == "sim")
            menuCliente(notas, checarLogin(admin));
        else
        {
            printf("Deseja criar uma conta em nosso banco? [sim/nao] ");
            scanf("%s", res);
            checartexto(res);
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
    printarcedulas(notas);
    printf("Encerrando sessao do administrador.\n");
    while (loop)
    {
        receberCliente(admin, notas, &loop);
    }
}
