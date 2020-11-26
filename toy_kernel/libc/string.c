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