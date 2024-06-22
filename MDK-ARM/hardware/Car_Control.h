#ifndef __CAR_CONTROL_H
#define __CAR_CONTROL_H

typedef struct{
		 char EnReturn;
	   char ReAdd;
}Return;

extern Return Areturn;

char Car_depart(char* startflage);

char Car_return(char* startflage);



#endif

