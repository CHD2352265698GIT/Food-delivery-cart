#ifndef __INFRARED_H__
#define __INFRARED_H__

struct infared{
	 char IO1;
	 char IO2;
	 char IO3;
	 char IO4;
	 char IO5;
	 char switchtemp; //����/�رռ��
};
typedef struct infared infared;
extern infared Infared;


#endif
