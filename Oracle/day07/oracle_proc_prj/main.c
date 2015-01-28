/* * main.c
 *
 *  Created on: 2014年5月29日
 *      Author: zhujy
 */


#include "oracle.h"

int main()
{
	sql_init();//初始化数据库
	sql_connect("dbuser1", "1", "orcl");//连接到oracle
	sql_exec("insert into table1 (id, name) values (5, '测试')");//执行非SELECT的SQL语句
	sql_open("select * from table1");//执行SELECT SQL语句
	sql_commit();//提交事务
	//sql_rollback();//回滚事务
	sql_disconnect();//断开连接
	sql_free();//释放资源
	return 0;
}


