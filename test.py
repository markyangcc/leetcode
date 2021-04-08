def Get_ei(a, b):

    if 0 == b:
        x = 1
        y = 0
        q = a
        return x, y, q
    xyq = Get_ei(b, a % b)
    x = xyq[0]
    y = xyq[1]
    q = xyq[2]
    temp = x
    x = y
    y = temp - a // b * y
    return x, y, q


def Get_Mi(m_list, M):  # 获取所有的Mi
    M_list = []
    for mi in m_list:
        M_list.append(M // mi)
    return M_list


def Get_ei_list(M_list, m_list):  # 取所有的Mi的逆元
    ei_list = []
    for i in range(len(M_list)):
        ei_list.append(Get_ei(M_list[i], m_list[i])[0])
    return ei_list


def get_c(M_list, ei_list):
    c_list = []
    for i in range(len(M_list)):
        c_list.append(M_list[i] * ei_list[i])
    return c_list


def crt1(a_list, m_list):
    M = 1  # M是所有mi的乘积
    for mi in m_list:
        M *= mi
    Mi_list = Get_Mi(m_list, M)
    Mi_inverse = Get_ei_list(Mi_list, m_list)

    x = 0
    for i in range(len(a_list)):  # 开始计算x
        x += Mi_list[i] * Mi_inverse[i] * a_list[i]
        x %= M
    return x


def crt2(num_list, opt, mlist, c_list):
    a_list = []
    b_list = []
    answer_list = []
    print_list = []
    for i in range(len(num_list)):
        a_list.append(num_list[0] % mlist[i])
        b_list.append(num_list[1] % mlist[i])

    if opt == '1':  # 加法
        for i in range(len(num_list)):
            answer_list.append((a_list[i] + b_list[i]) % mlist[i])  # 名字要一致
        x = 0  # 忘记初始化
        for i in range(len(answer_list)):
            x += answer_list[i] * c_list[i]
            x %= M

    elif opt == '2':  # 乘法
        for i in range(len(num_list)):
            answer_list.append((a_list[i] * b_list[i]) % mlist[i])
        x = 0  # 忘记初始化
        for i in range(len(answer_list)):
            x += answer_list[i] * c_list[i]
            x %= M

    return x


if __name__ == '__main__':
    print("选择您的操作：1是加法 2是乘法 3是计算物不知数")
    s = input()
    if s == '3':
        print("请输入a for crt1")
        a1_list = list(map(int, input().split(",")))
        print("请输入m for crt1")
        m1_list = list(map(int, input().split(",")))
        print("解决物不知数：", crt1(a1_list, m1_list))
    else:
        print("请输入numlist for crt2")
        num_list = list(map(int, input().split(",")))
        print("请输入mlist for crt2")
        m_list = list(map(int, input().split(",")))

        M = 1  # M是所有mi的乘积
        for mi in m_list:
            M *= mi
        Mi_list = Get_Mi(m_list, M)
        Mi_inverse = Get_ei_list(Mi_list, m_list)
        c_list = get_c(Mi_list, Mi_inverse)

        print("加法or乘法的结果为：", crt2(num_list, s, m_list, c_list))
