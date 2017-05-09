#include "main.h"
#include <math.h>
#include <stdio.h>


DF_CVTypeDef DF_CV;
DF_LSVTypeDef DF_LSV;
DF_SCVTypeDef DF_SCV;
DF_DPVTypeDef DF_DPV;
DF_NPVTypeDef DF_NPV;
DF_DNPVTypeDef DF_DNPV;
DF_SWVTypeDef DF_SWV;
DF_ACTypeDef DF_ACV;

float LUT1[10001];						// Reservamos memoria para meter el m�ximo de puntos en el peor de los casos
float LUT2[10001];
float LUT3[10001];
float LUTcomplete[31000];				// Reservo espacio de sobra para la LUT completa
int32_t LUTDAC[31000];					// Tabla con datos convertidos a valor DAC



/* FUNCTIONS DEFINITION --------------------------------------------------------------------------- */
void Init(DF_CVTypeDef* df, DF_LSVTypeDef* df2, DF_SCVTypeDef* df3, DF_DPVTypeDef* df4,\
	DF_NPVTypeDef* df5, DF_DNPVTypeDef* df6, DF_SWVTypeDef* df7, DF_ACTypeDef* df8);
uint32_t generateRamp(float eStart, float eStop, float eStep, float* lut);
uint32_t concatenateLUTs(float* lut1, float* lut2, float* lut3, float* lutC, uint32_t n1, uint32_t n2, uint32_t n3);
void generateDACValues(float* lut, int32_t* data, uint32_t n);

/* Functions for generating signal LUT */
void generateCVsignal(DF_CVTypeDef df);
void generateLSVsignal(DF_LSVTypeDef df);
void generateSCVsignal(DF_SCVTypeDef df);
void generateDPVsignal(DF_DPVTypeDef df);
void generateNPVsignal(DF_NPVTypeDef df);
void generateDNPV(DF_DNPVTypeDef df);
void generateSWV(DF_SWVTypeDef df);
void generateACV(DF_ACTypeDef df);

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

	/* Datos DPV */
	DF_DPV.Measurement.start = 0.2;
	DF_DPV.Measurement.stop = -4;
	DF_DPV.Measurement.step = 0.1;
	DF_DPV.Measurement.ePulse = 0.2;
	DF_DPV.Measurement.tPulse = 0.0012;
	DF_DPV.Measurement.sr = 5;

	/* Datos NPV */
	DF_NPV.Measurement.start = 1.96;
	DF_NPV.Measurement.stop = -4.66;
	DF_NPV.Measurement.step = 0.1;
	DF_NPV.Measurement.tPulse = 0.002;
	DF_NPV.Measurement.sr = 6;


	/* DNPV */
	DF_DNPV.Measurement.start = 1.26;
	DF_DNPV.Measurement.stop = -2.88;
	DF_DNPV.Measurement.step = 0.24;
	DF_DNPV.Measurement.ePulse = 0.13;
	DF_DNPV.Measurement.tPulse1 = 0.002;
	DF_DNPV.Measurement.tPulse2 = 0.002;
	DF_DNPV.Measurement.sr = 14;

	/* SWV */
	DF_SWV.Measurement.start = 3.33;
	DF_SWV.Measurement.stop = -4.60;
	DF_SWV.Measurement.step = 0.13;
	DF_SWV.Measurement.amplitude = 0.12;
	DF_SWV.Measurement.freq = 13;

	/* ACV */
	DF_ACV.Measurement.start = 2.21;
	DF_ACV.Measurement.stop = -3.9;
	DF_ACV.Measurement.step = 0.17;
	DF_ACV.Measurement.ACamplitude = 0.04;
	DF_ACV.Measurement.sr = 13;
	DF_ACV.Measurement.freq = 600;


	/* Generamos la se�al */
	Init(&DF_CV, &DF_LSV, &DF_SCV, &DF_DPV, &DF_NPV, &DF_DNPV, &DF_SWV, &DF_ACV);





	return 0;

}


