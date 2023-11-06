#ifndef STRUCTS
#define STRUCTS

// Estrutura que contém os campos dos registros da agenda
struct MREC 
{
  char name[30];
  char email[40];
  char phone[20];  
};

// Tipo criado para instanciar variaveis do tipo agenda
typedef struct MREC Contact;

// Cria estrutura para BST
typedef struct NODO
{
  Contact contact;
  struct NODO *left;
  struct NODO *right;
} Nodo;

// Tipo criado para instanciar variaveis do tipo arvore binaria de busca
typedef Nodo *Tree;

#endif