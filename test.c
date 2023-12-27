# include "get_next_line.h"

// join and free
char    *join_free(char *buffer, char *buf)
{
        char    *temp;

        temp = ft_strjoin(buffer, buf);
        free(buffer);
        return (temp);
}

// delete line find
char    *ft_next(char *buffer)
{
        int             i;
        int             j;
        char    *line;

        i = 0;
        // find len of first line
        while (buffer[i] && buffer[i] != '\n')
                i++;
        // if eol == \0 return NULL
        if (!buffer[i])
        {
                free(buffer);
                return (NULL);
        }
        // len of file - len of firstline + 1
        line = calloc((strlen(buffer) - i + 1), sizeof(char));
        i++;
        j = 0;
        // line == buffer
        while (buffer[i])
                line[j++] = buffer[i++];
        free(buffer);
        return (line);
}

// take line for return
char    *ft_line(char *buffer)
{
        char    *line;
        int             i;

        i = 0;
        // if no line return NULL
        if (!buffer[i])
                return (NULL);
        // go to the eol
        while (buffer[i] && buffer[i] != '\n')
                i++;
        // malloc to eol
        line = calloc(i + 2, sizeof(char));
        i = 0;
        // line = buffer
        while (buffer[i] && buffer[i] != '\n')
        {
                line[i] = buffer[i];
                i++;
        }
        // if eol is \0 or \n, replace eol by \n
        if (buffer[i] && buffer[i] == '\n')
                line[i++] = '\n';
        return (line);
}

char    *read_file(int fd, char *res)
{
        char    *buffer;
        int             byte_read;


        if (!res)
                res = calloc(1, 1);
        buffer = calloc(BUFFER_SIZE + 1, sizeof(char));
        byte_read = 1;
        while (byte_read > 0)
        {
                byte_read = read(fd, buffer, BUFFER_SIZE);
                if (byte_read == -1)
                {
                        free(buffer);
                        return (NULL);
                }
                buffer[byte_read] = 0;
                res = join_free(res, buffer);
                if (strchr(buffer, '\n'))
                        break ;
        }
        free(buffer);
        return (res);
}

char    *get_next_line(int fd)
{
        static char     *buffer;
        char            *line;

        // error handling
        if (fd < 0 || BUFFER_SIZE <= 0)
                return (NULL);
        buffer = read_file(fd, buffer);
        if (!buffer)
                return (NULL);
        line = ft_line(buffer);
        buffer = ft_next(buffer);
        return (line);
}
#include <stdio.h>
int main()
{
        int fd = open("test", O_RDONLY);

        char *f =  get_next_line(fd);
        printf("%s",f);
        // printf("--------------------\n");
        close(fd);
}