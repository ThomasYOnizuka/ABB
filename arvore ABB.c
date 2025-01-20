#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar os dados de cada registro
typedef struct {
    char nome[100];
    char cargo[100];
    char uorg_lotacao[100];
} Registro;

// Estrutura de um nó da árvore binária de busca
typedef struct Node {
    Registro registro;
    struct Node *esq, *dir;
} Node;

// Função para criar um novo nó
Node* novoNo(Registro registro) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->registro = registro;
    temp->esq = temp->dir = NULL;
    return temp;
}

// Função para inserir um novo registro na ABB
Node* inserir(Node* node, Registro registro) {
    if (node == NULL) return novoNo(registro);

    if (strcmp(registro.nome, node->registro.nome) < 0)
        node->esq = inserir(node->esq, registro);
    else if (strcmp(registro.nome, node->registro.nome) > 0)
        node->dir = inserir(node->dir, registro);

    return node;
}

// Função para buscar um registro pelo nome
Node* buscar(Node* root, char nome[]) {
    if (root == NULL || strcmp(root->registro.nome, nome) == 0)
        return root;

    if (strcmp(nome, root->registro.nome) < 0)
        return buscar(root->esq, nome);

    return buscar(root->dir, nome);
}

int main() {
    Node* root = NULL;
    char nomeBusca[100];

    // Simulação de leitura do CSV e inserção na ABB
    FILE *file = fopen("https://www.bioinfo.unifesp.br/datasets/ed2024/Unifesp-24r.csv", "r");
    if (file == NULL) {
         perror("Erro ao abrir o arquivo");
         return EXIT_FAILURE;
     }
    // Código para ler o arquivo e inserir registros na ABB
     fclose(file);

    // Simulando a inserção de registros
    Registro r1 = {"Alice Silva", "Engenheira", "Departamento A"};
    Registro r2 = {"Carlos Souza", "Analista", "Departamento B"};
    root = inserir(root, r1);
    root = inserir(root, r2);

    // Solicitar nome para busca
    printf("Digite o nome completo para busca: ");
    fgets(nomeBusca, sizeof(nomeBusca), stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';  // Remover newline

    Node* resultado = buscar(root, nomeBusca);
    if (resultado != NULL) {
        printf("Cargo: %s\n", resultado->registro.cargo);
        printf("UORG_LOTACAO: %s\n", resultado->registro.uorg_lotacao);
    } else {
        printf("Registro não encontrado.\n");
    }

    return 0;
}
