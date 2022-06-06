#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	//최대 배열 사이즈 13
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE//해시체이블 사이즈 13

int initialize(int **a);//초기화 함수
int freeArray(int *a);//메모리 해제 함수
void printArray(int *a);//출력함수

int selectionSort(int *a);//선택정렬함수
int insertionSort(int *a);//삽입정렬함수
int bubbleSort(int *a);//버블 정렬함수
int shellSort(int *a);//쉘 정렬 함수
/* recursive function으로 구현 */
int quickSort(int *a, int n);//퀵 정렬 함수


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);//해시 코드 생성 함수

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);//해시 테이블 제작 함수

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);//키값 찾기 함수


int main()
{
	printf("-----------------[2019038085] [lee hyeondo]----------------------\n");
	char command;//커멘드 변수
	int *array = NULL;//포인터 array
	int *hashtable = NULL;//포인터 hashtable
	int key = -1;//키 초기화
	int index = -1;//인덱스 초기화

	srand(time(NULL));//랜덤 

	do{//조건에 따라 반복
		printf("----------------------------------------------------------------\n");//메뉴 출력
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커멘드 입력

		switch(command) {//커멘드에 따라 작동
		case 'z': case 'Z'://커멘드가 z 면
			initialize(&array);//포인터 초기화
			break;
		case 'q': case 'Q'://커멘드가 q 면
			freeArray(array);//메모리 삭제
			break;
		case 's': case 'S'://커멘드가 s 면
			selectionSort(array);//선택정렬
			break;
		case 'i': case 'I'://커멘드가 i 면
			insertionSort(array);//삽입정렬
			break;
		case 'b': case 'B'://커멘드가 b 면
			bubbleSort(array);//버블정렬
			break;
		case 'l': case 'L'://커멘드가 l 면
			shellSort(array);//쉘 정렬
			break;
		case 'k': case 'K'://커멘드가 k 면
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//array 출력
			quickSort(array, MAX_ARRAY_SIZE);//큌정렬
			printf("----------------------------------------------------------------\n");
			printArray(array);//array 출력

			break;

		case 'h': case 'H'://커멘드가 h 면
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);//array 출력
			hashing(array, &hashtable);//해싱테이블 제작
			printArray(hashtable);//해시테이블 출력
			break;

		case 'e': case 'E'://커멘드가 e 면
			printf("Your Key = ");
			scanf("%d", &key);//키 입받음
			printArray(hashtable);//해시테이블 출력
			index = search(hashtable, key);//인덱스에 해시테이블에서 찾은 키값 입력
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);//상태 출력
			break;

		case 'p': case 'P'://커멘드가 p 면
			printArray(array);//array 출력
			break;
		default://모두 아니면 
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//집중
			break;
		}

	}while(command != 'q' && command != 'Q');//커멘드가 q가 아니면 다시 반복

	return 1;//종료
}

int initialize(int** a)//초기화 함수
{
	int *temp = NULL;//포인터 템프 생성

	
	if(*a == NULL) {// array가 NULL인 경우 메모리 할당
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//동적할당
		*a = temp;// 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함
	} else
		temp = *a;//포인터 a의 값 tenp에 입력

	
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈만큼 반복
		temp[i] = rand() % MAX_ARRAY_SIZE;// 랜덤값을 배열의 값으로 저장 

	return 0;
}

int freeArray(int *a)//메모리 삭제
{
	if(a != NULL)//a가 비어있지 않으면
		free(a);//메모리 삭제
	return 0;
}

void printArray(int *a)//출력함수
{
	if (a == NULL) {//a가 비어있으면 아무것도 없음을 출력
		printf("nothing to print.\n");
		return;
	}
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈만큼 반복
		printf("a[%02d] ", i);//i 출력
	printf("\n");
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈만큼 반복
		printf("%5d ", a[i]);//a 출력
	printf("\n");
}


int selectionSort(int *a)//선택 정렬
{
	int min;//작은값 넣을 변수
	int minindex;//작은값인덱스 넣을 변수
	int i, j;// 변수 i ,j

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);// a 출력

	for (i = 0; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈 만큼 반복
	{
		minindex = i;//i입력
		min = a[i];//i번째 인덱스 min에 입력
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)// 맥스 사이즈까지 반복 j는 i+1부터 시작
		{
			if (min > a[j])//입력 되었던 min보다 j번째 인덱스가 작으면
			{
				min = a[j];//min에 j번째 인덱스 입력
				minindex = j;//minindex는 j
			}
		}
		a[minindex] = a[i];//j의 위치에 i 입력하고
		a[i] = min;//i번째 인덱스에 j번째 인덱스 값 입력
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬후 a 출력
	return 0;
}

