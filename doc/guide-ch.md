# 使用指南 简体中文
如何使用本工具进行 .ini 文件的处理 
## 快速入门
您可以使用 ini 类进行对 .ini 文件的操作, 详细使用方法如下: 
0. 首先, 您需要包含 ini.hpp: 
`#include "ini/ini.hpp"`
1. 构造 ini 对象: 
`tab::ini myProfile("MyFilename");`
2. 访问某个值: 
`tab::Value val = myProfile["MySection"](MyKey);` 
您可以将Value类型的值转换为字符串或是其他C++基本类型, 只需这样: 
~~~C++
std::string str = val.val(); // 转换到字符串
int iVal = val.toInt(); // 转换到int
......
~~~
---------------------------------
