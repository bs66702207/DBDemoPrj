#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <mysql/mysql.h>

#define BUFSIZE 1024
MYSQL mysql, *connection;

void deletename(char *SQL)
{
	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要干掉的名字>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char name[1024];
    memset(name, 0, sizeof(name));
    read(STDIN_FILENO, name, sizeof(name));
    name[strlen(name) - 1] = 0;

    memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "DELETE FROM table1 WHERE name = '%s'", name); //
    printf("'%s'\n", SQL);
}

void insertname(char *SQL)
{
	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要插入的名字>:");
    write(STDOUT_FILENO, SQL, BUFSIZE);
	char name[1024];
	memset(name, 0, sizeof(name));
	read(STDIN_FILENO, name, sizeof(name));
	name[strlen(name)-1] = 0;
	
	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要插入的性别>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char sex[1024];
    memset(sex, 0, sizeof(sex));
    read(STDIN_FILENO, sex, sizeof(sex)); //等待 用户输入要插入的性别,
    sex[strlen(sex) - 1] = 0;

	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要插入的年龄>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char age[1024];
    memset(age, 0, sizeof(age));
    read(STDIN_FILENO, age, sizeof(age)); //等待 用户输入要插入的年龄
    age[strlen(age) - 1] = 0;

	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要插入的班级>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char classes[1024];
    memset(classes, 0, sizeof(classes));
    read(STDIN_FILENO, classes, sizeof(classes)); //等待 用户输入要插入的班级
    classes[strlen(classes) - 1] = 0; 

    memset(SQL, 0, BUFSIZE);

	sprintf(SQL, "INSERT INTO table1(name, sex, age, class) VALUES('%s', '%s', %s, '%s')",
		name, sex, age, classes);
	printf("'%s'\n", SQL);
}

void updatename(char *SQL)
{
	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要修改的名字>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char name[1024];
    memset(name, 0, sizeof(name));
    read(STDIN_FILENO, name, sizeof(name));
    name[strlen(name) - 1] = 0;

    memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要性别的性别>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char sex[1024];
    memset(sex, 0, sizeof(sex));
    read(STDIN_FILENO, sex, sizeof(sex));
    sex[strlen(sex) - 1] = 0;

    memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要年龄的年龄>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char age[1024];
    memset(age, 0, sizeof(age));
    read(STDIN_FILENO, age, sizeof(age));
    age[strlen(age) - 1] = 0; //将字符串最后一位\n替换为0,最后放的是整数0，而不是字符'0'

	memset(SQL, 0, BUFSIZE);
    sprintf(SQL, "%s", "请输入要修改的班级>:");
    write(STDOUT_FILENO, SQL, strlen(SQL));
    char classes[1024];
    memset(classes, 0, sizeof(classes));
    read(STDIN_FILENO, classes, sizeof(classes)); //等待 用户输入要插入的班级
    classes[strlen(classes) - 1] = 0; //将字符串最后一位\n替换为0,最后放的是整数0，而不是字符'0'

    memset(SQL, 0, BUFSIZE);

	sprintf(SQL,
			"UPDATE table1 SET sex = '%s', age = %s, class = '%s' WHERE name = '%s'",
			sex, age, classes, name);
	printf("'%s'\n", SQL);
}

void selectname(const char *SQL)
{
	if (mysql_query(connection, SQL) != 0)
    {
        printf("query error, %s\n", mysql_error(&mysql));
    }
	//调用mysql_store_result得到查询结果，结果放到MYSQL_RES结构当中
	MYSQL_RES *result = mysql_store_result(connection);
	//要知道返回数据集有多少列才能自由的使用各种SELECT语句
	MYSQL_FIELD *field;
	int iFieldCount = 0;
	while(1)
	{
		field = mysql_fetch_field(result);//循环得到列名，如果循环到了列的最后，函数返回NULL
		if(field == NULL)
			break;
		printf("%s\t", field->name);
		iFieldCount++;
	}
	printf("\n");

	//循环遍历每一行
	MYSQL_ROW row;
	while(1)
	{
		row = mysql_fetch_row(result);
		if(row == NULL)
			break;
		int i = 0;
		for(; i<iFieldCount;i++)
		{
			if(strlen((const char *)row[i])>=8)//为了输出美观，对齐
			{
				printf("%s", (const char *) row[i]);
			}else
				printf("%s\t", (const char *) row[i]);
		}
		printf("\n");
	}
	mysql_free_result(result);
}



int main(int argc, char *argv[])
{
	system("stty erase ^H");
	mysql_init(&mysql);
	if (argc < 4)
	{
		printf("没有给main传递参数，执行默认连接sql参数。。。");
		connection = mysql_real_connect(&mysql, "192.168.4.92", "dbuser1", "1", "db1", 0, 0, 0);
	}else	
	connection = mysql_real_connect(&mysql, argv[1], argv[2], argv[3], argv[4], 0, 0, 0);

	if(connection == NULL)
	{
		printf("connect error, %s\n", mysql_error(&mysql));
		return -1;
	}
	
	if (mysql_query(connection, "SET NAMES utf8") != 0)     //设置字符集为UTF8
    {
        printf("设置字符集错误, %s\n", mysql_error(&mysql));
    }

	char buf[BUFSIZE];
    memset(buf, 0, sizeof(buf));
    strcpy(buf, "请选择\n1:插入\n2:删除\n3:修改\n4:查询\n");
    write(STDOUT_FILENO, buf, strlen(buf));
    memset(buf, 0, sizeof(buf));
    read(STDIN_FILENO, buf, sizeof(buf));
    if (strncmp(buf, "4", 1) == 0)      //输入用户输入的是4
    {
        memset(buf, 0, sizeof(buf));
        strcpy(buf, "请输入任意SELECt语句");
        write(STDOUT_FILENO, buf, strlen(buf));
        memset(buf, 0, sizeof(buf));
        read(STDIN_FILENO, buf, sizeof(buf));
        selectname(buf);
    } else
    {
        if (strncmp(buf, "1", 1) == 0)      //输入用户输入的是1
        {
            insertname(buf);
        }

        if (strncmp(buf, "2", 1) == 0)      //输入用户输入的是2
        {
            deletename(buf);
        }

        if (strncmp(buf, "3", 1) == 0)      //输入用户输入的是3
        {
            updatename(buf);
        }
        mysql_query(connection, buf);
    }

	mysql_close(connection);
	printf("!!!Hello World!!! %d\n", EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
