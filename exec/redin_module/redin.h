# pragma once

# include "defines.h"
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

// # define BUFFER_SIZE 1024

void	redin(char *file, char *cmd, char *argv[]);
char	*read_file(char *file);
void	append_s(char **str1, char *str2);
int		ft_strlen(char *str);
