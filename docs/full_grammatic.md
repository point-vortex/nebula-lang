# Full grammatic
```

IfStatement = 'if' '(' BoolExpr ')' DoBlock 1 ['else' DoBlock2]
DoBlock1 = DoBlock
DoBlock2 = DoBlock
ForStatement = for '(' [VariableInitialization | Assign] ';' [Expression] ';' [Assign] ')' DoBlock
WhileStatement = 'while' '(' [Expression] ')' DoBlock
DoWhileStatement = 'do' DoBlock 'while' '(' Expression ')'

DoBlock = DoSection | Statement
DoSection = '{' StatementsList '}'
StatementsList = Statement {Statement}
Statement = ((VariableInitialization | Assign | Expression) ';') | ForStatement | IfStatement | WhileStatement | DoWhileStatement

Assign = ChainedAccessor '=' Expression

StructDefinitionShort = 'struct' Identifier ';'
StructDefinition = 'struct' Identifier '{' [ {VariableDeclaration ';'} VariableDeclaration] '}' ';'

ChainedAccessor = Identifier {('.' Identifier) | ('[' Expression ']')} 

FunctionDefinition = FunctionPrototype ';'
FunctionDeclaration = FunctionPrototype DoSection
FunctionPrototype = (Type | VoidType) Identifier '(' [ {VariableDeclaration ','} VariableDeclaration] ')'
FunctionCall = Identifier '(' [ {(ChainedAccessor | Const) ','} (ChainedAccessor | Const)] ')'

VariableInitialization = VariableDeclaration ['=' Expression]
VariableDeclaration = Type Identifier

Expression = TermWithUnaryOperator {BinaryOperator TermWithUnaryOperator}
ParenthesesExpression = '(' Expression ')'
TermWithUnaryOperator = ([UnaryOperator] Term) | (Term [UnaryOperator]) //TODO: fix rvalue problem
Term = FunctionCall | ChainedAccessor | Const | ParenthesesExpression

Identifier = Letter {Letter | Digit}
Type = 'int' | 'unsigned int' | 'long' | 'unsigned long' | 'float' | 'double' | 'bool' | 'vec2' | 'vec3' | 'vec4' | 'mat2' | 'mat3' 
       | 'mat4' | dict //TODO: add struct type
VoidType = 'void'

Const = IntConst | UnsignedIntConst | LongConst | UnsignedLongConst | FloatConst | DoubleConst | StringConst | BoolConst
UnsignedLongConst = UnsignedInt 'ul'
UnsignedIntConst = UnsignedInt 'u'
LongConst = IntConst 'l'
IntConst = [Sign]UnsignedInt
FloatConst = DoubleConst 'f'
DoubleConst = [Sign] (UnsignedReal | UnsignedRealExponentialNotation)

Sign = '+' | '-'
UnsignedRealExponentialNotation = (UnsignedReal | UnsignedInt) 'e' ['+' | '-'] UnsignedInt
UnsignedReal = UnsignedInt '.' UnsignedInt
UnsignedInt = Digit{Digit}
BoolConst = 'true' | 'false'
// TODO: change to "_asd72.asd"
StringLiteral = '"' {Letter | Digit} '"'

Operator = BinaryOperator | UnaryOperator
BinaryOperator = '+' | '-' | '*' | '/' | '=' | '==' | '<=' | '>=' | '<' | '>' | '!=' | '||' | '&&' | '<<' | '>>' | '^' | '|' | '&' 
                 | '+=' | '-=' | '*=' | '/='
UnaryOperator = '++' | '--' | '-' | '+'

EmbeddedFunction = 'min' | 'max' | 'rand' | 'randint' | 'cross' | 'dot' | 'normalize' | 'sin' | 'cos' | 'tan' | 'ctg' | 'asin' | 'acos' 
                    | 'atan' | 'actg' | 'radians' | 'degrees' | 'pow' | 'sqrt' | 'sqr' | 'log' | 'ln' | 'floor' | 'ceil' | 'round' | 'curl' 
                    | 'gaussian'
KeyWord = 'bool' | 'int' | 'long' | 'float' | 'double' | 'string' | 'void' | 'vec2' | 'vec3' | 'vec4' | 'mat2' | 'mat3' | 'mat4' | 'dict' 
           | 'true' | 'false' | 'do' | 'while' | 'for' | 'if' | 'else' | 'const'
Letter = 'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' | 'r' | 's' | 't' | 'u' | 'v' 
         | 'w' | 'x' | 'y' | 'z'
Digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
SpecialSymbol = '.' | ',' | ':' | ';' | '(' | ')' | '{' | '}' | '[' | ']' | '=' | '+' | '-' | '*' | '/' | '<' | '>' | '!' | '^' 
                | WhiteSpace | EndOfLine
WhiteSpace = ' ' | '\t'
EndOfLine = '\n' | '\r' | '\r\n' | '\n\r'
EndOfFile = '\0'
```
