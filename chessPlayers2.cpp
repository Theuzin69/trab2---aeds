/*Programa que gera arquivos a partir de outro arquivo chamado "players_raw.csv",
filtrando seus valores de acordo com a entrada do usuario.
Utiliza listas encadeadas com ponteiro apenas para o inicio, e para o proximo no.
Integrantes: Gabriel Ajeje, Jessica, Luiz Otavio, Matheus, Vanessa
Inicio: 04/10/2023 Entrega:16/10/2023*/
#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;
const int MAX_CHARS_LINE = 100;
const int MAX_CHARS = 60;

class player // noh da lista encadeada
{
private:
	player* prox;
	int order;
	int id;
	char* name;
	char* federation;
	char gender;
	char* title;
	int yob;

public:
	player();
	player(int _order, int _id, char* _name, char* _federation, char _gender,
		char* _title, int _yob);
	int getOrder();
	int getId();
	char* getName();
	char* getFederation();
	char getGender();
	char* getTitle();
	int getYob();

	player* getProx();
	void setProx(player* _prox);
};

class lista // lista ¯\_(ツ)_/¯
{
private:
	player* inicio;
public:
	lista();
	bool vazia();
	player* getInicio();
	void imprime();
	void insereFim(int _order, int _id, char* _name, char* _federation,
		char _gender, char* _title, int _yob);
	~lista();
};

// metodos da classe player

player::player() {
	order = 0;
	id = 0;
	name = 0;
	federation = 0;
	gender = 0;
	title = 0;
	yob = 0;
	prox = 0;
}
player::player(int _order, int _id, char* _name, char* _federation,
	char _gender, char* _title, int _yob) {
	order = _order;
	id = _id;
	name = new char[strlen(_name) + 1];
	strcpy(name, _name);
	federation = new char[strlen(_federation) + 1];
	strcpy(federation, _federation);
	gender = _gender;
	title = new char[strlen(_title) + 1];
	strcpy(title, _title);
	yob = _yob;
	prox = 0;
}
int player::getOrder() { return order; }
int player::getId() { return id; }
char* player::getName() { return name; }
char* player::getFederation() { return federation; }
char player::getGender() { return gender; }
char* player::getTitle() { return title; }
int player::getYob() { return yob; }

player* player::getProx() { return prox; }
void player::setProx(player* _prox) { prox = _prox; }

// metodos da classe lista
lista::lista() { inicio = 0; }

