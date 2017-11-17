/* Define to prevent recursive inclusion --------------------------------------*/

#ifndef __REGMAP_H

#define __REGMAP_H

/* Includes -------------------------------------------------------------------*/

#include "stm32f10x.h"
//#include "stm32f0xx.h"


/* Exported_Macros ------------------------------------------------------------*/

typedef uint16_t uint16;
typedef uint32_t uint32;

/* Exported_Types -------------------------------------------------------------*/

//2 byte aligned
#pragma pack(2)

typedef	struct sysStatus
{											        /* Register		Type  		 R/W */
	uint16		runStatus;					/* 41001	 16bit integer	r/w */
	uint16   	commStatus;					/* 41002	 16bit integer	r/w */
	uint16 		calibStatus;				/* 41003 	 16bit integer 	r/w */
	uint16		configStatus;				/* 41004	 16bit integer	r/w */
	uint32    productNum;					/* 41005	 32bit integer 	r/w */
	char		  deviceName[16];     /* 41007	 128bit char 	  r/w */
	char		  serialNum[16];      /* 41015	 128bit char 	  r/w */
	char		  hardwareVer[16];    /* 41023   128bit char    r/w */
	char		  softwareVer[16];    /* 41031   128bit char    r/w */
	uint16		reserved[8];				/* 41039   reserved */
} SYS_STATUS_T;

typedef struct commSettings
{											        /* Register		Type  		 R/W */
	uint16		modbusAddr;					/* 42001 	 16bit integer   r/w */
	uint16		modbusDatabits;			/* 42002 	 16bit integer   r/w */
	uint16		modbusParity;				/* 42003 	 16bit integer   r/w */
	uint32		modbusBaud;					/* 42004 	 32bit integer   r/w */
	uint16		reserved[4];				/* 42006   reserved */
} COMM_SETTINGS_T;

typedef	struct measureSettings
{											        /* Register		Type  		 R/W */
	uint16		sampleCycle;				/* 43001	 16bit integer	 r/w  useless*/
	float		  measureRange;			  /* 43002	 32bit float	   r/w */
	float		  smoothingFactor;		/* 43004 	 32bit float     r/w */
	uint16		command;				    /* 43006	 16bit integer	 r/w  useless*/
	uint16		reserved[4];			  /* 43007   reserved */
} MEASURE_SETTINGS_T;

typedef	struct calibSettings
{											        /* Register		Type  		 R/W */
	uint16		calibType;					/* 44001	 16bit integer	 r/w  1.单点校准   2.两点校准 */
	float		  calibSolution;		  /* 44002	 32bit float		 r/w  sample concentration */
	uint16		calibCommand;       /* 44004   16bit integer   r/w  DI calibration  ;*/  
	uint16		reserved[7];				/* 44005   reserved */
} CALIB_SETTINGS_T;
//struct filterSettings is not used, reserved
typedef	struct filterSettings
{											        /* Register		Type  		 R/W */
	uint16	filterType;					  /* 45001	 16bit integer   r/w */
	float		filterCoefficient_1;  /* 45002	 32bit float     r/w */
	float		filterCoefficient_2;  /* 45004	 32bit float     r/w */
	uint16	reserved[4];				  /* 45006   reserved */
} FILTER_SETTINGS_T;

typedef struct measureValues
{														  /* Register		Type  		 R/W */
	float		sensorValue;				  /* 46001	 32bit float	  r/w */
	float		sensorValue_mA;			  /* 46003	 32bit float	  r/w */
	float   temperatureValue;		  /* 46005	 32bit float	  r/w */
	float  	humidityValue; 			  /* 46007   32bit float    r/w (humidity) */
	float 	reserved[2];				  /* reserved */
} MEASURE_VALUES_T;


// Below are sensor specific registers, pH meter may have different definition
// All sensor specific registers start from 48001

typedef	struct sensorParam
{                           /* Register		Type  		 R/W */	
  uint16    reserved1;       /* 48001   16bit integer   useless r/w */
  float     slope;           /* 48002   32bit float     r/w */
  float     intercept;       /* 48004   32bit float     useless r/w */
  float     t1;              /* 48006   32bit float     r/w */
  float     t2;              /* 48008   32bit float     r/w */
  uint16    mARange1;        /* 48009   32bit float     r/w */
  uint16    mARange2;        /* 48010   16bit integer   r/w */
  uint16    reserved2;     /* 48011   16bit integer   r/w */
  uint16    ledDelayTime;    /* 48012   16bit integer   r/w */
  uint16    cLED1;           /* 48013   16bit integer   r/w */
  uint16    cLED2;           /* 48014   16bit integer   r/w */ 
  uint16    VGA1;
  uint16    VGA2;
  uint16    DAC2;	
  uint16    PD1di;           /* 48015   16bit integer   r/w */
  uint16    PD2di;           /* 48016   16bit integer   r/w */
  uint16    PD3di;           /* 48017   16bit integer   r/w */
  uint16    pdEnddi;         /* 48018   16bit integer   r/w */
  uint16    PD1;             /* 48019   16bit integer   r/w */
  uint16    PD2;             /* 48021   16bit integer   r/w */
  uint16    PD3;             /* 48022   16bit integer   r/w */
  uint16    pdEnd;           /* 48023   16bit integer   r/w */
  uint16    ctLED1Factory;   /* 48024   16bit integer   r/w */
  uint16    ctLED2Factory;   /* 48025   16bit integer   r/w */
  uint16    PD1diFactory;    /* 48026   16bit integer   r/w */
  uint16    PD2diFactory;    /* 48027   16bit integer   r/w */
  uint16    PD3diFactory;    /* 48028   16bit integer   r/w */
  uint16    pdEnddiFactory;  /* 48029   16bit integer   r/w */ 
  uint16    errorCode;	     /* 48030   16bit integer   useless r/w */
  uint16    reserved[4];     /* 48031 reserved */
} SENSOR_PARAM_T;

#pragma pack()

/* Exported_Functions ---------------------------------------------------------*/

#endif

