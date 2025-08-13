#ifndef CAMPEONATO_H
#define CAMPEONATO_H

#define MAX_NOME 100

typedef struct
{
    int id;
    char nome[MAX_NOME];
    int titulos;
    float media_gols;
} Time;

void carregar_times(const char *arquivo_csv);
void salvar_times(const char *arquivo_csv);

void inserir_time(Time novo_time);
int remover_time(int id);
int editar_time(int id, Time novo_time);
void listar_times();
Time *buscar_time(int id);
void liberar_memoria();

#endif
