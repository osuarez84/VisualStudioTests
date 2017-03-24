#include "main.h"
#include <math.h>


DF_CVTypeDef USB_DF_Rx;
float LUT[2000000];



void CV_Init(DF_CVTypeDef *USB_DF_Rx);
void generateRamp(float eStart, float eStop, float eStep, float* lut);





void main() {

	/* Generamos una trama de datos válida para simular la recepción desde el USB */
	USB_DF_Rx.Header.init_1 = 'C';
	USB_DF_Rx.Header.init_2 = 'O';
	USB_DF_Rx.Header.init_3 = 'N';

	USB_DF_Rx.Pretreatment.exp = 0x01;
	USB_DF_Rx.Pretreatment.rango = 0x01;
	USB_DF_Rx.Pretreatment.high_gain = 0x01;
	USB_DF_Rx.Pretreatment.cell_on = 0x01;
	USB_DF_Rx.Pretreatment.t_cond = 342.5;
	USB_DF_Rx.Pretreatment.e_cond = 0.003;
	USB_DF_Rx.Pretreatment.t_dep = 23;
	USB_DF_Rx.Pretreatment.e_dep = 0.012;
	USB_DF_Rx.Pretreatment.t_eq = 0.23;


	USB_DF_Rx.Measurement.start = 0;
	USB_DF_Rx.Measurement.vtx1 = -4;
	USB_DF_Rx.Measurement.vtx2 = 0;
	USB_DF_Rx.Measurement.step = 0.5;
	USB_DF_Rx.Measurement.sr = 13;


	/* Inicializamos la CV con los datos del USB */
	CV_Init(&USB_DF_Rx);


	return 0;

}



void CV_Init(DF_CVTypeDef *USB_DF_Rx) {

	generateRamp(USB_DF_Rx->Measurement.start, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT);

}


void generateRamp(float eStart, float eStop, float eStep, float* lut) {

	uint32_t nSamples = ceil(abs(eStart - eStop) / eStep) + 1;					// Calculamos número de puntos...
	LUT[0] = eStart;															// Cargamos primer valor en LUT...

	for (uint32_t i = 1; i < nSamples; i++) {

		if (eStart < eStop) {														// Rampa aumenta...
			LUT[i] = eStart + (i * eStep);
		}
		else {																	// Rampa disminuye...
			LUT[i] = eStart - (i * eStep);
		}

	}

}


