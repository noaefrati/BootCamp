#include <stdio.h>
#include <assert.h>
#include "sorted_list.h"


#define CHECK(test, str) ( (test) ? printf("passed %s tests\n", (str)) : printf("failed %s tests in line %d\n", (str), __LINE__))

typedef struct
{
	int height;
	int width;
} shape_t; 

int CompareWidth(const void *shape1, const void *shape2);
int ShapeAdd(void *data, void *params);
int CompareHeight(const void *height1, const void *height2);
void InitTest(void);
void InsertTest(void);
void RemoveTest(void);
void PopTest(void);
void ForEachTest(void);
void FindTest(void);
void MergeTest(void);

int main()
{
	InitTest();
	InsertTest();
	RemoveTest();
	PopTest();
	ForEachTest();
	FindTest();
	MergeTest();

	return 0;
}

void InitTest(void)
{
	srtlst_t *lst = SRTLSTCreate(&CompareHeight);
	
	int flag = 0;

	srtlst_iter_t begin = SRTLSTBegin(lst);
	srtlst_iter_t end = SRTLSTEnd(lst);

	flag = (1 == SRTLSTIsEmpty(lst));
	CHECK(flag, "list is empty");

	flag = (0 == SRTLSTSize(lst));
	CHECK(flag, "empty list size");

	flag = SRTLSTIsSameIter(begin, end);
	CHECK(flag, "begin = end empty list");

	flag = (1 == SRTLSTIsSameIter(end, SRTLSTNext(end)));	/*check when dummy is sent, return dummy*/
	CHECK(flag, "empty list next dummy");

	flag = (1 == SRTLSTIsSameIter(begin, SRTLSTPrev(begin)));	/*check when first is sent, return first*/
	CHECK(flag, "empty list prev first");

	flag = (NULL == SRTLSTGetData(begin));
	CHECK (flag, "get data from empty list");	

	SRTLSTDestroy(lst);
}

void InsertTest(void)
{


	srtlst_t *lst = SRTLSTCreate(&CompareHeight);

	static shape_t shapes[] = {{3, 2}, {1, 5}, {2, 8}};
	srtlst_iter_t runner = { NULL };
	int flag = 0;

	SRTLSTInsert(lst, shapes);
	SRTLSTInsert(lst, shapes + 1);
	SRTLSTInsert(lst, shapes + 2);

	flag = (0 == SRTLSTIsEmpty(lst));
	CHECK(flag, "list is empty");

	flag = (3 == SRTLSTSize(lst));
	CHECK(flag, "list size");

	runner = SRTLSTBegin(lst);

	flag = (shapes + 1 == SRTLSTGetData(runner));
	CHECK(flag, "correct position");

	runner = SRTLSTNext(runner);

	flag = (shapes + 2 == SRTLSTGetData(runner));
	CHECK(flag, "correct position");

	runner = SRTLSTNext(runner);

	flag = (shapes == SRTLSTGetData(runner));
	CHECK(flag, "correct position");

	SRTLSTDestroy(lst);
}


void RemoveTest(void)
{

	srtlst_t *lst = SRTLSTCreate(&CompareHeight);

	static shape_t shapes[] = {{3, 2}, {1, 5}, {2, 8}};
	int flag = 0;

	SRTLSTInsert(lst, shapes);
	SRTLSTInsert(lst, shapes + 1);
	SRTLSTInsert(lst, shapes + 2);

	SRTLSTRemove(SRTLSTBegin(lst));

	flag = (2 == SRTLSTSize(lst));
	CHECK(flag, "list size");

	flag = (shapes + 2 == SRTLSTGetData(SRTLSTBegin(lst)));
	CHECK(flag, "removed first");


	SRTLSTRemove(SRTLSTPrev(SRTLSTEnd(lst)));

	flag = (1 == SRTLSTSize(lst));
	CHECK(flag, "list size");

	flag = (shapes + 2 == SRTLSTGetData(SRTLSTPrev(SRTLSTEnd(lst))));
	CHECK(flag, "removed last");

	SRTLSTDestroy(lst);

}

void PopTest(void)
{

	srtlst_t *lst = SRTLSTCreate(&CompareHeight);

	static shape_t shapes[] = {{3, 2}, {1, 5}, {2, 8}};
	int flag = 0;

	SRTLSTInsert(lst, shapes);
	SRTLSTInsert(lst, shapes + 1);
	SRTLSTInsert(lst, shapes + 2);


	SRTLSTPopFront(lst);

	flag = (2 == SRTLSTSize(lst));
	CHECK(flag, "list size");

	flag = (shapes + 2 == SRTLSTGetData(SRTLSTBegin(lst)));
	CHECK(flag, "popped first");

	SRTLSTPopBack(lst);

	flag = (1 == SRTLSTSize(lst));
	CHECK(flag, "list size");

	flag = (shapes + 2 == SRTLSTGetData(SRTLSTPrev(SRTLSTEnd(lst))));
	CHECK(flag, "popped last");

	SRTLSTDestroy(lst);
	
}

