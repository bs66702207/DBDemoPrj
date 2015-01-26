#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <termios.h>
#include <mysql/mysql.h>

int main(void)
{
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

	if (mysql_query(connection, "delete from table1 Where name = '赵倩'") != 0)
	{
		printf("connect error, %s\n", mysql_error(&mysql));
        return -1;
	}	

	//4.断开与SQL server的连接
	mysql_close(connection);
	printf("!!!Hello World!!! %d\n", EXIT_SUCCESS);
	return EXIT_SUCCESS;
}
