#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>

struct reg_cliente {
    char nome[50];
    char tipo_carro[20];
    char marca_carro[20];
    int quantidade;
    int tipo_cliente;
    float desconto;
};

// Estrutura para representar a interface gráfica (GUI)
typedef struct {
    GtkWidget *window;
    GtkWidget *button_cadastro;
    GtkWidget *button_ver_alugueis;
    GtkWidget *button_apagar_alugueis;
    GtkWidget *button_atualizar_alugueis;
    GtkWidget *button_encerrar;
    struct reg_cliente aluguel;
} GUI;


GUI initialize_gui();

// Protótipos das funções do CRUD
void cadastroAluguel(void);
void localizarAlugueis(void);
void apagarAlugueis(void);
void updateAlugueis(void);

// Callbacks para os botões
void cadastro_button_clicked(GtkWidget *widget);
void ver_alugueis_button_clicked(GtkWidget *widget);
void apagar_alugueis_button_clicked(GtkWidget *widget);
void atualizar_alugueis_button_clicked(GtkWidget *widget);
void encerrar_button_clicked(GtkWidget *widget);

int main(void) {
    // Inicializar a interface gráfica
    initialize_gui();

    // Rodar o loop principal do GTK
    gtk_main();

    return 0;
}

GUI initialize_gui() {
    GUI gui;

    // Inicialização do GTK
    gtk_init(NULL, NULL);

    // Criação da janela principal
    gui.window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(gui.window), "Locadora de Carros");
    gtk_container_set_border_width(GTK_CONTAINER(gui.window), 10);
    gtk_widget_set_size_request(gui.window, 300, 200);
    g_signal_connect(gui.window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Criação dos botões
    gui.button_cadastro = gtk_button_new_with_label("CADASTRAR CLIENTE");
    gui.button_ver_alugueis = gtk_button_new_with_label("VER ALUGUEIS");
    gui.button_apagar_alugueis = gtk_button_new_with_label("APAGAR ALUGUEIS");
    gui.button_atualizar_alugueis = gtk_button_new_with_label("ATUALIZAR ALUGUEIS");
    gui.button_encerrar = gtk_button_new_with_label("ENCERRAR");

    // Adição dos botões à janela
    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(box), gui.button_cadastro, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), gui.button_ver_alugueis, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), gui.button_apagar_alugueis, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), gui.button_atualizar_alugueis, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(box), gui.button_encerrar, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(gui.window), box);

    // Conectar os callbacks aos botões
    g_signal_connect(gui.button_cadastro, "clicked", G_CALLBACK(cadastro_button_clicked), &gui);
    g_signal_connect(gui.button_ver_alugueis, "clicked", G_CALLBACK(ver_alugueis_button_clicked), &gui);
    g_signal_connect(gui.button_apagar_alugueis, "clicked", G_CALLBACK(apagar_alugueis_button_clicked), &gui);
    g_signal_connect(gui.button_atualizar_alugueis, "clicked", G_CALLBACK(atualizar_alugueis_button_clicked), &gui);
    g_signal_connect(gui.button_encerrar, "clicked", G_CALLBACK(encerrar_button_clicked), &gui);

    // Exibição da janela
    gtk_widget_show_all(gui.window);

    return gui;
}

// Implementação das funções do CRUD


void cadastroAluguel() {
  struct reg_cliente clientes;
      FILE *arquivo = fopen("alugueis.txt", "a");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para escrita.\n");
  } else {
    printf("\nCadastro de Cliente");
    printf("\nDigite o seu nome completo:  ");
      scanf("%s", clientes.nome);
    printf("\nQual o tipo de carro que deseja alugar ?: ");
      scanf("%s", clientes.tipo_carro);
    printf("\nQual a marca de carro que deseja alugar ?: ");
      scanf("%s", clientes.marca_carro);
    printf("\nDigite a quantidade de carro que deseja alugar: ");
      scanf("%d", &clientes.quantidade);
    printf("\nDigite o seu tipo de cliente:\n\n1 - Cliente comum | 2 - Cliente "
           "Prata | 3 - Cliente Ouro\n\nClientes Prata tem 10%% de desconto e "
           "Clientes Ouro tem 20%% de desconto: ");
      scanf("%d", &clientes.tipo_cliente);
    fprintf(arquivo, "%s %s %s %d %d\n", clientes.nome, clientes.tipo_carro, clientes.marca_carro, clientes.quantidade, clientes.tipo_cliente);
    printf("\nArquivo gravado com sucesso!\n");
  }
    fclose(arquivo);
}

void detalhesAlugueis(struct reg_cliente *aluguel) {
    printf("Nome: %s\t", aluguel->nome);
    printf("Tipo de carro: %s\t", aluguel->tipo_carro);
    printf("Marca: %s\t", aluguel->marca_carro);
    printf("Quantidade: %d\t", aluguel->quantidade);
    printf("Tipo do cliente: %d\n", aluguel->tipo_cliente);
}

void atualizaAlugueis(struct reg_cliente *aluguel) {
  FILE *transferencia = fopen("transferencia.txt", "a");
  fprintf(transferencia, "%s %s %s %d %d\n", aluguel->nome, aluguel -> tipo_carro, aluguel -> marca_carro, aluguel -> quantidade, aluguel -> tipo_cliente);
  fclose(transferencia);
}

