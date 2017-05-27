#include <MPU6050_Task.h>
#define  APP_CFG_TASK_MPU6050_PRIO          4u
#define  APP_CFG_TASK_MPU6050_STK_SIZE 		512
OS_TCB       MPU6050_TaskTCB;
CPU_STK      MPU6050_TaskStk[APP_CFG_TASK_MPU6050_STK_SIZE];
OS_SEM MPU6050_RunSem;
void MPU6050_Task()
{
	OS_ERR  err;
	CPU_TS ts;
	I2C_FastMode=1;
	while(DEF_TRUE)
	{
		MPU6050GetGyro(&gyro);
		MPU6050GetAcc(&acc);
		// ValueProtocalPrint((char*)&gyro,sizeof(gyro),GYRO_ID);
		// ValueProtocalPrint((char*)&acc,sizeof(acc),ACC_ID);
		GyroAccValuePrint();
		// OSSemPend(&MPU6050_RunSem,
		// 		  0,
		// 		  OS_OPT_PEND_BLOCKING,
		// 		  &ts,
		// 		  &err
		// 		  );
		OSTimeDlyHMSM(0u, 0u, 0u, 5u,
	                  OS_OPT_TIME_HMSM_STRICT,
	                  &err);
	}
}

void MPU6050_TaskCreate()
{
	OS_ERR  err;
	OSSemCreate(&MPU6050_RunSem,
				"MPU6050_Task timetick",
				(OS_SEM_CTR)0,
				&err);
	OSTaskCreate((OS_TCB      *)&MPU6050_TaskTCB,
                 (CPU_CHAR    *)"get sensor",
                 (OS_TASK_PTR  ) MPU6050_Task, 
                 (void        *) 0,
                 (OS_PRIO      ) APP_CFG_TASK_MPU6050_PRIO,
                 (CPU_STK     *)&MPU6050_TaskStk[0],
                 (CPU_STK_SIZE ) MPU6050_TaskStk[APP_CFG_TASK_MPU6050_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) APP_CFG_TASK_MPU6050_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&err);
}

