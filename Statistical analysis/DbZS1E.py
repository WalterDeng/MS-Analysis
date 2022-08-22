import pymysql


class DbZS1E():
    # 构造方法
    def __init__(self):
        conn = pymysql.connect(
            host='localhost',
            user='root',
            password='jzwl',
            db='zs1e',
            charset='utf8',
            autocommit=True,  # 如果插入数据，， 是否自动提交? 和conn.commit()功能一致。
        )
        self.conn = conn
        self.cur = conn.cursor()

    def transfer(self, source_id, target_id, money):
        if not self.check_account_avaialbe(source_id):

            raise Exception("账户不存在")
        if not self.check_account_avaialbe(target_id):
            raise Exception("账户不存在")
        if self.has_enough_money(source_id, money):
            try:
                self.reduce_money(source_id, money)
                self.add_money(target_id, money)
            except Exception as e:
                print("转账失败:", e)
                self.conn.rollback()
            else:
                self.conn.commit()
                print("%s给%s转账%s金额成功" % (source_id, target_id, money))


    def check_account_avaialbe(self, acc_id):
        """判断帐号是否存在， 传递的参数是银行卡号的id"""
        select_sqli = "select * from bankData where id=%d;" % (acc_id)
        print("execute sql:", select_sqli)
        res_count = self.cur.execute(select_sqli)
        if res_count == 1:
            return True
        else:
            # raise  Exception("账户%s不存在" %(acc_id))
            return False


    def has_enough_money(self, acc_id, money):
        """判断acc_id账户上金额> money"""
        # 查找acc_id存储金额?
        select_sqli = "select money from bankData where id=%d;" % (acc_id)
        print("execute sql:", select_sqli)
        self.cur.execute(select_sqli)  # ((1, 500), )
        # 获取查询到的金额钱数;
        acc_money = self.cur.fetchone()[0]
        # 判断
        if acc_money >= money:
            return True
        else:
            return False


    def add_money(self, acc_id, money):
        update_sqli = "update bankData set money=money+%d  where id=%d" % (money, acc_id)
        print("add money:", update_sqli)
        self.cur.execute(update_sqli)


    def reduce_money(self, acc_id, money):
        update_sqli = "update bankData set money=money-%d  where id=%d" % (money, acc_id)
        print("reduce money:", update_sqli)
        self.cur.execute(update_sqli)


    # 析构方法
    def __del__(self):
        self.cur.close()
        self.conn.close()


if __name__ == '__main__':
    # 1. 连接数据库，

    trans = db_ZS1E()
    trans.transfer(13997, 13998, 200)  # 账户13997向13998转账200