void localizarAlugueis(void) {
    struct reg_cliente clientes;
    FILE *arquivo = fopen("alugueis.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para leitura.\n");
    } else {
        int opcao = 0;
        char nomeCliente[50];
        printf("Escolha o modo de leitura:\n1 - Toda a lista\n2 - Por nome\n");

        // Limpar o buffer antes de ler a opção
        while ((getchar()) != '\n');

        scanf("%d", &opcao);

        if (opcao == 1) {
            while (fscanf(arquivo, "%s %s %s %d %d", clientes.nome, clientes.tipo_carro,
                          clientes.marca_carro, &clientes.quantidade, &clientes.tipo_cliente) != EOF) {
                detalhesAlugueis(&clientes);
            }
        } else if (opcao == 2) {
            printf("\nDigite o nome do cliente: ");
              scanf("%49s", nomeCliente);

            while (fscanf(arquivo, "%s %s %s %d %d", clientes.nome, clientes.tipo_carro,
                          clientes.marca_carro, &clientes.quantidade, &clientes.tipo_cliente) != EOF) {
                if (strcmp(clientes.nome, nomeCliente) == 0) {
                    detalhesAlugueis(&clientes);
                }
            }
        } else {
            printf("Opção inválida.\n");
        }
        fclose(arquivo);
    }
}


void apagarAlugueis(void) {
    struct reg_cliente clientes;
  FILE *transferencia = fopen("transferencia.txt", "w");
  FILE *arquivo = fopen("alugueis.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para leitura.\n");
  } else {
    int opcao = 0;
    char nomeCliente[50];
    printf("Escolha o modo de exclusão:\n1 - Toda a lista\n2 - Por nome\n");
      scanf("%d", &opcao);
    if (opcao == 1) {
      printf("\nTodo o registro sendo apagado...\n");
    }else if (opcao == 2) {
            printf("\nDigite o nome do cliente: ");
            scanf("%s", nomeCliente);
            while (fscanf(arquivo, "%s %s %s %d %d", clientes. nome, clientes.tipo_carro, clientes.marca_carro, &clientes.quantidade, &clientes.tipo_cliente) != EOF) {
              if(strcmp(clientes.nome, nomeCliente) != 0) {
                 atualizaAlugueis(&clientes);
              }
            }
          } else {
            printf("\nOpção inválida.\n");
          }
        fclose(arquivo);
        fclose(transferencia);
        remove("alugueis.txt");
        rename("transferencia.txt", "alugueis.txt");
        printf("\nOperação realizada com sucesso");
    }
}

void updateAlugueis(void) {
    struct reg_cliente clientes;
  FILE *transferencia = fopen("transferencia.txt", "w");
  FILE *arquivo = fopen("alugueis.txt", "r");
  if (arquivo == NULL) {
    printf("Erro ao abrir o arquivo para leitura.\n");
  } else {
    int opcao = 0;
    char nomeCliente[50];
    char mudancaString[50];
    int mudancaInt = 0;

    printf("\nDigite o nome do cliente a ser atualizado: ");
      scanf("%s", nomeCliente);
    printf("\nInforme a informação a ser atualizada:\n1 - NOME\n2 - TIPO DE CARRO\n3 - MARCA DO CARRO\n4 - QUANTIDADE DE CARROS\n5 - TIPO DE CLIENTE\n");
    scanf("%d", &opcao);
    printf("\n\nInforme para qual valor deseja atualizar:\n");


      while (fscanf(arquivo, "%s %s %s %d %d", clientes.nome, clientes.tipo_carro, clientes.marca_carro, &clientes.quantidade, &clientes.tipo_cliente) != EOF) {
        if(strcmp(clientes.nome, nomeCliente) != 0) {
           atualizaAlugueis(&clientes);
        }else if(opcao == 1){
          scanf("%s", mudancaString);
          strcpy(clientes.nome, mudancaString);
          atualizaAlugueis(&clientes);
        }else if(opcao == 2){
          scanf("%s", mudancaString);
          strcpy(clientes.tipo_carro, mudancaString);
          atualizaAlugueis(&clientes);
        }else if(opcao == 3){
          scanf("%s", mudancaString);
          strcpy(clientes.marca_carro, mudancaString);
          atualizaAlugueis(&clientes);
        }else if(opcao == 4){
          scanf("%d", &mudancaInt);
          clientes.quantidade = mudancaInt;
          atualizaAlugueis(&clientes);
        }else if(opcao == 5){
          scanf("%d", &mudancaInt);
          clientes.tipo_cliente = mudancaInt;
          atualizaAlugueis(&clientes);
        }
      }
      fclose(arquivo);
      fclose(transferencia);
      remove("alugueis.txt");
      rename("transferencia.txt", "alugueis.txt");
      printf("\n\nOperação realizada com sucesso\n\n");
    }
}

// Implementação dos callbacks

void cadastro_button_clicked(GtkWidget *widget) {
    system("cls");
    cadastroAluguel();
    // remove a referência não utilizada para evitar o aviso de variável não utilizada
    (void)widget;
}

void ver_alugueis_button_clicked(GtkWidget *widget) {
    system("cls");
    localizarAlugueis();
    // remove a referência não utilizada para evitar o aviso de variável não utilizada
    (void)widget;
}

void apagar_alugueis_button_clicked(GtkWidget *widget) {
    system("cls");
    apagarAlugueis();
    (void)widget;
}

void atualizar_alugueis_button_clicked(GtkWidget *widget) {
    system("cls");
    updateAlugueis();
    (void)widget;
}

// Encerrar a aplicação
void encerrar_button_clicked(GtkWidget *widget) {
    gtk_main_quit();
    (void)widget;
}