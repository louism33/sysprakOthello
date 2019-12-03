a university project - client to play reversi / othello
=======
# Alex the Friendly AI
Course project for System Praktikum, Winter Semester 2019 / 2020 at the LMU <br>
<br>
Reversi client and AI. <br>
<br>

to run tests

`make test `

to run get perft results to depth

`make perft DEPTH=(depth)`


to run valgrind:

`make -B && rm -f VALGRINDTESTLOG.log && valgrind --log-file=VALGRINDTESTLOG.log --leak-check=full --trace-children=yes ./sysprak-client TEST`

Written by : 

    Zhenhan Gao
    Yufan Lu
    Marlene Eder
    Louis Mackenzie-Smith

