#define _CRT_SECURE_NO_WARNINGS


#include <stdint.h>



#define		NBITSDAC	12
#define		VREF		3.3


/* Definición estructuras datos recibidas por el USB */
typedef struct {
	char init_1;
	char init_2;
	char init_3;
	uint8_t bipot, working;
} DF_HEADER;


typedef struct {
	uint8_t	exp;
	uint16_t rango;
	uint8_t high_gain;
	uint8_t cell_on;
	float tCond;
	float eCond;
	float tDep;
	float eDep;
	float tEq;
	float eEq;
	uint16_t cell;
}DF_PRETREATMENT_PAR;

/* Estructuras para VOLTAMETRIAS */
// CV
typedef struct {
	float start;
	float vtx1;
	float vtx2;
	float step;
	float sr;
	uint16_t scans;
} DF_MEASUREMENT_PAR_CV;

// LSV
typedef struct {
	float start;
	float stop;
	float step;
	float sr;
} DF_MEASUREMENT_PAR_LSV;

// SCV
typedef struct {
	float start;
	float stop;
	float step;
	float sr;
	float tHold;
	uint16_t scans;
} DF_MEASUREMENT_PAR_SCV;


// DPV
typedef struct {
	float start;
	float stop;
	float step;
	float ePulse;
	float tPulse;
	float sr;
}DF_MEASUREMENT_PAR_DPV;

// NPV
typedef struct {
	float start;
	float stop;
	float step;
	float tPulse;
	float sr;
}DF_MEASUREMENT_PAR_NPV;

// DNPV
typedef struct {
	float start;
	float stop;
	float step;
	float ePulse;
	float tPulse1;
	float tPulse2;
	float sr;
}DF_MEASUREMENT_PAR_DNPV;

// SWV
typedef struct {
	float start;
	float stop;
	float step;
	float amplitude;
	float freq;
}DF_MEASUREMENT_PAR_SWV;

// ACV | SHACV | FTACV
typedef struct {
	float start;
	float stop;
	float step;
	float ACamplitude;
	float sr;
	float freq;
}DF_MEASUREMENT_PAR_AC;



/* Estructuras para AMPEROMETRIAS */
// AD | FAM | ZRA
typedef struct {
	float Edc;
	float tInt;					// En FAM tInt < 0.05s
	float tRun;
}DF_MEASUREMENT_PAR_AD;

// DSCA
typedef struct {
	float eStep1;
	float tStep1;
	float eStep2;
	float tStep2;
	float tInt;
	float tRun;					// t run = tStep1 + tStep2
}DF_MEASUREMENT_PAR_DSCA;


// PAD
typedef struct {
	float Edc;
	float ePulse1;
	float tPulse1;
	float ePulse2;
	float tPulse2;
	float tInt;
	float tRun;
}DF_MEASUREMENT_PAR_PAD;

// DPA
typedef struct {
	float Edc;
	float ePulse;
	float tPulse;
	float tInt;					// tInt > tPulse
	float tRun;
	uint8_t mode;				// 3 modos de funcionamiento
}DF_MEASUREMENT_PAR_DPA;

// MSA (Multistep Amperometry)
// TODO: hay que definir cuantos steps vamos a ser capaces de definir como mucho
// para habilitar espacio de sobra en memoria para las variables
/*
typedef struct {
	
}DF_MEASUREMENT_PAR_MSA;
*/

// HFP
typedef struct {
	float dc;
}DF_MEASUREMENT_PAR_HFP;


/* Estructuras para POTENCIOMETRIAS */
// PD | FP 
typedef struct {					// Similar a la amperometría AD: aplicamos corriente cte y medimos potencial
	float Idc;
	float tInt;
	float tRun;
}DF_MEASUREMENT_PAR_PD;

// DSCP								// Waveform similar a la DSCA
typedef struct {
	float iStep1;
	float tStep1;
	float iStep2;
	float tStep2;
	float tInt;
	float tRun;					// t run = tStep1 + tStep2
}DF_MEASUREMENT_PAR_DSCP;


// CPCR
typedef struct {
	float iStart;
	float iStop;
	float step;
	float sr;
}DF_MEASUREMENT_PAR_CPCR;


// MSP (Multistep Potentiometry)
// TODO: hay que definir cuantos steps vamos a ser capaces de definir como mucho
// para habilitar espacio de sobra en memoria para las variables
/*typedef struct {

};
*/

// PSA
typedef struct {
	float iStrip;
	float eEnd;
	float tRun;
}DF_MEASUREMENT_PAR_PSA;



/* Estructuras para EIS */
// TODO: Falta definir los parámetros para las EIS




/* DEFINICIÓN DE DATA FRAMES COMPLETOS */
/* Data frames de VOLTAMETRIAS */

// CV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_CV Measurement;
} DF_CVTypeDef;

// LSV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_LSV Measurement;
}DF_LSVTypeDef;

// SCV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_SCV Measurement;
}DF_SCVTypeDef;

// DPV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_DPV Measurement;
}DF_DPVTypeDef;

// NPV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_NPV Measurement;
}DF_NPVTypeDef;

// DNPV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_DNPV Measurement;
}DF_DNPVTypeDef;

// SWV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_SWV Measurement;
}DF_SWVTypeDef;

// ACV | SHACV | FTACV
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_AC Measurement;
}DF_ACTypeDef;


/* Data frames de AMPEROMETRIAS */
// AD | FAM | ZRA
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_AD Measurement;
}DF_ADTypeDef;

// DSCA
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_DSCA Measurement;
}DF_DSCATypeDef;

// PAD
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_PAD Measurement;
}DF_PADTypeDef;

// DPA
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_DPA Measurement;
}DF_DPATypeDef;

// HFP
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_HFP Measurement;
}DF_HFPTypeDef;


/* Data frames de POTENCIOMETRIAS */
// PD | FP 
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_PD Measurement;
}DF_PDTypeDef;

// DSCP	
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_DSCP Measurement;
}DF_DSCPTypeDef;

// CPCR
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_CPCR Measurement;
}DF_CPCRTypeDef;

// PSA
typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_PSA Measurement;
}DF_PSATypeDef;

/* Data frames de EIS */
// TODO








