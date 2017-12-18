# infix-prefix
A program that asks the user to enter a math expression in infix
or prefix notation, converts it to the other notation, and prints
out the result. The program will run until the user enters 'x' to
quit.

## Notes:
- User must use integers 0 to 9 in their mathematical expression

- User must enter valid mathematical operators: (,),^,*,/,+,-

- User must enter a valid mathematical expression in either
infix or prefix notation

## Sample Tests: 
Order of operations
```
	       Infix: 1*2+3/4
	       Prefix: +*12/34

	       Prefix: +*12/34
	       Infix: ((1*2)+(3/4))
```         

Parentheses within expression
```
	       Infix: 1*(2+3)/4
	       Prefix: /*1+234

	       Prefix: /*1+234
	       Infix: ((1*(2+3))/4)
```        

Parentheses with order of operations inside
```
	       Infix: 1*(2+3/4)
	       Prefix: *1+2/34

	       Prefix: *1+2/34
	       Infix: (1*(2+(3/4)))
```

Parentheses outside expression	
 ```
	       Infix: ((1*2)+(3/4))
	       Prefix: +*12/34
```
