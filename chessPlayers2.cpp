/*Integrantes: Gabriel Ajeje, Jessica, Luiz Otavio, Matheus, Vanessa
Inicio: 04/10/2023 Entrega:16/10/2023*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
const int MAX_CHARS_LINE = 100;
const int MAX_CHARS = 30;

class player // noh da lista encadeada
{
private:
  player *prox;
  int order;
  int id;
  char *name;
  char *federation;
  char gender;
  char *title;
  int yob;

public:
  player();
  player(int _order, int _id, char *_name, char *_federation, char _gender,
         char *_title, int _yob);
  int getOrder();
  int getId();
  char *getName();
  char *getFederation();
  char getGender();
  char *getTitle();
  int getYob();

  void setOrder(int _order);
  void setId(int _id);
  void setName(char *_name);
  void setFederation(char *_federation);
  void setGender(char _gender);
  void setTitle(char *_title);
  void setYob(int _yob);
  player *getProx();
  void setProx(player *_prox);
};

class lista // lista ¯\_(ツ)_/¯
{
private:
  player *inicio;

public:
  lista();
  bool vazia();
  void imprime();
  void insereFim(int _order, int _id, char *_name, char *_federation,
                 char _gender, char *_title, int _yob);
  ~lista();
};

// metodos da classe player

player::player() {
  order = 0;
  id = 0;
  *name = 0;
  *federation = 0;
  gender = 0;
  *title = 0;
  yob = 0;
  prox = 0;
}
player::player(int _order, int _id, char *_name, char *_federation,
               char _gender, char *_title, int _yob) {
  order = _order;
  id = _id;
  name = _name;
  federation = _federation;
  gender = _gender;
  title = _title;
  yob = _yob;
  prox = 0;
}
int player::getOrder() { return order; }
int player::getId() { return id; }
char *player::getName() { return name; }
char *player::getFederation() { return federation; }
char player::getGender() { return gender; }
char *player::getTitle() { return title; }
int player::getYob() { return yob; }

void player::setId(int _id) { id = _id; }
player *player::getProx() { return prox; }
void player::setProx(player *_prox) { prox = _prox; }

// metodos da classe lista
lista::lista() { inicio = 0; }

bool lista::vazia() { return inicio == 0; }

void lista::imprime() {
  player *aux = inicio;
  while (aux) {
    cout << aux->getOrder() << endl;
    cout << "ID: " << aux->getId() << endl;
    cout << "Nome: " << aux->getName() << endl;
    cout << "Federacao: " << aux->getFederation() << endl;
    cout << "Sexo: " << aux->getGender() << endl;
    cout << "Titulacao: " << aux->getTitle() << endl;
    cout << "Ano: " << aux->getYob() << endl << endl;
    aux = aux->getProx();
  }
}
void lista::insereFim(int _order, int _id, char *_name, char *_federation,
                      char _gender, char *_title, int _yob) {
  player *jogador = new player(_order, _id, _name, _federation, _gender, _title, _yob);

  if (vazia())
    inicio = jogador;
  else {
    player *aux = inicio;
    while (aux->getProx())
      aux = aux->getProx();
    aux->setProx(jogador);
  }
}
lista::~lista() {
  player *aux;
  while (inicio) {
    aux = inicio;
    inicio = inicio->getProx();
    delete aux;
  }
}

// funcao que separa as informacoes do csv
void substring(char buff[MAX_CHARS_LINE], char aux[MAX_CHARS], int &i,
               char delim) {
  int k = 0;
  while (buff[i] != delim) {
    aux[k] = buff[i];
    i++;
    k++;
  }
  aux[k] = '\0';
  i++;
}

int main() {
  lista *l = new lista;
  char buff[MAX_CHARS_LINE];
  char aux1[MAX_CHARS]; // ID
  char aux2[MAX_CHARS]; // Name
  char aux3[MAX_CHARS]; // Federation
  char aux4[MAX_CHARS]; // Gender
  char aux5[MAX_CHARS]; // Title
  char aux6[MAX_CHARS]; // Yob
  int r; // entrada do usuario

  setlocale(LC_ALL, "Portuguese"); // inicio-leitura do arquivo
  ifstream fin("players_raw.csv");
  ofstream fout("dsfg.csv");

  if (fin.is_open()) // Checa se arquivo de entrada abriu corretamente
  {
    if (fout.is_open()) // Checa se arquivo de saida abriu corretamente
    {                   // inicio-leitura do arquivo
      int i, j = 0;

      fin.getline(buff, MAX_CHARS_LINE);

      while (fin.getline(buff, MAX_CHARS_LINE) && j < 4) {
        i = 0;

        substring(buff, aux1, i, ';'); //ID
        substring(buff, aux2, i, ';'); //Name
        substring(buff, aux3, i, ';'); //Federation
        substring(buff, aux4, i, ';'); //Gender
        substring(buff, aux5, i, ';'); //Title
        substring(buff, aux6, i, '\0'); //Yob
        l->insereFim(j+1, atoi(aux1), aux2, aux3, aux4[0], aux5, atoi(aux6));

        j++;
      }
      l->imprime();

      /*do {
              cout << "Gerar arquivo de jogadores por: " << endl
                      << "1 - Federacao" << endl
                      << "2 - Genero" << endl
                      << "3 - Titulo" << endl
                      << "0 - Sair do programa" << endl;
              cin >> r;
      } while (r >= 0 && r < 4);*/
    }
  } else
    cout << "Não conseguiu abrir o arquivo de leitura!";

  fin.close();
  delete l; // exclui o ponteiro

  return 0;
}
