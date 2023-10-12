/*Integrantes: Gabriel Ajeje, Jessica, Luiz Otavio, Matheus, Vanessa
Inicio: 04/10/2023 Entrega:/10/2023*/
#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
const int MAX_CHARS_LINE = 100;
const int MAX_CHARS = 100;

class player //noh da lista encadeada
{
private:
	player* prox;
	int id;
public:
	player();
	int getId();
	player* getProx();
	void setProx(player* _prox);
};

class lista //lista ¯\_(ツ)_/¯
{
private:
	player* inicio;
public:
	bool vazia();
	void imprime();
	void insereFim(int _id);
	~lista();
};

//metodos da classe player

player::player() {
	id = 0;
	prox = 0;
}

int player::getId() {
	return id;
}

player* player::getProx() {
	return prox;
}

void player::setProx(player* _prox) {
	prox = _prox;
}

//metodos da classe lista

bool lista::vazia() {
	return inicio == 0;
}

void lista::imprime() {
	player* aux = inicio;
	while (aux) {
		cout << aux->getId() << "";
		aux = aux->getProx();
	}
}

void lista::insereFim(int _id) {
	player* jogador = new player;

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
	char delim)
{
	int k = 0;
	while (buff[i] != delim)
	{
		aux[k] = buff[i];
		i++;
		k++;
	}
	aux[k] = '\0';
	i++;
}

int main() {
	lista* l = new lista;
	char buff[MAX_CHARS_LINE];
	char aux[MAX_CHARS];
	int r; //entrada do usuario

	setlocale(LC_ALL, "Portuguese"); // inicio-leitura do arquivo
	ifstream fin("players_raw.csv");
	ofstream fout("f.csv");

	if (fin.is_open()) // Checa se arquivo de entrada abriu corretamente
	{
		if (fout.is_open()) // Checa se arquivo de saida abriu corretamente
		{
			int i, j = 0;

			fin.getline(buff, MAX_CHARS_LINE);

			while (fin.getline(buff, MAX_CHARS_LINE)) {
				i = 0;

				substring(buff, aux, i, ';');
				l->insereFim(atoi(aux));

				j++;
			}

			l->imprime();

			do {
				cout << "Gerar arquivo de jogadores por: " << endl
					<< "1 - Federacao" << endl
					<< "2 - Genero" << endl
					<< "3 - Titulo" << endl
					<< "0 - Sair do programa" << endl;
				cin >> r;
			} while (r >= 0 && r < 4);
		}
	} else
		cout << "Não conseguiu abrir o arquivo de leitura!";

	fin.close();
	delete l; //exclui o ponteiro
	return 0;
}