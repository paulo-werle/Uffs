// Biblitecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Arquivos
#include "dataStructs.c"
#include "binarySearchTree.c"

#define EXIT 10  // valor fixo para a opção que finaliza a aplicação

// Apresenta o menu da aplicação e retorna a opção selecionada
int menu(int op)
{
  // Imprime opções
  printf("Digite a opção desejada \n\n");

  printf("1 Inserir contato \n");
  printf("2 Apagar contato \n");
  printf("3 Pesquisar contato \n");
  printf("4 Listar contatos \n");
  printf("%d Finalizar\n: ", EXIT);

  // Lê opção desejada
  scanf("%d%*c",&op);
  printf("\n\n");
  return op;
}

// Permite o cadastro de um contato
Tree insContact(Tree tree)
{
  // Cria variaveis necessarias
  Contact newContact;

  printf("---------- INSERIR CONTATO ----------\n");
  printf("Informe o nome do contato: ");
  fgets(newContact.name, sizeof(newContact.name), stdin);
  
  // Capitaliza string
  capitalize_str(newContact.name);

  printf("Informe o email do contato: ");
  fgets(newContact.email, sizeof(newContact.email), stdin);

  printf("Informe o telefone do contato: ");
  fgets(newContact.phone, sizeof(newContact.phone), stdin);
  
  // Insere na arvore binaria
  tree = insertBinarySearchTree(tree, newContact);
  printf("-------------------------------------\n");

  return tree;
}

// Permite excluir um contato da agenda
Tree delContact(Tree tree)
{
  char contact_name[30];

  printf("---------- APAGAR CONTATO ----------\n");
  printf("Informe o nome do contato que deseja excluir da agenda: ");
  fgets(contact_name, sizeof(contact_name), stdin);

  // Capitaliza string
  capitalize_str(contact_name);

  // Remove elemento da arvore
  tree = removeBinarySearchTree(tree, contact_name);
  printf("----------------------------------\n");

  return tree;
}

// Lista o conteudo da agenda (todos os campos)
void listContacts(Tree tree)
{
  printf("---------- LISTA DE CONTATOS ----------\n");
  // Imprime arvore binaria
  printBinarySearchTree(tree);
  printf("---------------------------------------\n");
  return;
}

// Permite consultar um contato da agenda por nome
void queryContact(Tree tree)
{
  // Cria variaveis necessarias
  Tree filtredTree;
  char contact_name[30];
  filtredTree = malloc(sizeof(Nodo));

  printf("---------- PESQUISAR CONTAT0 ----------\n");
  printf("Informe o nome do contato que deseja buscar na agenda: ");
  fgets(contact_name, sizeof(contact_name), stdin);

  // Capitaliza string
  capitalize_str(contact_name);

  // Filtra contato na arvore
  filtredTree = searchBinarySearchTree(tree, contact_name);

  if (filtredTree != NULL)
  { // Caso tiver algum contato
    printf("%s", filtredTree->contact.name);
    printf("%s", filtredTree->contact.email);
    printf("%s", filtredTree->contact.phone);
  }
  else
  { //Caso não tiver contato
    printf("Contato não encontrado\n");
  }
  printf("---------------------------------------\n");

  return;
}

// Abre arquivo com dados e tras para a memoria
Tree dataOpen(Tree tree)
{
  Contact newContact;

  // Abre arquivo no tipo escrita
  FILE *read_archive = fopen("ContactList", "r");
  if(read_archive == NULL)
  { // Caso não abrir arquivo em leitura, cria um arquivo no modo escrita

    FILE *write_archive = fopen("ContactList", "w");
    if(write_archive == NULL)
    { // Imprime erro
      printf("Erro ao abrir o arquivo!");
      printf("Não foi possivel abrir nem criar um arquivo!");
      exit(1);
    }
  }
  else 
  { // Percorre dados do arquivo para incluir na arvore
    while( fread(&newContact, sizeof(Contact), 1, read_archive) )
    { // Percorre arquivo para inserir na arvore
      
      tree = insertBinarySearchTree(tree, newContact);
    }

    // Fecha arquivo
    fclose(read_archive);
  }

  return tree;
}

// Salva dados da memoria em arquivo
void dataSave(Tree tree)
{ // Abre arquivo no tipo escrita

  FILE *write_archive = fopen("ContactList", "w");
  if(write_archive == NULL)
  { // Imprime erro
    printf("Erro ao abrir o arquivo!");
    exit(1);
  }
  
  // Salva arvore binaria em arquivo
  saveBinarySearchTree(tree, write_archive);

  // Fecha arquivo
  fclose(write_archive);
}

// Programa principal
int main()
{
  // Inicia a arvore binaria
  Tree root;
  root = NULL;

  root = dataOpen(root);
  int op=0;

  while (op!=EXIT)
  {
    op=menu(op);
    switch(op)
    {
      case 1 :
        root = insContact(root);
        printf("\n\n");
        break;
        
      case 2 :
        root = delContact(root);
        printf("\n\n");
        break;

      case 3 :
        queryContact(root);
        printf("\n\n");
        break;

      case 4 :
        listContacts(root);
        printf("\n\n");
        break;
    }
  }

  // Salva dados da arvore
  dataSave(root);
  return 0;
}