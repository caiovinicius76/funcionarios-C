#include <stdio.h>
#include <string.h>
#include <stdlib.h>


typedef struct {
    int id;
    char nome[50];
} Funcionario;

/
void imprimir_funcionario(Funcionario func);
void adicionar_funcionario(Funcionario **funcionarios, int *tamanho);
void listar_funcionarios(Funcionario *funcionarios, int tamanho);
void buscar_funcionario(Funcionario *funcionarios, int tamanho);
void editar_funcionario(Funcionario *funcionarios, int tamanho);
void excluir_funcionario(Funcionario **funcionarios, int *tamanho);

int main() {
    Funcionario *funcionarios = NULL;
    int tamanho = 0;

    int escolha;
    do {
        printf("\n\nMenu: \n");
        printf("1. Listar Funcionarios \n");
        printf("2. Adicionar Funcionario \n");
        printf("3. Buscar Funcionario \n");
        printf("4. Editar Funcionario \n");
        printf("5. Excluir Funcionario \n");
        printf("6. Sair \n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                listar_funcionarios(funcionarios, tamanho);
                break;
            case 2:
                adicionar_funcionario(&funcionarios, &tamanho);
                break;
            case 3:
                buscar_funcionario(funcionarios, tamanho);
                break;
            case 4:
                editar_funcionario(funcionarios, tamanho);
                break;
            case 5:
                excluir_funcionario(&funcionarios, &tamanho);
                break;
            case 6:
                printf("Saindo... \n");
                break;
            default:
                printf("Escolha invalida. Tente novamente. \n");
        }
    } while (escolha != 6);

    free(funcionarios);
    return 0;
}

void imprimir_funcionario(Funcionario func) {
    printf("ID: %d \n", func.id);
    printf("Nome: %s \n", func.nome);
}

void adicionar_funcionario(Funcionario **funcionarios, int *tamanho) {
    int id;
    char nome[50];
    printf("Digite o ID do funcionario: ");
    scanf("%d", &id);
    printf("Digite o nome do funcionario: ");
    scanf("%s", nome);

    Funcionario novoFuncionario;
    novoFuncionario.id = id;
    strcpy(novoFuncionario.nome, nome);

    (*tamanho)++;
    *funcionarios = (Funcionario *)realloc(*funcionarios, (*tamanho) * sizeof(Funcionario));
    (*funcionarios)[(*tamanho) - 1] = novoFuncionario;

    printf("Funcionario adicionado com sucesso. \n");
}

void listar_funcionarios(Funcionario *funcionarios, int tamanho) {
    if (tamanho == 0) {
        printf("Nenhum funcionario registrado. \n");
    } else {
        for (int i = 0; i < tamanho; i++) {
            printf("\nFuncionario %d:\n", i + 1);
            imprimir_funcionario(funcionarios[i]);
        }
    }
}

void buscar_funcionario(Funcionario *funcionarios, int tamanho) {
    int id;
    printf("Digite o ID do funcionario a ser buscado: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id == id) {
            printf("Funcionario encontrado:\n");
            imprimir_funcionario(funcionarios[i]);
            return;
        }
    }
    printf("Funcionario nao encontrado. \n");
}

void editar_funcionario(Funcionario *funcionarios, int tamanho) {
    int id;
    char nome[50];
    printf("Digite o ID do funcionario a ser editado: ");
    scanf("%d", &id);

    for (int i = 0; i < tamanho; i++) {
        if (funcionarios[i].id == id) {
            printf("Digite o novo nome do funcionario: ");
            scanf("%s", nome);
            strcpy(funcionarios[i].nome, nome);
            printf("Funcionario atualizado com sucesso. \n");
            return;
        }
    }
    printf("Funcionario nao encontrado. \n");
}

void excluir_funcionario(Funcionario **funcionarios, int *tamanho) {
    int id;
    printf("Digite o ID do funcionario a ser excluido: ");
    scanf("%d", &id);

    for (int i = 0; i < *tamanho; i++) {
        if ((*funcionarios)[i].id == id) {
            for (int j = i; j < (*tamanho - 1); j++) {
                (*funcionarios)[j] = (*funcionarios)[j + 1];
            }
            (*tamanho)--;
            *funcionarios = (Funcionario *)realloc(*funcionarios, (*tamanho) * sizeof(Funcionario));

            if (*tamanho == 0) {
                free(*funcionarios);
                *funcionarios = NULL;
            }

            printf("Funcionario excluido com sucesso. \n");
            return;
        }
    }
    printf("Funcionario nao encontrado. \n");
}
