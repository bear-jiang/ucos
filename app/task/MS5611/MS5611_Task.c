#include <MS5611_Task.h>
#define  APP_CFG_TASK_MS5611_PRIO          4u
#define  APP_CFG_TASK_MS5611_STK_SIZE 		512
OS_TCB       MS5611_TaskTCB;
CPU_STK      MS5611_TaskStk[APP_CFG_TASK_MS5611_STK_SIZE];

void MS5611_Task()
{
	OS_ERR  err;
	MS5611_Init();
	while(DEF_TRUE)
	{
		MS5611_Read_Adc_P();
		OSTimeDlyHMSM(0u, 0u, 0u, 10u,
	                  OS_OPT_TIME_HMSM_STRICT,
	                  &err);
	}
}

void MS5611_TaskCreate()
{
	OS_ERR  err;
	OSTaskCreate((OS_TCB      *)&MS5611_TaskTCB,
                 (CPU_CHAR    *)"get sensor",
                 (OS_TASK_PTR  ) MS5611_Task, 
                 (void        *) 0,
                 (OS_PRIO      ) APP_CFG_TASK_MS5611_PRIO,
                 (CPU_STK     *)&MS5611_TaskStk[0],
                 (CPU_STK_SIZE ) MS5611_TaskStk[APP_CFG_TASK_MS5611_STK_SIZE / 10u],
                 (CPU_STK_SIZE ) APP_CFG_TASK_MS5611_STK_SIZE,
                 (OS_MSG_QTY   ) 0u,
                 (OS_TICK      ) 0u,
                 (void        *) 0,
                 (OS_OPT       )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR | OS_OPT_TASK_SAVE_FP),
                 (OS_ERR      *)&err);
}