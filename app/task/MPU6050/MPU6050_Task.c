#include <MPU6050_Task.h>
#define  APP_CFG_TASK_MPU6050_PRIO          4u
#define  APP_CFG_TASK_MPU6050_STK_SIZE 		512
OS_TCB       MPU6050_TaskTCB;
CPU_STK      MPU6050_TaskStk[APP_CFG_TASK_MPU6050_STK_SIZE];

void MPU6050_Task()
{
	OS_ERR  err;
	while(DEF_TRUE)
	{
		MPU6050GetGyro(&gyro);
		MPU6050GetAcc(&acc);
		// USART1_Send(gyro.x_data>>8);
		OSTimeDlyHMSM(0u, 0u, 0u, 10u,
	                  OS_OPT_TIME_HMSM_STRICT,
	                  &err);
	}
}

void MPU6050_TaskCreate()
{
	OS_ERR  err;
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