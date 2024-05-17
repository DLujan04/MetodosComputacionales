#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

// Enumeración que representan los tipos de Tokens.
enum TokenType {
    Entero,
    Flotante,
    Asignacion,
    Suma,
    Resta,
    Multiplicacion,
    Division,
    Potencia,
    Variable,
    ParentesisIzquierdo,
    ParentesisDerecho,
    Comentario
};

// Estructura del Token.
struct Token {
    std::string valor;
    TokenType tipo;
};

std::vector<Token> lexer(const std::string& linea) {
    std::vector<Token> tokens;
    std::stringstream ss(linea);
    std::string palabra;
    std::regex entero_regex("^[0-9]+$");
    std::regex flotante_regex("^[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)?$");
    std::regex variable_regex("^[a-zA-Z_][a-zA-Z0-9_]*$");

    while (ss >> palabra) {
        if (regex_match(palabra, entero_regex)) {
            tokens.push_back({palabra, Entero});
        } else if (regex_match(palabra, flotante_regex)) {
            tokens.push_back({palabra, Flotante});
        } else if (palabra == "=") {
            tokens.push_back({palabra, Asignacion});
        } else if (palabra == "+") {
            tokens.push_back({palabra, Suma});
        } else if (palabra == "-") {
            tokens.push_back({palabra, Resta});
        } else if (palabra == "*") {
            tokens.push_back({palabra, Multiplicacion});
        } else if (palabra == "/") {
            tokens.push_back({palabra, Division});
        } else if (palabra == "^") {
            tokens.push_back({palabra, Potencia});
        } else if (palabra == "(") {
            tokens.push_back({palabra, ParentesisIzquierdo});
        } else if (palabra == ")") {
            tokens.push_back({palabra, ParentesisDerecho});
        } else if (palabra.substr(0, 2) == "//") {
            std::string comentario = linea.substr(linea.find("//"));
            tokens.push_back({comentario, Comentario});
            break;  // Recorre todo lo que queda de la línea para conseguir todo el comentario.
        } else if (regex_match(palabra, variable_regex)) {
            tokens.push_back({palabra, Variable});
        }
    }
    return tokens;
}

// Función principal.
void lexerAritmetico(std::string archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cerr << "No se pudo abrir el archivo: " << archivo << std::endl;
        return;
    }

    std::string linea;
    while (getline(file, linea)) {
        std::vector<Token> tokens = lexer(linea);
        for (const Token& token : tokens) {
            switch (token.tipo) {
                case Entero:
                    std::cout << token.valor << "  Entero" << std::endl;
                    break;
                case Flotante:
                    std::cout << token.valor << "  Flotante" << std::endl;
                    break;
                case Asignacion:
                    std::cout << token.valor << "  Asignacion" << std::endl;
                    break;
                case Suma:
                    std::cout << token.valor << "  Suma" << std::endl;
                    break;
                case Resta:
                    std::cout << token.valor << "  Resta" << std::endl;
                    break;
                case Multiplicacion:
                    std::cout << token.valor << "  Multiplicacion" << std::endl;
                    break;
                case Division:
                    std::cout << token.valor << "  Division" << std::endl;
                    break;
                case Potencia:
                    std::cout << token.valor << "  Potencia" << std::endl;
                    break;
                case Variable:
                    std::cout << token.valor << "  Variable" << std::endl;
                    break;
                case ParentesisIzquierdo:
                    std::cout << token.valor << "  Parentesis Izquierdo" << std::endl;
                    break;
                case ParentesisDerecho:
                    std::cout << token.valor << "  Parentesis Derecho" << std::endl;
                    break;
                case Comentario:
                    std::cout << token.valor << "  Comentario" << std::endl;
                    break;
            }
        }
    }

    file.close();
}

int main() {
    std::string archivo = "expresiones.txt";
    lexerAritmetico(archivo);
    return 0;
}

