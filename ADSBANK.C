#include <stdio.h>
#include <string.h>

#define MAX 5            //Definindo o numero maximo de clientes permitidos.
#define MAX_NOME 100     //Definindo o tamanho maximo do nome do cliente, quantos caracteres por exemplo.

//Definindo a estrutura que representa um cliente. 
typedef struct {
    char nome[MAX_NOME]; //Nome do cliente.
    char cpf[12];        //CPF do cliente.
    double saldo;        //Saldo da conta do cliente.
    int autorizado;      //Indica a autorização do cliente. 
} Cliente;

//Função para inserir um novo cliente no sistema.
void inserirCliente(Cliente clientes[MAX], int *numClientes) {
    if (*numClientes < MAX) { //Verifica se ainda há espaço para novos clientes.
        printf("Digite o nome completo do cliente: ");
        fgets(clientes[*numClientes].nome, MAX_NOME, stdin); //Lendo o nome do cliente.
        clientes[*numClientes].nome[strcspn(clientes[*numClientes].nome, "\n")] = '\0'; //Remove a quebra de linha
        printf("Digite o CPF do cliente: ");
        fgets(clientes[*numClientes].cpf, 12, stdin); //Lê o CPF do cliente.
        clientes[*numClientes].saldo = 0.0;           //Inicializa o saldo como 0.0.
        clientes[*numClientes].autorizado = 0;        //O cliente não está autorizado por padrão.
        (*numClientes)++;                             //Incrementa o número de clientes.
    } else {
        printf("Erro! Limite de clientes atingido.\n");
    }
}

//Função para listar todos os clientes cadastrados.
void listarClientes(Cliente clientes[MAX], int numClientes) {
    printf("\nClientes cadastrados:\n");
    for (int i = 0; i < numClientes; i++) {
        printf("Cliente %d: %s - CPF: %s - Saldo: %.2f - %s\n", 
            i + 1, clientes[i].nome, clientes[i].cpf, clientes[i].saldo,
            clientes[i].autorizado ? "Autorizado" : "Não autorizado"); //Mostra os detalhes do cliente.
    }
}

//Função para atualizar o nome e CPF de um cliente.
void atualizarCliente(Cliente clientes[MAX], int numClientes) {
    int index;
    printf("Digite o ID do cliente que deseja atualizar (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes) { //Verifica se o índice é válido.
        printf("Digite um novo nome para o cliente %d: ", index);
        fgets(clientes[index - 1].nome, MAX_NOME, stdin); //Atualiza o nome do cliente.
        clientes[index - 1].nome[strcspn(clientes[index - 1].nome, "\n")] = '\0'; //Remove a quebra de linha.
        printf("Digite um novo CPF para o cliente %d: ", index);
        fgets(clientes[index - 1].cpf, 12, stdin); //Atualiza o CPF do cliente.
    } else {
        printf("Erro! Número de cliente inválido.\n");
    }
}

//Função para alterar o CPF de um cliente.
void alterarCPF(Cliente clientes[MAX], int numClientes) {
    int index;
    printf("Digite o ID do cliente que deseja alterar o CPF (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes) { //Verifica se o índice é válido.
        printf("Digite o novo CPF para o cliente %d: ", index);
        fgets(clientes[index - 1].cpf, 12, stdin); //Atualiza o CPF do cliente.
        printf("CPF do cliente %d atualizado com sucesso.\n", index);
    } else {
        printf("Erro! Número de cliente inválido.\n");
    }
}

//Função para excluir um cliente do sistema.
void excluirCliente(Cliente clientes[MAX], int *numClientes) {
    int index;
    printf("Digite o ID do cliente que deseja excluir (1-%d): ", *numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= *numClientes) { //Verifica se o índice é válido.
        for (int i = index - 1; i < *numClientes - 1; i++) {
            clientes[i] = clientes[i + 1]; //Move os clientes para preencher o espaço do cliente excluído.
        }
        (*numClientes)--; //Decrementa o número de clientes.
        printf("Cliente %d excluído com sucesso.\n", index);
    } else {
        printf("Erro! Número de cliente inválido.\n");
    }
}

//Função para autorizar um cliente a realizar operações.
void autorizarCliente(Cliente clientes[MAX], int numClientes) {
    int index;
    printf("Digite o ID do cliente que deseja autorizar (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes) { //Verifica se o índice é válido
        clientes[index - 1].autorizado = 1; //Autoriza o cliente,
        printf("Cliente %d autorizado com sucesso.\n", index);
    } else {
        printf("Erro! Número de cliente inválido.\n");
    }
}

