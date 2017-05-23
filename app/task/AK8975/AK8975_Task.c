#include <AK8975_Task.h>
#define  APP_CFG_TASK_AK8975_PRIO          4u
#define  APP_CFG_TASK_AK8975_STK_SIZE 		512
OS_TCB       AK8975_TaskTCB;
CPU_STK      AK8975_TaskStk[APP_CFG_TASK_AK8975_STK_SIZE];

void AK8975_Task()
{
	OS_ERR  err;
	AK8975Init();
	while(DEF_TRUE)
	{
		GetMag(&mag);
		// USART1_Send(mag.x_data&0xff);
		OSTimeDlyHMSM(0u, 0u, 0u, 10u,
	                  OS_OPT_TIME_HMSM_STRICT,
	                  &err);
	}
}

void AK8975_TaskCreate()
{
	OS_ERR  err;
	OSTaskCreate((OS_TCB      *)&AK8975_TaskTCB,
                 (CPU_CHAR    *)"get sensor",
                 (OS_TASK_PTR  ) AK8975_Task, 
                 (void        *) 0,
                 (OS_PRIO      ) APP_CFG_TASK_AK8975_PRIO,
                 (CPU_STK     *)&AK8975_TaskStk[0],
                 (CPU_STK_SIZE ) AK8975_TaskStk[APP_CFG_TASK_AK8975_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) APP_CFG_TASK_AK8975_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&err);
}