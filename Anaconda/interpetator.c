#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef enum {
    TOKEN_ADD, TOKEN_SUB,
    TOKEN_MUL, TOKEN_DIV,
    TOKEN_ASSIGN, TOKEN_SEMI,
    TOKEN_LPAREN, TOKEN_RPAREN,
    TOKEN_LBRACE, TOKEN_RBRACE,
    TOKEN_ID, TOKEN_PRINT,
    TOKEN_IF, TOKEN_WHILE,
    TOKEN_FOR, TOKEN_INT,
    TOKEN_DOUBLE, TOKEN_STRING,
    TOKEN_MAGIC, TOKEN_UNKNOWN,
    TOKEN_ELSE, TOKEN_DCUETON, 
    TOKEN_LTHEN, TOKEN_GTHEN, 
    TOKEN_LSTRING, TOKEN_EQ,
    TOKEN_NEQ, TOKEN_LTE,
    TOKEN_GTE, TOKEN_COMMA
} TokenList;

typedef struct {
    TokenList token;
    char* name;
} Token;

typedef struct {
    int size;
    int cap;
    Token* arr;
} Rows;

// Abstract Syntax Tree

typedef enum {
    NODE_TYPE_ASSIGNMENT,
    NODE_TYPE_NUMBER,
    NODE_TYPE_STRING,
    NODE_TYPE_VAR_DECL,
    NODE_TYPE_BINARY_OP,
    NODE_TYPE_VARIABLE,
    NODE_TYPE_PRINT,
    NODE_TYPE_BLOCK,
    NODE_TYPE_IF,
    NODE_TYPE_WHILE,
    NODE_TYPE_FOR
} NodeType;

typedef struct {
    NodeType type;
} ASTNode;

typedef struct {
    ASTNode** statements;
    int size;
    int cap;
} ProgramNode;

typedef struct {
    ASTNode base;
    char* value;
} NumberNode;

typedef struct {
    ASTNode base;
    char* value;
} StringNode;

typedef struct {
    ASTNode base;
    ASTNode* left;
    Token op;
    ASTNode* right;
} BinaryOpNode;

typedef struct {
    ASTNode base;
    char* varName;
} VarNode;

typedef struct {
    ASTNode base;
    TokenList varType;
    char* varName;
    ASTNode* value;
} VarDeclNode;

typedef struct {
    ASTNode base;
    ASTNode** arguments;
    int argCount;
    int argCap;
} PrintNode;

typedef struct {
    ASTNode base;
    ASTNode** statements;
    int size;
    int cap;
} BlockNode;

typedef struct {
    ASTNode base;
    ASTNode* condition;
    BlockNode* thenBlock;
    BlockNode* elseBlock;
} IfNode;

typedef struct {
    ASTNode base;
    ASTNode* condition;
    BlockNode* body;
} WhileNode;

typedef struct {
    ASTNode base;
    ASTNode* intitializer;
    ASTNode* condition;
    ASTNode* increment;
    BlockNode* body;
} ForNode;

typedef struct {
    ASTNode base;
    VarNode* variable;
    ASTNode* expression;
} AssignmentNode;

typedef struct  {
    Rows* rows;
    int lineCount;
    int currentRow;
    int currentCol;
} Parser;

// Interpretator

typedef enum { 
    VAL_TYPE_BOOL,
    VAL_TYPE_NULL,
    VAL_TYPE_NUMBER,
    VAL_TYPE_STRING
} ValueType;

typedef struct {
    ValueType type;
    union {
        bool boolean;
        double number;
        char* string;
    } as;
} Value;

typedef struct {
    char* name;
    Value value;
} Variable;

typedef struct {
    Variable* variables;
    int size;
    int cap;
} SymbolTable;

// helping functions

int countLines(char*);

void* createArray(size_t);

char* readFile(char*);

bool isSpase(char);

bool isDigit(char);

bool isAlpha(char);

Token* pushToken(Rows*, Token*);

void pushStatementToBlock(BlockNode*, ASTNode*);

void pushStatementToProgram(ProgramNode*, ASTNode*);

void addArgumentToPrintNode(PrintNode*, ASTNode*);

// AST constructor functions

ASTNode* createAsssignmentNode(VarNode*, ASTNode*);

ASTNode* createNumberNode(char*);

ASTNode* createStringNode(char*);

ASTNode* createVarDeclNode(TokenList, char*, ASTNode*);

ASTNode* createBinaryOpNode(ASTNode*, Token, ASTNode*);

ASTNode* createPrintNode(void);

BlockNode* createBlockNode(void);

ASTNode* createIfNode(ASTNode*, BlockNode*, BlockNode*);

ASTNode* createWhileNode(ASTNode*, BlockNode*);

ASTNode* createForNode(ASTNode*, ASTNode*, ASTNode*, BlockNode*);

