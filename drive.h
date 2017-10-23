/*
 * drive.h
 *
 * Created: 10/23/2017 3:16:43 PM
 *  Author: abheesh
 */ 


#ifndef DRIVE_H_
#define DRIVE_H_

#include "motor.h"


float velocity_motor[3];
float ocr_motor[4];
int velocity_robot[3];
extern Motor m1,m2,m3,m4;
float coupling_matrix[4][3] = {{-0.707,0.707,1},{-0.707,-0.707,1},{0.707,-0.707,1},{0.707,0.707,1}};

void calculatevel()
{
	
	for(int i=0;i<4;i++)
	{
		velocity_motor[i] = 0;
		for(int j=0;j<3;j++)
		{
			velocity_motor[i] += velocity_robot[j] * coupling_matrix[i][j];
		}
	}
	
	for(int i=0;i<4;i++)
	{
		ocr_motor[i] = int(((249.0*velocity_motor[i])/(MAX_RPM)));//multiply by icr_top value
		//velocity_robot[i] = 0;
	}
	m1.SetOcrValue(ocr_motor[0]);
	m2.SetOcrValue(ocr_motor[1]);
	m3.SetOcrValue(ocr_motor[2]);
	m4.SetOcrValue(ocr_motor[3]);
	
}


void movx(void)
{
	UART0TransmitString("x direction \r\n");
	velocity_robot[0] = 100;
	velocity_robot[1] = 0; 
	velocity_robot[2] = 0;
	calculatevel();
}

void movy(void)
{
	UART0TransmitString("y direction \r\n");
	velocity_robot[1] = 100;
	velocity_robot[0] = 0;
	velocity_robot[2] = 0;
	calculatevel();
}




#endif /* DRIVE_H_ */