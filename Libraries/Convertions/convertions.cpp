#include "convertions.h"

String convertions::charToString(char *valor)      
{
  return String(valor);
}

char* convertions::stringToChar(String valor)
{
	  char charBuf [valor.length()+1];
	  valor.toCharArray(charBuf,valor.length());
	  charBuf [valor.length()+1] = '\0';
	  return charBuf;
}

char* convertions::substr(int inicio,int largo,char *ch)
{
    char subbuff [largo+1];
    memcpy( subbuff, &ch[inicio], largo );
    subbuff[largo+1] = '\0';
    return subbuff;
}

char *convertions::concat(char *char1,char *char2)
{
		int len = strlen(char1) + strlen(char2) + 1;
		char res[len] ;
		strlcpy (res,char1,len);
		strlcat(res, char2, len);
		res[len] = '\0';
		return res;
}

char* convertions::intToChar (int i)
{
  	String str;  //declaring string
  	str=String(i); //converting integer into a string
  	char b[str.length()+1];   //declaring character array
  	str.toCharArray(b,2);
  	b[str.length()+1] = '\0';
  	return b;
	}

/*
char * convertions::split (char * str, char separador)
{
	
//char str[] = "this is a test";
  
  /*  char *test[sizeof(strtok(str, separador))];
    if(sizeof(test) > 0)
    {
        test[0] = strtok(str, " "); // Splits spaces between words in str
        printf ("%s\n",test[0]); // Writes "this"
        for(int i = 1; i < sizeof(strtok(str, " ")); i++)
        {
            test[i] = strtok (NULL, " ,.-");
            printf ("%s\n",test[i]); // Writes "is"
        }
    }
 
    
    return 0;
 
}
   */