bool lista::vazia() { return inicio == 0; }
player* lista::getInicio() { return inicio; }
void lista::imprime() {
	player* aux = inicio;
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
void lista::insereFim(int _order, int _id, char* _name, char* _federation,
	char _gender, char* _title, int _yob) {
	player* jogador = new player(_order, _id, _name, _federation, _gender, _title, _yob);

	if (vazia())
		inicio = jogador;
	else {
		player* aux = inicio;
		while (aux->getProx())
			aux = aux->getProx();
		aux->setProx(jogador);
	}
}
lista::~lista() {
	player* aux;
	while (inicio) {
		aux = inicio;
		inicio = inicio->getProx();
		delete aux;
	}
}

// funcao que separa as informacoes do csv
void substring(char buff[MAX_CHARS_LINE], char aux[MAX_CHARS], int& i,
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
void menu() {
	cout << "Gerar arquivo de jogadores por: " << endl
		<< "1 - Federacao" << endl
		<< "2 - Genero" << endl
		<< "3 - Titulo" << endl
		<< "0 - Sair do programa" << endl
		<< "Sua entrada: ";
}

int main() {
	lista* l = new lista;
	char buff[MAX_CHARS_LINE];
	char aux1[MAX_CHARS]; // ID
	char aux2[MAX_CHARS]; // Name
	char aux3[MAX_CHARS]; // Federation
	char aux4[MAX_CHARS]; // Gender
	char aux5[MAX_CHARS]; // Title
	char aux6[MAX_CHARS]; // Yob
	int r; // entrada do usuario //nome do arquivo de saida
	char csv[19], temp[4]; //19 = max de caracteres do nome do arquivo
	setlocale(LC_ALL, "Portuguese"); // inicio-leitura do arquivo

	ifstream fin("players_raw.csv");


	if (fin.is_open()) // Checa se arquivo de entrada abriu corretamente
	{

		// inicio-leitura do arquivo
		int i, j = 0;

		fin.getline(buff, MAX_CHARS_LINE);

		while (fin.getline(buff, MAX_CHARS_LINE)) {
			i = 0;

			substring(buff, aux1, i, ';'); //ID
			substring(buff, aux2, i, ';'); //Name
			substring(buff, aux3, i, ';'); //Federation
			substring(buff, aux4, i, ';'); //Gender
			substring(buff, aux5, i, ';'); //Title
			substring(buff, aux6, i, '\0'); //Yob
			l->insereFim(j + 1, atoi(aux1), aux2, aux3, aux4[0], aux5, atoi(aux6));

			j++; //Order
		}

		do {
			menu();
			/* << "Gerar arquivo de jogadores por: " << endl
			   << "1 - Federacao" << endl
			   << "2 - Genero" << endl
			   << "3 - Titulo" << endl
			   << "0 - Sair do programa" << endl;*/
			cin >> r;

			if (r == 1) //escolheu "Federacao"
			{
				strcpy(csv, "Federation_");
				cout << "Insira a Federacao desejada: ";
				cin >> temp;
				strcat(csv, temp);
				strcat(csv, ".csv");
				ofstream fout(csv); //Inicio-Escrita do arquivo de saida
				if (fout.is_open()) // Checa se arquivo de saida abriu corretamente
				{
					fout << "order; fide_id; name; federation; gender; title; yob" << endl;
					char field[4]; //federation
					player* aux = l->getInicio();
					while (aux) {
						strcpy(field, aux->getFederation());
						if (strcmp(field, temp) == 0) {
							fout << aux->getOrder() << ";";
							fout << aux->getId() << ";";
							fout << aux->getName() << ";";
							fout << aux->getFederation() << ";";
							fout << aux->getGender() << ";";
							fout << aux->getTitle() << ";";
							fout << aux->getYob() << endl;
							aux = aux->getProx();
						}
					}
					fout.close();
				}
				else
					cout << "Nao conseguiu abrir o arquivo de escrita!";
			}
			else if (r == 2) {
				strcpy(csv, "Gender_");
				cout << "Insira o Genero desejado: ";
				cin >> temp;
				strcat(csv, temp);
				strcat(csv, ".csv");
				ofstream fout(csv); //Inicio-Escrita do arquivo de saida
				if (fout.is_open()) // Checa se arquivo de saida abriu corretamente
				{
					fout << "order; fide_id; name; federation; gender; title; yob" << endl;
					char field; //gender
					player* aux = l->getInicio();
					while (aux) {
						field = aux->getGender();
						if (field == temp[0]) {
							fout << aux->getOrder() << ";";
							fout << aux->getId() << ";";
							fout << aux->getName() << ";";
							fout << aux->getFederation() << ";";
							fout << aux->getGender() << ";";
							fout << aux->getTitle() << ";";
							fout << aux->getYob() << endl;
							aux = aux->getProx();
						}
					}
					fout.close();
				}
				else
					cout << "Nao conseguiu abrir o arquivo de escrita!";
			}
			else if (r == 3) {
				strcpy(csv, "Title_");
				cout << "Insira a Titulacao desejada: ";
				cin >> temp;
				strcat(csv, temp);
				strcat(csv, ".csv");
				ofstream fout(csv); //Inicio-Escrita do arquivo de saida
				if (fout.is_open()) // Checa se arquivo de saida abriu corretamente
				{
					fout << "order; fide_id; name; federation; gender; title; yob" << endl;
					char field[3]; //title
					player* aux = l->getInicio();
					while (aux) {
						strcpy(field, aux->getTitle());
						if (strcmp(field, temp) == 0) {
							fout << aux->getOrder() << ";";
							fout << aux->getId() << ";";
							fout << aux->getName() << ";";
							fout << aux->getFederation() << ";";
							fout << aux->getGender() << ";";
							fout << aux->getTitle() << ";";
							fout << aux->getYob() << endl;
							aux = aux->getProx();
						}
					}
					fout.close();
				}
				else
					cout << "Nao conseguiu abrir o arquivo de escrita!";
			}
		}


		while (r > 0 && r < 4);

	}
	else
		cout << "Nao conseguiu abrir o arquivo de leitura!";

	fin.close();
	delete aux;
	delete l; // exclui o ponteiro

	return 0;
}
