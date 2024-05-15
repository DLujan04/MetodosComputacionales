#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

enum TokenType {
    INTEGER,
    FLOAT,
    OPERATOR,
    IDENTIFIER,
    SPECIAL_SYMBOL,
    COMMENT,
    UNKNOWN
};

struct Token {
    string value;
    TokenType type;
};

vector<Token> lexerAritmetico(string archivo) {
    ifstream file(archivo);
    string line;
    vector<Token> tokens;

    regex integer_regex("^-?[0-9]+$");
    regex float_regex("^-?[0-9]*\\.[0-9]+([eE][-+]?[0-9]+)?$");
    regex operator_regex("^[=+\\-*/^]$");
    regex identifier_regex("^[a-zA-Z_][a-zA-Z0-9_]*$");
    regex special_symbol_regex("^[()]$");
    regex comment_regex("^//.*$");

    while (getline(file, line)) {
        istringstream iss(line);
        string word;
        bool inComment = false;
        while (getline(iss, word, ' ')) {
            if (!inComment && word.find("//") == 0) {
                inComment = true;
                continue;
            }
            if (inComment) {
                if (word.find("\n")!= string::npos) {
                    inComment = false;
                }
                continue;
            }
            for (char& c : word) {
                string str(1, c);
                Token token;
                token.value = str;
                if (regex_match(str, integer_regex)) {
                    token.type = INTEGER;
                } else if (regex_match(str, float_regex)) {
                    token.type = FLOAT;
                } else if (regex_match(str, operator_regex)) {
                    token.type = OPERATOR;
                } else if (regex_match(str, identifier_regex)) {
                    token.type = IDENTIFIER;
                } else if (regex_match(str, special_symbol_regex)) {
                    token.type = SPECIAL_SYMBOL;
                } else {
                    token.type = UNKNOWN;
                }
                tokens.push_back(token);
            }
        }
    }

    return tokens;
}

int main() {
    string archivo = "expresion.txt";
    cout << "Leyendo el archivo: " << archivo << endl;
    vector<Token> tokens = lexerAritmetico(archivo);

    cout << "Tokens encontrados: " << tokens.size() << endl;

    for (Token token : tokens) {
        cout << "Token: " << token.value << ", Tipo: ";
        switch (token.type) {
            case INTEGER: cout << "Entero"; break;
            case FLOAT: cout << "Real"; break;
            case OPERATOR: cout << "Operador"; break;
            case IDENTIFIER: cout << "Variable"; break;
            case SPECIAL_SYMBOL: cout << "Símbolo especial"; break;
            case COMMENT: cout << "Comentario"; break;
            case UNKNOWN: cout << "Desconocido"; break;
        }
        cout << endl;
    }

    return 0;
}

