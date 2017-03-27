#include "main.h"
#include <math.h>


DF_CVTypeDef USB_DF_Rx;
float LUT1[10001];						// Reservamos memoria para meter el máximo de puntos en el peor de los casos
float LUT2[10001];
float LUT3[10001];
float LUTcomplete[31000];				// Reservo espacio de sobra para la LUT completa
int32_t LUTDAC[31000];					// Tabla con datos convertidos a valor DAC




void CV_Init(DF_CVTypeDef *USB_DF_Rx);
uint32_t generateRamp(float eStart, float eStop, float eStep, float* lut);
uint32_t concatenateLUTs(float* lut1, float* lut2, float* lut3, float* lutC, uint32_t n1, uint32_t n2, uint32_t n3);
void generateDACValues(float* lut, uint32_t n);



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


	USB_DF_Rx.Measurement.start = 1;
	USB_DF_Rx.Measurement.vtx1 = 5;
	USB_DF_Rx.Measurement.vtx2 = 3;
	USB_DF_Rx.Measurement.step = 0.001;
	USB_DF_Rx.Measurement.sr = 13;


	/* Inicializamos la CV con los datos del USB */
	CV_Init(&USB_DF_Rx);



	return 0;

}


/**
* @brief	This function initializes the system to perform a CV
* @param	Data from PC
* @retval	None
*/
void CV_Init(DF_CVTypeDef* USB_DF_Rx) {
	
	
	/* Configurar todos los relés y switches para seleccion de escalas, etc */
	// TODO

	/* Crear la tabla de datos para la SDRAM */
	uint32_t nSamples1 = generateRamp(USB_DF_Rx->Measurement.start, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT1);
	uint32_t nSamples2 = generateRamp(USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.step, LUT2);
	uint32_t nSamples3 = generateRamp(USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT3);

	uint32_t lengthLUT = concatenateLUTs(LUT1, LUT2, LUT3, LUTcomplete, nSamples1, nSamples2, nSamples3);

	/* Conversión de los valores de la LUT a datos para el DAC */
	// TODO
	// La fórmula para convertir valores de tensión al DAC es: 
	// 			DAC_DHR (valor digital) = ( (2^n + 1) * Vout ) / Vref
	//		
	//		Donde:
	//			+ DAC_DHR => valor digital que queremos cargar en el DAC	
	//			+ n => número de bits (en este caso es 12 bits)
	//			+ Vout => tensión que queremos sacar por el DAC. Este es el valor que se guarda
	//					en la LUT.
	//			+ Vref => es la tensión de referencia que tiene el DAC conectada (en este caso 3.3VDC)
	generateDACValues(LUTcomplete, LUTDAC, lengthLUT);



	/* Configurar el Timer que dispara la salida del DAC */
	// TODO



	/* Envío de datos a la SDRAM */
	// TODO

}



/**
* @brief	Generate the data points between start and stop points
* @param	Start point
* @param	End point
* @param	Step between two consecutive points
* @param	Pointer to an array to save the data
* @retval	No. samples 
*/
uint32_t generateRamp(float eStart, float eStop, float eStep, float* lut) {


	uint32_t nSamples = ceil(abs(eStart - eStop) / eStep) + 1;					// Calculamos número de puntos...
	lut[0] = eStart;															// Cargamos primer valor en LUT...

	for (uint32_t i = 1; i < nSamples; i++) {

		if (eStart < eStop) {													// Rampa aumenta...
			lut[i] = eStart + (i * eStep);
		}
		else {																	// Rampa disminuye...
			lut[i] = eStart - (i * eStep);
		}

	}

	return nSamples;


}


/**
* @brief	Concatenates the arrays containing the LUTs
* @param	Pointer to LUT1
* @param	Pointer to LUT2
* @param	Pointer to LUT3
* @param	Pointer to LUT where to put the complete data
* @param	No. samples of the LUT1
* @param	No. samples of the LUT2
* @param	No. samples of the LUT3
* @retval	No. samples of the complete data (1 scan)
*/
uint32_t concatenateLUTs(float* lut1, float* lut2, float* lut3, float* lutC, uint32_t n1, uint32_t n2, uint32_t n3) {

	n1--;																// El último pto de la LUT1 es igual al primero de la LUT2
	n2--;																// por lo que lo desechamos. Lo mismo para LUT2 y LUT3
	
	for (uint32_t i = 0; i < n1; i++) {									
		lutC[i] = lut1[i];												
	}

	for (uint32_t i = 0; i < n2; i++) {									
		lutC[i + n1] = lut2[i];
	}

	for (uint32_t i = 0; i < n3; i++) {
		lutC[i + (n1 + n2)] = lut3[i];
	}

	return (n1 + n2 + n3);

}



/**
* @brief	Computes the DAC value from the voltage value 
* @param	Pointer to LUT with output voltage data
* @param	Pointer to an array to save the DAC LUT
* @param	No. samples of LUT with the output voltage data
* @retval	None
*/
void generateDACValues(float* lut, int32_t* data, uint32_t n) {

	/* Rutina para calcular la potencia de 2^NBITSDAC (para evitar el uso de pow())*/
	uint32_t DACp = 2;		// base
	for (uint32_t i = 0; i < (NBITSDAC - 1); i++) {
		DACp *= 2;
	}

	for (uint32_t i = 0; i <= n; i++) {
		data[i] = (( (DACp + 1) * lut[i]) / VREF);
	}

}