/**
* @brief	This function initializes the system to perform a CV
* @param	Data from PC
* @retval	None
*/
void Init(DF_CVTypeDef* df, DF_LSVTypeDef* df2, DF_SCVTypeDef* df3, DF_DPVTypeDef* df4, \
		DF_NPVTypeDef* df5, DF_DNPVTypeDef* df6, DF_SWVTypeDef* df7, DF_ACTypeDef* df8) {
	
	
	/* Configurar todos los rel�s y switches para seleccion de escalas, etc */
	// TODO

//	uint32_t nSamples1 = generateRamp(USB_DF_Rx->Measurement.start, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT1);
//	uint32_t nSamples2 = generateRamp(USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.step, LUT2);
//	uint32_t nSamples3 = generateRamp(USB_DF_Rx->Measurement.vtx2, USB_DF_Rx->Measurement.vtx1, USB_DF_Rx->Measurement.step, LUT3);

//	uint32_t lengthLUT = concatenateLUTs(LUT1, LUT2, LUT3, LUTcomplete, nSamples1, nSamples2, nSamples3);

	/* Generating LUTs */
	//generateCVsignal(*df);
	//generateLSVsignal(*df2);
	//generateSCVsignal(*df3);
	//generateDPVsignal(*df4);
	//generateNPVsignal(*df5);
	//generateDNPV(*df6);
	//generateSWV(*df7);
	generateACV(*df8);

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



void generateDPVsignal(DF_DPVTypeDef df) {

	uint16_t i, j;

	/* Establecemos un n� m�nimo de samples en el pulso para evitar aliasing a frecuencias altas */
	uint16_t nSamplesPulse = 10;

	/* Tiempo de disparo de cada sample */
	float tTimer = df.Measurement.tPulse / nSamplesPulse;

	/* Calculamos t interval (t dc + t pulse) */
	float tInt = df.Measurement.step / df.Measurement.sr;

	/* Calculamos n� de samples en la zona DC */
	float nSamplesDC = ceil((tInt - df.Measurement.tPulse) / tTimer);

	/* Calculamos el n� de steps */
	// TODO
	uint32_t nSteps = abs((df.Measurement.stop - df.Measurement.start) / df.Measurement.step);

	uint32_t contRow = 0;	// Lleva el seguimiento de la posici�n de la LUT 


	/* Generamos el patr�n de se�al */
	if (df.Measurement.stop > df.Measurement.start) {		// Si steps suben...

		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesDC; j++) {				// Generamos parte DC..
				
				LUTcomplete[j + contRow] = df.Measurement.start + (df.Measurement.step * (i));

			}
			contRow += j;

			for (j = 0; j < nSamplesPulse; j++) {			// Generamos pulso...

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.ePulse) + \
					(df.Measurement.step * i);
			}

			contRow += j;

		}

	}

	else {													// Si steps bajan...
		
		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesDC; j++) {				// Generamos parte DC..

				LUTcomplete[j + contRow] = df.Measurement.start - (df.Measurement.step * (i));

			}
			contRow += j;

			for (j = 0; j < nSamplesPulse; j++) {			// Generamos pulso...

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.ePulse) - \
					(df.Measurement.step * i);
			}

			contRow += j;

		}

	}


	
	
	/* TESTING */
	printFloatToFile(LUTcomplete, contRow);


}



void generateNPVsignal(DF_NPVTypeDef df) {

	uint16_t i, j;
	
	/* Establecemos un n� m�nimo de samples en el pulso para evitar aliasing a frecuencias altas */
	uint16_t nSamplesPulse = 10;

	/* Tiempo de disparo de cada sample */
	float tTimer = df.Measurement.tPulse / nSamplesPulse;

	/* Calculamos t interval (t dc + t pulse) */
	float tInt = df.Measurement.step / df.Measurement.sr;

	/* Calculamos n� de samples en la zona DC */
	float nSamplesDC = ceil((tInt - df.Measurement.tPulse) / tTimer);

	/* Calculamos el n� de steps */
	uint32_t nSteps = abs((df.Measurement.stop - df.Measurement.start) / df.Measurement.step);

	uint32_t contRow = 0;

	/* Generamos el patr�n de se�al */
	if (df.Measurement.stop > df.Measurement.start) {			// Si step sube...

		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesDC; j++) {					// Generamos parte DC...

				LUTcomplete[j + contRow] = df.Measurement.start;
			}

			contRow += j;

			for (j = 0; j < nSamplesPulse; j++) {				// Generamos pulso...

				LUTcomplete[j + contRow] = df.Measurement.start + (df.Measurement.step * i);
			}
			contRow += j;
		}
	}
	
	else {														// Si step baja...

		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesDC; j++) {					// Generamos parte DC...

				LUTcomplete[j + contRow] = df.Measurement.start;
			}
			contRow += j;

			for (j = 0; j < nSamplesPulse; j++) {				// Generamos pulso...

				LUTcomplete[j + contRow] = df.Measurement.start - (df.Measurement.step * i);
			}
			contRow += j;
		}
		
	}

	/* TESTING */
	printFloatToFile(LUTcomplete, contRow);

}



