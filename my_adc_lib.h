#define ADC_CHANNEL 0
#define V_REF 1.1


/* Initialize the ADC module: selects ADC input and reference
* voltage. Sets sampling speed depending on clock rate
* Arguments:  none
* Returns: none 
*/
void adc_init(void);


/* Read ADC input from ADC_CHANNEL
* Arguments: none
* Returns: 10 bit right-justified digitized word
*/
unsigned int get_adc(void);