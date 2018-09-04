//importing the necessary libraries
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>


//function prototypes registration here.
int 	findLength(char *sentence);
void 	delimitAndReverse(char* sentence, char delimiter, int sentenceLength);
char* 	stringSort(char* string);
void 	delimitAndSort(char* sentence, char delimiter, int sentenceLength);

/**
 * @brief 	  	takes a sentence to reverse order words and sort them character by character maintaing space. 
 * @param argc	number of command line arguements. 
 * @param argv	actual command line arguements.
 * @return 		control back to the operating system.
 */
int main(int argc, char ** argv)
{	
	// String variable to contain the user input. 
	char* sentence;
	char* sentenceBackup;
	int actualCharsCount, userCharsCount, textOverFlow = 0;
	
	// ask the user for input based on which the char array can be dynamically space allocated.
	printf("Enter the maximum number of characters that would be provided:\n");
	scanf("%d", &userCharsCount);  
	
	// dynamically allocate the char array based on the userinput
	sentence = (char*)malloc(userCharsCount*sizeof(char));
	sentenceBackup = (char*)malloc(userCharsCount*sizeof(char));
	
	// this ensures that the user enters the source text.
	getchar(); 
	
	//ask the user forsinput
	printf("Enter a free formed sentence that needs to be sorted: \n");
	
	//accept the user entry into sentence.
	fgets(sentence,userCharsCount,stdin);
	
	// replace the newline added by fgets in the end so the text is sanitized. 
	actualCharsCount = findLength(sentence);
	if(sentence[actualCharsCount-1]=='\n')
		{
			sentence[actualCharsCount-1]='\0';
		}
	
	// fire the overflow flag if there's a difference between expected and actual charsCount.
	if(actualCharsCount<=userCharsCount)
		{
			textOverFlow = 1;
		}
	
	// keep a backup for further operation.
	strncpy(sentenceBackup, sentence, findLength(sentence));
	
	// strncpy doesn't add terminating characters automatically.
	sentenceBackup[findLength(sentence)]='\0'; 
	
	//display the sentence entered.
	printf("\n\nThe sentence is:\n%s", sentence);
	
	printf("\n\nReversed order of each word in the sentence:\n");
	
	//function to split a sentence based on the delimiting character. Find the length of the sequence using the method.
	delimitAndReverse(sentence,' ', findLength(sentence));

	printf("\n\nAlphabetically sorted each word in the sentence:\n"); 
	
	// Alphabetically sort each word in the sentence.
	delimitAndSort(sentenceBackup,' ',findLength(sentenceBackup));
	
	// free the dynamically allocated memory
	free(sentence);
	free(sentenceBackup);
	
	
	if(textOverFlow)
		{
			printf("\n\n\n\n\n\nFYI: If there were more characters entered than the expected,"); 
			printf(" the output is stripped just until the expected characters.");

		}
	
	printf("\n\n\n\n\nDynamically allocated memory freed!");
	
	// keep the display output on the screen.	
	getchar();
	return 0;	
}


/**
   * @brief 			finds the length of the given string excluding the null terminating string-'\0.
   * @strategy  		run an iterative loop as long as there is no terminating character 
   * 			 		encountered while counting the source text.
   * @param sentence 	the string to be length counted.
   * @return 			the length of the string.
*/
int findLength(char * sentence)
{   
	// this variable keeps a track of the length of the sentence, 
	// this also acts as the index of iteration initally.
	int len=0;
	
	// keep counting as long as the current iteration doesn't
	// encounter a null terminating character.
	while(sentence[len] != '\0')
	{
		len++;
	}	
	return len;	
}



 /**
  * @brief           	  breaks the sentence as delimited tokens and prints them in reverse order.
  * @strategy        	  traverse from right to left, replacing every delimiting character with a terminal character.
  *			         	  print those words in the same order as that of traversal.	 	
  * @param sentence       the source text on which delimiter must be applied. 
  * @param delimiter      the actual break up character that must be applied on text.
  * @param sentenceLength length of the source text.
  */
