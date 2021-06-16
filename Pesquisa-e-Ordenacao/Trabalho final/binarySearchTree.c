// ---------- Arvore binaria de busca - BST ----------
#include "dataStructs.c"

// Helpers para a arvore

// Capitaliza strings
void capitalize_str(char *str)
{
  int i;
  for (i = 0; i <= strlen(str); i++)
  {
    if (i == 0 || str[(i-1)] == ' ')
    {
      str[i] = toupper(str[i]);
    }
    else
    {
      str[i] = tolower(str[i]);
    }
  }
}

// Procura o menor valor para trocar quando for remover um elemento
Tree searchMinimumValue(Tree root)
{ // Cria variavel auxiliar
  Tree rootTemp = root;

  // Percorre até achar o valor menor 
  while (rootTemp && rootTemp->left != NULL)
  {
    rootTemp = rootTemp->left;
  }

  return rootTemp;
}



// Insere dados a arvore binaria
Tree insertBinarySearchTree(Tree root, Contact contact)
{
  Tree newTree;

  if (root == NULL)
  { // Caso a raiz for nula cria um novo nodo e retorna

    // Cria um novo contato na arvore
    newTree = malloc(sizeof(Nodo));
    newTree->contact = contact;
    newTree->left = NULL;
    newTree->right = NULL;

    return newTree;
  }

  if ( strcmp( root->contact.name, contact.name) > 0 )
  { // contact.name <= raiz->contact.name
    root->left = insertBinarySearchTree(root->left, contact);
  }
  else
  { // contact.name > raiz->contact.name
    root->right = insertBinarySearchTree(root->right, contact);
  }
  return root;
}

// Salva dados da arvore binaria em um arquivo
void saveBinarySearchTree(Tree root, FILE *archive)
{
  if (root!=NULL)
  {
    // Vai para o elemento da esquerda
    saveBinarySearchTree(root->left, archive);

    // Grava no arquivo o dado do contato
    fwrite(&root->contact, sizeof(Contact), 1, archive);

    // Vai para o elemento da direita
    saveBinarySearchTree(root->right, archive);
  }
}

// Procura nome na arvore binaria
Tree searchBinarySearchTree(Tree root, char *contact_name) 
{
  if ( root == NULL)
  { // Caso a arvore não tiver nenhum elemento
    return NULL; 
  }
  else
  { 
    if ( strcmp(root->contact.name, contact_name) == 0 )
    { // Caso o elemento da raiz for o contato
      return root;
    }
    else 
    {
      if (strcmp(root->contact.name, contact_name) > 0)
      { // contact.name <= raiz->contact.name
        root->left = searchBinarySearchTree(root->left, contact_name);
      }
      else
      { // contact.name > raiz->contact.name
        root->right = searchBinarySearchTree(root->right, contact_name);
      }
    }
  } 
}

// Remove um contato da arvore
Tree removeBinarySearchTree(Tree root, char *contact_name)
{
  if (root == NULL)
  { // Caso não encontrar o valor
    printf("Contato não encontrado ou inexistente\n");
    return root;
  }

  if (strcmp( root->contact.name, contact_name ) > 0)
  { // Caso estiver em um filho menor
    root->left = removeBinarySearchTree(root->left, contact_name);
  }
  else if (strcmp( root->contact.name, contact_name ) < 0)
  { // Caso estiver em um filho maior
    root->right = removeBinarySearchTree(root->right, contact_name);
  }
  else 
  { // Caso encontrar o elemento
    if (root->left == NULL)
    { // Caso tiver apenas um filho, cria variavel auxiliar e depois remove contato
      Tree temp = root->right;
      free(root);

      printf("Contato apagado com sucesso \n");
      return temp;
    }
    else if (root->right == NULL)
    { // Caso tiver apenas um filho, cria variavel auxiliar e depois remove contato
      Tree temp = root->left;
      free(root);
      
      printf("Contato apagado com sucesso \n");
      return temp;
    }

    // Caso tiver os dois filhos
    // Procura o menor elemento do filho maior
    Tree temp = searchMinimumValue(root->right);

    // Troca valor do contato pelo do seu filho
    root->contact = temp->contact;

    // Chama função com seu filho para remove-lo
    root->right = removeBinarySearchTree(root->right, temp->contact.name);
  }
  return root;
}



// Imprime a arvore binaria ordenada
// ---------- Tree sort ----------
// Pior caso    Θ(N log N)
// Medio caso   Θ(N log N)
// Melhor caso  Θ(N log N)
// Espaço       Θ(N)
// -------------------------------
void printBinarySearchTree(Tree root)
{
  if (root!=NULL)
  {
    // Vai para o elemento da esquerda
    printBinarySearchTree(root->left);

    // Imprime dados do contato (todos os campos)
    printf("Nome: %s",root->contact.name);
    printf("Telefone: %s",root->contact.phone);
    printf("Email: %s",root->contact.email);
    printf("\n");

    // Vai para o elemento da direita
    printBinarySearchTree(root->right);
  }
}