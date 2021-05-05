#include <stdio.h>
#include <string.h>

void checarcedulas(int *valor) {
    if(*valor >= 0)
        return;
    else {
        printf("A quantidade de cedulas deve ser maior ou igual a 0, digite novamente: ");
        scanf("%d", valor);
        checarcedulas(valor);
    }
}

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

void checarvalor(int *valor) {
    if(*valor >= 0)
        return;
    else {
        printf("O valor deve ser maior ou igual a zero. Digite novamente: ");
        scanf("%s", &valor);
        checarvalor(valor);
    }
}

void recebercedulas(int *duz, int *cem, int *cinq, int *vin, int *dez, int *cinc, int *dois) {
    printf("Insira a quantidade de cedulas de R$ 200,00: ");
    scanf("%d", duz);
    checarcedulas(duz);

    printf("Insira a quantidade de cedulas de R$ 100,00: ");
    scanf("%d", cem);
    checarcedulas(cem);

    printf("Insira a quantidade de cedulas de R$ 50,00: ");
    scanf("%d", cinq);
    checarcedulas(cinq);

    printf("Insira a quantidade de cedulas de R$ 20,00: ");
    scanf("%d", vin);
    checarcedulas(vin);

    printf("Insira a quantidade de cedulas de R$ 10,00: ");
    scanf("%d", dez);
    checarcedulas(dez);

    printf("Insira a quantidade de cedulas de R$ 5,00: ");
    scanf("%d", cinc);
    checarcedulas(cinc);

    printf("Insira a quantidade de cedulas de R$ 2,00: ");
    scanf("%d", dois);
    checarcedulas(dois);
}

void printarcedulas(int qduz, int qcem, int qcinq, int qvin, int qdez, int qcinc, int qdois, int total) {
    printf("\n|-----------CAIXA-----------|\n");
    printf("   Valor  | Qtd. de cedulas \n");
    printf("|---------------------------|\n");
    printf("   200,00 |      %d \n", qduz);
    printf("   100,00 |      %d \n", qcem);
    printf("   50,00  |      %d \n", qcinq);
    printf("   20,00  |      %d \n", qvin);
    printf("   10,00  |      %d \n", qdez);
    printf("   05,00  |      %d \n", qcinc);
    printf("   02,00  |      %d \n", qdois);
    printf("|---------------------------|\n");
    printf("   Total  |      %d,00 \n", total);
    printf("|---------------------------|\n\n");
}

int saque(int *duz, int *cem, int *cinq, int *vin, int *dez, int *cinc, int *dois, float saldo, int valor, int *total) {
    //Calcular o menor número de cédulas necessárias para realizar o saque
    int Sduz = *duz, Scem = *cem, Scinq = *cinq, Svin = *vin, Sdez = *dez, Scinc = *cinc, Sdois = *dois;
    int sacar = valor, checar = 0;

    while (Sduz > 0 && (sacar - 200) >= 0 && checar < valor) {
        Sduz--;
        sacar -= 200;
        checar += 200;
    }
    while (Scem > 0 && (sacar - 100) >= 0 && checar < valor) {
        Scem--;
        sacar -= 100;
        checar += 100;
    }
    while (Scinq > 0 && (sacar - 50) >= 0 && checar < valor) {
        Scinq--;
        sacar -= 50;
        checar += 50;
    }
    while (Svin > 0 && (sacar - 20) >= 0 && checar < valor) {
        Svin--;
        sacar -= 20;
        checar += 20;
    }
    while (Sdez > 0 && (sacar - 10) >= 0 && checar < valor) {
        Sdez--;
        sacar -= 10;
        checar += 10;
    }
    while (Scinc > 0 && (sacar - 5) >= 0 && checar < valor) {
        Scinc--;
        sacar -= 5;
        checar += 5;
    }
    while (Sdois > 0 && (sacar - 2) >= 0 && checar < valor) {
        Sdois--;
        sacar -= 2;
        checar += 2;
    }
    //Checa se foi possível sacar o valor
    if (checar != valor) {
        printf("Cedulas insuficientes para realizar a operacao!\n");
        return saldo;
    }
    //Exibe e atualiza o saldo e as quantidades de cédulas
    else {
        printf("\n|-----------SAQUE-----------|\n");
        if (Sduz != *duz)
            printf("    %d Notas de R$ 200,00    \n", (*duz - Sduz));
        if (Scem != *cem)
            printf("    %d Notas de R$ 100,00    \n", (*cem - Scem));
        if (Scinq != *cinq)
            printf("    %d Notas de R$  50,00    \n", (*cinq - Scinq));
        if (Svin != *vin)
            printf("    %d Notas de R$  20,00    \n", (*vin - Svin));
        if (Sdez != *dez)
            printf("    %d Notas de R$  10,00    \n", (*dez - Sdez));
        if (Scinc != *cinc)
            printf("    %d Notas de R$   5,00    \n", (*cinc - Scinc));
        if (Sdois != *dois)
            printf("    %d Notas de R$   2,00    \n", (*dois - Sdois));
        printf("|---------------------------|\n\n");

        *duz = *duz - (*duz - Sduz);
        *cem = *cem - (*cem - Scem);
        *cinq = *cinq - (*cinq - Scinq);
        *vin = *vin - (*vin - Svin);
        *dez = *dez - (*dez - Scinc);
        *cinc = *cinc - (*cinc - Scinc);
        *dois = *dois - (*dois - Sdois);
        *total = *duz * 200 + *cem * 100 + *cinq * 50 + *vin * 20 + *dez * 10 + *cinc * 5 + *dois * 2;
        return (saldo - valor);
    }
}

