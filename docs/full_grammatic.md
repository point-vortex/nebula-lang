# Full grammatic

|Metasymbol|Definition|
|-|-|
|```=```|Defined as|
|```|```|Alternative|
|```[ x ]```|0 or 1 instance of the ```x```|
|```{ x }```|0 or more instances of the ```x```|
|```( x | y )```|Grouping: any of x or y|
|```Zxy```|Non terminal|
|```zxy```|Non terminal|
|```'1'```|Terminal|
|```"1"```|Terminal|

> Extended Backus–Naur form

```
Program = ProgramSegment 'void' 'main' '(' ')' DoSection ProgramSegment
ProgramSegment = {ContextVariableInitialization | FunctionDeclaration | FunctionDefinition | VariableInitialization}

IfStatement = 'if' '(' BoolExpr ')' DoBlock 1 ['else' DoBlock2]
DoBlock1 = DoBlock
DoBlock2 = DoBlock
ForStatement = for '(' [VariableInitialization | Assign | Expression] ';' [Expression] ';' [Expression | Assign] ')' DoBlock
WhileStatement = 'while' '(' Expression ')' DoBlock
DoWhileStatement = 'do' DoBlock 'while' '(' Expression ')'
ReturnStatement = 'return' [Expression]

DoBlock = DoSection | Statement
DoSection = '{' StatementsList '}'
StatementsList = Statement {Statement}
Statement = ((VariableInitialization | Assign | Expression) ';') | ForStatement | IfStatement | WhileStatement 
            | DoWhileStatement | ReturnStatement

Assign = ChainedAccessor '=' Expression

StructDefinitionShort = 'struct' Identifier ';'
StructDefinition = 'struct' Identifier '{' {VariableDeclaration ';'} '}' ';'

ChainedAccessor = Identifier {('.' Identifier) | ('[' Expression ']')} 

FunctionDefinition = FunctionPrototype ';'
FunctionDeclaration = FunctionPrototype DoSection
FunctionPrototype = (Type | VoidType) Identifier '(' [ {VariableDeclaration ','} VariableDeclaration] ')'
FunctionCall = Identifier '(' [(ChainedAccessor | Const) {',' (ChainedAccessor | Const)}] ')'

ContextVariableInitialization = ContextVariableDeclaration ['=' (Expression | BraceEnclosedList)]
VariableInitialization = VariableDeclaration ['=' (Expression | BraceEnclosedList)]
BraceEnclosedList = '{' [(ChainedAccessor | Const) {',' (ChainedAccessor | Const)}] '}'
ContextVariableDeclaration = ContextSpecifier Type Identifier
VariableDeclaration = ['const'] Type Identifier

Expression = (TermWithUnaryOperator | ParenthesesExpression) {BinaryOperator (TermWithUnaryOperator | ParenthesesExpression)}
ParenthesesExpression = '(' Expression ')'
TermWithUnaryOperator = Term | ([LvalueUnaryOperator] Lvalue) | (Lvalue [LvalueUnaryOperator]) 
                             | ([RvalueUnaryOperator] Rvalue) | (Rvalue [RvalueUnaryOperator])
Term = Rvalue | Lvalue
Rvalue = Const | ParenthesesExpression | FunctionCall
Lvalue = ChainedAccessor

Identifier = Letter {Letter | Digit}
Type = 'int' | 'unsigned int' | 'long' | 'unsigned long' | 'float' | 'double' | 'bool' | 'vec2' | 'vec3' | 'vec4' 
       | 'mat2' | 'mat3' | 'mat4' | 'dict' | 'spreadsheet' | Identifier
VoidType = 'void'

Const = IntConst | UnsignedIntConst | LongConst | UnsignedLongConst | FloatConst | DoubleConst | StringConst | BoolConst
UnsignedLongConst = UnsignedInt 'ul'
UnsignedIntConst = UnsignedInt 'u'
LongConst = IntConst 'l'
IntConst = [Sign]UnsignedInt
FloatConst = DoubleConst 'f'
DoubleConst = [Sign] (UnsignedReal | UnsignedRealExponentialNotation)
BoolConst = 'true' | 'false'

Sign = '+' | '-'
UnsignedRealExponentialNotation = (UnsignedReal | UnsignedInt) 'e' ['+' | '-'] UnsignedInt
UnsignedReal = (’.’ UnsignedInt) | (UnsignedInt ’.’) | (UnsignedInt ’.’ UnsignedInt)
UnsignedInt = Digit{Digit}
StringLiteral = '"' {StringAlphabet} '"'

Operator = BinaryOperator | UnaryOperator
BinaryOperator = '+' | '-' | '*' | '/' | '=' | '==' | '<=' | '>=' | '<' | '>' | '!=' | '||' | '&&' | '<<' | '>>' | '^' 
                 | '|' | '&' | '+=' | '-=' | '*=' | '/='
LvalueUnaryOperator = '++' | '--' 
RvalueUnaryOperator = '-' | '+' | LvalueUnaryOperator

EmbeddedFunction = 'min' | 'max' | 'rand' | 'randint' | 'cross' | 'dot' | 'normalize' | 'sin' | 'cos' | 'tan' | 'ctg' 
                   | 'asin' | 'acos' | 'atan' | 'actg' | 'radians' | 'degrees' | 'pow' | 'sqrt' | 'sqr' | 'log' | 'ln'
                   | 'floor' | 'ceil' | 'round' | 'curl' | 'gaussian'
KeyWord = 'bool' | 'int' | 'long' | 'float' | 'double' | 'string' | 'void' | 'vec2' | 'vec3' | 'vec4' | 'mat2' | 'mat3' 
          | 'mat4' | 'dict' | 'spreadsheet' | 'return'
          | 'true' | 'false' | 'do' | 'while' | 'for' | 'if' | 'else' | 'const'
Alphabet = StringAlphabet | '"'
StringAlphabet = Letter | Digit | SpecialSymbol 
Letter = LowercaseLetter | UppercaseLetter
LowercaseLetter = 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' 
                  | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'
UppercaseLetter = 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H' | 'I' | 'J' | 'K' | 'L' | 'M' | 'N' | 'O' | 'P' | 'Q' 
                  | 'R' | 'S' | 'T' | 'U' | 'V' | 'W' | 'X' | 'Y1' | 'Z'
Digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
SpecialSymbol = '.' | ',' | ':' | ';' | '(' | ')' | '{' | '}' | '[' | ']' | '=' | '+' | '-' | '*' | '/' | '<' | '>' 
                | '!' | '^' | '_' | WhiteSpace | EndOfLine
WhiteSpace = ' ' | '\t'
EndOfLine = '\n' | '\r' | '\r\n' | '\n\r'
EndOfFile = '\0'

ContextSpecifier = InContextSpecifier | OutContextSpecifier

InContextSpecifier = 'in'
OutContextSpecifier = 'out'
```
