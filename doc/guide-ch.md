# ʹ��ָ�� ��������
���ʹ�ñ����߽��� .ini �ļ��Ĵ��� 
## ��������
������ʹ�� ini ����ж� .ini �ļ��Ĳ���, ��ϸʹ�÷�������: 
1. ����, ����Ҫ���� ini.hpp: 
`#include "ini/ini.hpp"`
2. ���� ini ����: 
`tab::ini myProfile("MyFilename");`
3. ����ĳ��ֵ: 
`tab::Value val = myProfile["MySection"](MyKey);` 
�����Խ�Value���͵�ֵת��Ϊ�ַ�����������C++��������, ֻ������: 
~~~C++
std::string str = val.val(); // ת�����ַ���
int iVal = val.toInt(); // ת����int
......
~~~
---------------------------------
