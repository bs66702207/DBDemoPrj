#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <mysql/mysql.h>

int main(void)
{
	//system("stty erase ^H");
	struct termios term;//定义一个temions结构
	if(tcgetattr(STDIN_FILENO, &term) == -1)//得到系统termion的设置
	{
		printf("tcgetattr error is %s\n", strerror(errno));
		return -1;
	}
	term.c_cc[VERASE] = '\b';//'\b'为退格键的ASCII码
	if (tcsetattr(STDIN_FILENO, TCSANOW, &term) == -1)//设置系统termion
	{
		printf("tcsetattr error is %s\n", strerror(errno));
	}

	MYSQL mysql, *connection=NULL;
	//1.相当于SQL内部初始化了一个TCP的socket，同时初始化了SQL必须的内存和一些结构
	mysql_init(&mysql);
	connection = mysql_real_connect(&mysql, "192.168.4.92", "dbuser1", "1", "db1", 0, 0, 0);
	//2.连接到mysql server
	if(connection == NULL)
	{
		printf("connect error, %s\n", mysql_error(&mysql));
		return -1;
	}
	
	//3.sql语句
	if (mysql_query(connection, "SET NAMES utf8") != 0)		//设置字符集为UTF8, 很重要, 否则下一条不会删除	
	{		
		printf("设置字符集错误, %s\n", mysql_error(&mysql));	
	}
	char SQL[1024];
	memset(SQL, 0, sizeof(SQL));
	sprintf(SQL, "%s", "请输入要干掉的名字>:");	write(STDOUT_FILENO, SQL, strlen(SQL));
	
	char name[1024];
	memset(name, 0, sizeof(name));
	read(STDIN_FILENO, name, sizeof(name));
	name[strlen(name)-1] = 0;//将敲入的回车替换为0

	sprintf(SQL, "delete from table1 Where name = '%s'", name);
	if (mysql_query(connection, SQL) != 0)
	{
		printf("connect error, %s\n", mysql_error(&mysql));
        return -1;
	}	

	//4.断开与SQL server的连接
	mysql_close(connection);
	printf("!!!Hello World!!! %d\n", EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
