#define _CRT_SECURE_NO_WARNINGS
//实现函数功能

#include"contact.h"

void InitContact(struct Contact* ps)
{
	//memset(ps->data, 0, sizeof(ps->data));
	//ps->size = 0; //设置通讯录最初只有一个元素
	ps->data = (struct PeoInfo*)malloc(3 * sizeof(struct PeoInfo));
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	
	//把文件中已经存放的通讯录中的信息加载到通讯录中
	LoadContact(ps);
}

//声明函数
void CheckCapacity(struct Contact* ps);
void LoadContact(struct Contact* ps)
{
	struct PeoInfo tmp = { 0 };
	FILE* pfRead = fopen("contact.dat", "rb");
	if (pfRead == NULL)
	{
		printf("LoadContact::%s\n", strerror(errno));
		return;
	}

	//读取文件,存放到通讯录中
	while (fread(&tmp, sizeof(struct PeoInfo), 1, pfRead))
	{
		CheckCapcity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	
	//关闭文件
	fclose(pfRead);
	pfRead = NULL;
}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//增容
		struct PeoInfo* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("增容成功\n");
		}
		else
		{
			printf("增容失败\n");
		}
	}
}

void AddContact(struct Contact* ps)
{
	//检测当前通讯录的容量
	//1.如果满了,增加空间
	//2.如果不满,无操作
	CheckCapacity(ps);

	//增加数据
	printf("请输入名字:");
	scanf("%s", ps->data[ps->size].name);
	printf("请输入年龄:");
	scanf("%s", &(ps->data[ps->size].age));
	printf("请输入性别:");
	scanf("%s", ps->data[ps->size].sex);
	printf("请输入电话:");
	scanf("%s", ps->data[ps->size].tele);
	printf("请输入地址:");
	scanf("%s", ps->data[ps->size].addr);

	ps->size++;
	printf("添加成功\n");
}


void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
	}
	else
	{
		int i = 0;
		//打印标题
		printf("%-20s\t %-4s\t %-5s\t %-12s\t %-20s\n", "名字", "年龄", "性别", "电话", "地址");
		//打印数据
		for (i = 0; i < ps->size; i++)
		{
			printf("%20s\t %4d\t %5s\t %12s\t %20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr
			);
		}
	}
}

//私有函数只有该类的成员变量或成员函数可以访问.在C语言中,也有"private函数",它就是接下来要说的static函数,完成面向对象编程中private函数的功能
//所以static函数的作用域是本源文件,把它想象为面向对象中的private函数就可以了
static int FindByName(const struct Contact* ps, char name[MAX_NAME])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (0 == strcmp(ps->data[i].name, name))
		{
			return i;
		}
	}
	return -1; //找不到的情况
}

void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入想要删除的名字:");
	scanf("%s", name);

	//1.查找要删除的名字在什么位置
	//找到了返回名字所在元素的下标
	//找不到返回-1
	int pos = FindByName(ps, name);

	//2.删除
	if (pos == -1)
	{
		printf("要删除的人不存在\n");
	}
	else
	{
		//删除数据
		int i = 0;
		int j = 0;
		for (j = i; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("删除成功\n");
	}
}


void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];  //此时就会发现代码冗余了,删除和修改函数都需要先进行查找,所以只需要封装一个通用的函数实现查找
	printf("请输入要查找人的名字:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("要查找的人不存在\n");
	}
	else
	{
		printf("%-20s\t %-4s\t %-5s\t %-12s\t %-20s\n", "名字", "年龄", "性别", "电话", "地址");
		printf("%20s\t %4d\t %5s\t %12s\t %20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr
		);
	}
}


void ModifyContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("请输入要修改人的名字\n");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("要修改人的信息不存在\n");
	}
	else
	{
		printf("请输入名字:");
		scanf("%s", ps->data[pos].name);
		printf("请输入年龄:");
		scanf("%s", &(ps->data[pos].age));
		printf("请输入性别:");
		scanf("%s", ps->data[pos].sex);
		printf("请输入电话:");
		scanf("%s", ps->data[pos].tele);
		printf("请输入地址:");
		scanf("%s", ps->data[pos].addr);

		printf("修改完成\n");
	}
}


void SortContact(struct Contact* ps)
{
	//利用冒泡排序
}

void DestroyContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}

void SaveContact(struct Contact* ps)
{
	FILE* pfWrite = fopen("SaveContact::contact.data","wb");
	if (pfWrite == NULL)
	{
		printf("%s\n", strerror(errno));
		return;
	}

	//写通讯录中的数据到文件中
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeoInfo), 1, pfWrite);
	}
    //关闭文件
	fclose(pfWrite);
	pfWrite = NULL;
}