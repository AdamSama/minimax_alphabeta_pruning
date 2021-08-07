# A Minmax Solver
## The program solves a minmax file and supports alpha-beta pruning
The input file is graph of minimax tree. </br>
A tree like this:
![alt text](https://github.com/AdamSama/minimax_alphabeta_pruning/blob/master/ex1.png.jpg?raw=true)
</img src="ex1.png" style="height: 100px; width:100px;"/>
would have a tree file like this: </br>
a: [a1, a2, a3]</br>
a1: [b, c]</br>
a3: [xy, wx]</br>
a2: [b19, b29]</br>
b=4</br>
c=3</br>
b19=5</br>
b29=2</br>
xy=-1</br>
wx=8</br>
</br>
using the following rules: </br>
* Each line should contain a node description
* A node label should be any string with alphanumeric characters
* A leaf node will have:
    * Sub Using n=v An integer v indicating a score (final or possibly from a heuristic evaluator) associated with a node label n
   An internal node will use a colon and comma separated [] indicating parent child labels
    * Sub Using n:[n1,n2,...] two or more node labels indicating child nodes
* Valid input is a tree or DAG (no cycles) with a value at every leaf node and a single root (node with no incoming edges).
<a/>
Output should have the format:
max(a) chooses a2 for 2
or 
min(a) chooses a1 for 3

To compile the minimax program, simply type 
```bash
make
```
The followings are possible arguments for the program:
    -v verbose mode.
    -ab alpha-beta pruning.
One of the following argument is required:
    min let the root player to be a Min player.
    max let the root player to be a Max player.
File name is also required:
    eg. example.txt
Examples for the compilation:
```bash
    ./minmax -v -ab min example.txt
```

To clean ./minmax, type 
```bash
make cleanm
```

