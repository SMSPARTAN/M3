#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>

std::string converterParaMinuscula(std::string& str)                        // função que itera por cada caractere de uma string e retorna a mesma string com todas as letras minúsculas
{                                                                           // usada para facilitar a compração de strings
    std::string resultado = "";                                             // define uma string vazia para ser utilizada de retono para a string convertida
    for(char& c : str)                                                      // define a variável 'char c' para iterar sobre cada caractere da string 'str'
    {
        resultado += tolower(c);                                            // utiliza a função tolower() para deixar 'char c' em letrr minúscula e adiciona à string 'resultado'
    }
    return resultado;                                                       // retorna a string convertida
}

int indexConvidado(std::vector<std::string>& vec,std::string& str)          // Retorna a posição (index) da string desejada dentro de um vetor
{
    int index = 0;                                                          // define uma variável int para guardar a posição do index
    for(int i = 0; i < vec.size(); i++)
    {
        if(converterParaMinuscula(str) == converterParaMinuscula(vec[i]))   // verifica se a string digitada está no vetor comparando ela com cada posição do vetor (vec[i])
        {
            index = i;                                                      // se as strings forem iguais, define o index como a posição i do vetor
        }
    }
    return index;                                                           // retorna o valor do index
}

void adicionarParaLista(std::vector<std::string>& vec, std::string& str, std::fstream& file)
{
    while(true)                                                             // repete o bloco em loop se a opção 'adicionar' for escolhida
    {
        std::cout << "Digite o nome do convidado para adicionar à lista ou digite 'finalizar' para salvar a lista de convidados: ";
        std::getline(std::cin, str);                                        // lê a linha inteira digitada pelo usuário e armazena o input em 'convidado'
        if(converterParaMinuscula(str) == "finalizar")                      // converte a string convidado pra minúscula e verifica se é igual a finalizar, se for, quebra o loop.s
        {
            file.open("lista de convidados.txt", std::ios::out);            // abre a lista de convidados em modo output (digitar na lista) 
            for(std::string& nome : vec)                                    // para salvar os nomes que foram escritos dentro do vetor
            {
                file << nome << '\n';                                       // escreve os nomes dentro do vetor 1 por linha
            }
            file.close();                                                   // fecha o arquivo e quebra o loop
            break;
        }
        vec.push_back(str);                                                 // caso o usuário decidir não finalizar o programa, salva o nome digitado dentro do vetor
    }
}

void removerDaLista(std::vector<std::string>& vec, std::string& str, std::fstream& file)
{
    while(true)                                                             // repete o loop caso o usuário tenha escolhido a opção de remover um convidado da lista
    {
        std::cout << "Digite o nome do convidado para remover da lista ou digite 'finalizar' para salvar a lista: ";
        std::getline(std::cin, str);                                        // le a linha digitada pelo usuário e armazena o input em 'convidado'

        if(converterParaMinuscula(str) == "finalizar")                      // verifica se o usuário digitou 'finalizar' para encerrar o programa
        {
            file.open("lista de convidados.txt", std::ios::out);            // se o usuário digitar'finalizar' abre a lista de convidados e escreve todos os nomes
            for(std::string& nome : vec)                                    // dentro vetor na lista de convidados
            {
                file << nome << '\n';
            }
        file.close();                                                       // fecha o arquivo e finaliza e quebra o loop
            break;
        }

        std::vector<std::string>::iterator it = vec.begin();                // define um iterador para o inicio do vetor
        std::advance(it, indexConvidado(vec, str));                         // usa a função std::advance para avançar o iterador para alguma posição do vetor, neste caso
                                                                            // é usada a função indexConvidado() para encontrar a posição onde o nome a ser removido da lista
        vec.erase(it);                                                      // se encontra dentor do vetor e usa a função 'vector.erase()' para apagar o item na posição   
    }                                                                       // na qual o iterador aponta
}

