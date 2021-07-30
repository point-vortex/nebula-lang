# Full grammatic
```

IfStatement = 'if' '(' BoolExpr ')' DoBlock 1 'else' DoBlock2
DoBlock1 = DoBlock
DoBlock2 = DoBlock
ForStatement = for '('  ')' // ---------- finish

DoBlock = ('{' StatementList '}') | Statement
DoSection = '{' StatementsList '}'
StatementsList = Statement {Statement}
Statement = ((Declaration | Assign | FunctionCall) ';') | ForStatement | IfStatement | WhileStatement | DoWhileStatement

Assign = Identifier ’=’ Expression
Initialization = Type IdentifierDeclaration
IdentifierDeclaration = Ident [‘=’ Expression] // fix
Type = 'int' | 'unsigned int' | 'long' | 'unsigned long' | 'float' | 'double' | 'bool' | 'vec2' | 'vec3' | 'vec4' | 'mat2' | 'mat3' 
       | 'mat4' | dict //TODO: add struct type

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
StringLiteral = '"' {Letter | Digit} '"'

Operator = '+' | '-' | '*' | '/' | '=' | '==' | '<=' | '>=' | '<' | '>' | '!=' | '||' | '&&' | '<<' | '>>' | '^' | '|' | '&'

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