void caixaeletronico(int *qduz, int *qcem, int *qcinq, int *qvin, int *qdez, int *qcinc, int *qdois, float *saldo, int *total) {
    int rets, retd;

    //Impedir o saque caso o saldo seja negativo
    if (*saldo < 0) {
        char resp[3], s[] = "sim", n[] = "nao";
        printf("O seu saldo esta negativo!\n");
        printf("Deseja realizar um deposito? [sim/nao] ");
        scanf("%s", &resp);

        if (strcmp(resp, n) == 0)
            return;
        else
            rets = 1;
    }
    //Escolher saque ou deposito
    else {
        char v[9], s[] = "saque", d[] = "deposito";
        printf("Digite a operacao desejada. [saque/deposito] ");
        scanf(" %s", &v);
        rets = strncmp(v, s, 5);
        retd = strncmp(v, d, 8);
        while (rets != 0 && retd != 0) {
            printf("Comando invalido!\n");
            printf("Digite a operacao desejada. [saque/deposito] ");
            scanf(" %s", &v);
            rets = strncmp(v, s, 5);
            retd = strncmp(v, d, 9);
        }
    }
    int valor;
    if (rets == 0) {
        //Funções relacionadas ao saque
        printf("Digite o valor a ser sacado: ");
        scanf("%d", &valor);
        checarvalor(&valor);
        *total = *qduz * 200 + *qcem * 100 + *qcinq * 50 + *qvin * 20 + *qdez * 10 + *qcinc * 5 + *qdois * 2;
        //Checar se o valor é compativel com o saldo ou com as cédulas da máquina
        while (valor > *saldo || valor > *total) {
            *total = *qduz * 200 + *qcem * 100 + *qcinq * 50 + *qvin * 20 + *qdez * 10 + *qcinc * 5 + *qdois * 2;
            if (valor > *saldo) {
                printf("O valor a ser sacado eh incompativel com o saldo da conta.\n");
                printf("O saque tem que ser menor ou igual a seu saldo: %.2f\n", *saldo);
            }
            if (valor > *total) {
                printf("O valor a ser sacado eh incompativel com o dinheiro disponivel na maquina.\n");
                printf("O saque tem que ser menor ou igual a R$ %d,00.\n", *total);
                printf("Abaixo uma amostragem das cedulas disponiveis.\n");
                printarcedulas(*qduz, *qcem, *qcinq, *qvin, *qdez, *qcinc, *qdois, *total);
                if (*total == 0) return;
            }
            printf("Por favor, digite o valor a ser sacado: ");
            scanf("%d", &valor);
        }
        //Atualizar e exibir o saldo pos saque
        *saldo = saque(qduz, qcem, qcinq, qvin, qdez, qcinc, qdois, *saldo, valor, total);
        printf("|---------------------------|\n");
        printf("   Saldo  =      %.2f        \n", *saldo);
        printf("|---------------------------|\n\n");
        printarcedulas(*qduz, *qcem, *qcinq, *qvin, *qdez, *qcinc, *qdois, *total);
    } 
    else {
        //Funções relacionadas ao depósito
        printf("Digite o valor a ser depositado: ");
        scanf("%d", &valor);
        checarvalor(&valor);
        //Receber as cédulas que serão depositadas e conferí-las
        printf("Para realizar a operacao voce deve informar o numero de cedulas que serao depositadas.\n");
        int Dduz, Dcem, Dcinq, Dvin, Ddez, Dcinc, Ddois, soma;
        recebercedulas(&Dduz, &Dcem, &Dcinq, &Dvin, &Ddez, &Dcinc, &Ddois);
        soma = Dduz * 200 + Dcem * 100 + Dcinq * 50 + Dvin * 20 + Ddez * 10 + Dcinc * 5 + Ddois * 2;
        while (soma != valor) {
            printf("O valor que deseja depositar eh diferente do valor recebido pela maquina.\n");
            printf("Para realizar a operacao voce deve informar o numero de cedulas que serao depositadas.\n");
            recebercedulas(&Dduz, &Dcem, &Dcinq, &Dvin, &Ddez, &Dcinc, &Ddois);
            soma = Dduz * 200 + Dcem * 100 + Dcinq * 50 + Dvin * 20 + Ddez * 10 + Dcinc * 5 + Ddois * 2;
        }
        //Calcular a nova quantidade de cédulas
        *qduz += Dduz;
        *qcem += Dcem;
        *qcinq += Dcinq;
        *qvin += Dvin;
        *qdez += Ddez;
        *qcinc += Dcinc;
        *qdois += Ddois;
        *total = *qduz * 200 + *qcem * 100 + *qcinq * 50 + *qvin * 20 + *qdez * 10 + *qcinc * 5 + *qdois * 2;
        //Atualizar e exibir o novo saldo e as novas quantidades de cédulas
        printarcedulas(*qduz, *qcem, *qcinq, *qvin, *qdez, *qcinc, *qdois, *total);
        *saldo += valor;
        printf("|---------------------------|\n");
        printf("   Saldo  =      %.2f        \n", *saldo);
        printf("|---------------------------|\n\n");
    }
}

