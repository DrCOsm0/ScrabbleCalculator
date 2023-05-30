#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 30

struct data_t {
	int nval; 		/* current number of values in array */
	int max; 		/* allocated number of values */
	char **words;		/* the data array */
};

int scrabble_search(struct data_t data, int arr_size, char* word);
void scrabble_tile_search(struct data_t data, char* buf);

enum {INIT = 1, GROW = 2};

int main(void) 
{
	FILE *fp = fopen("scrabble.txt", "r");
	char buf[LEN];
	int i = 0;
	struct data_t *data = malloc(sizeof(struct data_t));
	data->nval = INIT;
	data->max = INIT;
	data->words = NULL;

	int user;
	int temp;
	
  
  while (fgets(buf, LEN, fp)) {
    
		if (data->words == NULL)
		{
			data->words = malloc(sizeof(char*));

		}else if (data->nval > data->max)
		{
			data->words = realloc(data->words, GROW * data->max *sizeof(char*));
			data->max = GROW * data->max;
		}
		
		*(data->words + i) = malloc(sizeof(char) * strlen(buf));
		strncpy(*(data->words + i), buf, strlen(buf) - 1);
	
		i++;
        data->nval++;		
	}

	fclose(fp); 
	data->nval--;

	while(1)
	{
		printf("Scrabble Menu\n");
		printf("1: Find if a word is in the the scrabble dictionary\n");
		printf("2: Determine best play from tiles\n");
		printf("3: Quit\n");
		printf("Selection:");
		scanf("%d", &user);

		switch(user)
		{

			case 1:

				printf("Enter Word:");
				scanf("%s", buf);
				printf("\n");

				temp = scrabble_search(*data, data->nval, buf);

				if(temp == 1)
					printf("%s is not a valid scrabble word\n\n", buf);

				if(temp == 0)
					printf("%s is a valid scrabble word\n\n", buf);

			break;

			case 2: ;

				printf("Enter tiles as a word:");
				scanf("%s", buf);
				printf("\n");

				scrabble_tile_search(*data, buf);

			break;

			case 3:

				for(int i = 0; i < data->nval; i++)
					free(*(data->words + i));

				free(data->words);
				free(data);
				return 0;

			break;
		}
	}
}

int scrabble_search(struct data_t data, int arr_size, char* word)
{

	int left = 0;
	int right = data.nval - 1;
	int index_search;
	while(left <= right)
		{

			index_search = left + (right - left) / 2;   //divide array in half
	
			if(strcmp(*(data.words + index_search), word) == 0)
			{
				return(0);
			}

			if(strcmp(*(data.words + index_search), word) < 0)
						left = index_search + 1;

			if(strcmp(*(data.words + index_search), word) > 0)
						right = index_search - 1;
		}

		return(1);
}

void scrabble_tile_search(struct data_t data, char* buf)
{

	int tile_len = strlen(buf);
	int arry_tile[25];
	int arry_word[25];
	int arry_point[25];
	char arry_wordbuf[LEN];
	int count_tile = 0;
	int count_word = 0;
	int counter = 0;
	int highest_val = 0;
	int index_highest_val = 0;

	arry_point[0] = 1;
	arry_point[1] = 3;
	arry_point[2] = 3;
	arry_point[3] = 2;
	arry_point[4] = 1;
	arry_point[5] = 4;
	arry_point[6] = 2;
	arry_point[7] = 4;
	arry_point[8] = 1;
	arry_point[9] = 8;
	arry_point[10] = 5;
	arry_point[11] = 1;
	arry_point[12] = 3;
	arry_point[13] = 1;
	arry_point[14] = 1;
	arry_point[15] = 3;
	arry_point[16] = 10;
	arry_point[17] = 1;
	arry_point[18] = 1;
	arry_point[19] = 1;
	arry_point[20] = 1;
	arry_point[21] = 4;
	arry_point[22] = 4;
	arry_point[23] = 8;
	arry_point[24] = 4;
	arry_point[25] = 10;

	for(int i = 0; i < 26; i++)
	{
		arry_tile[i] = 0;
	}

	for(int i = 0; i < 26; i++) //letter counter
	{
		for(int j = 0; j < tile_len; j++) 
		{
			if(buf[j] == i + 97)
			{
				count_tile++;
				arry_tile[i] = count_tile;   
			}
		}
		count_tile = 0;
	}

	for(int i = 0; i < data.nval; i++)
	{
		for(int i = 0; i < 26; i++)
		{
			arry_word[i] = 0;
		}

		int str_len = strlen(*(data.words + i));
		strncpy(arry_wordbuf, *(data.words + i), strlen(*(data.words + i)));

		for(int i = 0; i < 26; i++)
		{
			for(int j = 0; j < str_len; j++) 
			{	
				if(arry_wordbuf[j] == i + 97)
				{
					count_word++;
					arry_word[i] = count_word;
				}
			}
			count_word = 0;	
		}

		counter = 0;
		for(int k = 0; k < 26; k++)
		{
			if(arry_tile[k] >= arry_word[k])
				counter++;	
		}

		if(counter == 26)
		{
			int point_val = 0;
		
			for(int x = 0; x < 26; x++)
			{
				point_val = point_val + (arry_word[x] * arry_point[x]);
			}

			if(point_val > highest_val)
			{
				highest_val = point_val;
				index_highest_val = i;
			}
		}
	}

	printf("Best play is %s", *(data.words + index_highest_val));
	printf(" %d points\n\n", highest_val);
}
