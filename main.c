#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_STRING_SIZE 256
#define MAX_ARGS_NUMBER 100
#define MAX_ARG_SIZE 250
#define MAX_COMMANDS_NUMBER_IN_LINE 10

int echo(int argc, char* argv[]) {
	for (int i = 1; i < argc; ++i) {
		printf("%s%c", argv[i], i == argc - 1 ? '\n' : ' ');
	}
	return argc - 1;
}

int retcode(int argc, char* argv[]) {
	printf("%d\n", argc);
	return 0;
}

void implement_command(char* command_args[], int* args_count)
{
	if (strcmp(command_args[0], "echo") == 0)
	{
		echo(*args_count + 1, command_args);
	}
	else if (strcmp(command_args[0], "retcode") == 0)
	{
		retcode(*args_count, command_args);
	}
}

void parse_and_implement_command(char* command, int* args_count, char* string_context)
{
	char* command_args[MAX_ARGS_NUMBER];
	char* command_arg;
	int i = 0, k = 0, args_number = 0;
	command_arg = strtok_s(command, " ", &string_context);
	if (command_arg == NULL)
	{
		return;
	}
	command_args[0] = command_arg;
	while (command_arg != NULL)
	{
		if (i != 0)
		{
			command_args[i] = command_arg;
			args_number++;
		}
		i++;
		command_arg = strtok_s(NULL, " ", &string_context);
	}
	if (args_number > 0)
	{
		*args_count = args_number;
	}
	implement_command(command_args, args_count);
}

int main(int argc, char* argv[]) {
	char input_string[MAX_STRING_SIZE];
	char* command;
	int i, k, cm_count = 0;
	int args_count_pointer = 0;
	char* command_context = NULL;
	char* string_context = NULL;
	while (fgets(input_string, MAX_STRING_SIZE, stdin) != NULL)
	{
		command = strtok_s(input_string, ";\n", &string_context);
		cm_count = 0;
		while (command != NULL)
		{
			if (cm_count != 0)
			{
				command = strtok_s(NULL, ";\n", &string_context);
			}
			if (command != NULL)
			{
				parse_and_implement_command(command, &args_count_pointer, string_context);
			}
			cm_count++;
		}
	}
	return 0;
}