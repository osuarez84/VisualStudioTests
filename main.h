#define _CRT_SECURE_NO_WARNINGS


#include <stdint.h>



#define		NBITSDAC	12
#define		VREF		3.3

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
	float t_cond;
	float e_cond;
	float t_dep;
	float e_dep;
	float t_eq;
	uint16_t cell;
}DF_PRETREATMENT_PAR;


typedef struct {
	float start;
	float vtx1;
	float vtx2;
	float step;
	float sr;
	uint16_t scans;
} DF_MEASUREMENT_PAR_CV;



typedef struct {
	DF_HEADER Header;
	DF_PRETREATMENT_PAR Pretreatment;
	DF_MEASUREMENT_PAR_CV Measurement;
} DF_CVTypeDef;



