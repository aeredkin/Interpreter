#include "stdlib.h"
#include "readline/readline.h"
#include "json-c/json.h"

char *get_word(char **curpos) {
	char *afterword = strchr(*curpos, ' ');
	char *word;
	if (afterword == NULL)
		afterword = *curpos + strlen(*curpos);
	word = strndup(*curpos, afterword - *curpos);
	*curpos = afterword + 1;
	return word;
}

int main(int argc, char **argv) {
	char *str;
	char *word;
	char *curpos;
	struct json_object *com;
	struct json_object *args;
	struct json_object *jobj = json_object_new_array();
	printf("%s\n", "Введите строки с командами и аргументами через пробел, нажимая \"Enter\" в конце "
			"каждой строки.\nДля вывода результата и выхода введите \"EXIT\" и нажмите \"Enter\".");
	for (;;) {
		str = readline(NULL);
		if (str) {
			if (strcmp(str, "EXIT") == 0)
				break;
			curpos = str;
			word = get_word(&curpos);
			com = json_object_new_object();
			json_object_object_add(com, "command", json_object_new_string(word));
			free(word);
			args = json_object_new_array();
			while (curpos < str + strlen(str)) {
				word = get_word(&curpos);
				json_object_array_add(args, json_object_new_string(word));
				free(word);
			}
			json_object_object_add(com, "arguments", args);
        	free(str);
		}
		json_object_array_add(jobj, com);
	}
	free(str);
    printf("%s", json_object_to_json_string_ext(jobj, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY));
	return 0;
}
