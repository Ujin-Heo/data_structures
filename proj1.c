#include <stdio.h>
#include <stdlib.h> // malloc, realloc, free, qsort
#include <string.h> // strdup, strcmp, memmove

#define SORT_BY_WORD	0 // 단어 순 정렬
#define SORT_BY_FREQ	1 // 빈도 순 정렬

#define MAX_LEN 100 // 한 단어의 최대 길이

// 구조체 선언
// 단어 구조체
typedef struct {
	char	*word;		// 단어
	int		freq;		// 빈도
} tWord;

// 사전(dictionary) 구조체
typedef struct {
	int		len;		// 배열에 저장된 단어의 수
	int		capacity;	// 배열의 용량 (배열에 저장 가능한 단어의 수)
	tWord	*data;		// 단어 구조체 배열에 대한 포인터  // 사전을 나타내는 베열의 첫번째 단어를 가리킴(head) 역할
} tWordDic;

////////////////////////////////////////////////////////////////////////////////
// 함수 원형 선언(declaration)

// 단어를 사전에 저장
// 새로 등장한 단어는 사전에 추가
// 이미 사전에 존재하는(저장된) 단어는 해당 단어의 빈도를 갱신(update)
// capacity는 1000으로부터 시작하여 1000씩 증가 (1000, 2000, 3000, ...)
void word_count( FILE *fp, tWordDic *dic);

// 사전을 화면에 출력 ("단어\t빈도" 형식)
void print_dic( tWordDic *dic);

// 사전에 할당된 메모리를 해제
void destroy_dic(tWordDic *dic);

// qsort를 위한 비교 함수
// 정렬 기준 : 단어
//int compare_by_word( const void *n1, const void *n2);  // 얘는 실제로 과제에 사용되지는 않음. 구현할 필요x

// 정렬 기준 : 빈도 내림차순(1순위), 단어(2순위-> strcmp 쓰기)
// 바꿔야 되면 1 출력
int compare_by_freq( const void *n1, const void *n2);

////////////////////////////////////////////////////////////////////////////////
// 이진탐색 함수
// found : key가 발견되는 경우 1, key가 발견되지 않는 경우 0
// return value: key가 발견되는 경우, 배열의 인덱스
//				key가 발견되지 않는 경우, key가 삽입되어야 할 배열의 인덱스
int binary_search( const void *key, const void *base, size_t nmemb, size_t size, 
				int (*compare)(const void *, const void *), int *found);

// 먼저 적어준 문자열(str1)이 뒤에 적어준 문자열(str2)보다 사전 순서로 앞이면 음수를 뒤면 양수를 반환한다.
// 즉, strcmp(str1, str2) 값이 양수가 나올 때 두 문자열의 순서를 바꿔주면서 사전 순서대로 정리하는 것이다.
int compare(const void* a, const void* b);
////////////////////////////////////////////////////////////////////////////////
// 함수 정의 (definition)

// 사전을 초기화 (빈 사전을 생성, 메모리 할당)
// len를 0으로, capacity를 1000으로 초기화
// return : 구조체 포인터
tWordDic *create_dic(void)
{
	tWordDic *dic = (tWordDic *)malloc( sizeof(tWordDic));
	
	dic->len = 0;
	dic->capacity = 1000;
	dic->data = (tWord *)malloc(dic->capacity * sizeof(tWord));

	return dic;
}

void word_count( FILE *fp, tWordDic *dic) {
	char key[MAX_LEN];
	int found;

	while (fgets(key, MAX_LEN, fp)) {
		key[strcspn(key, "\n")] = 0; // strcspn (string complementary span): "/n"가 안 나오는 길이 반환 -> 최초로 "\n"가 나오는 인덱스 반환
		
		int index = binary_search(key, dic->data, dic->len, sizeof(tWord), compare, &found);
		
		// tWord* kw = (dic->data) + index*sizeof(tWord);
		// tWord* kw = &dic->data[index];
		// 위 같이 하면 dic->capacity, dic->len이 1000개인데 index가 1000이면 오류.

		if (found) { // 찾은 경우
			dic->data[index].freq++;
			// ((dic->data) + index*sizeof(tWord))->freq++;
		} else { // 못 찾은 경우
			// (dic->len)++;
			if (dic->len >= dic->capacity) { // dic->capacity % 1000 == 0
				dic->capacity += 1000;
				dic->data = realloc(dic->data, dic->capacity * sizeof(tWord));
			}

			tWord* kw = &dic->data[index];
			memmove(&dic->data[index + 1], &dic->data[index], (dic->len - index) * sizeof(tWord));
			// memove(kw + sizeof(tWord), kw, (dic->len - index) * sizeof(tWord)); 이것도 되지 않을까?
			// kw->word = (char*)malloc(sizeof(char)*strlen(key)); 안 해도 되나?
			kw->word = strdup(key);
			kw->freq = 1;
			dic->len++;
		}
    }
}

