#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <locale>
#include <algorithm>

struct Convidado                                                                // define um objeto de nome Convidado que armazena os valores do nome e status da confirmação do convidado
{
    std::string nome;
    std::string confirmado;
};

void pausarAteNewLine()                                                         // imprime na tela a instrução para continuar o código, limpa o cin e usa a função std::cin.get()
{                                                                               // para pausar o console até que um input de newline seja recebido
    std::cout << "\nPressione 'Enter' para continuar...";
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

void limparCin()                                                                // limpa o cin para evitar problemas no input de um cin para outro
{
    std::cin.clear();                                                           // limpa a flag de erro do cin e ignora a linha de input até o newline ('\n')
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void clearScreen()                                                              // função para limpar a tela
{
    std::cout << "\x1B[2J\x1B[H";
}

std::string stringApagarEspacosNoFinal(std::string &str)                // função para achar apagar espaços que existem após o fim de uma string
{                                                                       // é criada uma variável inicializada para o valor da string original e é
    std::string strSemEspaços = str;  
                                                                        // usado str.find_last_not_of(' ') para achar o último caractere que não é um espaço
    int inicio = strSemEspaços.find_last_not_of(' ');                   // após isso é usado str.erase(inicio + 1) para apagar tudo começando pelo primeiro espaço até o fim da string
    strSemEspaços.erase(inicio + 1);

    return  strSemEspaços;                                              // e, por fim, retorna o valor o valor da string sem espaços no final
}

std::string separarNomeDeConfirmado(std::string &str,const int &retType)    // função para separar o número de uma string
{                                                                           // no arquivo a formatação é nome presença, presença sendo representa por 1 = sim e 0 = não
    int confirmado = str.find_first_of("0123456789", 0);                    // portanto é necessário separar o número que representa a presença da parte que representa o nome na string
                                                                            // é usada a função find_first_of(); para achar a primeira ocorrência de um número na string começando pelo inicio 
    std::string nome = str.substr(0, confirmado);                           // da string e armazena a posição na variável confirmado    
    nome = stringApagarEspacosNoFinal(nome);                                // usada a função .substr para remover uma parte em específica da string, neste caso tudo depois da posição 'confirmado
                                                                            // e logo após a função stringApagarEspacosNoFinal() para apagar espaços que podem ter ficado no final da string
    std::string num(1, str[confirmado]);                                    // é iniciada uma string de nome num para armazenar o numero da string original
                                                                            // neste caso num(1, str[confirmado]) diz para iniciar a variável num com tamanho 1 e com o valor
    if(retType == 1)                                                        // presente na posição 'confirmado' da string
    {                                                                       // verifica se a função foi chamada (informado no argumento retType) como 1 ou não, se for chamada como 1,
        return nome;                                                        // retorna a parte do nome da string se não, retorna a parte númerica    
    }
    return num;
}

std::string converterParaMinuscula(std::string &str)                        // função que itera por cada caractere de uma string e retorna a mesma string com todas as letras minúsculas
{                                                                           // usada para facilitar a compração de strings
    std::string resultado = "";                                             // define uma string vazia para ser utilizada de retono para a string convertida
    for(char& c : str)                                                      // define a variável 'char c' para iterar sobre cada caractere da string 'str'
    {
        resultado += tolower(c);                                            // utiliza a função tolower() para deixar 'char c' em letrr minúscula e adiciona à string 'resultado'
    }
    return resultado;                                                       // retorna a string convertida
}

int indexConvidado(std::vector<Convidado> &vec,std::string &str)            // Retorna a posição (index) da string desejada dentro de um vetor
{
    int index = -1;                                                          // define uma variável int para guardar a posição do index
    for(int i = 0; i < vec.size(); i++)
    {
        if(converterParaMinuscula(str) == converterParaMinuscula(vec[i].nome))   // verifica se a string digitada está no vetor comparando ela com cada posição do vetor (vec[i].nome)
        {
            index = i;                                                      // se as strings forem iguais, define o index como a posição i do vetor
        }
    }
    return index;                                                           // retorna o valor do index
}

void adicionarParaLista(std::vector<Convidado> &vec, std::string &str, std::fstream &file)
{
    while(true)                                                             // repete o bloco em loop se a opção 'adicionar' for escolhida
    {
        std::cout << "Digite o nome do convidado para adicionar à lista ou digite 'fim' para salvar a lista de convidados: ";
        std::getline(std::cin, str);
        str = stringApagarEspacosNoFinal(str);                                           
        if(converterParaMinuscula(str) == "fim")                            // converte a string convidado pra minúscula e verifica se é igual a fim, se for, quebra o loop.s
        {
            file.open("lista de convidados.txt", std::ios::out);            // abre a lista de convidados em modo output (digitar na lista) 
            for(Convidado &nome : vec)                                      // para salvar os nomes que foram escritos dentro do vetor
            {
                file << nome.nome << " " << nome.confirmado << '\n';        // escreve os nomes dentro do vetor 1 por linha
            }
            file.close();                                                   // fecha o arquivo e quebra o loop
            break;
        }
        vec.push_back({str, "0"});                                          // caso o usuário decidir não fim o programa, salva o nome digitado dentro do vetor e, por padrão,
    }                                                                       // define a presença como 0
}

void confirmarPresenca(std::vector<Convidado> &vec, std::string &str,std::fstream &file)    
{                                                                                           
    while(true)                                                                             
    {                                                                                       
        std::cout << "\nDigite o nome do convidado para confirmar a presença ou digite 'fim' para salvar as presenças ";
        std::getline(std::cin, str);

        if(converterParaMinuscula(str) == "fim")                                            // função para adicionar presença à convidados
        {                                                                                   // faz um loop para pegar o input do usuário e verifica se o input é 'fim' ou não
            clearScreen();
            break;                                                                          // se for 'fim' salva o arquivo, se não, itera pelo vetor e encontra o nome do convidado e
        }                                                                                   // define o valor 'confirmado' como 1

        for(Convidado &convidado : vec)
        {
            if(converterParaMinuscula(str) == converterParaMinuscula(convidado.nome))
            {
                convidado.confirmado = "1";
            }
        }
        file.open("lista de convidados.txt", std::ios::out);
        for(Convidado &convidado : vec)
        {
            file << convidado.nome << " " << convidado.confirmado << '\n';
        }
        file.close();
    }
}

void removerDaLista(std::vector<Convidado> &vec, std::string &str, std::fstream &file)
{
    while(true)                                                             // repete o loop caso o usuário tenha escolhido a opção de remover um convidado da lista
    {
        std::cout << "Digite o nome do convidado para remover da lista ou digite 'fim' para salvar a lista: ";
        std::getline(std::cin, str);                                        // le a linha digitada pelo usuário e armazena o input em 'convidado'

        if(converterParaMinuscula(str) == "fim")                            // verifica se o usuário digitou 'fim' para encerrar o programa
        {
            file.open("lista de convidados.txt", std::ios::out);                          // se o usuário digitar'fim' abre a lista de convidados e escreve todos os nomes
            for(Convidado &nome : vec)                                      // dentro vetor na lista de convidados
            {
                file << nome.nome << " " << nome.confirmado << '\n';
            }
            file.close();                                                   // fecha o arquivo e finaliza e quebra o loop
            clearScreen();
            break;
        }

        int index = indexConvidado(vec, str);                                   

        if(index == -1)                                                         // verifica se o nome especificado existe no vetor, se não existir, retorna um erro
        {
            std::cout << "\n\n -- Convidado Não Está na Lista! -- \n\n";
        }

        else                                                                    // se o nome existir na lista, deleta o convidado especificado     
        {
            index = indexConvidado(vec, str);

            std::vector<Convidado>::iterator it = vec.begin();                  // define um iterador para o inicio do vetor
            std::advance(it, index);                                            // usa a função std::advance para avançar o iterador para alguma posição do vetor, neste caso
                                                                                // é usada a função indexConvidado() para encontrar a posição onde o nome a ser removido da lista
            vec.erase(it);                                                      // se encontra dentor do vetor e usa a função 'vector.erase()' para apagar o item na posição                                                                                   
        }                                                                       // na qual o iterador aponta

        std::cout << '\n';
    }
}

void pesquisarNaLista(std::vector<Convidado> &vec, std::string &str)
{
    while(true)                                                             // repete o loop caso o usuário tenha escolhido a opção de pesquisar por um convidado
    {
        std::cout << "\nDigite o nome do convidado para verificar se ele foi convidado ou digite 'fim' para encerrar o programa: ";
        std::getline(std::cin, str);                                        // lê a linha digitada pelo usuário e a armazena em 'convidados'
        std::string strConvertida = converterParaMinuscula(str);
        if(converterParaMinuscula(str) == "fim")                            // verifica se o usuário digitou 'fim' para encerrar o input, se sim, quebra o loop
        {
            clearScreen();
            break;
        }

        for(Convidado &pessoa : vec)                                                                // faz um loop for e imprime o nome do convidado e o status da presença
        {                                                                                           // utilizando-se de um ternário para definir o valor da string 'presença'
            std::string presenca = (pessoa.confirmado == "1") ? "confirmada" : "não confirmada";    // verifica se pessoa.confirmado é igual a 1 e retorna se verdadeiro
            if(converterParaMinuscula(str) == converterParaMinuscula(pessoa.nome))                  // o valor anstes de : e se falso o valor após :
            {
                std::cout << pessoa.nome << " -- Presença: " << presenca << '\n';
            }
        }
    }
}

void definirTipoDeImpressao(int &escolha)                                                           
{
    std::cout << "\n1. Imprimir todos convidados\n2. Imprimir só convidados com presença confirmada\n3. Imprimir só convidados com presença não confirmada\nEscolha: ";
    std::cin >> escolha;                                                                            // função usada em conjunção com imprimirLista(), esta função é usada para
                                                                                                    // para definir o tipo de lista a ser impressa
    if(std::cin.fail())
    {
        std::cout << "\n\n -- Escolha Inválida! -- \n\n";
        limparCin();
    }
}

void imprimirLista(std::vector<Convidado> &vec, int &escolha)                                       // usada em conjunção com definirTipoDeImpressao(), esta função é usada para
{                                                                                                   // imprimir o tipo de lista escolhido
    switch(escolha) 
    {
        case 1:
            for(Convidado &nome: vec)
            {
                std::string confirmado = (nome.confirmado == "1") ? "confirmada" : "não confirmada";
                std::cout << '\n' << nome.nome << " -- Presença: " << confirmado << '\n';
            }
            std::cout << std::endl;
            pausarAteNewLine();
            break;   
        case 2:
            for(Convidado &nome: vec)
            {
                if(nome.confirmado == "1")
                {
                    std::cout << '\n'<< nome.nome << " " << " -- Presença: Confirmado" << '\n';
                }
            }
            std::cout << std::endl;
            pausarAteNewLine();
            break; 
        case 3:
            for(Convidado &nome : vec)
            {
                if(nome.confirmado != "1")
                {
                    std::cout << '\n' << nome.nome << " " << " -- Presença: Não confirmado" << '\n';
                }
            }
            std::cout << std::endl;
            pausarAteNewLine();
            break;
    }
}


std::fstream listaConvidados;                                                   // variável do tipo std::fstream, responsável por gerenciar arquivos
std::string convidado;
std::vector<Convidado> convidados; 
int escolha;
bool fim = false;                                                               // bools usados para definir fim do loop de escolhas

int main()
{
    setlocale(LC_ALL, ("pt_BR.UTF-8"));                                    // define o locale para pt_BR para imprimir caracteres do alfabeto Português

    listaConvidados.open("lista de convidados.txt", std::ios::in);              // abre o arquivo lista de convidados.txt e verifica se ele está vazio
    if(listaConvidados.peek() != EOF)                                           // se não está vazio, pega o nome de todos os convidados e os armazena no vetor 
    {
        while(std::getline(listaConvidados, convidado)) 
        {
            convidados.push_back({separarNomeDeConfirmado(convidado, 1), separarNomeDeConfirmado(convidado, 0)});
        }
    }
    listaConvidados.close();                                                    // fecha o arquivo

    while(!fim)                                                                 // enquanto o usuário não escolher a opção 5, continua o loop.
    {
        clearScreen();

        std::cout << "Opções:\n1. Adicionar Convidado à lista\n2. Remover convidado da lista\n3. Pesquisar por convidado na lista\n4. Imprimir lista de convidados"
        "\n5. Confirmar presença de um convidado\n6. Encerra o programa\nDigite sua escolha: ";
        std::cin >> escolha;

        switch(escolha)                                                         // função de desvio com 6 casos (escolhas de 1 à 6) e um caso padrão se o input do usuário for inválido
        {
            case 1:                                                             // dependendo da escolha do usuário executa limparCin() e clearScreen()
                limparCin();                                                    // e executa a função responsável para a ação escolhida pelo usuário
                clearScreen();
                adicionarParaLista(convidados, convidado, listaConvidados);
                break;
            case 2:
                limparCin();
                clearScreen();
                removerDaLista(convidados, convidado, listaConvidados);
                break;
            case 3:
                limparCin();
                clearScreen();
                pesquisarNaLista(convidados, convidado);
                break;
            case 4:
                limparCin();
                clearScreen();
                definirTipoDeImpressao(escolha);
                imprimirLista(convidados, escolha);
                break;
            case 5:
                limparCin();
                clearScreen();
                confirmarPresenca(convidados, convidado, listaConvidados);
                break;
            case 6:
                fim = true;                                                     // define a booleana responsável pelo fim do loop principal como true.
                break;
            default:
                limparCin();                                                    // caso o input seja inválido - Ex:. usuário digita uma letra ou escolhe
                std::cout << "\n\n -- Escolha Inválida -- \n\n";                // uma opção maior que 6 e menor que 1 -- retorna uma mensagem de erro e limpa o cin
                break;
        }
    }
    return 0;                                                                   // fim do programa
}