void generateDNPV(DF_DNPVTypeDef df) {

	uint16_t i, j;
	
	/* Establecemos un n� m�nimo de samples en el pulso para evitar aliasing a frecuencias altas */
	uint16_t nSamplesPulse1 = 10;

	/* Tiempo de disparo de cada sample */
	float tTimer = df.Measurement.tPulse1 / nSamplesPulse1;

	/* Calculamos t interval (t dc + t pulse) */
	float tInt = df.Measurement.step / df.Measurement.sr;

	/* Calculamos n� de samples en la zona DC */
	float nSamplesDC = ceil((tInt - (df.Measurement.tPulse1 + df.Measurement.tPulse2 )) / tTimer);

	/* N� de samples en pulse1 */
	float nSamplesP1 = ceil(df.Measurement.tPulse1 / tTimer);

	/* N� de samples en pulse2 */
	float nSamplesP2 = ceil(df.Measurement.tPulse2 / tTimer);

	/* Calculamos el n� de steps */
	uint32_t nSteps = abs((df.Measurement.stop - df.Measurement.start) / df.Measurement.step);

	uint32_t contRow = 0;

	/* Generamos el patr�n de se�al */
	if (df.Measurement.stop > df.Measurement.start) {		// Si steps suben...
		for (i = 0; i < nSteps; i++) {

			for (j = 0; j < nSamplesDC; j++) {				// Generamos parte DC...

				LUTcomplete[j + contRow] = df.Measurement.start;
			}
			contRow += j;

			for (j = 0; j < nSamplesP1; j++) {				// Generamos pulse1...

				LUTcomplete[j + contRow] = df.Measurement.start + (df.Measurement.step * i);
			}
			contRow += j;

			for (j = 0; j < nSamplesP2; j++) {				// Generamos pulse2...

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.ePulse) + \
					(df.Measurement.step * i);
			}
			contRow += j;

		}


	}

	else {													// Si steps bajan...
		for (i = 0; i < nSteps; i++) {

			for (j = 0; j < nSamplesDC; j++) {				// Generamos parte DC...

				LUTcomplete[j + contRow] = df.Measurement.start;
			}
			contRow += j;

			for (j = 0; j < nSamplesP1; j++) {				// Generamos pulse1...

				LUTcomplete[j + contRow] = df.Measurement.start - (df.Measurement.step * i);
			}
			contRow += j;

			for (j = 0; j < nSamplesP2; j++) {				// Generamos pulse2...

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.ePulse) - \
					(df.Measurement.step * i);
			}
			contRow += j;

		}


	}

	/* TESTING */
	printFloatToFile(LUTcomplete, contRow);
}