void pesquisarNaLista(std::vector<std::string>& vec, std::string& str)
{
    while(true)                                                             // repte o loop caso o usuário tenha escolhido a opção de pesquisar por um convidado
    {
        std::cout << "\nDigite o nome do convidado para verificar se ele foi convidado ou digite 'finalizar' para encerrar o prograna: ";
        std::getline(std::cin, str);                                        // lê a linha digitada pelo usuário e a armazena em 'convidados'

        if(converterParaMinuscula(str) == "finalizar")                      // verifica se o usuário digitou 'finalizar' para encessar o input, se sim, quebra o loop
        {
            break;
        }

        bool achado = false;                                                // define a booleana 'achado' como falso para que ela não permaneça como 'true' em loops subsequentes
        for(int i = 0; i < vec.size(); i++)
        {
            if(converterParaMinuscula(str) == converterParaMinuscula(vec[i]))               // verifica se o nome do convidado digitado está na lista
            {                                                                              // se estiver, retorna a mensagem "Convidado está na lista!" e define achado como 'true'
                std::cout << "Convidado está na lista!";
                achado = true;
            }
        }
        if(!achado)                                                         // caso o nome do convidado não esteja na lista,
        {                                                                   // a varíavel achado permanece falsa e, após o fim do loop for, retorna a mensagem "Convidado não está na lista!" 
            std::cout << "Convidado não está na lista!";                
        }
    }
}

void imprimirLista(std::vector<std::string>& vec)
{
    for(std::string& nome : vec)
    {
        std::cout << nome << "\n";
    }
}

void limparCin()                                                                // limpa o cin para evitar problemas no input de um cin para outro
{
    std::cin.clear();                                                           // limpa a flag de erro do cin e ignora a linha de input até o newline ('\n')
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}


std::fstream listaConvidados;                                                   // variável do tipo std::fstream, responsável por gerenciar arquivos
std::string convidado;
std::vector<std::string> convidados; 
int escolha;
bool fim = false;                                                               // bools usados para definir fim do loop de escolhas

int main()
{
    std::setlocale(LC_ALL, ("pt_BR.UTF-8"));                                    // define o locale para pt_BR para imprimir caracteres do alfabeto Português

    listaConvidados.open("lista de convidados.txt", std::ios::in);              // abre o arquivo lista de convidados.txt e verifica se ele está vazio
    if(listaConvidados.peek() != EOF)                                           // se não está vazio, pega o nome de todos os convidados e os armazena no vetor 
    {
        while(std::getline(listaConvidados, convidado)) 
        {
            convidados.push_back(convidado);
        }
    }
    listaConvidados.close();                                                    // fecha o arquivo

    while(!fim)                                                                 // enquanto o usuário não escolher a opção 5, continua o loop.
    {
        std::cout << "Opções:\n1. Adicionar Convidado à lista\n2. Remover convidado da lista\n3. Pesquisar por convidado na lista\n4. Imprimir lista de convidados"
        "\n5. Encerra o programa\nDigite sua escolha: ";
        std::cin >> escolha;

        switch(escolha)                                                         // função de desvio com 3 casos (escolha 1, 2 ou 3) e um caso padrão se o input do usuário for inválido
        {
            case 1:                                                             // dependendo da escolha do usuário executa limparCin()
            limparCin();                                                        // e executa a função responsável para a ação escolhida pelo usuário
                adicionarParaLista(convidados, convidado, listaConvidados);
                break;
            case 2:
                limparCin();
                removerDaLista(convidados, convidado, listaConvidados);
                break;
            case 3:
                limparCin();
                pesquisarNaLista(convidados, convidado);
                break;
            case 4:
                limparCin();
                imprimirLista(convidados);
                break;
            case 5:
                fim = true;                                                     // define a booleana responsável pelo fim do loop principal como true.
                break;
            default:
                limparCin();                                                    // caso o input seja inválido - Ex:. usuário digita uma letra ou escolhe
                std::cout << "\n\n -- Escolha Inválida -- \n\n";                // uma opção maior que 3 e menor que 1 -- retorna uma mensagem de erro e limpa o cin
                break;
        }
    }
    return 0;                                                                   // fim do programa
}
