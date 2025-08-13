#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "campeonato.h"

// 'times' é um ponteiro para um array de estruturas Time.
// 'total_times' mantém o número atual de times no array.
static Time *times = NULL;
static int total_times = 0;

void carregar_times(const char *arquivo_csv)
{
    FILE *arquivo = fopen(arquivo_csv, "r");
    if (!arquivo)
        return;
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo))
    {
        // Remove o caractere de nova linha lido por fgets.
        linha[strcspn(linha, "\n")] = 0; // é usada para determinar a posição da primeira ocorrência de um caractere específico dentro de uma string
        // Ignora linhas vazias.
        if (strlen(linha) == 0) // conta o número de caracteres em uma string até encontrar o caractere nulo
            continue;
        Time temp;
        // Analisa a string lida do CSV, extraindo os dados do time.
        // O formato "%d-%[^-]-%d-%f" usa ifens para separar os campos:
        if (sscanf(linha, "%d-%[^-]-%d-%f", &temp.id, temp.nome, &temp.titulos, &temp.media_gols) == 4)
        {
            // sscanf le os dados de uma string e convertê-los para diferentes tipos de variáveis
            // Realoca a memória para o array 'times' para acomodar um novo time.
            // O novo endereço é atribuído a 'temp_times' primeiro para segurança.
            Time *temp_times = realloc(times, (total_times + 1) * sizeof(Time));
            times = temp_times;
            // Adiciona o novo time ao final do array e incrementa.
            times[total_times++] = temp;
        }
    }
    fclose(arquivo);
}
void salvar_times(const char *arquivo_csv)
{
    FILE *arquivo = fopen(arquivo_csv, "w"); // Abre o arquivo em modo de escrita (sobrescreve se existir)
    if (!arquivo)
        return; // Retorna se o arquivo não puder ser aberto
    for (int i = 0; i < total_times; i++)
    {
        fprintf(arquivo, "%d-%s-%d-%.2f\n", times[i].id, times[i].nome, times[i].titulos, times[i].media_gols);
        // fprint é usado para escrever dados formatados em um arquivo.
    }
    fclose(arquivo);
}
void inserir_time(Time novo_time)
{
    // Realoca a memória para o array 'times' para acomodar o novo time.
    Time *temp_times = realloc(times, (total_times + 1) * sizeof(Time));
    // Se funcionar, atualiza o ponteiro 'times'.
    times = temp_times;
    // Adiciona o novo time e incrementa a contagem.
    times[total_times++] = novo_time;
}
int remover_time(int id)
{
    for (int i = 0; i < total_times; i++)
    {
        if (times[i].id == id)
        {
            // Desloca os outros times para preencher o espaço do removido.
            for (int j = i; j < total_times - 1; j++)
            {
                times[j] = times[j + 1];
            }
            total_times--; // Decrementa a contagem total de times
            // Realoca a memoria para o vet 'times' para o novo tamanho.
            if (total_times > 0)
            {
                Time *temp_times = realloc(times, total_times * sizeof(Time));
                times = temp_times;
            }
            else
            {
                // libera toda a memória e define 'times' como NULL se não tiver mais times.
                free(times);
                times = NULL;
            }
            return 1;
        }
    }
    return 0; // Time não encontrado
}
int editar_time(int id, Time novo_time)
{
    for (int i = 0; i < total_times; i++)
    {
        if (times[i].id == id)
        {
            times[i] = novo_time; // Atualiza os dados do time
            return 1;             // Time editado com sucesso
        }
    }
    return 0; // Time não encontrado
}
void listar_times()
{
    for (int i = 0; i < total_times; i++)
    {
        printf("ID: %d | Nome: %s | Títulos: %d | Média de Gols: %.2f\n", times[i].id, times[i].nome, times[i].titulos, times[i].media_gols);
    }
}
Time *buscar_time(int id)
{
    for (int i = 0; i < total_times; i++)
    {
        if (times[i].id == id)
        {
            return &times[i]; // Retorna o endereço do time encontrado
        }
    }
    return NULL; // Time nao encontrado
}
void liberar_memoria()
{
    free(times);  // Libera a memoria apontada por 'times'
    times = NULL; // Define o ponteiro como NULL
}
