# 1.1 Description

# 1.2 Syntax
## General symbols
```
Alphabet = StringAlphabet | '"'
StringAlphabet = Letter | Digit | SpecialSymbol 

Letter =        'a' | 'b' | 'c' | 'd' | 'e' | 'f' | 'g' | 'h' | 'i' | 'j' | 'k' | 'l' | 'm' | 'n' | 'o' | 'p' | 'q' 
                | 'r' | 's' | 't' | 'u' | 'v' | 'w' | 'x' | 'y' | 'z'
                
Digit =         '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'

SpecialSymbol = '.' | ',' | ':' | ';' | '(' | ')' | '{' | '}' | '[' | ']' | '=' | '+' | '-' | '*' | '/' | '<' | '>' 
                | '!' | '^' | '_' | WhiteSpace | EndOfLine
                
WhiteSpace =    ' ' | '\t'
EndOfLine =     '\n' | '\r' | '\r\n' | '\n\r'
EndOfFile =     '\0'
```
## Literals
### Syntax
```
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
StringAlphabet = Letter | Digit | SpecialSymbol
```
### Restrictions
- Each literal must have a type.
- The value of the literal must be in the range of representative values for its type.
### Examples
```c
12
-12
12u
12l
-12l
12ul
1.12
-1.12
1.12d
-1.12d
2e+12
2e12
2e-12
2.0e12
-2.0e12
"hello"
true
false
```
## Instructions
### Syntax
```
DoSection = '{' StatementsList '}'
StatementsList = Statement {Statement}
Statement = ((VariableInitialization | Assign | Expression) ';') 
            | ForStatement | IfStatement | WhileStatement | DoWhileStatement | ReturnStatement
```
### Overview
Statements define algorithm that must be executed in program.
### Semantics
The instructions are executed sequentially in writing order until a branch operator or a loop operator is encountered.
### Example
```glsl
void main() {
    int foo = 20;
    foo = 22;
    if (foo > 20) {
        foo = 20;
    }
    int result = foo;
}
```

## Expressions
### Syntax
```
Expression = (TermWithUnaryOperator | ParenthesesExpression) 
             {BinaryOperator (TermWithUnaryOperator | ParenthesesExpression)}
ParenthesesExpression = '(' Expression ')'
TermWithUnaryOperator = Term | ([LvalueUnaryOperator] Lvalue) | (Lvalue [LvalueUnaryOperator]) 
                             | ([RvalueUnaryOperator] Rvalue) | (Rvalue [RvalueUnaryOperator])
Term = Rvalue | Lvalue
Rvalue = Const | ParenthesesExpression | FunctionCall
Lvalue = ChainedAccessor
ChainedAccessor = Identifier {('.' Identifier) | ('[' Expression ']')} 
Identifier = Letter {Letter | Digit}
```

### Overview
An expression is a sequence of operators and operands that determines the order in which a value is calculated.
Operators have following priorities:

|a|a|
|-|-|
|a|a|

A sequence of two or more operators with the same priority is associative.

### Restrictions
- The type of each variable must be defined.
- Repeating the declared variable causes an error at compilation time.
- Using an undeclared variable causes an error at compilation time.

### Semantics
- Each expression result has a type determined by its shape and meaning.
- The variable becomes important in the assignment instructions.
- If two types are incompatible - the compiler will try to cast left right operand to left operand type. 
  If it's impossible - you will get compilation error.
- Operations are performed on the priority of operators.

### Example
```c
int a = 2 + 2;
int b = (2 + 3) * 2 / 3 + 2;
bool c = 2 > 3 && 3 < 2;
float d = 2.f + 2u + 3ul;
```

## Variable declaration
### Syntax
```
VariableInitialization = VariableDeclaration ['=' (Expression | BraceEnclosedList)]
BraceEnclosedList = '{' [(ChainedAccessor | Const) {',' (ChainedAccessor | Const)}] '}'
VariableDeclaration = ['const'] Type Identifier
Type = 'int' | 'unsigned int' | 'long' | 'unsigned long' | 'float' | 'double' | 'bool' | 'vec2' | 'vec3' | 'vec4' 
       | 'mat2' | 'mat3' | 'mat4' | 'dict' | 'spreadsheet' | Identifier
```

### Overview
A variable declaration specifies a set of variable identifiers that can be used in a program.

### Restrictions
- Each identifier must be declared only once in scope.
- Brace enclosed list can be used only to initialize arrays and structs.  
- Quantity of brace enclosed list members must match the members quantity of the structure that it initializes.
- The type of each brace enclosed list member must be able to cast to corresponding data structure member.

