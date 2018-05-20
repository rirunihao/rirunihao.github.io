1.用easyX安装头文件及配置信息
2.easyX仅适用于c++文件
3.vc6.0中可以这样使用sprintf
		char s[50];
		sprintf(s, "游戏时间 %d",time);
但是在vs编译器中使用sprintf
		TCHAR str[50];
		sprintf(str,"剩余时间：%2d s",sec);
