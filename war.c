// ============================================================================
//         PROJETO WAR ESTRUTURADO - DESAFIO DE CÓDIGO
// ============================================================================
//        
// ============================================================================
//
// OBJETIVOS:
// - Modularizar completamente o código em funções especializadas.
// - Implementar um sistema de missões para um jogador.
// - Criar uma função para verificar se a missão foi cumprida.
// - Utilizar passagem por referência (ponteiros) para modificar dados e
//   passagem por valor/referência constante (const) para apenas ler.
// - Foco em: Design de software, modularização, const correctness, lógica de jogo.
//
// ============================================================================

// Inclusão das bibliotecas padrão necessárias para entrada/saída, alocação de memória, manipulação de strings e tempo.

// --- Constantes Globais ---
// Definem valores fixos para o número de territórios, missões e tamanho máximo de strings, facilitando a manutenção.

// --- Estrutura de Dados ---
// Define a estrutura para um território, contendo seu nome, a cor do exército que o domina e o número de tropas.

// --- Protótipos das Funções ---
// Declarações antecipadas de todas as funções que serão usadas no programa, organizadas por categoria.
// Funções de setup e gerenciamento de memória:
// Funções de interface com o usuário:
// Funções de lógica principal do jogo:
// Função utilitária:

// --- Função Principal (main) ---
// Função principal que orquestra o fluxo do jogo, chamando as outras funções em ordem.
//int main() {
    // 1. Configuração Inicial (Setup):
    // - Define o locale para português.
    // - Inicializa a semente para geração de números aleatórios com base no tempo atual.
    // - Aloca a memória para o mapa do mundo e verifica se a alocação foi bem-sucedida.
    // - Preenche os territórios com seus dados iniciais (tropas, donos, etc.).
    // - Define a cor do jogador e sorteia sua missão secreta.

    // 2. Laço Principal do Jogo (Game Loop):
    // - Roda em um loop 'do-while' que continua até o jogador sair (opção 0) ou vencer.
    // - A cada iteração, exibe o mapa, a missão e o menu de ações.
    // - Lê a escolha do jogador e usa um 'switch' para chamar a função apropriada:
    //   - Opção 1: Inicia a fase de ataque.
    //   - Opção 2: Verifica se a condição de vitória foi alcançada e informa o jogador.
    //   - Opção 0: Encerra o jogo.
    // - Pausa a execução para que o jogador possa ler os resultados antes da próxima rodada.

    // 3. Limpeza:
    // - Ao final do jogo, libera a memória alocada para o mapa para evitar vazamentos de memória.

    //return 0;
//}

// --- Implementação das Funções ---

// alocarMapa():
// Aloca dinamicamente a memória para o vetor de territórios usando calloc.
// Retorna um ponteiro para a memória alocada ou NULL em caso de falha.

// inicializarTerritorios():
// Preenche os dados iniciais de cada território no mapa (nome, cor do exército, número de tropas).
// Esta função modifica o mapa passado por referência (ponteiro).

// liberarMemoria():
// Libera a memória previamente alocada para o mapa usando free.

// exibirMenuPrincipal():
// Imprime na tela o menu de ações disponíveis para o jogador.

// exibirMapa():
// Mostra o estado atual de todos os territórios no mapa, formatado como uma tabela.
// Usa 'const' para garantir que a função apenas leia os dados do mapa, sem modificá-los.

// exibirMissao():
// Exibe a descrição da missão atual do jogador com base no ID da missão sorteada.

// faseDeAtaque():
// Gerencia a interface para a ação de ataque, solicitando ao jogador os territórios de origem e destino.
// Chama a função simularAtaque() para executar a lógica da batalha.

// simularAtaque():
// Executa a lógica de uma batalha entre dois territórios.
// Realiza validações, rola os dados, compara os resultados e atualiza o número de tropas.
// Se um território for conquistado, atualiza seu dono e move uma tropa.

// sortearMissao():
// Sorteia e retorna um ID de missão aleatório para o jogador.

// verificarVitoria():
// Verifica se o jogador cumpriu os requisitos de sua missão atual.
// Implementa a lógica para cada tipo de missão (destruir um exército ou conquistar um número de territórios).
// Retorna 1 (verdadeiro) se a missão foi cumprida, e 0 (falso) caso contrário.

// limparBufferEntrada():
// Função utilitária para limpar o buffer de entrada do teclado (stdin), evitando problemas com leituras consecutivas de scanf e getchar.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h> 

struct territorio                       //Definicao da Struct com os parametros
{
    char nome[30];
    char cor[10];
    int tropas;
};

