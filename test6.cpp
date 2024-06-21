#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>

std::string converterParaMinuscula(std::string& str) // funÃ§Ã£o que itera por cada caractere de uma string e retorna a mesma string com todas as letras minÃºsculas
{                                                    // usada para facilitar a compraÃ§Ã£o de strings
    std::string resultado = ""; // define uma string vazia para ser utilizada de retono para a string convertida
    for(char& c : str) // define a variÃ¡vel 'char c' para iterar sobre cada caractere da string 'str'
    {
        resultado += tolower(c);   // utiliza a funÃ§Ã£o tolower() para deixar 'char c' em letrr minÃºscula e adiciona Ã  string 'resultado'
    }
    return resultado; // retorna a string convertida
}

int indexConvidado(std::vector<std::string>& vec,std::string& str) // Retorna a posiÃ§Ã£o (index) da string desejada dentro de um vetor
{
    int index = 0; // define uma variÃ¡vel int para guardar a posiÃ§Ã£o do index
    for(int i = 0; i < vec.size(); i++)
    {
        if(converterParaMinuscula(str) == converterParaMinuscula(vec[i])) // verifica se a string digitada estÃ¡ no vetor comparando ela com cada posiÃ§Ã£o do vetor (vec[i])
        {
            index = i; // se as strings forem iguais, define o index como a posiÃ§Ã£o i do vetor
        }
    }
    return index; // retorna o valor do index
}

