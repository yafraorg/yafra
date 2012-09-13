/*D***********************************************************
 * Header:    MPaktObj.h
 *            Aktions-Objektdefinitionen als Default falls
 *            kundenspezifische Definition nicht vorhanden                     
 *                                                            
 * Copyright: yafra.org, Basel, Switzerland     
 *************************************************************/



/************************************************************
 * Sektion:  Aktionsobjekte
 *
 * Nr.Kreis: 1001 - 1099
 *************************************************************/
#define		_AUFTRAG_TYP		(int)1001	/* OUTauftrag    */
#define		_FAKTURA_TYP		(int)1002	/* OUTfaktura    */
#define		_PASSAGIER_TYP		(int)1003	/* OUTpassagier  */
#define		_PROGRAM_TYP		(int)1004	/* OUTprogram    */
#define		_TICKET_TYP 		(int)1005	/* OUTticket     */
#define		_VOUCHER_TYP		(int)1006	/* OUTvoucher    */
#define		_MANIFEST_TYP		(int)1007	/* OUTmanifest   */
#define		_ABACUS_TYP			(int)1008	/* OUTabacus     */
#define    	_CONTROL_TYP     	(int)1009  	/* OUTcontrol    */
#define    	_REQUEST_TYP      (int)1010   /* OUTrequest    */
#define    	_STATISTIK_TYP    (int)1011   /* OUTstatistik  */
#define    	_ANNULATION_TYP   (int)1012   /* OUTannulation */
#define    	_ORDER_TYP   		(int)1013   /* OUTorder controler */
#define    	_PAXBUS_TYP   		(int)1014   /* OUTpaxbus liste    */
#define    	_STAMM_TYP   		(int)1015   /* OUTstamm control liste  */
#define    	_OPTION_TYP   		(int)1016   /* OUToption control liste  */
#define    	_REVENU_TYP   		(int)1017   /* OUTrevenu report statistik */
#define    	_STATDLT_TYP   	(int)1018   /* OUTstatdlt report statistik */
#define    	_PAXDL_TYP   		(int)1019   /* OUTpaxdl liste    */

#define    	_COMMON_TYP 	   (int)1099   /* for all actions */


/** ACHTUNG !!
 * 
 *  Falls hier ein neuer Typ dazu kommt, File ACT/AKTdeptxt.c
 *  entsprechend mutieren in Funktion SelectAktionsText()
*/