ASTNode* createVarNode(char*);

// parser functions

Token currentToken(Parser*);

void advance(Parser*);

bool isEnd(Parser*);

void creatAndpushToken(Rows*, TokenList, const char*, int);

TokenList getKeywordToken(const char*);

Rows* tokenizing(char*, Rows*, size_t);

void searchUnknown(Rows*, size_t);

ProgramNode* parse(Rows*, int);

ASTNode* parseStatement(Parser*);

ASTNode* parseComparisonExpression(Parser*);

ASTNode* parseAdditiveExperssion(Parser*);

ASTNode* parseMultiplicativeExpression(Parser*);

ASTNode* parsePrimaryExpression(Parser*);

ASTNode* parseAssignmentExpression(Parser*);

ASTNode* parseExpression(Parser*);

BlockNode* parseBlock(Parser*);

ASTNode* parseVariableDeclaration(Parser*, bool);

ASTNode* parsePrintStatement(Parser*);

ASTNode* parseIfStatement(Parser*);

ASTNode* parseWhileStatement(Parser*);

ASTNode* parseForStatement(Parser*);

// Interpretator functions

void tableInit(SymbolTable*);

void tableDefine(SymbolTable*, char*, Value);

void tableAssigne(SymbolTable*, char*, Value);

Value tableGet(SymbolTable*, char*);

void tableFree(SymbolTable*);

Value makeNumberValue(double);

Value makeBoolValue(bool);

Value makeNullValue(void);

void printValue(Value);

Value evalueateExpression(ASTNode*, SymbolTable*);

bool isTruthy(Value);

void executeStatement(ASTNode*, SymbolTable*);

void executeProgram(ProgramNode*);

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Add filename!!!\n");
        exit(1);
    }
    
    char* buffer = readFile(argv[1]);
    int lines = countLines(buffer);

    Rows* rowsArray = (Rows*) createArray(sizeof(Rows) * lines);
    rowsArray = tokenizing(buffer, rowsArray, lines);
    searchUnknown(rowsArray, lines);

    ProgramNode* programAST = parse(rowsArray, lines);
    executeProgram(programAST);

    return 0;
}

// helping functions

int countLines(char* buffer)
{
    int count = 1;

    while (*buffer) {
        if (*buffer == '\n') {
            ++count;
        }

        ++buffer;
    }

    return count;
}

void* createArray(size_t size)
{
    void* res = calloc(1, size);

    if (!res) {
        perror("");
        exit(errno);
    }

    return res;
}

char* readFile(char* fileName)
{
    FILE* fptr = fopen(fileName, "r");
    int size = 0;

    if (!fptr) {
        perror("");
        exit(errno);
    }

    fseek(fptr, 0, SEEK_END);
    size = ftell(fptr);

    char* buffer = (char*) malloc(sizeof(char) * (size + 1));

    if (!buffer) {
        perror("");
        exit(errno);
    }
    
    fseek(fptr, 0, SEEK_SET);
    fread(buffer, size, 1, fptr);

    buffer[size] = '\0';
    fclose(fptr);

    return buffer;
}

bool isSpase(char sym)
{
    return sym == ' ' || sym == '\t' || sym == '\r';
}

bool isDigit(char sym)
{
    return sym >= 48 && sym <= 57;
}

bool isAlpha(char sym)
{
    return (sym >= 65 && sym <= 90) || (sym >= 97 && sym <= 122) || sym == '_';
}

Token* pushToken(Rows* arr, Token* element)
{
    if (arr->size >= arr->cap) {
        int newCap = arr->cap == 0 ? 8 : arr->cap * 2;
        arr->arr = (Token*) realloc(arr->arr, sizeof(Token) * newCap);

        if (!arr->arr) {
            perror("");
            exit(errno);
        }
        
        arr->cap = newCap;
    }
    
    arr->arr[arr->size] = *element;
    arr->arr[arr->size].name = strdup(element->name);
    arr->size++;

    return arr->arr;
}

void pushStatementToBlock(BlockNode* block, ASTNode* statement)
{
    if (block->size >= block->cap) {
        int newCap = block->cap == 0 ? 8 : block->cap * 2;
        block->statements = (ASTNode**) realloc(block->statements, sizeof(ASTNode*) * newCap);

        if (!block->statements) {
            perror("");
            exit(errno);
        }

        block->cap = newCap;
    }

    block->statements[block->size++] = statement;

    return;
}

void pushStatementToProgram(ProgramNode* program, ASTNode* statement)
{
    if (program->size >= program->cap) {
        int newCap = program->cap == 0 ? 8 : program->cap * 2;
        program->statements = (ASTNode**) realloc(program->statements, sizeof(ASTNode*) * newCap);

        if (!program->statements) {
            perror("");
            exit(errno);
        }

        program->cap = newCap;
    }

    program->statements[program->size++] = statement;

    return;
}

