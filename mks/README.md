# Конструирование контактных схем

Реализован алгоритм построения контактных схем. В данном алгоритме по тупиковым ДНФ строится бор и соответствующее контактное дерево со склеенными листьями, далее производится склеивание контактов.

Пример:

Input:<br>
00000001100001101001011111101001<br>

Output:<br>
25597929<br>
33<br>
0 1<br>
0 2 2 0 0 5 2 1 0 12 1 1 1 4 5 1 1 7 5 0 1 10 5 1 1 11 5 0 1 14 5 0 1 16 5 1 1 17 5 1 1 17 4 1 1 19 5 1 1 21 5 0 1 21 4 0 1 22 5 0 2 3 3 1 2 15 1 1 3 4 4 1 5 6 3 0 5 8 1 0 5 20 1 1 6 7 4 0 8 9 3 1 9 10 4 0 9 11 4 1 12 13 3 0 12 18 3 1 13 14 4 0 15 16 4 1 15 17 3 1 18 19 4 1 20 21 3 0 20 22 4 0
