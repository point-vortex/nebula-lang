# 1.1 Description

# 1.2 Syntax
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
Sign = '+' | '-'
UnsignedRealExponentialNotation = (UnsignedReal | UnsignedInt) 'e' ['+' | '-'] UnsignedInt
UnsignedReal = UnsignedInt '.' UnsignedInt
UnsignedInt = Digit{Digit}
BoolConst = 'true' | 'false'
StringLiteral = '"' {Letter | Digit} '"'
Digit = '0' | '1' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9'
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
Statement = ((Declaration | Assign | FunctionCall) ';') | ForStatement | IfStatement | WhileStatement | DoWhileStatement
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

```
