/*
    Universidade Federal de São Carlos – UFSCar
    Departamento de Computação

    1001490 - Algoritmos e Estruturas de Dados 2 – Trabalho 1
    Prof. Dr. Diego Furtado Silva

    Aluno: João Victor Mendes Freire
    RA: 758943
*/

#include <iostream>
#include <string>
#include <unordered_map>

int main()
{
    // Código da operação e argumentos
    std::string buffer;
    std::string opcode;
    std::string nome;
    std::string telefone;

    // Hashmap
    std::unordered_map<std::string, std::string> hash;
    std::unordered_map<std::string, std::string>::iterator it;

    for (;;)
    {
        // Lendo comando
        std::getline(std::cin, buffer);
        buffer = buffer.substr(0, buffer.length() - 1);

        // Separando opcode
        size_t pos1 = 0;
        size_t pos2 = buffer.find(" ");
        opcode = buffer.substr(pos1, pos2 - pos1);

        // Separando nome
        pos1 = pos2 + 1;
        pos2 = buffer.find(" ", pos1);
        nome = buffer.substr(pos1, pos2 - pos1);

        // Separando telefone
        pos1 = pos2 + 1;
        pos2 = buffer.find(" ", pos1);
        telefone = buffer.substr(pos1);

        // Realizando o comando
        if (opcode == "I")
        {
            it = hash.find(nome);

            // Se ir != hash.end(), elemento existe no hashmap
            if (it == hash.end())
                hash[nome] = telefone;
            else
                std::cout << "Contatinho ja inserido" << "\n";
        }
        else if (opcode == "P")
        {
            it = hash.find(nome);

            // Se ir != hash.end(), elemento existe no hashmap
            if (it != hash.end())
                std::cout << "Contatinho encontrado: telefone " + it->second << "\n";
            else
                std::cout << "Contatinho nao encontrado" << "\n";
        }
        else if (opcode == "R")
        {
            if (hash.erase(nome) == 0)
                std::cout << "Operacao invalida: contatinho nao encontrado" << "\n";
        }
        else if (opcode == "A")
        {
            it = hash.find(nome);
            
            // Se ir != hash.end(), elemento existe no hashmap
            if (it != hash.end())
                it->second = telefone;
            else
                std::cout << "Operacao invalida: contatinho nao encontrado" << "\n";
        }
        else
        {
            exit(0);
        }
    }

    return 0;
}
