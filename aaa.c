// mode即传入的存储权限信息的整数， 如0754（八进制表示）
// 提示：传入的 mode 变量不仅包含权限信息，高位可能还包含文件类型。
// 在进行位运算时，请注意屏蔽（Mask）掉不需要的高位数据。000111111111
void parse_permissions(mode_t mode, char *perms) {

    // 权限字符对照表
    char rwx[] = {'r', 'w', 'x'};

    // 请补全代码写在 TO DO 与 END OF TO DO 之间：
    // TO DO

    mode=mode&0777;//(即为111111111)

    for(int i=0;i<9;i++)
    {
        if(mode & (0400 >> i))//判断权限
        {
            perms[i]= rwx[i % 3] ;
        }
        else
        {
            perms[i]='-';
        }
    }

    // END OF TO DO

    perms[9] = '\0'; // 字符串结尾
}