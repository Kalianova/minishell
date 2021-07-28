#include <unistd.h>
#include <stdio.h>
#include <string.h>

void	my_test(char *s)
{
	write(1, s, strlen(s));
	write(1, "\n", 1);
	sleep(1);
}

void	test_one_cmd()
{
	my_test("ls -la");
	my_test("   ls   -la    ");
	my_test("grep main");
	my_test("cat \"main.c\"");
	my_test("|");
	my_test("|||");
	my_test(">>>>");
	my_test("<<<<<");
}

void	test_two_cmd()
{
	my_test("ls -la | grep main");
	my_test("   ls   -la   | grep    kek");
	my_test("cat \"main.c\" >>>>> grep \"asda\"");
	my_test("grep main ||| ls -la");
}

void	test_multi_pipe_cmd()
{
	my_test("ls -la | grep main | wc -w");
	my_test("   ls   -la   | grep    kek | wc -c");
}

int main()
{
	test_one_cmd();
	test_two_cmd();
	test_multi_pipe_cmd();
	return(0);
}