void delimitAndReverse(char* sentence, char delimiter, int sentenceLength)
{
	// used as an iterator variable.	
	int i;
	
	// move from the reverse order of the source text sentence
	for(i=sentenceLength-1;i>=0;i--)
		{
			// when encountered with a delimiter character, 
			if(sentence[i]==delimiter)
			{
				// replace that delimiting character (whitespace in this case) with a terminating null character - '\0'
				sentence[i] = '\0';
				
				//reference operator is used to get the value out.   
				printf("%s",&(sentence[i])+1);
		
				// add whitespaces to tokens.  
				printf(" ");
			}
		}
	// print the last word after the terminating character. Essentially, this is the first word while 
	// reading naturally. But however, while traversing from the reverse order (right to left) this 
	// becomes the last word. 
	printf("%s",sentence);
}	

/**
 * @brief 					splits the source text into words, sorts those words and prints them. 
 * @strategy 				delimit the source text using pointers and pass the delimited tokens 
 * 							to the case insensitive sort function.
 * @param sentence 			the actual source text.
 * @param delimiter 		the target where the split must happen.
 * @param sentenceLength 	the size of the source text.
 */
void delimitAndSort(char* sentence, char delimiter, int sentenceLength)
{
	// used for further processing to sort on the word.
	char temp[findLength(sentence)];
	
	// p & q are initally set to the first pointer values of the 
	// sentence so they serve as update values later. 
	char* p = &sentence[0];
	char* q = &sentence[0];
	int len = findLength(sentence), i, delimiterFlag = 0;
	
	// iterate through the whole sentence
	for(i = 0; i < len + 1; i++)
	{   
		// fill temp with 0.
		memset(temp, 0, len);
		
		// if character is either a delimiter or a null terminating character
		if(sentence[i] == delimiter || sentence[i] == '\0')
		{
			// get the value and store it to p.
			q = &sentence[i];
			
			// copy the delimited token 
			strncpy(temp, p, q-p);
			
			// print the sorted text by calling the sort function on the token. 
			printf("%s", stringSort(temp));
			printf(" ");
		}
		
		// proceed to the next word 
		p = q+(p!=&sentence[0]);
		
		
		// warn the user about potential damage if more than one delimiter(spacebar) is used simultaneously & fire the delimiter flag. 
		if(sentence[i] == delimiter && sentence[i+1] == delimiter)
		{
			delimiterFlag = 1;
		}
	}
	
	
	if(delimiterFlag){
		printf("\n\n\n\n\nWARNING: More than 1 delimiters simultaneously found, please enter just one");
					printf(" delimiter next time or otherwise output might not behave as expected.");	
	}
}	


/**
 * @brief 			sorts the given word. 	
 * @strategy		iterate from left to right keeping two literal pointers that check to see if the character on right is 
 * 					lexographically larger than the one on left, if so, swap the characters so that the ordering is alphabetical.
 * 					Repeating this process throughout the word ensures the output contains sorted characters.
 * @param string	the source text (usually a word) which must be sorted on characters.
 * @return 			the sorted word.
 */
char* stringSort(char* string)
{
  // used for holding variable during swap.
  char temp;
  int i, j, length;
  length = findLength(string);
  
  // iterate from the first character until the last but one
  for(i=0; i<length-1; i++)
  { 
	// iterate from the secod character until the last one
	for (j=i+1; j<length; j++)
	{
	   // if the character from first loop is lexographically larger than
	   // the character from second loop, then swap them so they fit alphabetically.
	   // comparisons must be done so that the case senstivity of those characters 
	   // has no effect during comparision - one way is to do tolower() on the comparing characters.
	   if (tolower(string[i]) > tolower(string[j]))
	   { 
		 // swapping  
		 temp=string[i];
		 string[i]=string[j];
		 string[j]=temp;
	   }
	}
  }
  
  //Alphabetically sorted word
  return string;
}


 