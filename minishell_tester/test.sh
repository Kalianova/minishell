cd ..
make
cd minishell_tester/
gcc main.c -o tester.out
clear
./tester.out | ../minishell
