# TM1638 LED数码管显示模块驱动库
## 基于具体模块开发， <u> 非通用 </u>
### 实现函数：
- void tm_init(void);
	- 上电初始化 
- void tm_clear(void);
	- 清屏 
- void setNum(u8 order,u8 num);
	- 显示数字；num==16清空当前数码管
- void setNumdot(u8 order,u8 num);
	- 显示数字同时点亮对应小数点
- void setLed(u8 order,u8 on);
	- 控制LED灯珠亮灭
- u8 readKey(void);
	- 返回首个按下的按键序号
- u8 readKeylist(u8 *keylist);
	- 返回按下按键的数量，并将所有按下按键序号填入keylist指向地址