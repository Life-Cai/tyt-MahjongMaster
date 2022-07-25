/*
* 一个简易的JSON解析器 非标准JSON
* 实现功能：列表 对象 布尔型 数字(只有整型) 字符串(不支持转义\u)
* 允许换行、缩进 不允许注释
* 不符合以上规范解析器大概率当场暴毙(?)
* 符合以上规范解析器也可能照样暴毙(??)
*/

#ifndef TYT_JSON
#define TYT_JSON

#include"JSONBasic.hpp"
#include"JSONParse.hpp"
#include"JSONStringify.hpp"

#endif