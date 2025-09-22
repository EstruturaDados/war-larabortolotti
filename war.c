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

//Bibliotecas usadas
#include <stdio.h>          
#include <string.h>
#include <stdlib.h>
#include <time.h> 

#define MISSOESTOTAIS 5         //definicao do maximo de missoes existente nos jogo

struct territorio                       //Definicao da Struct com os parametros
{
    char nome[30];
    char cor[10];
    int tropas;
};

char* missoes[MISSOESTOTAIS] ={             //Criacao do Vetor de 5 missoes
        "conquistar 3 territorios seguidos",
        "Conquistar todos os exercitos vermelhos", 
        "Possuir 10 tropas",
        "Derrotar 2 openentes seguidos",
        "Ganhar 6 batalhas seguidas"
    };
//Prototipos das funcoes usadas 
void LimparBufferEntrada();
void CadastrarTropas(int *territoriosUsuarios, struct territorio *war);
void Ataque (struct territorio *atacante, struct territorio *defensor, int *VitoriasSeguidas);
void LiberarMemoria(struct territorio *war);
void ExibirMapa(const struct territorio *war, int territoriosUsuarios);
void MenuAcoes();
int VerificarMissao(char *missoes, struct territorio *mapa, int tamanho, int VitoriasSeguidas);
void AtribuirMissoes(char *destino, char* missoes[], int TotalMissoes);

int main () {
     // declaracao das variaveis usadas no jogo
    int territoriosUsuarios;
    int opcao;
    struct territorio *war;
    char *MissaoJogador;
    int VitoriasSeguidas = 0;
    int Venceu = 0;


    srand(time(NULL));                      //garante numero aleatorizados diferentes em casa rodada

    printf("Bem-vindo ao jogo War.\n");                     //Introducao ao jogo
    printf("Para iniciar defina com quantos territorio sera o jogo:  \n\n");
    scanf("%d", &territoriosUsuarios);                      // Definicao de quantos territorios iram ter no jogo
    LimparBufferEntrada();

    war= (struct territorio*)malloc(territoriosUsuarios*sizeof(struct territorio)); //Alocacao dinamica de memoria para os territorios 
    if (war == NULL)
    {
        printf("ERRO DE ALOCAO DE MEMORIA TERRITORIO\n");
        return 1;
    }

    MissaoJogador =(char*)malloc(100 * sizeof(char));       //Alocacao de memoria para as missoes do jogadores
     if (MissaoJogador == NULL)
     {
        printf("ERRO NA LOCACAO DE MEMORIA MISSAO\n");
        return 1;
     }
         
    CadastrarTropas(&territoriosUsuarios, war);         //Chama a funcao de cadastro das tropas

    AtribuirMissoes(MissaoJogador, missoes, MISSOESTOTAIS);     //Chama a funcao de atribuicao das missoes antes do jogo comecar
    printf("Sua missao: %s\n\n", MissaoJogador);

    ExibirMapa(war, territoriosUsuarios);       //Chama a funcao de mostra o mapa do jogo antes de inicar as batalhas

   do{
           if (VerificarMissao(MissaoJogador, war, territoriosUsuarios, VitoriasSeguidas))  //Chama a funcao de verificar a missao antes de comecar a batalha
        {
            printf("\n Parabens, missao cumprida %s \n", MissaoJogador);
            Venceu = 1;
            break;
        }
        

    MenuAcoes();                //Chama a funcao de menu do jogo 
    scanf("%d", &opcao);        //Armazena a opcao do jogador
    LimparBufferEntrada();

    switch (opcao) {

         case 1: {
                int opcaoAtacante;
                printf("\n Escolha um territorio atacante, ou 0 para sair: \n");
                scanf("%d", &opcaoAtacante);
                LimparBufferEntrada();
        
                 if (opcaoAtacante > 0 && opcaoAtacante <= territoriosUsuarios){ //Condicional para ataque valido 
    
                int atacante = opcaoAtacante - 1;       //Variavel de ataque, "opcao - 1" devido aos indices do array
                int defensor;

                printf("\n TERRITORIO ATACANTE: %s\n\n", war[atacante].nome);

                printf("Escolha o territorio defensor: \n");
                scanf("%d", &defensor);
                LimparBufferEntrada();
                defensor--;

                if (defensor >= 0 && defensor < territoriosUsuarios && defensor != atacante) //Condicional de defensor valido
                {            
                printf("\n TERRITORIO DEFENSOR: %s \n", war[defensor].nome);

                Ataque(&war[atacante], &war[defensor], &VitoriasSeguidas); //Chama a funcao ataque

                for (int i = 0; i < territoriosUsuarios; i++)   //Atualizacao de territorio
                {
                printf("\n%d- %s (Exercito: %s, Tropas: %d) \n", i +1, war[i].nome, war[i].cor, war[i].tropas);
                }
                
                } else { 
                printf("Opcao invalida \n");
                }}
                break;
                }

            case 2:     
                if (VerificarMissao(MissaoJogador, war, territoriosUsuarios, VitoriasSeguidas )) {
                    printf("\nPARABENS! Voce cumpriu sua missao: %s\n", MissaoJogador);
                } else{
                
                    printf("Voce ainda nao cumpriu sua missao. \n");
                }
        
                break;
    
            case 0:

                printf("Saindo do jogo\n");

            break;
    
            default:
        
                printf("OPCAO INVALIDA\t");
                printf("PRESSIONE ENTER PARA CONTINUAR \n");
                getchar();      // Le o comando enter

             break;
            }
    } while (opcao !=0);
        LiberarMemoria(war);        //Chama a funcao de liberarr a memoria
        free(MissaoJogador);
return 0; }

