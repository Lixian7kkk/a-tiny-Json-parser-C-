# a-tiny-Json-parser-C-
my first c++ project
用c++实现的一个简易的Json解析器，根据b站视频学习所写：
https://www.bilibili.com/video/BV1TP411p7cC/?spm_id_from=333.788.top_right_bar_window_custom_collection.content.click&vd_source=8dcd757b019b9d80d7fa35287b8929ae
缺点：1.Json类中的赋值构造函数对于数组类型和对象类型的处理是直接赋值的指针，存在安全隐患；
      2.当数组对象作为值添加到对象类型中时，此时只能对对象类型执行clear操作，若对数组和对象同时执行clear操作则会出现问题
