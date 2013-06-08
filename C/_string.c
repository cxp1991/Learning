/*
*  Find "orig" in "str" and repacle it with "rep"
*/

char* replace_str(char *str, char *orig, char *rep)
{
	static char buffer[4096];
	char *p;
	char *p1 = buffer;
  
	strncpy(buffer,str,strlen(str));

	while (p = strstr (str,orig))
	{
		sprintf(p1 + (p-str), "%s%s", rep, p + strlen(orig));
		p1 = p1 + ((p - str) + strlen(rep));
		str = str + (p - str + strlen(orig));
	}		
	
	return buffer;
}

/*
*	Remove head blank
*/

char* remove_head_blank(char* str)
{
	while(*str == ' ' || *str == '\t')
		str++;
	return str;
}

/*
*	Remove head blank
*/

char* remove_tail_blank(char* str)
{

}

/*
*	Remove head & end blank
*/

char* remove_head_tail_blank(char* str)
{
	char *tmp1;

	remove_head_blank(str);
	remove tail_blank(str);
	return str;
}

