#define _CRT_SECURE_NO_WARNINGS
//ʵ�ֺ�������

#include"contact.h"

void InitContact(struct Contact* ps)
{
	//memset(ps->data, 0, sizeof(ps->data));
	//ps->size = 0; //����ͨѶ¼���ֻ��һ��Ԫ��
	ps->data = (struct PeoInfo*)malloc(3 * sizeof(struct PeoInfo));
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0;
	ps->capacity = DEFAULT_SZ;
	
	//���ļ����Ѿ���ŵ�ͨѶ¼�е���Ϣ���ص�ͨѶ¼��
	LoadContact(ps);
}

//��������
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

	//��ȡ�ļ�,��ŵ�ͨѶ¼��
	while (fread(&tmp, sizeof(struct PeoInfo), 1, pfRead))
	{
		CheckCapcity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
	
	//�ر��ļ�
	fclose(pfRead);
	pfRead = NULL;
}

void CheckCapacity(struct Contact* ps)
{
	if (ps->size == ps->capacity)
	{
		//����
		struct PeoInfo* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeoInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
			printf("���ݳɹ�\n");
		}
		else
		{
			printf("����ʧ��\n");
		}
	}
}

void AddContact(struct Contact* ps)
{
	//��⵱ǰͨѶ¼������
	//1.�������,���ӿռ�
	//2.�������,�޲���
	CheckCapacity(ps);

	//��������
	printf("����������:");
	scanf("%s", ps->data[ps->size].name);
	printf("����������:");
	scanf("%s", &(ps->data[ps->size].age));
	printf("�������Ա�:");
	scanf("%s", ps->data[ps->size].sex);
	printf("������绰:");
	scanf("%s", ps->data[ps->size].tele);
	printf("�������ַ:");
	scanf("%s", ps->data[ps->size].addr);

	ps->size++;
	printf("���ӳɹ�\n");
}


void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		//��ӡ����
		printf("%-20s\t %-4s\t %-5s\t %-12s\t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
		//��ӡ����
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

//˽�к���ֻ�и���ĳ�Ա�������Ա�������Է���.��C������,Ҳ��"private����",�����ǽ�����Ҫ˵��static����,��������������private�����Ĺ���
//����static�������������Ǳ�Դ�ļ�,��������Ϊ��������е�private�����Ϳ�����
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
	return -1; //�Ҳ��������
}

void DelContact(struct Contact* ps)
{
	char name[MAX_NAME];
	printf("��������Ҫɾ��������:");
	scanf("%s", name);

	//1.����Ҫɾ����������ʲôλ��
	//�ҵ��˷�����������Ԫ�ص��±�
	//�Ҳ�������-1
	int pos = FindByName(ps, name);

	//2.ɾ��
	if (pos == -1)
	{
		printf("Ҫɾ�����˲�����\n");
	}
	else
	{
		//ɾ������
		int i = 0;
		int j = 0;
		for (j = i; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("ɾ���ɹ�\n");
	}
}


void SearchContact(const struct Contact* ps)
{
	char name[MAX_NAME];  //��ʱ�ͻᷢ�ִ���������,ɾ�����޸ĺ�������Ҫ�Ƚ��в���,����ֻ��Ҫ��װһ��ͨ�õĺ���ʵ�ֲ���
	printf("������Ҫ�����˵�����:>");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("Ҫ���ҵ��˲�����\n");
	}
	else
	{
		printf("%-20s\t %-4s\t %-5s\t %-12s\t %-20s\n", "����", "����", "�Ա�", "�绰", "��ַ");
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
	printf("������Ҫ�޸��˵�����\n");
	scanf("%s", name);
	int pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("Ҫ�޸��˵���Ϣ������\n");
	}
	else
	{
		printf("����������:");
		scanf("%s", ps->data[pos].name);
		printf("����������:");
		scanf("%s", &(ps->data[pos].age));
		printf("�������Ա�:");
		scanf("%s", ps->data[pos].sex);
		printf("������绰:");
		scanf("%s", ps->data[pos].tele);
		printf("�������ַ:");
		scanf("%s", ps->data[pos].addr);

		printf("�޸����\n");
	}
}


void SortContact(struct Contact* ps)
{
	//����ð������
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

	//дͨѶ¼�е����ݵ��ļ���
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeoInfo), 1, pfWrite);
	}
    //�ر��ļ�
	fclose(pfWrite);
	pfWrite = NULL;
}