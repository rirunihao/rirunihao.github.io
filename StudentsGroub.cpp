#include<stdio.h>
#include<malloc.h>
struct student
{
	int age;
	float sore;
	char name[100];
};

int main()
{
	int i, j;
	int len;
	struct student *pArr;
	struct student t;

	printf("enter student number:\n");
	printf("len = :");
	scanf("%d", &len);
	pArr = (struct student *)malloc(sizeof(t) * len);

	for(i = 0; i < len; ++i)
	{
		printf("输入第%d个学生的信息\n", i + 1);
		printf("student age is:" );
		scanf("%d", &pArr[i].age);

		printf("student name is:");
		scanf("%s", pArr[i].name);

		printf("student sore is:");
		scanf("%f", &pArr[i].sore);
		printf("\n");
	}
	for(i = 0; i < len; ++i)
	{
		for(j = 0; j < len - 1 - i; ++j)
		{
			if(pArr[j].sore > pArr[j + 1].sore)
			{
				t = pArr[j];
				pArr[j] = pArr[j + 1];
				pArr[j + 1] = t;

			}
		}
	}
	printf("\n\n\nstudent message are\n\n\n");
for(i = 0; i < len; ++i)
	{
		printf("第%d个学生信息是:", i + 1);

		printf("student age is:%d\n", pArr[i].age);
		
		printf("student name is:%s\n", pArr[i].name);

		printf("student sore is:%.1f\n", pArr[i].sore);
		printf("\n");
	}
	return 0;
}