void addArgumentToPrintNode(PrintNode* node, ASTNode* arg)
{
    if (node->argCount >= node->argCap) {
        int newCap = node->argCap == 0 ? 8 : node->argCap * 2;

        node->arguments = (ASTNode**) realloc(node->arguments, sizeof(ASTNode*) * newCap);

        if (!node->arguments) {
            perror("");
            exit(errno);
        }

        node->argCap = newCap;
    }

    node->arguments[node->argCount++] = arg;

    return;
}

// AST constructor functions

ASTNode* createAsssignmentNode(VarNode* var, ASTNode* expression)
{
    AssignmentNode* node = (AssignmentNode*) createArray(sizeof(AssignmentNode));

    node->base.type = NODE_TYPE_ASSIGNMENT;
    node->variable = var;
    node->expression = expression;

    return (ASTNode*) node;
}

ASTNode* createNumberNode(char* value)
{
    NumberNode* node = (NumberNode*) createArray(sizeof(NumberNode));

    node->base.type = NODE_TYPE_NUMBER;

    node->value = strdup(value);

    return (ASTNode*) node;
}

ASTNode* createStringNode(char* value)
{
    StringNode* node = (StringNode*) createArray(sizeof(StringNode));

    node->base.type = NODE_TYPE_STRING; 
    node->value = strdup(value);

    return (ASTNode*) node;
}

ASTNode* createVarDeclNode(TokenList varType, char* varName, ASTNode* valueNode)
{
    VarDeclNode* node = (VarDeclNode*) createArray(sizeof(VarDeclNode));

    node->base.type = NODE_TYPE_VAR_DECL;

    node->varType = varType;
    node->varName = strdup(varName);
    node->value = valueNode;

    return (ASTNode*) node;
}

ASTNode* createBinaryOpNode(ASTNode* left, Token op, ASTNode* right)
{
    BinaryOpNode* node = (BinaryOpNode*) createArray(sizeof(BinaryOpNode));   

    node->base.type = NODE_TYPE_BINARY_OP;
    
    node->left = left;
    node->op = op;
    node->right = right;

    return (ASTNode*) node;
}

ASTNode* createPrintNode(void)
{
    PrintNode* node = (PrintNode*) createArray(sizeof(PrintNode));

    node->base.type = NODE_TYPE_PRINT;
    node->argCount = 0;
    node->argCap = 0;
    node->arguments = NULL;
    
    return (ASTNode*) node;
}

BlockNode* createBlockNode(void)
{
    BlockNode* block = (BlockNode*) createArray(sizeof(BlockNode));        

    block->base.type = NODE_TYPE_BLOCK;

    block->size = 0;
    block->cap = 0;
    block->statements = NULL;

    return block;
}

ASTNode* createIfNode(ASTNode* condition, BlockNode* thenBlock, BlockNode* elseBlock)
{
    IfNode* node = (IfNode*) createArray(sizeof(IfNode));

    node->base.type = NODE_TYPE_IF;

    node->condition = condition;
    node->thenBlock = thenBlock;
    node->elseBlock = elseBlock;

    return (ASTNode*) node;
}

ASTNode* createWhileNode(ASTNode* condition, BlockNode* body)
{
    WhileNode* node = (WhileNode*) createArray(sizeof(WhileNode));

    node->base.type = NODE_TYPE_WHILE;

    node->condition = condition;
    node->body = body;

    return (ASTNode*) node;
}

ASTNode* createForNode(ASTNode* intitializer, ASTNode* condition, ASTNode* increment, BlockNode* body)
{
    ForNode* node = (ForNode*) createArray(sizeof(ForNode));  

    node->base.type = NODE_TYPE_FOR;

    node->intitializer = intitializer;
    node->condition = condition;
    node->increment = increment;
    node->body = body;

    return (ASTNode*) node;
}

ASTNode* createVarNode(char* varName)
{
    VarNode* node = (VarNode*) createArray(sizeof(VarNode));
    node->base.type = NODE_TYPE_VARIABLE;
    node->varName = strdup(varName);

    return (ASTNode*) node;
}

// parser functions 

Token currentToken(Parser* parser)
{
    return parser->rows[parser->currentRow].arr[parser->currentCol];
}

void advance(Parser* parser)
{
    parser->currentCol++;

    while (parser->currentRow < parser->lineCount &&
        (parser->rows[parser->currentRow].size == 0 || parser->currentCol >= parser->rows[parser->currentRow].size)) {
        parser->currentRow++;
        parser->currentCol = 0;
    }

    return;
}

bool isEnd(Parser* parser)
{
    return parser->currentRow >= parser->lineCount;
}


