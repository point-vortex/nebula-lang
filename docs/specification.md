# 1.1 Description

# 1.2 Syntax
## Literals
### Syntax
```
Const = IntConst | FloatConst | StringConst | BoolConst
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
