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
```glsl
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
