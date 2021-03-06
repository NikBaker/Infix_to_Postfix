# Лабораторная работа по дисциплине "Основы построения трансляторов"
## Щучкин Никита А-13а-19
#

### **1.	Задание.**  
    Разработать алгоритм и реализовать программу для перевода 
    арифметических выражений в постфиксную запись и их вычисления. 
    Для арифметических выражений допустимы операции: 
    сложения, вычитания, умножения, деления. 
    Арифметическое выражение может содержать идентификаторы, 
    значения которых задаются при запуске.  

### **2.	Входные данные.**  
    Строка, представляющая собой арифметическое выражение в инфиксной записи. 
    Может содержать операторы +, -, *, /; скобки, операнды могут быть либо 
    идентификаторами(из букв и цифр, первая обязательно буква), 
    либо вещественными константами.

### **3.	Выходные данные.**  
    Строка, представляющая собой арифметическое выражение в постфиксной записи 
    (знак ~ в постфиксной записи обозначает унарный минус), 
    а также результат вычисления выражения.

### **4.	Алгоритм.**  

1. Константы и переменные кладутся в формируемую запись в порядке их появления в исходном массиве. 
2. При появлении операции в исходном массиве:  
	a) если в стеке нет операций или верхним элементом стека является 	
    открывающая скобка, операция кладется в стек;  	

	b) если новая операция имеет больший приоритет, чем верхняя операция в стеке, то новая операция кладется в стек;  	

	c) если новая операция имеет меньший или равный приоритет, чем верхняя операция в стеке, то операции, находящиеся в стеке, до ближайшей открывающей скобки или до операции с приоритетом меньшим, чем у новой операции, перекладываются в формируемую запись, а новая операция кладется в стек.  
3. Открывающая скобка кладется в стек. 
4. Закрывающая скобка выталкивает из стека в формируемую запись все операции до ближайшей открывающей скобки, открывающая скобка удаляется из стека. 
5. После того, как мы добрались до конца исходного выражения, операции, оставшиеся в стеке, перекладываются в формируемое выражение.


### **5.	Тесты.**  

~~~  
--------------------------------------------------------------------------
                                  TEST1
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
a                                   |       a
Enter the value for a: 1            |       Result of expression: 1  
                                    |       End with succes!  
--------------------------------------------------------------------------
                                  TEST2
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
-a                                  |       a ~
Enter the value for a: 3            |       Result of expression: -3  
                                    |       End with succes!  
--------------------------------------------------------------------------
                                  TEST3
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
a+b-3.5                             |       a b + 3.5 -
Enter the value for a: 5.7          |       Result of expression: 9.3  
Enter the value for b: 7.1          |       End with succes!  
--------------------------------------------------------------------------
                                  TEST4
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Division by zero!
a/b+2                               |       End with error!
Enter the value for a: 5            |       
Enter the value for b: 0            |         
--------------------------------------------------------------------------
                                  TEST5
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Wrong format of number
1a                                  |       End with error!
--------------------------------------------------------------------------
                                  TEST6
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
(a1+b1)*3                           |       a1 b1 + 3 *
Enter the value for a: 2            |       Result of expression: 21
Enter the value for b: 5            |       End with succes!
--------------------------------------------------------------------------
                                  TEST7
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Wrong expression
(a+b))*3                            |       Wrong format  
Enter the value for a: 1            |       (the number of left brackets  
Enter the value for b: 2            |       is not equal the number of  
                                    |       right brackets)
                                    |       End with error!
--------------------------------------------------------------------------
                                  TEST8
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
-(-a)                               |       a ~ ~
Enter the value for a: 3            |       Result of expression: 3
                                    |       End with succes!
--------------------------------------------------------------------------
                                  TEST9
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
-a*(b+c)+(g-f)/3                    |       a ~ b c + * g f - 3 / +
Enter the value for a: 3            |       Result of expression: -13
Enter the value for b: 2.5          |       End with succes!  
Enter the value for c: 2.5          |
Enter the value for g: 9            |
Enter the value for f: 3            |
--------------------------------------------------------------------------
                                  TEST10
--------------------------------------------------------------------------
INPUT                               |       OUTPUT  
--------------------------------------------------------------------------
Enter the expression:               |       Postfix form:
(a+b)*(a-b)                         |       a b + a b - *
Enter the value for a: 4            |       Result of expression: 7
Enter the value for b: 3            |       End with succes!
~~~ 
