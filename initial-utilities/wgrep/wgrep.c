#include <stdio.h>
#include <stdlib.h>

int match(char *, char *);

void grep(char const *pattern, FILE *fd) {

    char *line = NULL;
    size_t len = 0;
    size_t nread;

    if (!fd) {
        while((nread = getline(&line, &len, stdin)) != -1) {
            if (match((char *)pattern, line))
                printf("%s", line);
        }
    }
    else {
        while((nread = getline(&line, &len, fd)) != -1) {
            if (match((char *)pattern, line))
                printf("%s", line);
        }
    }
}


int main(int argc, char const *argv[])
{
    if (argc <= 1) {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char const *pattern = argv[1];

    if (argc <= 2) {
        grep(pattern, NULL);
    }

    int count = 2;
    while (count < argc) {
        FILE *fd = fopen(argv[count++], "r");
        if (fd == NULL) {
            printf("wgrep: cannot open file\n");
            exit(1);
        }

        grep(pattern, fd);
        fclose(fd);
    }

    return 0;
}


// Not my code: Picked from xv6 version of grep
// Adding source loc: https://github.com/xenial-xerus/xv6-public/blob/master/grep.c


// Regexp matcher from Kernighan & Pike,
// The Practice of Programming, Chapter 9.

int matchhere(char*, char*);
int matchstar(int, char*, char*);

int
match(char *re, char *text)
{
  if(re[0] == '^')
    return matchhere(re+1, text);
  do{  // must look at empty string
    if(matchhere(re, text))
      return 1;
  }while(*text++ != '\0');
  return 0;
}

// matchhere: search for re at beginning of text
int matchhere(char *re, char *text)
{
  if(re[0] == '\0')
    return 1;
  if(re[1] == '*')
    return matchstar(re[0], re+2, text);
  if(re[0] == '$' && re[1] == '\0')
    return *text == '\0';
  if(*text!='\0' && (re[0]=='.' || re[0]==*text))
    return matchhere(re+1, text+1);
  return 0;
}

// matchstar: search for c*re at beginning of text
int matchstar(int c, char *re, char *text)
{
  do{  // a * matches zero or more instances
    if(matchhere(re, text))
      return 1;
  }while(*text!='\0' && (*text++==c || c=='.'));
  return 0;
}
