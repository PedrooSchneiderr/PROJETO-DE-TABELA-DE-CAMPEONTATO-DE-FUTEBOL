#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

int main()
{
    // Carrega os times do arquivo CSV ao iniciar o programa.
    // A alocação de memória para os times é realizada dentro de `carregar_times`.
    carregar_times("dados.csv");
    int opcao;

    do
    {
        // Exibe o menu de opções ao usuário.
        printf("\nMenu:\n");
        printf("1. Listar times\n");
        printf("2. Inserir time\n");
        printf("3. Remover time\n");
        printf("4. Editar time\n");
        printf("5. Buscar time\n");
        printf("6. Salvar e sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        // Processa a opcao escolhida pelo usuario.
        if (opcao == 1)
        {
            // Chama a função para listar todos os times carregados na memoria
            // Esta função apenas acessa e exibe os dados
            listar_times();
        }
        else if (opcao == 2)
        {
            Time novo; // Declara uma estrutura time para armazenar os dados do novo time
            printf("ID: ");
            scanf("%d", &novo.id);
            // Consumir o caractere de nova linha pendente depois do scanf anterior
            // Serve para 'fgets' leia corretamente a proxima string
            while (getchar() != '\n')
                ;
            printf("Nome: ");
            // Usa fgets para ler o nome, que pode conter espaços.
            // MAX_NOME é o tamanho máximo do que o nome pode ter, def na biblioteca
            fgets(novo.nome, MAX_NOME, stdin);
            // Remove o caractere de nova linha que fgets adiciona ao final da string lida.
            novo.nome[strcspn(novo.nome, "\n")] = 0;
            printf("Titulos: ");
            scanf("%d", &novo.titulos);
            printf("Media de gols: ");
            scanf("%f", &novo.media_gols);
            // Chama a função para inserir o novo time na estrutura de dados .csv
            // A alocacao de memória para o novo time eh gerenciada dentro de 'inserir_time'
            inserir_time(novo);
        }
        else if (opcao == 3)
        {
            int id;
            printf("ID do time a remover: ");
            scanf("%d", &id);
            // Chama a função para remover um time pelo ID.
            // A realocação de memória para ajustar o tamanho do vet é gerenciada dentro de da func 'remover_time'
            remover_time(id);
        }
        else if (opcao == 4)
        {
            int id;
            Time novo; // Declara uma estrutura Time para os novos dados do time.
            printf("ID do time a editar: ");
            scanf("%d", &id);
            while (getchar() != '\n')
                ;
            printf("Novo nome: ");
            fgets(novo.nome, MAX_NOME, stdin);
            novo.nome[strcspn(novo.nome, "\n")] = 0;
            printf("Novo numero de titulos: ");
            scanf("%d", &novo.titulos);
            printf("Nova media de gols: ");
            scanf("%f", &novo.media_gols);
            novo.id = id; // Atribui o ID para a estrutura a ser editada.
            // Chama a função para editar um time existente.
            // Esta func apenas modifica os dados de um time existente, sem malloc ou realloc
            editar_time(id, novo);
        }
        else if (opcao == 5)
        {
            int id;
            printf("ID: ");
            scanf("%d", &id);
            // Chama a func para buscar um time pelo ID.
            // Retorna um ponteiro para o time encontrado (se existir), sem alocação/desalocação.
            Time *t = buscar_time(id);
            if (t)
            {
                printf("Nome: %s | Titulos: %d | Media de Gols: %.2f\n", t->nome, t->titulos, t->media_gols);
            }
            else
            {
                printf("Time nao encontrado.\n");
            }
        }
    } while (opcao != 6); // O loop continua até que o usuário escolha a opção '6. Salvar e sair'.
    // Salva os times de volta no arquivo CSV antes de sair do programa.
    // Não há alocação/desalocação de memória nesta função.
    salvar_times("dados.csv");
    // Libera toda a memória alocada dinamicamente para os times.
    liberar_memoria();
    return 0;
}