void reabastecer(int *qduz, int *qcem, int *qcinq, int *qvin, int *qdez, int *qcinc, int *qdois, int *total) {
    int rduz, rcem, rcinq, rvin, rdez, rcinc, rdois;

    recebercedulas(&rduz, &rcem, &rcinq, &rvin, &rdez, &rcinc, &rdois);
    *qduz += rduz;
    *qcem += rcem;
    *qcinq += rcinq;
    *qvin += rvin;
    *qdez += rdez;
    *qcinc += rcinc;
    *qdois += rdois;
    *total = *qduz * 200 + *qcem * 100 + *qcinq * 50 + *qvin * 20 + *qdez * 10 + *qcinc * 5 + *qdois * 2;
}

int main() {
    //Receber quantidade de cédulas
    int qduz, qcem, qcinq, qvin, qdez, qcinc, qdois, total;
    char v[3], sim[] = "sim", nao[] = "nao", resp[] = "nao";

    recebercedulas(&qduz, &qcem, &qcinq, &qvin, &qdez, &qcinc, &qdois);
    total = qduz * 200 + qcem * 100 + qcinq * 50 + qvin * 20 + qdez * 10 + qcinc * 5 + qdois * 2;
    printarcedulas(qduz, qcem, qcinq, qvin, qdez, qcinc, qdois, total);
    //Receber o saldo disponível na conta
    float saldo;
    printf("Insira o saldo disponivel na conta: ");
    scanf("%f", &saldo);
    //Realizar operações de saque, depósito ou reabastecimento
    caixaeletronico(&qduz, &qcem, &qcinq, &qvin, &qdez, &qcinc, &qdois, &saldo, &total);
    printf("Deseja realizar outra operacao? [sim/nao] ");
    scanf("%s", &v);
    checartexto(v);
    printf("Deseja realizar o reabastecimento de cedulas? [sim/nao] ");
    scanf("%s", &resp);
    checartexto(resp);
    //Checar se deseja encerrar o programa
    while (strcmp(v, sim) == 0 || strcmp(resp, sim) == 0) {
        if (strcmp(resp, sim) == 0){
            reabastecer(&qduz, &qcem, &qcinq, &qvin, &qdez, &qcinc, &qdois, &total);
            printarcedulas(qduz, qcem, qcinq, qvin, qdez, qcinc, qdois, total);
        }
        if (strcmp(v, sim) == 0)
            caixaeletronico(&qduz, &qcem, &qcinq, &qvin, &qdez, &qcinc, &qdois, &saldo, &total);
        printf("Deseja realizar outra operacao? [sim/nao] ");
        scanf("%s", &v);
        checartexto(v);
        printf("Deseja realizar o reabastecimento de cedulas? [sim/nao] ");
        scanf("%s", &resp);
        checartexto(resp);
    }
    printf("\n|---------------------------|\n");
    printf("|    PROGRAMA ENCERRADO!    |\n");
    printf("|---------------------------|\n");
    
    return 0;
}