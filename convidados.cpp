#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>

std::string converterParaMinuscula(std::string& str)                        // função que itera por cada caractere de uma string e retorna a mesma string com todas as letras minúsculas
{                                                                           // usada para facilitar a compração de strings
    std::string stringMinuscula = "";                                       // define uma string vazia para ser utilizada de retono para a string convertida
    for(char& c : str)                                                      // define a variável 'char c' para iterar sobre cada caractere da string 'str'
    {
        stringMinuscula += tolower(c);                                      // utiliza a função tolower() para deixar 'char c' em letrr minúscula e adiciona à string 'stringMinuscula'
    }
    return stringMinuscula;                                                 // retorna a string convertida
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

void limparCin()                                                            // limpa o cin para evitar problemas no input de um cin para outro
{
    std::cin.clear();                                                       // limpa a flag de erro do cin e ignora a linha de input até o newline ('\n')
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::fstream listaConvidados;                                               // variável do tipo std::fstream, responsável por gerenciar arquivos
std::string convidado;
std::vector<std::string> convidados; 
int escolha;
bool remover = false, adicionar = false, pesquisar = false, achado = false, imprimir = false; // bools usados para definir opção o usuário selecionou

int main()
{
    setlocale(LC_ALL, ("pt_BR.UTF-8"));                                     // define o locale para pt_BR para imprimir caracteres do alfabeto Português

    listaConvidados.open("lista de convidados.txt", std::ios::in);          // abre o arquivo lista de convidados.txt e verifica se ele está vazio
    if(listaConvidados.peek() != EOF)                                       // se não está vazio, pega o nome de todos os convidados e os armazena no vetor 
    {
        while(std::getline(listaConvidados, convidado)) 
        {
            convidados.push_back(convidado);
        }
    }
    listaConvidados.close();                                                // fecha o arquivo

    while(!adicionar && !remover && !pesquisar && !imprimir)                // enquanto o usuário não escolher uma opção válida, repete o bloco em loop.
    {
        std::cout << "Opções:\n1. Adicionar Convidado à lista\n2. Remover convidado da lista\n3. Pesquisar por convidado na lista\n4. Imprimir lista de convidados\nDigite sua escolha: ";
        std::cin >> escolha;

        switch(escolha)                                                     // função de desvio com 4 casos (escolha 1, 2, 3 ou 4)
        {                                                                   // e um caso padrão se o input do usuário for inválido
            case 1:                                                         // dependendo da escolha do usuário executa limparCin() 
                limparCin();                                                // e define booleana relaciona a opção escolhida como verdadeira.
                adicionar = true;
                break;
            case 2:
                limparCin();
                remover = true;
                break;
            case 3:
                limparCin();
                pesquisar = true;
                break;
            case 4:
                limparCin();
                imprimir = true;
                break;
            default:
                limparCin();                                                // caso o input seja inválido retorna uma mensagem de erro e limpa o cin
                std::cout << "\n\n -- Escolha Inválida -- \n\n";            // Ex:. usuário digita uma letra ou escolhe uma opção maior que 3 e menor que 1
                break;
        }
    }
    
    while(adicionar)                                                        // repete o bloco em loop se a opção 'adicionar' for escolhida
    {
        std::cout << "Digite o nome do convidado para adicionar à lista ou digite 'finalizar' para salvar a lista de convidados: ";
        std::getline(std::cin, convidado);                                  // lê a linha inteira digitada pelo usuário e armazena o input em 'convidado'
        if(converterParaMinuscula(convidado) == "finalizar")                // converte a string convidado pra minúscula e verifica se é igual a finalizar, se for, quebra o loop.s
        {
            listaConvidados.open("lista de convidados.txt", std::ios::out); // abre a lista de convidados em modo output (digitar na lista) 
            for(std::string& nome : convidados)                             // para salvar os nomes que foram escritos dentro do vetor
            {
                listaConvidados << nome << '\n';                            // escreve os nomes dentro do vetor 1 por linha
            }
            listaConvidados.close();                                        // fecha o arquivo e quebra o loop
            break;
        }
        convidados.push_back(convidado);                                    // caso o usuário decidir não finalizar o programa, salva o nome digitado dentro do vetor
    }

    while(remover)                                                          // repete o loop caso o usuário tenha escolhido a opção de remover um convidado da lista
    {
        std::cout << "Digite o nome do convidado para remover da lista ou digite 'finalizar' para salvar a lista: ";
        std::getline(std::cin, convidado);                                  // le a linha digitada pelo usuário e armazena o input em 'convidado'

        if(converterParaMinuscula(convidado) == "finalizar")                // verifica se o usuário digitou 'finalizar' para encerrar o programa
        {
            listaConvidados.open("lista de convidados.txt", std::ios::out); // se o usuário digitar'finalizar' abre a lista de convidados e escreve todos os nomes
            for(std::string& nome : convidados)                             // dentro vetor na lista de convidados
            {
                listaConvidados << nome << '\n';
            }
            listaConvidados.close();                                        // fecha o arquivo e finaliza e quebra o loop
            break;
        }

        std::vector<std::string>::iterator it = convidados.begin();         // define um iterador para o inicio do vetor
        std::advance(it, indexConvidado(convidados, convidado));            // usa a função std::advance para avançar o iterador para alguma posição do vetor, neste caso
                                                                            // é usada a função indexConvidado() para encontrar a posição onde o nome a ser removido da lista
        convidados.erase(it);                                               // se encontra dentro do vetor e usa a função 'vector.erase()' para apagar o item na posição   
    }                                                                       // na qual o iterador aponta

    while(pesquisar)                                                        // repete o loop caso o usuário tenha escolhido a opção de pesquisar por um convidado
    {
        std::cout << "\nDigite o nome do convidado para verificar se ele foi convidado ou digite 'finalizar' para encerrar o prograna: ";
        std::getline(std::cin, convidado);                                  // lê a linha digitada pelo usuário e a armazena em 'convidados'

        if(converterParaMinuscula(convidado) == "finalizar")                // verifica se o usuário digitou 'finalizar' para encessar o input, se sim, quebra o loop
        {
            break;
        }

        achado = false;                                                     // define a booleana 'achado' como falso para que ela não permaneça como 'true' em loops subsequentes
        for(int i = 0; i < convidados.size(); i++)
        {
            if(converterParaMinuscula(convidado) == converterParaMinuscula(convidados[i])) // verifica se o nome do convidado digitado está na lista
            {                                                                              // se estiver, retorna a mensagem "Convidado está na lista!" e define achado como 'true'
                std::cout << "Convidado está na lista!";
                achado = true;
            }
        }
        if(!achado)                                                                         // caso o nome do convidado não esteja na lista,
        {                                                                                   // a varíavel achado permanece falsa e, após o fim do loop 'for',
            std::cout << "Convidado não está na lista!";                                    // retorna a mensagem "Convidado não está na lista!"
        }
    }

    if(imprimir)                                                                            // verifica se o usuário escolheu imprimir a lista
    {
        for(std::string& nome : convidados)                                                 // itera pelo vetor e imprime o nome de todos os convidados dentro da lista
        {
            std::cout << nome << '\n';
        }
    }   

    return 0;  // fim do programa
}