void print_dic( tWordDic *dic) {
	int len = dic->len;
	for (int i = 0; i < len; i++) {
		// tWord* kw = (dic->data) + i*sizeof(tWord);
		tWord* kw = &dic->data[i];
		printf("%s\t%d\n", kw->word, kw->freq);
		// printf("%s\t%d\n", dic->data[i].word, dic->data[i].freq);
	}
}

void destroy_dic(tWordDic *dic) {
	int len = dic->len;
	for (int i = 0; i < len; i++) {
		// tWord* kw = (dic->data) + i*sizeof(tWord);
		// free(kw->word);
		// free(kw); 안 해도 됨. 이래서 kw 굳이 정의 안 해도 됐음.

		//free(dic->data[i].word);
		free(((dic->data) + i)->word);
	}
	free(dic->data);
	free(dic);
}

// qsort용
int compare_by_freq( const void *n1, const void *n2) {
	tWord* a = (tWord*)n1;
	tWord* b = (tWord*)n2;
	// freq: 내림차순: b - a 출력
	if (a->freq > b->freq) 
		return -1;
	else if (a->freq < b->freq)
		return 1;
	else {
		// freq 같음: 알파벳순: 오름차순: a - b 출력
		if (strcmp(a->word, b->word) < 0) // 알파벳순
			return -1;
		else if (strcmp(a->word, b->word) > 0) // not 알파벳순
			return 1;
	}

	// if (a->freq != b->freq) {
	// 	return b->freq - a->freq; // 바꿔야 되면 양수 출력 (내림차순)
	// }
	// return strcmp(a->word, b->word); // 알파벳 오름차순 (오름차순 -> 점점 커짐 -> n1 < n2 -> 이 순서 그대로)
	// }
}

int binary_search( const void *key, const void *base, size_t nmemb, size_t size, 
				int (*compare)(const void *, const void *), int *found) {
	// char* kw = (char*)key;
	int l = 0, r = nmemb - 1;
	*found = 0; // 못 찾은 걸로 found 초기화
	int index;

	while (l <= r) {
		int m = (l + r) / 2;

		tWord* mid = (tWord*)base + m;
		//tWord *mid = (tWord *)((char *)base + (m * size)); --> base를 char*로 형변환해서 포인터 연산이 1Byte 단위로 이루어지게 함.

		int cmp = compare(key, mid->word);
		if (cmp < 0) { // key < m
            r = m - 1;
        } else if (cmp > 0) { // key > m
            l = m + 1;
        } else {
            *found = 1;
            return m; // Found the key
        }
	}

	index = l;

	return index;
}

int compare(const void* a, const void* b) {
	return strcmp((char *)a, (char *)b);
}

////////////////////////////////////////////////////////////////////////////////
int main(int argc, char **argv)
{
	tWordDic *dic;
	int option;
	FILE *fp;
	
	if (argc != 3)
	{
		fprintf( stderr, "Usage: %s option FILE\n\n", argv[0]);
		fprintf( stderr, "option\n\t-w\t\tsort by word\n\t-f\t\tsort by frequency\n");
		return 1;
	}
	
	if (strcmp( argv[1], "-w") == 0) option = SORT_BY_WORD;
	else if (strcmp( argv[1], "-f") == 0) option = SORT_BY_FREQ;
	else {
		fprintf( stderr, "unknown option : %s\n", argv[1]);
		return 1;
	}
	
	// 사전 초기화
	dic = create_dic();

	// 입력 파일 열기
	if ((fp = fopen( argv[2], "r")) == NULL) // fp라는 파일 오브젝트(파일을 가리키는 포인터; 읽기모드로) 생성
	{
		fprintf( stderr, "cannot open file : %s\n", argv[2]);
		return 1;
	}

	// 입력 파일로부터 단어와 빈도를 사전에 저장
	word_count( fp, dic);

	fclose( fp); // fopen할 때 밑에 미리 써두는 게 좋음

	// 정렬 (빈도 내림차순, 빈도가 같은 경우 단어순)
	if (option == SORT_BY_FREQ) {
		qsort( dic->data, dic->len, sizeof(tWord), compare_by_freq);
	}
		
	// 사전을 화면에 출력
	print_dic( dic);

	// 사전 메모리 해제
	destroy_dic( dic);
	
	return 0;
}