int insertionSort(int *a)//삽입 정렬
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//a출력

	for(i = 1; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈 만큼 반복
	{
		t = a[i];//i번째 인덱스값 t에 입력
		j = i;//인덱스 번호 i 를 j에 입력
		while (a[j-1] > t && j > 0)//j-1의 값이 t값보다 작고 j가 0보다 큰 동안
		{
			a[j] = a[j-1];//j번째 인덱스 값에 j-1번째 인덱스 값 입력
			j--;//j값 1 감소
		}
		a[j] = t;//j번째 인덱스에 t입력
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후 a 출력

	return 0;
}

int bubbleSort(int *a)//버블 정렬 함수
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//a 출력 

	for(i = 0; i < MAX_ARRAY_SIZE; i++)//i가 맥스 사이즈 까지
	{
		for (j = 0; j < MAX_ARRAY_SIZE; j++)//j가 맥스 사이즈 까지
		{
			if (a[j] > a[j+1])//전값이 더 크면
			{
				t = a[j];//전 값과 현재 값 교체
				a[j] = a[j+1];
				a[j+1] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);//a 출력

	return 0;
}

int shellSort(int *a)//쉘 정렬
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);//정렬전 a 출력

	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2)//h는 맥스사이즈/2 이고 h가 0보다 큰동안 반복
	{
		for (i = 0; i < h; i++)//i가 h보다 작은동안 반복
		{
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)//j가 맥스 사이즈까지 반복
			{
				v = a[j];//v에 j번째 인덱스 값 입력
				k = j;//k에 j입력
				while (k > h-1 && a[k-h] > v)//k가 h-1보다 크고 k-h번째 인덱스 값이 v 보다 큰동안
				{
					a[k] = a[k-h];//k의 값에 k-h 값 입력
					k -= h;//k는 h만큼 감소
				}
				a[k] = v;//k번째 인덱스값에 v 입력
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);//정렬 후 a 출력

	return 0;
}

int quickSort(int *a, int n)//퀵 정렬
{
	int v, t;
	int i, j;

	if (n > 1)//맥스 인덱스 사이즈가 1보다 크면
	{
		v = a[n-1];//v에 마지막 전 인덱스 값 입력
		i = -1;//i에 -1 입력
		j = n - 1;//j에 마지막 전 인덱스 번호 입력

		while(1)//반복
		{
			while(a[++i] < v);//i값 v까지 
			while(a[--j] > v);//j값 v까지

			if (i >= j) break;//i가 j보다 크면 종료
			t = a[i];//t에 i번째 인덱스 값 입력
			a[i] = a[j];//i번째 인덱스에 j번째 인덱스 값 입력
			a[j] = t;//j번째 인덱스에 t값 입력
		}
		t = a[i];//t에 i번째 인덱스 값 입력
		a[i] = a[n-1];//i번째 인덱스에 n-1번째 인덱스 값 입력
		a[n-1] = t;//n-1 번째 인덱스에 t 값 입력

		quickSort(a, i);//퀵 정렬 다시 호출.인자 값 i 
		quickSort(a+i+1, n-i-1);//퀵 정렬 다시 호출 n-i-1
	}


	return 0;
}

int hashCode(int key) {//해시코드 제작 함수
   return key % MAX_HASH_TABLE_SIZE;//입력받은 키를 맥스 테이블 사이즈로 나눈 나머지 리턴
}

int hashing(int *a, int **ht)//해싱 함수
{
	int *hashtable = NULL;//해시 테이블 값 초기화

	/* hash table이 NULL인 경우 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);//동적 할당
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)//해시 테이블 -1로 초기화
		hashtable[i] = -1;

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)//맥스 사이즈만큼 반복
	{
		key = a[i];//키에 i번째 인덱스 값 입력
		hashcode = hashCode(key);//해시 코드에 해시코드 함수값 입력

		if (hashtable[hashcode] == -1)//해시테이블의 해시코드번째 인덱스가 -1 이면
		{
			hashtable[hashcode] = key;// key 입력
		} else 	{

			index = hashcode;//아니면 인덱스에 해시코드 입력

			while(hashtable[index] != -1)//인덱스 값이 -1이 아닌동안
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;//인덱스는 인덱스 값 +1 한것을 맥스테이블로 나눈 나머지 입력
				
			}
			hashtable[index] = key;//해시 테이블의 인덱스번째 값에 키 입력
		}
	}

	return 0;
}

int search(int *ht, int key)//키값 찾기 함수
{
	int index = hashCode(key);//인덱스에 해시 코드 입력

	if(ht[index] == key)//만약 key값을 찾으면 
		return index;//키값의 인덱스 리턴

	while(ht[++index] != key)//해시테이블 값이 키값이 아닌동안
	{
		index = index % MAX_HASH_TABLE_SIZE;//인덱스는 인덱스를 맥스 테이블사이즈로 나눈 나머지
	}
	return index;//인덱스 리턴
}