//Função para depositar um valor na conta de um cliente.
void depositar(Cliente clientes[MAX], int numClientes) {
    int index;
    double valor;
    printf("Digite o ID do cliente que deseja realizar o depósito (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes && clientes[index - 1].autorizado) { //Verifica se o cliente está autorizado.
        printf("Digite o valor a ser depositado: ");
        scanf("%lf", &valor);
        getchar();
        clientes[index - 1].saldo += valor; //Atualiza o saldo do cliente.
        printf("Depósito realizado com sucesso! Novo saldo: %.2f\n", clientes[index - 1].saldo);
    } else {
        printf("Erro! Cliente não autorizado ou inválido.\n");
    }
}

//Função para sacar um valor da conta de um cliente.
void sacar(Cliente clientes[MAX], int numClientes) {
    int index;
    double valor;
    printf("Digite o ID do cliente que deseja realizar o saque (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes && clientes[index - 1].autorizado) { //Verifica se o cliente está autorizado.
        printf("Digite quanto deseja sacar: ");
        scanf("%lf", &valor);
        getchar();
        if (clientes[index - 1].saldo >= valor) { //Verifica se o cliente tem saldo suficiente.
            clientes[index - 1].saldo -= valor; //Atualiza o saldo do cliente.
            printf("Saque realizado com sucesso! Novo saldo: %.2f\n", clientes[index - 1].saldo);
        } else {
            printf("Erro! Saldo insuficiente.\n");
        }
    } else {
        printf("Erro! Cliente não autorizado ou inválido.\n");
    }
}

//Função para verificar o saldo de um cliente.
void verificarSaldo(Cliente clientes[MAX], int numClientes) {
    int index;
    printf("Digite o número do cliente para verificar o saldo (1-%d): ", numClientes);
    scanf("%d", &index);
    getchar();

    if (index >= 1 && index <= numClientes && clientes[index - 1].autorizado) { //Verifica se o cliente está autorizado
        printf("Saldo do cliente %d (%s): %.2f\n", index, clientes[index - 1].nome, clientes[index - 1].saldo);
    } else {
        printf("Erro! Cliente não autorizado ou inválido.\n");
    }
}

//Função para transferir saldo entre contas de clientes.
void transferir(Cliente clientes[MAX], int numClientes) {
    int indexOrigem, indexDestino;
    double valor;
    
    printf("Digite o ID do cliente que deseja transferir o saldo (1-%d): ", numClientes);
    scanf("%d", &indexOrigem);
    getchar();

    if (indexOrigem >= 1 && indexOrigem <= numClientes && clientes[indexOrigem - 1].autorizado) {
        printf("Digite o ID do cliente que receberá o saldo (1-%d): ", numClientes);
        scanf("%d", &indexDestino);
        getchar();

        if (indexDestino >= 1 && indexDestino <= numClientes && clientes[indexDestino - 1].autorizado) {
            printf("Digite quanto deseja transferir: ");
            scanf("%lf", &valor);
            getchar();
            if (clientes[indexOrigem - 1].saldo >= valor) {
                clientes[indexOrigem - 1].saldo -= valor;
                clientes[indexDestino - 1].saldo += valor;
                printf("Transferência realizada com sucesso! Novo saldo do cliente %d: %.2f\n", indexOrigem, clientes[indexOrigem - 1].saldo);
            } else {
                printf("Erro! Saldo insuficiente para transferência.\n");
            }
        } else {
            printf("Erro! Cliente de destino não autorizado ou inválido.\n");
        }
    } else {
        printf("Erro! Cliente de origem não autorizado ou inválido.\n");
    }
}

//Função principal.
int main() {
    Cliente clientes[MAX]; //Array de clientes.
    int numClientes = 0;   //Número de clientes cadastrados.
    int opcao;

    do {
        printf("\n=======Menu=======\n");
        printf("1. Inserir cliente\n");
        printf("2. Listar clientes\n");
        printf("3. Atualizar cliente\n");
        printf("4. Excluir cliente\n");
        printf("5. Autorizar cliente\n");
        printf("6. Alterar CPF do Cliente\n");
        printf("7. Transferir valor entre contas\n");
        printf("8. Realizar depósito\n");
        printf("9. Realizar saque\n");
        printf("10. Verificar saldo\n");
        printf("11. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                inserirCliente(clientes, &numClientes);
                break;
            case 2:
                listarClientes(clientes, numClientes);
                break;
            case 3:
                atualizarCliente(clientes, numClientes);
                break;
            case 4:
                excluirCliente(clientes, &numClientes);
                break;
            case 5:
                autorizarCliente(clientes, numClientes);
                break;
            case 6:
                alterarCPF(clientes, numClientes);
                break;
            case 7:
                transferir(clientes, numClientes);
                break;
            case 8:
                depositar(clientes, numClientes);
                break;
            case 9:
                sacar(clientes, numClientes);
                break;
            case 10:
                verificarSaldo(clientes, numClientes);
                break;
            case 11:
                printf("Operações finalizadas!\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 11);

    return 0;
}