void createAndpushToken(Rows* row, TokenList type, const char* name, int len)
{
    Token tok;
    char* tokenName = (char*) malloc(sizeof(char) * (len + 1));

    if (!tokenName) {
        perror("");
        exit(1);
    }

    strncpy(tokenName, name, len);
    tokenName[len] = '\0';

    tok.token = type;
    tok.name = tokenName;

    pushToken(row, &tok);
    free(tokenName);

    return;
}

TokenList getKeywordToken(const char* word)
{
    if (!strcmp(word, "print")) return TOKEN_PRINT;
    if (!strcmp(word, "ete")) return TOKEN_IF;
    if (!strcmp(word, "kam")) return TOKEN_ELSE;
    if (!strcmp(word, "while")) return TOKEN_WHILE;
    if (!strcmp(word, "for")) return TOKEN_FOR;
    if (!strcmp(word, "tiv")) return TOKEN_INT;
    if (!strcmp(word, "sahox")) return TOKEN_DOUBLE;
    if (!strcmp(word, "tox")) return TOKEN_STRING;

    return TOKEN_ID;    
}

Rows* tokenizing(char* buffer, Rows* arr, size_t size)
{
    char* start = NULL;
    int indexLine = 0;

    while (*buffer != '\0' && indexLine < size) {
        if (isSpase(*buffer)) {
            ++buffer;
            continue;
        }

        if (*buffer == '\n') {
            ++indexLine;
            ++buffer;
            continue;
        }

        char symbol = *buffer;

        if (symbol == '=' && *(buffer + 1) == '=') {
            createAndpushToken(&arr[indexLine], TOKEN_EQ, "==", 2);
            buffer += 2;
            continue;
        }

        if (symbol == '!' && *(buffer + 1) == '=') {
            createAndpushToken(&arr[indexLine], TOKEN_NEQ, "!=", 2);
            buffer += 2;
            continue;
        }

        if (symbol == '<' && *(buffer + 1) == '=') {
            createAndpushToken(&arr[indexLine], TOKEN_LTE, "<=", 2);
            buffer += 2;
            continue;
        }

        if (symbol == '>' && *(buffer + 1) == '=') {
            createAndpushToken(&arr[indexLine], TOKEN_GTE, ">=", 2);
            buffer += 2;
            continue;
        }

        if (symbol == ',') {
            createAndpushToken(&arr[indexLine], TOKEN_COMMA, ",", 1);
            ++buffer;
            continue;
        }

        if (strchr("=;(){}$~#@<>", symbol)) {
            TokenList type;

            switch (symbol) {
                case '=': type = TOKEN_ASSIGN; break;
                case ';': type = TOKEN_SEMI; break;
                case '(': type = TOKEN_LPAREN; break;
                case ')': type = TOKEN_RPAREN; break;
                case '{': type = TOKEN_LBRACE; break;
                case '}': type = TOKEN_RBRACE; break;
                case '$': type = TOKEN_ADD; break;
                case '~': type = TOKEN_SUB; break;
                case '#': type = TOKEN_MUL; break;
                case '@': type = TOKEN_DIV; break;
                case '<': type = TOKEN_LTHEN; break;
                case '>': type = TOKEN_GTHEN; break;
                default: type = TOKEN_UNKNOWN; break;
            }

            createAndpushToken(&arr[indexLine], type, &symbol, 1);
            ++buffer;
            continue;
        }

        if (*buffer == '"') {
            createAndpushToken(&arr[indexLine], TOKEN_DCUETON, "\"", 1);
            ++buffer;

            start = buffer;

            while (*buffer != '"' && *buffer != '\0') ++buffer;

            if (buffer > start) {
                createAndpushToken(&arr[indexLine], TOKEN_LSTRING, start, buffer - start);
            }

            if (*buffer == '"') {
                createAndpushToken(&arr[indexLine], TOKEN_DCUETON, "\"", 1);
                ++buffer;
            }

            continue;
        }

        if (isDigit(*buffer)) {
            start = buffer;
            
            while (isDigit(*buffer)) ++buffer;

            createAndpushToken(&arr[indexLine], TOKEN_MAGIC, start, buffer - start);
            continue;
        }

        if (isAlpha(*buffer)) {
            start = buffer;

            while (isAlpha(*buffer) || isDigit(*buffer)) ++buffer;

            int len = buffer - start;
            char* word = (char*) malloc(sizeof(char) * (len + 1));

            if (!word) {
                perror("");
                exit(errno);
            }

            strncpy(word, start, len);
            word[len] = '\0';

            TokenList type = getKeywordToken(word);
            createAndpushToken(&arr[indexLine], type, word, len);

            free(word);
            continue;
        }

        createAndpushToken(&arr[indexLine], TOKEN_UNKNOWN, buffer, 1);
        ++buffer;
    }

    return arr;
}

