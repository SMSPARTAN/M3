#include <iostream>
#include <string>

std::string separarNomeDeConfirmado(std::string &str, const int &retType) // função para separar o número de uma string
{                                                                         // no arquivo a formatação é nome presença, presença sendo representa por 1 = sim e 0 = não
    int confirmado = str.find_first_of("0123456789", 0);                  // portanto é necessário separar o número que representa a presença da parte que representa o nome na string
                                                                          // é usada a função find_first_of(); para achar a primeira ocorrência de um número na string começando pelo inicio
    std::string nome = str.substr(0, confirmado);                         // da string e armazena a posição na variável confirmado
                                                                          //    nome = stringApagarEspacosNoFinal(nome);                                // usada a função .substr para remover uma parte em específica da string, neste caso tudo depois da posição 'confirmado
                                                                          // e logo após a função stringApagarEspacosNoFinal() para apagar espaços que podem ter ficado no final da string
                                                                          // std::string num(1, str[confirmado]);                                  // é iniciada uma string de nome num para armazenar o numero da string original
    std::string num;
    num = str.substr(confirmado);
    // neste caso num(1, str[confirmado]) diz para iniciar a variável num com tamanho 1 e com o valor
    if (retType == 1)        // presente na posição 'confirmado' da string
    {                        // verifica se a função foi chamada (informado no argumento retType) como 1 ou não, se for chamada como 1,
        return nome; // retorna a parte do nome da string se não, retorna a parte númerica
    }
    return num;
}

std::string str = "Waluigi 11";

int main()
{
    std::printf("Nome: %s\nNumber: %s", separarNomeDeConfirmado(str, 1).c_str(), separarNomeDeConfirmado(str, 0).c_str());

    return 0;
}