### Semantics
- Identifier in scope can shadow other identifier in outer scope if their names are same.
- Identifier can be initialized in declaration.
- If identifier isn't initialized - it will get default value.

### Example
```glsl
vec3 a;
vec3 b = vec3(1.0f, 2.0f, 3);
```
Variable ```a``` is shadowed:
```glsl
void main() {
    int a = 0;
    {
        vec3 a = vec3(0, 0, 0);
        a.x = 0;
    }
    a = 2;
}
```
```glsl
struct MyStruct {
    int foo;
    vec3 bar;
};

MyStruct baz = {10, vec3(1, 0, 0)}
```

## Context input
### Syntax
```
ContextVariableInitialization = ContextVariableDeclaration ['=' (Expression | BraceEnclosedList)]
ContextVariableDeclaration = (FlowSpecifier | ContextSpecifier) Type Identifier

FlowSpecifier = InFlowSpecifier | OutFlowSpecifier
ContextSpecifier = InContextSpecifier | OutContextSpecifier

InContextSpecifier = 'in'
OutContextSpecifier = 'out'
InFlowSpecifier = 'inflow' ('1' - '5')
OutFlowSpecifier = 'outflow' ('1' - '5')
```
### Overview
// TODO: come up with design of flows workflow.
### Restrictions
### Semantics
TODO: finish | Problem with access to flow variables.
### Example
```glsl
struct Inflow1Type {
    vec3 point;
};
inflow1 Inflow1Type;
```


## Assignment instruction
### Syntax
```
Assign = ChainedAccessor '=' Expression
```

### Overview
### Restrictions
- Rvalue type must be same or able to be cast to lvalue type.
### Semantics
- Lvalue is a reference to a place where the value of the variable with specified identifier is stored.
- Rvalue has value with a type of calculated expression.
### Example
```c
int a;
a = 10 + 20;
a = 10.f;
```

## Branching operator
### Syntax
```
IfStatement = 'if' '(' BoolExpr ')' DoBlock 1 ['else' DoBlock2]
DoBlock1 = DoBlock
DoBlock2 = DoBlock
DoBlock = DoSection | Statement
```

### Overview
- The body of the DoBlock1 loop operator is executed once if the BoolExpr condition is satisfied.
- The body of the DoBlock2 loop operator is executed once if the BoolExpr condition is NOT met.
### Semantics
- If the condition is satisfied, that is the condition is true - then DoBlock1 is executed, if not - then DoBlock2.

### Example
```c
int foo = 10;
if (foo > (foo + 1)) {
    print("Everything is good! :D");
} else {
    print("Something is wrong! :(");
}
```

## For loop statement
### Syntax
```
ForStatement = for '(' FirstExpression ';' SecondExpression ';' ThirdExpression ')' DoBlock
FirstExpression = [VariableInitialization | Assign | Expression]
SecondExpression = [Expression]
ThirdExpression = [Expression | Assign]
DoBlock = DoSection | Statement
```

### Overview
The body of the DoBlock is executed multiple times or is not executed at all depending on the SecondExpression condition.

### Semantics
- Before the first iteration, the value of FirstExpression is calculated.
- The ThirdExpression is executed after each iteration.
- The FirstExpression is executed before the loop.
- Iteration continues if SecondExpression calculated value is truthy.
- SecondExpression value calculates before each iteration.

### Example
```c
for (int i = 0; i < 10; i++) {
    print(i);
}
```

## While loop statement
### Syntax
```
WhileStatement = 'while' '(' Condition ')' DoBlock
Condition = Expression
DoBlock = DoSection | Statement
```
### Overview
The body of the DoBlock is executed multiple times or is not executed at all depending on the Condition condition.

### Semantics
- Iteration continues if Condition calculated value is truthy.
- Condition value calculates before each iteration.

### Example
```c
int i = 0;
while (i < 10) {
    i++;
    print(i);
}

while(true) 
    print(0);
```

## Do while loop statement
### Syntax
```
DoWhileStatement = 'do' DoBlock 'while' '(' Condition ')'
Condition = Expression
DoBlock = DoSection | Statement
```
### Overview
The body of the DoBlock is executed multiple times or is not executed at all depending on the Condition condition.

### Semantics
- Iteration continues if Condition calculated value is truthy.
- Condition value calculates after each iteration.

### Example
```c
int i = 0;
do {
    i++;
    print(i);
} while (i < 10);
```

## For loop statement
### Syntax
### Overview
### Restrictions
### Semantics
### Example