void searchUnknown(Rows* arr, size_t size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < arr[i].size; ++j) {
            if (arr[i].arr[j].token == TOKEN_UNKNOWN) {
                printf("IN %d LINE IS UNDIFINED EXPRESSION!\n", i + 1);
                exit(1);
            }
        }
    }

    return;
}

ProgramNode* parse(Rows* rows, int lineCount)
{
    Parser parser;        
    
    parser.rows = rows;
    parser.lineCount = lineCount;
    parser.currentRow = 0;
    parser.currentCol = 0;

    ProgramNode* program = (ProgramNode*) createArray(sizeof(ProgramNode));

    program->size = 0;
    program->cap = 0;
    program->statements = NULL;

    while (!isEnd(&parser)) {
        ASTNode* stmt = parseStatement(&parser);

        if (stmt) {
            pushStatementToProgram(program, stmt);
        }
    }

    return program;
}

ASTNode* parseStatement(Parser* parser)
{
    if (isEnd(parser)) return NULL;

    Token tok = currentToken(parser);

    switch (tok.token) {
        case TOKEN_INT:
        case TOKEN_DOUBLE:
        case TOKEN_STRING:
            return parseVariableDeclaration(parser, true);

        case TOKEN_PRINT:
            return parsePrintStatement(parser);

        case TOKEN_IF:
            return parseIfStatement(parser);

        case TOKEN_WHILE:
            return parseWhileStatement(parser);

        case TOKEN_FOR:
            return parseForStatement(parser);

        case TOKEN_LBRACE:
            return (ASTNode*) parseBlock(parser);

        default:
            ASTNode* expr = parseExpression(parser);
            
            if (currentToken(parser).token != TOKEN_SEMI) {
                printf("Error on line %d. Expected ';' character:\n", parser->currentRow + 1);
                exit(1);
            }
            
            advance(parser);
            return expr;
    }
}

ASTNode* parseComparisonExpression(Parser* parser)
{
    ASTNode* left = parseAdditiveExperssion(parser);

    while (!isEnd(parser) &&
        (currentToken(parser).token == TOKEN_EQ || currentToken(parser).token == TOKEN_NEQ ||
        currentToken(parser).token == TOKEN_LTHEN || currentToken(parser).token == TOKEN_GTHEN ||
        currentToken(parser).token == TOKEN_LTE || currentToken(parser).token == TOKEN_GTE)) {

        Token op = currentToken(parser);
        advance(parser);

        ASTNode* right = parseAdditiveExperssion(parser);
        left = createBinaryOpNode(left, op, right);
    }

    return left;
}

ASTNode* parseAdditiveExperssion(Parser* parser)
{
    ASTNode* left = parseMultiplicativeExpression(parser); 

    while (!isEnd(parser) &&
        (currentToken(parser).token == TOKEN_ADD || currentToken(parser).token == TOKEN_SUB)) {
        Token op = currentToken(parser);
        advance(parser);

        ASTNode* right = parseMultiplicativeExpression(parser);
        left = createBinaryOpNode(left, op, right);
    }

    return left;
}

ASTNode* parseMultiplicativeExpression(Parser* parser)
{
    ASTNode* left = parsePrimaryExpression(parser);

    while (!isEnd(parser) &&
        (currentToken(parser).token == TOKEN_MUL || currentToken(parser).token == TOKEN_DIV)) {
        Token op = currentToken(parser);
        advance(parser);
        
        ASTNode* right = parsePrimaryExpression(parser);
        left = createBinaryOpNode(left, op, right);
    }

    return left;
}

ASTNode* parsePrimaryExpression(Parser* parser)
{
    Token tok = currentToken(parser); 

    if (tok.token == TOKEN_MAGIC) {
        ASTNode* node = createNumberNode(tok.name);
        advance(parser);
        
        return node;
    }

    if (tok.token == TOKEN_ID) {
        ASTNode* node = createVarNode(tok.name);
        advance(parser);

        return node;
    }

    if (tok.token == TOKEN_DCUETON) {
        advance(parser);

        ASTNode* node;

        if (currentToken(parser).token == TOKEN_DCUETON) {
            node = createStringNode("");
        }

        else if (currentToken(parser).token == TOKEN_LSTRING) {
            node = createStringNode(currentToken(parser).name);
            advance(parser);
        } else {
            printf("Error on line %d. Expected string content after quote\n", parser->currentRow + 1);
            exit(1);
        }

        if (currentToken(parser).token != TOKEN_DCUETON) {
            printf("Error on line %d. Line not closed with \"\n", parser->currentRow + 1);
            exit(1);
        }

        advance(parser);
        return node;
    }

    if (tok.token == TOKEN_LPAREN) {
        advance(parser);
        ASTNode* expr = parseExpression(parser);

        if (currentToken(parser).token != TOKEN_RPAREN) {
            printf("Error on line %d. Expected a closing parenthesis ')':\n", parser->currentRow + 1);
            exit(1);
        }

        advance(parser);
        return expr;
    }

    printf("Error on line %d. Expected a number, variable, string, or '('\n", parser->currentRow + 1);
    exit(1); 
}

