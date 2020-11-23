#include <stdio.h>
int main()
{
	char *str = "Hello World";
	while (*str != 0)
	{
		printf("%c", *str);
		str++;
	}
	printf("\n");
	//char * -> Error
	//char* will place string in the `read-only` parts of the memory
	//char[] put the literal string in `read-only` memory and copied to newly allocated memory on the stack
	char src[] = "Src String";
	char dst[] = "DST STRING";
	printf("%s\n%s\n", src, dst);
	int offset = 0;

	while (src[offset] != '\0')
	{
		printf("%d ",offset);
		fflush(stdout);
		dst[offset] = src[offset];
		++offset;
	}
	printf("\n");
	printf("%s\n%s\n", src, dst);
	return 0;
}
