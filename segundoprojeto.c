#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct user user;
struct user {
    char *usuario;
    char *senha;
    float saldo;
    user *next;
    user *prev;
};
void checartexto(char v[]) {
    char s[] = "sim", n[] = "nao";
    if(strcmp(v, s) == 0 || strcmp(v, n) == 0)
        return;
    else {
        printf("Comando invalido! Digite novamente. [sim/nao] ");
        scanf("%s", &v);
        checartexto(v);
    }
}
void checarLogin(user *estrutura){
    char username[15], password[15];
    printf("Usuario: ");
    scanf("%s", username);
    printf("Senha: ");
    scanf("%s", password);
    if(username != estrutura->usuario || password != estrutura->senha){
        printf("Usuario ou senha incorretos, por favor, tente novamente.\n");
        checarLogin(estrutura);
    }
}
void checarcedulas(int *valor) {
    if(*valor >= 0)
        return;
    else {
        printf("A quantidade de cedulas deve ser maior ou igual a 0, digite novamente: ");
        scanf("%d", valor);
        checarcedulas(valor);
    }
}
void recebercedulas(int *notas) {
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
void reabastecer(int *notas){
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
void printarcedulas(int *notas) {
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
void cadastraCliente(user *admin){
    user *novo = malloc(sizeof(user));
    novo->saldo = 0;
    printf("Crie seu nome de usuario: ");
    scanf("%s", novo->usuario);
    printf("Digite uma senha: ");
    scanf("%s", novo->senha);
    if(admin->next == NULL){
        admin->next = novo;
        novo->prev = admin;
        novo->next = NULL;
    }
    else{
        while() // buscar a posição e inserir 
    }
}
void menuCliente(){

}
void receberCliente(user *admin, int *notas, int *loop){
    char res[3];
    printf("Bem vindo ao Banco do Programador!\n");
    printf("Deseja efetuar operacoes de administrador? [sim/nao] ");
    scanf("%s", res);
    checartexto(res);
    if(res == "sim"){
        checarLogin(admin);
        printf("Deseja desligar a maquina? [sim/nao] ");
        scanf("%s", res);
        if(res == "sim"){
            *loop = 0;
            return;
        }
        else{
            printf("Iniciando operacao de reabastecimento.\n");
            reabastecer(notas);
            printf("Caixa reabastecido, segue as quantidades.\n");
            printarcedulas(notas);
        }
        printf("Encerrando sessao do administrador.\n");
    }
    else{
        printf("Voce ja eh cliente? [sim/nao] ");
        scanf("%s", res);
        checartexto(res);
        if(res == "sim"){
            checarLogin(procurarCadastro());
            menuCliente(estruturaDoCliente, notas);
        }
        else{
            printf("Deseja criar uma conta em nosso banco? [sim/nao] ");
            scanf("%s", res);
            checartexto(res);
            if(res == "sim"){
                cadastraCliente(admin);
            }
            else{
                printf("OK! Obrigada, tenha um otimo dia.\n");
            }
        }
    }
}
int main(){
    user *admin = malloc(sizeof(user));
    admin->usuario = "admin";
    admin->senha = "admin";
    admin->next = NULL;
    admin->prev = NULL;
    int notas[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int loop = 1;
    printf("Este caixa eletronico acabou de ser iniciado.\n");
    printf("Nao ha cedulas na maquina, acesse o usuario administrador para reabastecer.\n");
    checarLogin(admin);
    reabastecer(notas);
    printf("Caixa reabastecido, segue as quantidades.\n");
    printarcedulas(notas);
    printf("Encerrando sessao do administrador.\n");
    while (loop){
        receberCliente(admin, notas, &loop);
    }
       
}