ASTNode* parseAssignmentExpression(Parser* parser)
{
    ASTNode* left = parseComparisonExpression(parser);

    if (!isEnd(parser) && currentToken(parser).token == TOKEN_ASSIGN) {
        advance(parser);

        ASTNode* right = parseAssignmentExpression(parser);

        if (left->type != NODE_TYPE_VARIABLE) {
            printf("Error on line %d. The left side of the assignment must be a variable\n", parser->currentRow + 1);
            exit(1);
        }

        return createAsssignmentNode((VarNode*) left, right);
    }

    return left;
}

ASTNode* parseExpression(Parser* parser)
{
    return parseAssignmentExpression(parser);    
}

BlockNode* parseBlock(Parser* parser)
{
    if (currentToken(parser).token != TOKEN_LBRACE) {
        printf("Error on line %d. Expected '{' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);
    BlockNode* block = createBlockNode();

    while (currentToken(parser).token != TOKEN_RBRACE && !isEnd(parser)) {
        ASTNode* stmt = parseStatement(parser);

        if (stmt) {
            pushStatementToBlock(block, stmt);
        }
    }

    if (currentToken(parser).token != TOKEN_RBRACE) {
        printf("Error on line %d. Expected '}' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);
    return block;
}

ASTNode* parseVariableDeclaration(Parser* parser, bool consumeSemicolon)
{
    TokenList varType = currentToken(parser).token;    
    advance(parser);

    Token idToken = currentToken(parser);

    if (idToken.token != TOKEN_ID) {
        printf("Error on line %d. Expected variable name\n", parser->currentRow + 1);
        exit(1);
    }

    char* varName = strdup(idToken.name);
    advance(parser);

    if (currentToken(parser).token != TOKEN_ASSIGN) {
        printf("Error on line %d. Expected '=' sign.\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    ASTNode* valueNode = parseExpression(parser);

    if (consumeSemicolon) {
        if (currentToken(parser).token != TOKEN_SEMI) {
            printf("Error on line %d. Expected a ';' character.\n", parser->currentRow + 1);
            exit(1);
        }

        advance(parser);
    }

    ASTNode* VarDeclNode = createVarDeclNode(varType, varName, valueNode);

    free(varName);
    return VarDeclNode;
}

ASTNode* parsePrintStatement(Parser* parser)
{
    advance(parser);

    if (currentToken(parser).token != TOKEN_LPAREN) {
        printf("Error on line %d. Expected '(' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    PrintNode* printNode = (PrintNode*) createPrintNode();

    if (currentToken(parser).token != TOKEN_RPAREN) {
        addArgumentToPrintNode(printNode, parseExpression(parser));

        while (!isEnd(parser) && currentToken(parser).token == TOKEN_COMMA) {
            advance(parser);
            addArgumentToPrintNode(printNode, parseExpression(parser));
        }
    }

    if (currentToken(parser).token != TOKEN_RPAREN) {
        printf("Error on line %d. Expected ')' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    if (currentToken(parser).token != TOKEN_SEMI) {
        printf("Error on line %d. Expected ';' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    return (ASTNode*) printNode;
}

ASTNode* parseIfStatement(Parser* parser)
{
    advance(parser);

    if (currentToken(parser).token != TOKEN_LPAREN) {
        printf("Error on line %d. Expected '(' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    ASTNode* condition = parseExpression(parser);
    
    if (currentToken(parser).token != TOKEN_RPAREN) {
        printf("Error on line %d. Expected ')' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    BlockNode* thenBlock = parseBlock(parser);
    BlockNode* elseBlock = NULL;

    if (!isEnd(parser) && currentToken(parser).token == TOKEN_ELSE) {
        advance(parser);

        if (currentToken(parser).token == TOKEN_LBRACE) {
            elseBlock = parseBlock(parser);
        } else {
            printf("Error on line %d. Expected '{' character:\n", parser->currentRow + 1);
            exit(1);
        }
    }

    return createIfNode(condition, thenBlock, elseBlock);
}

ASTNode* parseWhileStatement(Parser* parser)
{
    advance(parser);    

    if (currentToken(parser).token != TOKEN_LPAREN) {
        printf("Error on line %d. Expected '(' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    ASTNode* condition = parseExpression(parser);

    if (currentToken(parser).token != TOKEN_RPAREN) {
        printf("Error on line %d. Expected ')' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);
    BlockNode* body = parseBlock(parser);

    return createWhileNode(condition, body);    
}

ASTNode* parseForStatement(Parser* parser)
{
    ASTNode* intitializer = NULL;
    ASTNode* condition = NULL;
    ASTNode* increment = NULL;

    advance(parser);

    if (currentToken(parser).token != TOKEN_LPAREN) {
        printf("Error on line %d. Expected '(' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    Token initialTok = currentToken(parser);

    if (initialTok.token == TOKEN_INT || 
        initialTok.token == TOKEN_DOUBLE ||
        initialTok.token == TOKEN_STRING) {

        intitializer = parseVariableDeclaration(parser, false);
    }

    else if (currentToken(parser).token != TOKEN_SEMI) {
        intitializer = parseExpression(parser);
    }

    if (currentToken(parser).token != TOKEN_SEMI) {
        printf("Error on line %d. Expected ';' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    if (currentToken(parser).token != TOKEN_SEMI) {
        condition = parseExpression(parser);
    }

    if (currentToken(parser).token != TOKEN_SEMI) {
        printf("Error on line %d. Expected ';' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);

    if (currentToken(parser).token != TOKEN_RPAREN) {
        increment = parseExpression(parser);
    }

    if (currentToken(parser).token != TOKEN_RPAREN) {
        printf("Error on line %d. Expected ')' character:\n", parser->currentRow + 1);
        exit(1);
    }

    advance(parser);
    BlockNode* body = parseBlock(parser);

    return createForNode(intitializer, condition, increment, body);
}

// Interpretator functions

void tableInit(SymbolTable* table)
{
    table->size = 0;
    table->cap = 0;
    table->variables = NULL;

    return;
}

void tableDefine(SymbolTable* table, char* name, Value value)
{
    if (table->size >= table->cap) {
        int new_cap = table->cap == 0 ? 8 : table->cap * 2;
        
        table->variables = (Variable*) realloc(table->variables, sizeof(Variable) * new_cap);

        if (!table->variables) {
            perror("");
            exit(errno);
        }
        
        table->cap = new_cap;
    }

    table->variables[table->size].name = strdup(name);
    table->variables[table->size].value = value;
    table->size++;

    return;
}

void tableAssigne(SymbolTable* table, char* name, Value value)
{
    for (int i = 0; i < table->size; ++i) {
        if (!strcmp(table->variables[i].name, name)) {
            table->variables[i].value = value;
            return;
        }
    }

    printf("Error: Attempted assignment to undeclared variable '%s'.\n", name);
    exit(1);
}

Value tableGet(SymbolTable* table, char* name)
{
    for (int i = 0; i < table->size; ++i) {
        if (!strcmp(table->variables[i].name, name)) {
            return table->variables[i].value;
        }
    }

    printf("Error: Undeclared variable '%s':\n", name);
    exit(1);
}

void tableFree(SymbolTable* table)
{
    for (int i = 0; i < table->size; ++i) {
        free(table->variables[i].name);

        if (table->variables[i].value.type == VAL_TYPE_STRING) {
            free(table->variables[i].value.as.string);
        }
    }

    free(table->variables);
    tableInit(table);

    return;
}

Value makeNumberValue(double number)
{
    Value val;

    val.type = VAL_TYPE_NUMBER;
    val.as.number = number;

    return val;
}

Value makeBoolValue(bool boolean)
{
    Value val;

    val.type = VAL_TYPE_BOOL;
    val.as.boolean = boolean;

    return val;
}

Value makeNullValue(void)
{
    Value val;
    
    val.type = VAL_TYPE_NULL;
    val.as.number = 0;

    return val;
}

void printValue(Value val)
{
    switch (val.type) {
        case VAL_TYPE_NUMBER:
            double num = val.as.number;
            
            if (num == (long long)num) {
                printf("%lld\n", (long long)num);
            } else {
                printf("%f\n", num);
            }

            break;

        case VAL_TYPE_STRING:
            printf("%s\n", val.as.string);
            break;

        case VAL_TYPE_BOOL:
            printf("%s\n", val.as.boolean ? "true" : "false");
            break;

        case VAL_TYPE_NULL:
            printf("null\n");
            break;
    }
}

Value evalueateExpression(ASTNode* node, SymbolTable* table)
{
    switch (node->type) {
        case NODE_TYPE_NUMBER: {
            return makeNumberValue(atof(((NumberNode*)node)->value));
        }

        case NODE_TYPE_STRING: {
            Value val;
            
            val.type = VAL_TYPE_STRING;
            val.as.string = strdup(((StringNode*)node)->value);

            return val;
        }

        case NODE_TYPE_VARIABLE: {
            return tableGet(table, ((VarNode*)node)->varName);
        }

        case NODE_TYPE_BINARY_OP: {
            BinaryOpNode* opNode = (BinaryOpNode*) node;

            Value left = evalueateExpression(opNode->left, table);
            Value right = evalueateExpression(opNode->right, table);

            switch (opNode->op.token) {
                case TOKEN_ADD: 
                    return makeNumberValue(left.as.number + right.as.number);

                case TOKEN_SUB:
                    return makeNumberValue(left.as.number - right.as.number);

                case TOKEN_MUL:
                    return makeNumberValue(left.as.number * right.as.number);

                case TOKEN_DIV:
                    return makeNumberValue(left.as.number / right.as.number);

                // boolean operators
                
                case TOKEN_GTHEN:
                    return makeBoolValue(left.as.number > right.as.number);

                case TOKEN_LTHEN:
                    return makeBoolValue(left.as.number < right.as.number);

                case TOKEN_GTE:
                    return makeBoolValue(left.as.number >= right.as.number);

                case TOKEN_LTE:
                    return makeBoolValue(left.as.number <= right.as.number);

                case TOKEN_EQ:
                    return makeBoolValue(left.as.number == right.as.number);

                case TOKEN_NEQ:
                    return makeBoolValue(left.as.number != right.as.number);

                default:
                    printf("Unknown two-seat operator։\n");
                    exit(1);
            }

        }

        case NODE_TYPE_ASSIGNMENT: {
            AssignmentNode* assignNode = (AssignmentNode*) node;
            Value value = evalueateExpression(assignNode->expression, table);
            tableAssigne(table, assignNode->variable->varName, value);
            break;
        }

        default: 
            printf("Unknown expression type:\n");
            exit(1);
    }    
}

bool isTruthy(Value value)
{
    switch (value.type) {
        case VAL_TYPE_NULL: return false;
        case VAL_TYPE_BOOL: return value.as.boolean;
        case VAL_TYPE_NUMBER: return value.as.number != 0;
        case VAL_TYPE_STRING: return strlen(value.as.string) > 0;
        default: return false;
    }
}

void executeStatement(ASTNode* node, SymbolTable* table)
{
    if (node == NULL) return;

    switch (node->type) {
        case NODE_TYPE_VAR_DECL: {
            VarDeclNode* declNode = (VarDeclNode*) node;
            Value value = evalueateExpression(declNode->value, table);
            tableDefine(table, declNode->varName, value);
            break;
        }

        case NODE_TYPE_ASSIGNMENT: {
            AssignmentNode* assignNode = (AssignmentNode*) node;
            Value value = evalueateExpression(assignNode->expression, table);
            tableAssigne(table, assignNode->variable->varName, value);
            break;
        }

        case NODE_TYPE_PRINT: {
            PrintNode* printNode = (PrintNode*) node;

            for (int i = 0; i < printNode->argCount; ++i) {
                Value val = evalueateExpression(printNode->arguments[i], table);
                
                printValue(val);

                if (i < printNode->argCount - 1) {
                    printf(" ");
                }
            }

            printf("\n");
            break;
        }

        case NODE_TYPE_BLOCK: {
            BlockNode* blockNode = (BlockNode*) node;

            for (int i = 0; i < blockNode->size; ++i) {
                executeStatement(blockNode->statements[i], table);
            }

            break;
        }

        case NODE_TYPE_IF: {
            IfNode* ifNode = (IfNode*) node;

            Value condition = evalueateExpression(ifNode->condition, table);

            if (isTruthy(condition)) {
                executeStatement((ASTNode*)ifNode->thenBlock, table);
            }

            else if (ifNode->elseBlock != NULL) {
                executeStatement((ASTNode*)ifNode->elseBlock, table);
            }

            break;
        }

        case NODE_TYPE_WHILE: {
            WhileNode* whileNode = (WhileNode*) node;

            while (isTruthy(evalueateExpression(whileNode->condition, table))) {
                executeStatement((ASTNode*)whileNode->body, table);
            }

            break;
        }

        case NODE_TYPE_FOR: {
            ForNode* forNode = (ForNode*) node;

            if (forNode->intitializer) {
                executeStatement(forNode->intitializer, table);
            }

            while (true) {
                if (forNode->condition) {
                    if (!isTruthy(evalueateExpression(forNode->condition, table))) {
                        break;
                    }
                }

                executeStatement((ASTNode*)forNode->body, table);

                if (forNode->increment) {
                    evalueateExpression(forNode->increment, table);
                }
            }

            break;
        }

        default:
            evalueateExpression(node, table);
            break;
    }
}

void executeProgram(ProgramNode* program)
{
    SymbolTable globalTable;
    tableInit(&globalTable);

    for (int i = 0; i < program->size; ++i) {
        executeStatement(program->statements[i], &globalTable);
    }

    tableFree(&globalTable);
}
