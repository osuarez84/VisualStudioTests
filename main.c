#include "main.h"
#include <math.h>
#include <stdio.h>


DF_CVTypeDef DF_CV;
DF_LSVTypeDef DF_LSV;
DF_SCVTypeDef DF_SCV;

float LUT1[10001];						// Reservamos memoria para meter el m�ximo de puntos en el peor de los casos
float LUT2[10001];
float LUT3[10001];
float LUTcomplete[31000];				// Reservo espacio de sobra para la LUT completa
int32_t LUTDAC[31000];					// Tabla con datos convertidos a valor DAC




void Init(DF_CVTypeDef* df, DF_LSVTypeDef* df2, DF_SCVTypeDef* df3);
uint32_t generateRamp(float eStart, float eStop, float eStep, float* lut);
uint32_t concatenateLUTs(float* lut1, float* lut2, float* lut3, float* lutC, uint32_t n1, uint32_t n2, uint32_t n3);
void generateDACValues(float* lut, int32_t* data, uint32_t n);
void generateCVsignal(DF_CVTypeDef df);
void generateLSVsignal(DF_LSVTypeDef df);
void generateSCVsignal(DF_SCVTypeDef df);

void printFloatToFile(float* lut, uint32_t LUTsize);


void main() {

	/* Datos CV */
	DF_CV.Measurement.start = 0.34;
	DF_CV.Measurement.vtx1 = -0.4;
	DF_CV.Measurement.vtx2 = 0.76;
	DF_CV.Measurement.step = 0.01;
	DF_CV.Measurement.sr = 1;

	/* Datos LSV */
	DF_LSV.Measurement.start = 1.1;
	DF_LSV.Measurement.stop	= -4.3;
	DF_LSV.Measurement.step = 0.3;

	/* Datos SCV */
	DF_SCV.Measurement.start = 1.1;
	DF_SCV.Measurement.stop = -4.3;
	DF_SCV.Measurement.step = 0.21;



	/* Inicializamos la CV con los datos del USB */
	Init(&DF_CV, &DF_LSV, &DF_SCV);





	return 0;

}


/**
* @brief	This function initializes the system to perform a CV
* @param	Data from PC
* @retval	None
*/
void Init(DF_CVTypeDef* df, DF_LSVTypeDef* df2, DF_SCVTypeDef* df3) {
	
	
	/* Configurar todos los rel�s y switches para seleccion de escalas, etc */
	// TODO

//	uint32_t nSamples1 = generateRamp(USB_DF_Rx->Measurement.start, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT1);
//	uint32_t nSamples2 = generateRamp(USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.step, LUT2);
//	uint32_t nSamples3 = generateRamp(USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT3);

//	uint32_t lengthLUT = concatenateLUTs(LUT1, LUT2, LUT3, LUTcomplete, nSamples1, nSamples2, nSamples3);

	/* Generating LUTs */
	//generateCVsignal(*df);
	//generateLSVsignal(*df2);
	generateSCVsignal(*df3);

	/* Conversi�n de los valores de la LUT a datos para el DAC */
	// TODO
	// La f�rmula para convertir valores de tensi�n al DAC es: 
	// 			DAC_DHR (valor digital) = ( (2^n + 1) * Vout ) / Vref
	//		
	//		Donde:
	//			+ DAC_DHR => valor digital que queremos cargar en el DAC	
	//			+ n => n�mero de bits (en este caso es 12 bits)
	//			+ Vout => tensi�n que queremos sacar por el DAC. Este es el valor que se guarda
	//					en la LUT.
	//			+ Vref => es la tensi�n de referencia que tiene el DAC conectada (en este caso 3.3VDC)
	//generateDACValues(LUTcomplete, LUTDAC, lengthLUT);



	/* Configurar el Timer que dispara la salida del DAC */
	// TODO



	/* Env�o de datos a la SDRAM */
	// TODO



	/* Debugging to a txt file */
	//printFloatToFile(LUTcomplete, lengthLUT);

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

	// TODO : si trabajamos con valores uint16_t directamente
	// es necesario cambiar la funci�n fabsf que devuelve un float
	// a abs, que devuelve un int

	uint32_t nSamples = ceil(fabsf(eStart - eStop) / eStep) + 1;				// Calculamos n�mero de puntos...
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

	n1--;																// El �ltimo pto de la LUT1 es igual al primero de la LUT2
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


/* FUNCTIONS FOR GENERATING SIGNALS LUT ---------------------------------------------------------------------- */
void generateCVsignal(DF_CVTypeDef df) {

	uint32_t nSamples1 = generateRamp(df.Measurement.start, df.Measurement.vtx1, df.Measurement.step, LUT1);
	uint32_t nSamples2 = generateRamp(df.Measurement.vtx1, df.Measurement.vtx2, df.Measurement.step, LUT2);
	uint32_t nSamples3 = generateRamp(df.Measurement.vtx2, df.Measurement.vtx1, df.Measurement.step, LUT3);

	uint32_t lengthLUT = concatenateLUTs(LUT1, LUT2, LUT3, LUTcomplete, nSamples1, nSamples2, nSamples3);



	/* TESTING */
	printFloatToFile(LUTcomplete, lengthLUT);
}


void generateLSVsignal(DF_LSVTypeDef df) {
	
	uint32_t lengthLUT = generateRamp(df.Measurement.start, df.Measurement.stop, df.Measurement.step, LUTcomplete);

	/* Escribimos el Estop en el �ltimo valor de la LUT */
	LUTcomplete[lengthLUT-1] = df.Measurement.stop;

	/* TESTING */
	printFloatToFile(LUTcomplete, lengthLUT);
}


void generateSCVsignal(DF_SCVTypeDef df) {

	uint32_t nSamples1 = generateRamp(df.Measurement.start, df.Measurement.stop, df.Measurement.step, LUT1);
	uint32_t nSamples2 = generateRamp(df.Measurement.stop, df.Measurement.start, df.Measurement.step, LUT2);

	/* Enviamos el �ltimo punto del per�odo completo, que es el start */
	// Usamos la misma funci�n concatenateLUTs, pero como en este caso son dos tramos hacemos
	// este truco y enviamos el �ltimo punto en la tercera LUT. As� no necesitamos definir
	// otra funci�n.
	uint32_t nSamples3 = 1;
	LUT3[0] = df.Measurement.start;

	uint32_t lengthLUT = concatenateLUTs(LUT1, LUT2, LUT3, LUTcomplete, nSamples1, nSamples2, nSamples3);


	/* TESTING */
	printFloatToFile(LUTcomplete, lengthLUT);
}


/**
* @brief	Prints data to txt file (debugging purposes)
* @param	Pointer to LUT containing data
* @param	Size of the LUT
* @retval	None
*/
void printFloatToFile(float* lut, uint32_t LUTsize) {

	FILE *f = fopen("LUT.txt", "w");
	if (f == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	for (uint32_t i = 0; i < LUTsize; i++) {
		fprintf(f, "%f\n", lut[i]);
	}

	fclose(f);


}