void ForEachTest(void)
{

	srtlst_t *lst = SRTLSTCreate(&CompareHeight);
	srtlst_iter_t runner = { NULL };
	static shape_t shapes[] = {{1, 5}, {2, 8}, {3, 2}};
	int flag = 0;
	int to_add = 1;

	SRTLSTInsert(lst, shapes);
	SRTLSTInsert(lst, shapes + 1);
	SRTLSTInsert(lst, shapes + 2);

	SRTLSTForEach(SRTLSTBegin(lst), SRTLSTEnd(lst), &ShapeAdd, &to_add);


	runner = SRTLSTBegin(lst);

	flag = (2 == ((shape_t*)SRTLSTGetData(runner))->height);
	CHECK(flag, "correct data");
	flag = (6 == ((shape_t*)SRTLSTGetData(runner))->width);
	CHECK(flag, "correct data");

	runner = SRTLSTNext(runner);

	flag = (3 == ((shape_t*)SRTLSTGetData(runner))->height);
	CHECK(flag, "correct data");
	flag = (9 == ((shape_t*)SRTLSTGetData(runner))->width);
	CHECK(flag, "correct data");

	runner = SRTLSTNext(runner);

	flag = (4 == ((shape_t*)SRTLSTGetData(runner))->height);
	CHECK(flag, "correct data");
	flag = (3 == ((shape_t*)SRTLSTGetData(runner))->width);
	CHECK(flag, "correct data");

	SRTLSTDestroy(lst);

}

void FindTest(void)
{
	srtlst_t *lst = SRTLSTCreate(&CompareHeight);
	static shape_t shapes[] = {{0, 2}, {1, 5}, {2, 8}, {1, 10}, {8, 5}};
	int flag = 0;


	SRTLSTInsert(lst, shapes);
	SRTLSTInsert(lst, shapes + 1);
	SRTLSTInsert(lst, shapes + 2);


	flag = SRTLSTIsSameIter(SRTLSTNext(SRTLSTBegin(lst)), SRTLSTFind(lst,SRTLSTBegin(lst),
				 SRTLSTEnd(lst), shapes + 3));

	CHECK(flag, "found according to cmp_func");

	flag = SRTLSTIsSameIter(SRTLSTEnd(lst), SRTLSTFind(lst,SRTLSTBegin(lst),
				 SRTLSTEnd(lst), shapes + 4));

	CHECK(flag, "found according to cmp_func not in list");


	flag = SRTLSTIsSameIter(SRTLSTNext(SRTLSTBegin(lst)), SRTLSTFindIf(SRTLSTBegin(lst),
				 SRTLSTEnd(lst), &CompareWidth, shapes + 4));

	CHECK(flag, "found according to other cmp");

	flag = SRTLSTIsSameIter(SRTLSTEnd(lst), SRTLSTFindIf(SRTLSTBegin(lst),
				 SRTLSTEnd(lst), &CompareWidth, shapes + 3));

	CHECK(flag, "found according to other cmp not in list");

	SRTLSTDestroy(lst);
}

void MergeTest(void)
{
	srtlst_t *dest = SRTLSTCreate(&CompareHeight);
	srtlst_t *src = SRTLSTCreate(&CompareHeight);
	srtlst_iter_t runner = { NULL };
	int i = 0;

	static shape_t shapes[] = {{0, 2}, {2, 5}, {4, 8}, {1, 10}, {3, 5}, {5, 9}, {6, 7}};
	int flag = 0;


	SRTLSTInsert(dest, shapes);
	SRTLSTInsert(dest, shapes + 1);
	SRTLSTInsert(dest, shapes + 2);

	SRTLSTMerge(dest, src);
	
	flag = SRTLSTIsEmpty(src);
	CHECK(flag, "src is empty");

	flag  = (3 == SRTLSTSize(dest));
	CHECK(flag, "correct size empty src");


	SRTLSTInsert(src, shapes + 3);
	SRTLSTInsert(src, shapes + 4);
	SRTLSTInsert(src, shapes + 5);
	SRTLSTInsert(src, shapes + 6);

	SRTLSTMerge(dest, src);
	
	flag = SRTLSTIsEmpty(src);
	CHECK(flag, "src is empty");

	flag  = (7 == SRTLSTSize(dest));
	CHECK(flag, "correct size");

	flag = 1;
	runner = SRTLSTBegin(dest);
	for(; i < 7; ++i)
	{
		if (i != ((shape_t*)SRTLSTGetData(runner))->height)
		{
			flag = 0;
		}

		runner = SRTLSTNext(runner);	
	}

	CHECK(flag, "merge tests");

	SRTLSTDestroy(dest);
	SRTLSTDestroy(src);
}

int CompareHeight(const void *shape1, const void *shape2)
{
	if (((shape_t*)shape1)->height > ((shape_t*)shape2)->height)
	{
		return 1;
	}
	else if (((shape_t*)shape1)->height < ((shape_t*)shape2)->height)
	{
		return -1;
	}

	return 0;
}


int CompareWidth(const void *shape1, const void *shape2)
{
	return ((shape_t*)shape1)->width == ((shape_t*)shape2)->width;
}



int ShapeAdd(void *data, void *params)
{
	((shape_t*)data)->height += *(int*)params;
	((shape_t*)data)->width += *(int*)params;

	return 0;
}