void LimparBufferEntrada(){              //Funcao para limbar o Buffer e evitar erros
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
}

void CadastrarTropas(int *territoriosUsuarios, struct territorio *war){ //Funcao de cadastro de tropas com os parametros estabelecidos

    for (int i = 0; i <*territoriosUsuarios; i++)            //Laco for para cadastro dos territorios
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
    LimparBufferEntrada();   

} }

void ExibirMapa(const struct territorio *war, int territoriosUsuarios){ //funcao de exibicao de mapa

    printf("===================================\n\n");
    printf("MAPA DOS TERRITORIOS: \n \n");
    
for (int i = 0; i < territoriosUsuarios; i++)                //Laco for para impressao dos territorios cadastrados
{
    printf("%d- %s (Exercito: %s, Tropas: %d) \n", i +1, war[i].nome, war[i].cor, war[i].tropas);
}
  printf("PRESSIONE ENTRER PARA CONTINUAR \n");
        getchar();
    
}
void Ataque(struct territorio *atacante, struct territorio *defensor,  int *VitoriasSeguidas ){     //Funcao ataque

    int TropasAtaque = (rand() % 6) + 1;    //Aleatorizacao dos dados de ataque
    int TropasDefesa = (rand() % 6) + 1;    //Aleatorizacao dos dados de defesa

    printf("\n %s ataca com %d tropas \n", atacante->nome, TropasAtaque);
    printf("\n %s defende com %d tropas \n", defensor->nome, TropasDefesa);
    printf("\n-----RESULTADO DA BATALHA-----\n\n");

    if (TropasAtaque > TropasDefesa)    // Logica para ataque e resultado da batalha
    {
        defensor->tropas -= 1;
        printf("%s Ganhou a rodada, %s perdeu 1 tropa.\n", atacante->nome, defensor->nome);
        (*VitoriasSeguidas)++;

        if (defensor->tropas <= 0) {     //Logica para conquista de territorio
        {
            printf("%s CONQUISTOU O TERRITORIO DE %s\n", atacante->nome, defensor->nome);

            strcpy(defensor->cor, atacante->cor);   //Tranferencia de cor do territorio conquistado para o atacante
            int TropasTransferidas = atacante->tropas /2;   //Tranferencia das tropas.
                defensor->tropas = TropasTransferidas;
                atacante->tropas -= TropasTransferidas;
        }
        } else if (TropasAtaque < TropasDefesa){
        atacante->tropas -= 1;
        printf("%s Ganhou a rodada, %s perdeu uma tropa\n", defensor->nome, atacante->nome);
        *VitoriasSeguidas = 0;
    } else{
        printf("Rodada empatada\n");
        *VitoriasSeguidas = 0;
    }
}}

void LiberarMemoria(struct territorio *war){        //Liberando memoria 
    free(war);
    printf("MEMORIA LIVRE\n");
}

void MenuAcoes(){       //Menu de acoes do jogo

    printf("Menu de acoes \n\n");
    printf("1-Atacar \n");
    printf("2-Ver missao \n");
    printf("0-Sair\n");
}

void AtribuirMissoes(char *destino, char* missoes[], int TotalMissoes){ //Funcao de atribuicao aleatoria de missoes.
    int sorteio = rand() % TotalMissoes;
    strcpy(destino, missoes[sorteio]);
}

int VerificarMissao(char *missoes, struct territorio *mapa, int tamanho, int VitoriasSeguidas){     //Funcao para verificar o cumprimento das missoes.

    if (strstr(missoes, "Conquistar 3 territorios seguidos")) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas > 0) count++;
            else count = 0;
            if (count >= 3) return 1; // missão cumprida
        }

    } else if (strstr(missoes, "Possuir 10 tropas")){
    int total = 0;
        for (int i = 0; i < tamanho; i++)
        {
            total += mapa[i].tropas;
        } if (total >= 10)
            return 1;
    } else if (strstr(missoes, "Dettorar 2 oponentes seguidos"))
    {
        if (VitoriasSeguidas >=2) return 1;
        
    } else if (strstr(missoes, "Ganhar 6 batalhas seguidas"))
    {
        if (VitoriasSeguidas >=6) return 1;
        
    }

    return 0; // missão não cumprida
}

