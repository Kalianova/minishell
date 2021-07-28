cd ..
make
cd minishell_tester/
gcc main.c -o tester
clear
./tester | ../minishell
