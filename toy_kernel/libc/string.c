void append(char s[], char data)
{
    while (*s++ != '\0')
        ;
    --s;
    *s = data;
    *(s + 1) = '\0';
}

void delete (char s[])
{
    if (*s == '\0')
        return;
    while (*s++ != '\0')
        ;
    --s;
    --s;
    *s = '\0';
}

char to_lower(char data)
{
    if (data >= 'A' && data <= 'Z')
        return data + 'a' - 'A';
    return data;
}
int cmpOneWord(char *word, char *str)
{
    while (*word != '\0')
        if (*word++ != *str++)
            return 0;
    return 1;
}