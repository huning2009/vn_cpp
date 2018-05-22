//
// Created by root on 5/11/18.
//

#ifndef BT_GBK2UTF_H
#define BT_GBK2UTF_H
#include <stdlib.h>
#include <locale.h>
/******************************************************************************
 * function: gbk2utf8
 * description: 实现由gbk编码到utf8编码的转换
 *
 * input: utfstr,转换后的字符串;  srcstr,待转换的字符串; maxutfstrlen, utfstr的最
            大长度
 * output: utfstr
 * returns: -1,fail;>0,success
 *
 * modification history
 * --------------------
 *  2011-nov-25, lvhongya written
 * --------------------
 ******************************************************************************/
#define  null 0
int gbk2utf8(char *utfstr,const char *srcstr,int maxutfstrlen)
{
    if(srcstr==null)
    {
        printf("bad parameter1\n");
        return -1;
    }
    //首先先将gbk编码转换为unicode编码

    if(null==setlocale(LC_ALL,"zh_CN.gbk"))//设置转换为unicode前的码,当前为gbk编码
    {
        printf("bad parameter2\n");
        return -1;
    }
    int unicodelen=mbstowcs(null,srcstr,0);//计算转换后的长度
    if(unicodelen<=0)
    {
        printf("can not transfer!!!\n");
        return -1;
    }
    wchar_t *unicodestr=(wchar_t *)calloc(sizeof(wchar_t),unicodelen+1);
    mbstowcs(unicodestr,srcstr,strlen(srcstr));//将gbk转换为unicode

    //将unicode编码转换为utf8编码
    if(null==setlocale(LC_ALL,"zh_CN.utf8"))//设置unicode转换后的码,当前为utf8
    {
        printf("bad parameter\n");
        return -1;
    }
    int utflen=wcstombs(null,unicodestr,0);//计算转换后的长度
    if(utflen<=0)
    {
        printf("can not transfer!!!\n");
        return -1;
    }
    else if(utflen>=maxutfstrlen)//判断空间是否足够
    {
        printf("dst str memory not enough\n");
        return -1;
    }
    wcstombs(utfstr,unicodestr,utflen);
    utfstr[utflen]=0;//添加结束符
    free(unicodestr);
    return utflen;
}
#endif //BT_GBK2UTF_H
