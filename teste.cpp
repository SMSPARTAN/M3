#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>
#include <algorithm>

struct Convidado
{
    std::string nome;
    std::string confirmado = "0";
};

std::string separarNomeDeConfirmado(std::string &str, int retType)
{
    size_t confirmado = str.find_last_of("0123456789", 0);
    std::string nome = str.substr(0, confirmado);
    std::string::iterator it = std::find_if(nome.begin(), nome.end(),[](char c){return !isspace(c);});
    std::string num(1, str[confirmado]);
    if(retType == 1)
    {
        return nome;
    }
    return num;
}

std::fstream listaConvidados;                                                   // variável do tipo std::fstream, responsável por gerenciar arquivos
std::string convidado;
std::vector<Convidado> convidados; 
int escolha;
bool fim = false;                                                               // bools usados para definir fim do loop de escolhas

int main()
{
    std::setlocale(LC_ALL, ("pt_BR.UTF-8"));                                    // define o locale para pt_BR para imprimir caracteres do alfabeto Português

    listaConvidados.open("teste.txt", std::ios::in);              // abre o arquivo lista de convidados.txt e verifica se ele está vazio
    if(listaConvidados.peek() != EOF)                                           // se não está vazio, pega o nome de todos os convidados e os armazena no vetor 
    {
        while(std::getline(listaConvidados, convidado)) 
        {
            convidados.push_back({separarNomeDeConfirmado(convidado, 1), separarNomeDeConfirmado(convidado, 0)});
        }
    }
    listaConvidados.close();                                                    // fecha o arquivo
    
    for(Convidado &pessoa : convidados)
    {
        std::cout << pessoa.nome << " " << pessoa.confirmado << '\n';
    }

    return 0;
}