void LimparBufferdeEntrada (){              //funcao para limbar o Buffer e evitar erros
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

void ataque (struct territorio *atacante, struct territorio *defensor){     //funcao ataque

    int TropasAtaque = (rand() % 6) + 1;    //aleatorizacao dos dados de ataque
    int TropasDefesa = (rand() % 6) + 1;    //aleatorizacao dos dados de defesa

    printf("\n %s ataca com %d tropas \n", atacante->nome, TropasAtaque);
    printf("\n %s defende com %d tropas \n", defensor->nome, TropasDefesa);
    printf("\n-----RESULTADO DA BATALHA-----\n\n");

    if (TropasAtaque > TropasDefesa)    //logica para ataque
    {
        defensor->tropas -= 1;
        printf("%s Ganhou a rodada, %s perdeu 1 tropa.\n", atacante->nome, defensor->nome);

        if (defensor->tropas <= 0)       //logica para conquista de territorio
        {
            printf("%s CONQUISTOU O TERRITORIO DE %s\n", atacante->nome, defensor->nome);

            strcpy(defensor->cor, atacante->cor);   //tranferencia de cor do territorio conquistado para o atacante
            int TropasTransferidas = atacante->tropas /2;   //tranferencia das tropas.
                defensor->tropas = TropasTransferidas;
                atacante->tropas -= TropasTransferidas;
        
        }
    } else
    {
        atacante->tropas -= 1;
        printf("%s Ganhou a rodada, %s perdeu uma tropa\n", defensor->nome, atacante->nome);
    }
}
void LiberarMemoria(struct territorio* mapa){
    free(mapa);
}

int main () {
     
    int territoriosUsuarios;
    int opcao;
    srand(time(NULL));                      //garante numero aleatorizados diferentes em casa rodada

    printf("Bem-vindo ao jogo War.\n");                     //introducao ao jogo
    printf("Para iniciar defina com quantos territorio sera o jogo:  \n\n");
    scanf("%d", &territoriosUsuarios);
    LimparBufferdeEntrada();
    printf("Cadastre as tropas: \n");

    struct territorio*war= (struct territorio*)malloc(territoriosUsuarios*sizeof(struct territorio)); //alocacao dinamica de memoria 
    if (war == NULL)
    {
        printf("ERRO DE ALOCAO DE MEMORIA \n");
        return 1;
    }
    
for (int i = 0; i < territoriosUsuarios; i++)            //laco for para cadastro dos territorios
{
    printf("===================================\n");
    printf("-----CADASTRO DO TERRITORIO %d----- \n \n", i + 1); 
    
    printf("Nome do Territorio: \n");
    fgets(war[i].nome, 30, stdin);

    printf("Cor do Exercíto: \n");
    fgets(war[i].cor, 10, stdin);

    war[i].nome[strcspn(war[i].nome, "\n")] = '\0';
    war[i].cor[strcspn(war[i].cor, "\n")] = '\0';

    printf("Quantidade de Tropas: \n");
    scanf("%d",&war[i].tropas);
    LimparBufferdeEntrada();   

};
    printf("===================================\n\n");
    printf("MAPA DOS TERRITORIOS: \n \n");
    
    
for (int i = 0; i < territoriosUsuarios; i++)                //laco for para impressao dos territorios cadastrados
{
    printf("%d- %s (Exercito: %s, Tropas: %d) \n", i +1, war[i].nome, war[i].cor, war[i].tropas);
}

printf("\n------FASE DE ATAQUE------\n\n");

do {
    printf("\nEscolha um territorio atacante, ou 0 para sair: \n");
    scanf("%d", &opcao);
    LimparBufferdeEntrada();

    if (opcao == 0 )
    { 
        printf("Saindo do jogo \n");
        break;
    } else if (opcao > 0 && opcao <= territoriosUsuarios) //condicional para ataque valido 
    {
        int atacante = opcao - 1;       //variavel de ataque, "opcao - 1 devido ao array"
        int defensor;

        printf("\nTERRITORIO ATACANTE: %s\n\n", war[atacante].nome);

        printf("Escolha o territorio defensor: \n");
        scanf("%d", &defensor);
        LimparBufferdeEntrada();
        defensor--;

        if (defensor >= 0 && defensor < territoriosUsuarios && defensor != atacante) //condicional de defensor valido
        {            
            printf("\n TERRITORIO DEFENSOR: %s \n", war[defensor].nome);

            ataque(&war[atacante], &war[defensor]); //chama a funcao ataque

        for (int i = 0; i < territoriosUsuarios; i++)   //atualizacao de territorio
        {
            printf("\n%d- %s (Exercito: %s, Tropas: %d) \n", i +1, war[i].nome, war[i].cor, war[i].tropas);
        }
                
        } else { 
            printf("Opcao invalida \n");
        }
    } else
    {
        printf("Opcao invalida \n");
    }

} while (1);
LiberarMemoria(war);        //chama a funcao de liberarr a memoria
return 0;
}