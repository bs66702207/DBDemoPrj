/*
 * oracle.h
 *
 *  Created on: 2014年5月29日
 *      Author: zhujy
 */

#ifndef ORACLE_H_
#define ORACLE_H_

void sql_error();//打印错误信息

void sql_init();//初始化oracle

int sql_connect(const char *User, const char *Password, const char *DBName);//连接到oracle

int sql_exec(const char *DySQL);//执行非select SQL语句

int sql_commit();//提交事务

int sql_rollback();//回滚事务

int sql_open(const char *DySQL);//执行select SQL语句

int sql_disconnect();//断开连接

int sql_free();//释放资源



#endif /* ORACLE_H_ */