void limparCin() // limpa o cin para evitar problemas no input de um cin para outro
{
    std::cin.clear();                                                           // limpa a flag de erro do cin e ignora a linha de input atÃ© o newline ('\n')
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::fstream listaConvidados; // variÃ¡vel do tipo std::fstream, responsÃ¡vel por gerenciar arquivos
std::string convidado;
std::vector<std::string> convidados; 
int escolha;
bool remover = false, adicionar = false, pesquisar = false, achado = false, imprimir = false; // bools usados para definir opÃ§Ã£o o usuÃ¡rio selecionou

int main()
{
    setlocale(LC_ALL, ("Portuguese")); // define o locale para pt_BR para imprimir caracteres do alfabeto PortuguÃªs

    listaConvidados.open("lista de convidados.txt", std::ios::in); // abre o arquivo lista de convidados.txt e verifica se ele estÃ¡ vazio
    if(listaConvidados.peek() != EOF)                              // se nÃ£o estÃ¡ vazio, pega o nome de todos os convidados e os armazena no vetor 
    {
        while(std::getline(listaConvidados, convidado)) 
        {
            convidados.push_back(convidado);
        }
    }
    listaConvidados.close(); // fecha o arquivo

    while(!adicionar && !remover && !pesquisar && !imprimir) // enquanto o usuÃ¡rio nÃ£o escolher uma opÃ§Ã£o vÃ¡lida, repete o bloco em loop.
    {
        std::cout << "OpÃ§Ãµes:\n1. Adicionar Convidado Ã  lista\n2. Remover convidado da lista\n3. Pesquisar por convidado na lista\n4. Imprimir lista de convidados\nDigite sua escolha: ";
        std::cin >> escolha;

        switch(escolha) // funÃ§Ã£o de desvio com 3 casos (escolha 1, 2 ou 3) e um caso padrÃ£o se o input do usuÃ¡rio for invÃ¡lido
        {
            case 1: // dependendo da escolha do usuÃ¡rio executa limparCin() e define booleana relaciona a opÃ§Ã£o escolhida como verdadeira.
                limparCin();
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
                limparCin(); // caso o input seja invÃ¡lido - Ex:. usuÃ¡rio digita uma letra ou escolhe uma opÃ§Ã£o maior que 3 e menor que 1 -- retorna uma mensagem de erro e limpa o cin
                std::cout << "\n\n -- Escolha InvÃ¡lida -- \n\n";
                break;
        }
    }
    
    while(adicionar) // repete o bloco em loop se a opÃ§Ã£o 'adicionar' for escolhida
    {
        std::cout << "Digite o nome do convidado para adicionar Ã  lista ou digite 'finalizar' para salvar a lista de convidados: ";
        std::getline(std::cin, convidado); // le a linha inteira digitada pelo usuÃ¡rio e armazena o input em 'convidado'
        if(converterParaMinuscula(convidado) == "finalizar") // converte a string convidado pra minÃºscula e verifica se Ã© igual a finalizar, se for, quebra o loop.s
        {
            listaConvidados.open("lista de convidados.txt", std::ios::out); // abre a lista de convidados em modo output (digitar na lista) 
            for(std::string& nome : convidados)                             // para salvar os nomes que foram escritos dentro do vetor
            {
                listaConvidados << nome << '\n'; // escreve os nomes dentro do vetor 1 por linha
            }
            listaConvidados.close(); // fecha o arquivo e quebra o loop
            break;
        }
        convidados.push_back(convidado); // caso o usuÃ¡rio decidir nÃ£o finalizar o programa, salva o nome digitado dentro do vetor
    }

    while(remover) // repete o loop caso o usuÃ¡rio tenha escolhido a opÃ§Ã£o de remover um convidado da lista
    {
        std::cout << "Digite o nome do convidado para remover da lista ou digite 'finalizar' para salvar a lista: ";
        std::getline(std::cin, convidado); // le a linha digitada pelo usuÃ¡rio e armazena o input em 'convidado'

        if(converterParaMinuscula(convidado) == "finalizar") // verifica se o usuÃ¡rio digitou 'finalizar' para encerrar o programa
        {
            listaConvidados.open("lista de convidados.txt", std::ios::out); // se o usuÃ¡rio digitar'finalizar' abre a lista de convidados e escreve todos os nomes
            for(std::string& nome : convidados)                             // dentro vetor na lista de convidados
            {
                listaConvidados << nome << '\n';
            }
            listaConvidados.close(); // fecha o arquivo e finaliza e quebra o loop
            break;
        }

        std::vector<std::string>::iterator it = convidados.begin(); // define um iterador para o inicio do vetor
        std::advance(it, indexConvidado(convidados, convidado));    // usa a funÃ§Ã£o std::advance para avanÃ§ar o iterador para alguma posiÃ§Ã£o do vetor, neste caso
                                                                    // Ã© usada a funÃ§Ã£o indexConvidado() para encontrar a posiÃ§Ã£o onde o nome a ser removido da lista
        convidados.erase(it);                                       // se encontra dentor do vetor e usa a funÃ§Ã£o 'vector.erase()' para apagar o item na posiÃ§Ã£o   
    }                                                               // na qual o iterador aponta

    while(pesquisar) // repte o loop caso o usuÃ¡rio tenha escolhido a opÃ§Ã£o de pesquisar por um convidado
    {
        std::cout << "\nDigite o nome do convidado para verificar se ele foi convidado ou digite 'finalizar' para encerrar o prograna: ";
        std::getline(std::cin, convidado); // lÃª a linha digitada pelo usuÃ¡rio e a armazena em 'convidados'

        if(converterParaMinuscula(convidado) == "finalizar") // verifica se o usuÃ¡rio digitou 'finalizar' para encessar o input, se sim, quebra o loop
        {
            break;
        }

        achado = false; // define a booleana 'achado' como falso para que ela nÃ£o permaneÃ§a como 'true' em loops subsequentes
        for(int i = 0; i < convidados.size(); i++)
        {
            if(converterParaMinuscula(convidado) == converterParaMinuscula(convidados[i])) // verifica se o nome do convidado digitado estÃ¡ na lista
            {                                                                              // se estiver, retorna a mensagem "Convidado estÃ¡ na lista!" e define achado como 'true'
                std::cout << "Convidado estÃ¡ na lista!";
                achado = true;
            }
        }
        if(!achado) // caso o nome do convidado nÃ£o esteja na lista, a varÃ­avel achado permanece falsa e, apÃ³s o fim do loop for, retorna a mensagem "Convidado nÃ£o estÃ¡ na lista!"
        {
            std::cout << "Convidado nÃ£o estÃ¡ na lista!";
        }
    }

    if(imprimir) // verifica se o usuÃ¡rio escolheu imprimir a lista
    {
        for(std::string& nome : convidados) // itera pelo vetor e imprime o nome de todos os convidados dentro da lista
        {
            std::cout << nome << '\n';
        }
    }   

    return 0;  // fim do programa
}
