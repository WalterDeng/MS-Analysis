# -*- coding: utf-8 -*-

# 导入必要模块
import pandas as pd
from sqlalchemy import create_engine

# 初始化数据库连接，使用pymysql模块
# MySQL的用户：root, 密码:jzwl, 端口：3306,数据库：zs1e
engine = create_engine('mysql+pymysql://root:jzwl@localhost:3306/zs1e')

def db_read_table(sql):
    """
    依据sql语句读出数据
    :param sql: eg: 'select * from mydb limit 3'
    :return: pd.df
    """
    df = pd.read_sql_query(sql, engine)
    return df

def db_write_table(table_name, df_data):
    """
    无表时自动建表，表存在就追加
    :param table_name: 'table_name'
    :param df_data: pd.df
    :return:
    """
    # 将新建的DataFrame储存为MySQL中的数据表，不储存index列
    df_data.to_sql(table_name, engine, index=False, if_exists='append')
    return

def db_delete_data(dele_sql):
    """
    如果有一个列表要删除，可以参考：
    for id in df_newdata.index:
        # 先删除要新增的数据
        dele_sql = f"delete from student where id={id}"
        engine.execute(dele_sql)
    :param dele_sql:
    :return:
    """
    engine.execute(dele_sql)
    return

def db_execute(sql):
    engine.execute(sql)
    return

# db_write_table('mydb', pd.DataFrame({'id': [5,6], 'num': [66, 67]}))
# df = db_read_table('select * from mydb limit 3')
# print(df)