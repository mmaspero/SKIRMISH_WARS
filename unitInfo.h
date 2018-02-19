#pragma once
#include <climits>



#define FIRST_W	RECON //para determinar facilmente el basic type
#define FIRST_F	MECH
#define FIRST_T TANK

#define MAX_HP		8	//para todas las unidades! empiezan con el max
#define HEAL_HP		2	//cuanto se cura cuando hace un heal (si alcanza)
#define REDUCED_HP	4	//hasta cuanto hp cuenta como reducida (de 1 a 4 inclusive)

/*	RECON  */
#define RE_DEFENSE	3
#define	RE_TYPE		WHEEL
#define RE_COST		4
#define RE_MP		8
#define RE_RNG_MIN	1
#define	RE_RNG_MAX	1

#define RE_FP_FT	7
#define RE_FP_TRD	7
#define RE_FP_WHL	7

#define RE_RFP_FT	4
#define RE_RFP_TRD	6
#define RE_RFP_WHL	5

#define RE_MC_T		2			//plain tile
#define RE_MC_A		1			//road (Autopista)
#define RE_MC_F		3			//forest
#define RE_MC_R		UINT_MAX	//river
#define RE_MC_H		UINT_MAX	//hill


/*	ROCKET  */
#define RO_DEFENSE	3
#define	RO_TYPE		WHEEL
#define RO_COST		15
#define RO_MP		5
#define RO_RNG_MIN	3
#define	RO_RNG_MAX	5

#define RO_FP_FT	9
#define RO_FP_TRD	11
#define RO_FP_WHL	10

#define RO_RFP_FT	5
#define RO_RFP_TRD	10
#define RO_RFP_WHL	10

#define RO_MC_T		2			//plain tile
#define RO_MC_A		1			//road (Autopista)
#define RO_MC_F		3			//forest
#define RO_MC_R		UINT_MAX	//river
#define RO_MC_H		UINT_MAX	//hill


/*  MECH  */
#define ME_DEFENSE	2
#define	ME_TYPE		FOOT
#define ME_COST		3
#define ME_MP		2
#define ME_RNG_MIN	1
#define	ME_RNG_MAX	1

#define ME_FP_FT	6
#define ME_FP_TRD	10
#define ME_FP_WHL	10

#define ME_RFP_FT	4
#define ME_RFP_TRD	7
#define ME_RFP_WHL	6

#define ME_MC_T		1	//plain tile
#define ME_MC_A		1	//road (Autopista)
#define ME_MC_F		1	//forest
#define ME_MC_R		1	//river
#define ME_MC_H		1	//hill


/*  INFANTRY  */
#define IN_DEFENSE	1
#define	IN_TYPE		FOOT
#define IN_COST		1
#define IN_MP		3
#define IN_RNG_MIN	1
#define	IN_RNG_MAX	1

#define IN_FP_FT	5
#define IN_FP_TRD	5
#define IN_FP_WHL	5

#define IN_RFP_FT	3
#define IN_RFP_TRD	3
#define IN_RFP_WHL	3

#define IN_MC_T		1	//plain tile
#define IN_MC_A		1	//road (Autopista)
#define IN_MC_F		1	//forest
#define IN_MC_R		2	//river
#define IN_MC_H		2	//hill

/*  TANK  */
#define TA_DEFENSE	6
#define	TA_TYPE		TREAD
#define TA_COST		7
#define TA_MP		6
#define TA_RNG_MIN	1
#define	TA_RNG_MAX	1

#define TA_FP_FT	7
#define TA_FP_TRD	10
#define TA_FP_WHL	10

#define TA_RFP_FT	4
#define TA_RFP_TRD	8
#define TA_RFP_WHL	6

#define TA_MC_T		1	//plain tile
#define TA_MC_A		1	//road (Autopista)
#define TA_MC_F		2	//forest
#define TA_MC_R		UINT_MAX	//river
#define TA_MC_H		UINT_MAX	//hill


/*  ARTILLERY  */
#define AR_DEFENSE	4
#define	AR_TYPE		TREAD
#define AR_COST		6
#define AR_MP		5
#define AR_RNG_MIN	2
#define	AR_RNG_MAX	3

#define AR_FP_FT	9
#define AR_FP_TRD	11
#define AR_FP_WHL	9

#define AR_RFP_FT	5
#define AR_RFP_TRD	9
#define AR_RFP_WHL	6

#define AR_MC_T		1	//plain tile
#define AR_MC_A		1	//road (Autopista)
#define AR_MC_F		2	//forest
#define AR_MC_R		UINT_MAX	//river
#define AR_MC_H		UINT_MAX	//hill


/*  ANTI-AIR  */
#define AA_DEFENSE	4
#define	AA_TYPE		TREAD
#define AA_COST		8
#define AA_MP		6
#define AA_RNG_MIN	1
#define	AA_RNG_MAX	1

#define AA_FP_FT	10
#define AA_FP_TRD	8
#define AA_FP_WHL	8

#define AA_RFP_FT	6
#define AA_RFP_TRD	7
#define AA_RFP_WHL	5

#define AA_MC_T		1	//plain tile
#define AA_MC_A		1	//road (Autopista)
#define AA_MC_F		2	//forest
#define AA_MC_R		UINT_MAX	//river
#define AA_MC_H		UINT_MAX	//hill


/*  APC  */

#define AP_DEFENSE	4
#define	AP_TYPE		TREAD
#define AP_COST		5
#define AP_MP		6

//EL APC NO PUEDE ATACAR!!

#define AP_MC_T		1	//plain tile
#define AP_MC_A		1	//road (Autopista)
#define AP_MC_F		2	//forest
#define AP_MC_R		UINT_MAX	//river
#define AP_MC_H		UINT_MAX	//hill

#define AP_CAPACITY	2	//unidades que puede llevar

/*  MED_TANK  */
#define MT_DEFENSE	9
#define	MT_TYPE		TREAD
#define MT_COST		16
#define MT_MP		5
#define MT_RNG_MIN	1
#define	MT_RNG_MAX	1

#define MT_FP_FT	10
#define MT_FP_TRD	12
#define MT_FP_WHL	11

#define MT_RFP_FT	5
#define MT_RFP_TRD	10
#define MT_RFP_WHL	7

#define MT_MC_T		1	//plain tile
#define MT_MC_A		1	//road (Autopista)
#define MT_MC_F		2	//forest
#define MT_MC_R		UINT_MAX	//river
#define MT_MC_H		UINT_MAX	//hill