void generateSWV(DF_SWVTypeDef df) {

	uint16_t i, j;

	/* Sacamos samples totales conociendo frecuencia */
	float fSampling = 100 * df.Measurement.freq;		// oversampling...

	/* Tiempo de disparo de cada sample */
	float tTimer = 1 / df.Measurement.freq;


	/* Calculamos el n� de steps */
	uint32_t nSteps = abs((df.Measurement.start - df.Measurement.stop) / df.Measurement.step);

	/* Hacemos la se�al en dos pasos... */
	/* PASO 1: generamos la onda cuadrada */
	float nSamples1 = (1 / df.Measurement.freq) / tTimer;
	float nSamples2 = (1 / df.Measurement.freq) / tTimer;

	for (i = 0; i < nSamples1; i++) {				// Primer semiper�odo...

		LUT1[i] = df.Measurement.amplitude;
	}

	for (i = 0; i < nSamples2; i++) {				// Segundo semiper�odo...

		LUT2[i] = - (df.Measurement.amplitude);
	}


	/* PASO 2: generamos el DC offset */
	uint32_t contRow = 0;

	if (df.Measurement.start < df.Measurement.stop) {		// Si steps suben...

		for (i = 0; i < nSteps; i++) {

			for (j = 0; j < nSamples1; j++) {			// Generamos primer semiper�odo m�s parte DC

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.step * i) + \
					LUT1[j];
			}
			contRow += j;

			for (j = 0; j < nSamples2; j++) {			// Generamos segundo semiper�odo m�s parte DC

				LUTcomplete[j + contRow] = (df.Measurement.start + df.Measurement.step * i) + \
					LUT2[j];
			}
			contRow += j;
		}

	}

	else {												// Si steps bajan...

		for (i = 0; i < nSteps; i++) {

			for (j = 0; j < nSamples1; j++) {			// Generamos primer semiper�odo m�s parte DC

				LUTcomplete[j + contRow] = (df.Measurement.start - df.Measurement.step * i) + \
					LUT1[j];
			}
			contRow += j;

			for (j = 0; j < nSamples2; j++) {			// Generamos segundo semiper�odo m�s parte DC

				LUTcomplete[j + contRow] = (df.Measurement.start - df.Measurement.step * i) + \
					LUT2[j];
			}
			contRow += j;
		}

	}



	/* TESTING */
	printFloatToFile(LUTcomplete, contRow);
}




void generateACV(DF_ACTypeDef df) {

	uint16_t i, j;

	/* Sacamos samples totales conociendo la frecuencia */
	float fSampling = df.Measurement.freq * 100;
	float tTimer = 1 / fSampling;
	float nSamplesAC = ceil((1 / df.Measurement.freq) / tTimer);

	/* Calculamos el t interval */
	float tInt = df.Measurement.step / df.Measurement.sr;

	/* PASO 1 : generaci�n de la senoide para todo el per�odo */
	/* Calculamos n� per�odos AC que caben en t interval */
	float nPerAC = tInt / (1 / df.Measurement.freq);

	/* Esto nos da el n� de ptos totales del t interval */
	float nSamplesTint = ceil(nPerAC * nSamplesAC);

	/* Generamos la senoidal para todo el t int */
	/* IMPORTANTE */
	/* En caso de que el n� de per�odos AC que caben en el t itnerval no sea
	 un n�mero entero, debemos de poder sacar los puntos del per�odo incompleto.
	 Esto se hace en la segunda parte del "if" */

	uint32_t contRow = 0;

	for (i = 0; i < ceil(nPerAC); i++) {

		if (i < nPerAC) {						// Si no es el �ltimo per�odo...
			for (j = 0; j < nSamplesAC; j++) {

				LUT1[j + contRow] = df.Measurement.ACamplitude * sin((2 * PI / nSamplesAC)*j);
			}
			contRow += j;
		}
		else {									// Si �ltimo per�odo...

			float nSamplesRest = nSamplesTint - contRow;

			for (j = 0; j < nSamplesRest; j++) {

				LUT1[j + contRow] = df.Measurement.ACamplitude * sin((2 * PI / nSamplesAC)*j);
			}
		}

	}

	/* Generaci�n del offset + AC para toda la prueba */
	float nSteps = ceil(abs((df.Measurement.start - df.Measurement.stop) / df.Measurement.step));

	contRow = 0;

	if (df.Measurement.start < df.Measurement.stop) {			// Si steps suben...
		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesTint; j++) {

				LUTcomplete[j + contRow] = (df.Measurement.start + (df.Measurement.step*i)) + \
					LUT1[j];
			}
			contRow += j;
		}
	}
	else {														// Si steps bajan...
		for (i = 0; i < nSteps; i++) {
			for (j = 0; j < nSamplesTint; j++) {

				LUTcomplete[j + contRow] = (df.Measurement.start - (df.Measurement.step*i)) + \
					LUT1[j];
			}
			contRow += j;

		}
	}

	/* TESTING */
	printFloatToFile(LUTcomplete, contRow);
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