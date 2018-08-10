/*
 *
 *		Visual Effects Sample Program
 *
 */

/***************************************************************************
 *      �C���N���[�h�t�@�C��
 *      Include file
 ***************************************************************************/

#include	<shinobi.h>
#include	<sg_mw.h>
#include	<string.h>

#include	"usr.h"

/***************************************************************************
 *      �萔�}�N��
 *      MACRO CONSTANT
 ***************************************************************************/

/*	SAN�p�e�N�X�`����			*/
/*	Number of textures for SAN	*/
#define	NUM_TEX			1

/*	�t�@�C���Đ��p���[�N�̈�̑傫��	*/
/*	Work area size of CD stream play	*/
#define	WKSIZE			ADXT_CALC_WORK(2, ADXT_PLY_STM, 2, 44100)

/***************************************************************************
 *      �����}�N��
 *      Process MACRO
 ***************************************************************************/

/*	�t���OON/OFF�̔��]		*/
/*	Turn over flag(ON/OFF)	*/
#define NOT_FLAG(flag)		(((flag) == OFF) ? ON : OFF)

/***************************************************************************
 *      �ϐ���`
 *		Variable Declaration
 ***************************************************************************/

/*	�A�v���P�[�V�����\����											*/
/*	Application structure											*/
typedef struct {
	Sint32	term_flag;			//	Application terminate flag
	Sint32	disp_flag;			//	Display information flag
	Sint32	pause_flag;			//	Pause flag
	char	*fname;				//	File name
	ADXT	adxt;				//	ADXT handle
	SAN		san;				//	SAN handle
	MWPLY	ply;				//	Middleware Play handle
	Uint8	*sanwk;				//  SAN work area
	Uint8	*sandat;			//  SAN data
	MWS_PLY_CPRM_SFD cprm;		//	Create parameter
	Uint8	adxtwk[WKSIZE];		//  ADX work area
} AP_OBJ, *AP;

/*	�A�v���P�[�V�����I�u�W�F�N�g									*/
/*	Application Object												*/
AP_OBJ ap_obj = {
	OFF,						//	Execute App.
	ON,							//	Display Info.
	OFF,						//	not puase
	"SAMPLE.SFD",				//	File name
	NULL,						//	ADXT handle
	NULL,						//	SAN handle
	NULL,						//	Middleware Play handle
	NULL,						//  SAN work area
	NULL,						//  SAN data
};

/***************************************************************************
 *      �֐���`
 *      Function Declaration
 ***************************************************************************/

/***
 *			�~�h���E�F�A�̍Đ�
 *			Playing middleware
 ***/

/*	�~�h���E�F�A�̃G���[�������ɋN������֐�			*/
/*	Callback function when an error occur in middleware	*/
void ap_mw_err_func(void *obj, char *errmsg)
{
	AP ap=(AP)obj;

	for (;;);
}

/*	�~�h���E�F�A�̏�����				*/
/*	Initialize Middleware				*/
void ApInitMw(AP ap,
		Sint32 mod, Sint32 frm, Sint32 cnt, Sint32 ltncy, void *vtxbuf)
{
	MWS_PLY_INIT_SFD	iprm;

	memset(&iprm, 0, sizeof(iprm));	/*	�\�񃁃��o�̃[���ݒ�			*/
									/*	initialize reserved member		*/
	iprm.mode		= mod;			/*	Resolution, NTSC, PAL, VGA		*/
	iprm.frame		= frm;			/*	RGB565, ARGB8888				*/
	iprm.count		= cnt;			/*	Game period by the V-Sync count */
	iprm.latency	= ltncy;		/*	Latency (2V or 3V)				*/
#ifdef NINJA1
	mwPlyInitSofdec(&iprm);
#else
	mwPlyInitSfdFx(&iprm);
	mwPlySetVertexBuffer(vtxbuf);
#endif
	mwPlyEntryErrFunc(ap_mw_err_func, ap);

	/*	SAN ���C�u�����̏�����								*/
	/*	Initialization for SAN								*/
#ifdef NINJA1
	SAN_Init();
#else
	SAN_InitKm();
	SAN_SetVertexBuffer(vtxbuf);
#endif
	SAN_EntryErrFunc((SAN_ERRFN)ap_mw_err_func, ap);

	/*	Initialization for ADX								*/
	ADXT_Init();
	ADXT_EntryErrFunc(ap_mw_err_func, ap);
}

/*	�~�h���E�F�A�̏I��					*/
/*	Finalize Middleware					*/
void ApFinishMw(AP ap)
{
	ADXT_Finish();			/*	ADXT���C�u�����I������				*/
							/*	Finalize ADXT library				*/
#ifdef NINJA1
	SAN_Finish();			/*	SAN���C�u�����I������				*/
							/*	Finalize SAN library				*/
	mwPlyFinishSofdec();	/*	���C�u�����I������					*/
							/*	Finalize Middleware					*/
#else
	SAN_FinishKm();			/*	SAN���C�u�����I������				*/
							/*	Finalize SAN library				*/
	mwPlyFinishSfdFx();		/*	���C�u�����I������					*/
							/*	Finalize Middleware					*/
#endif
}

/*	�A�v���P�[�V�����J�n����	*/
/*	Start application		*/
void ApStart(AP ap)
{
    MWS_PLY_CPRM_SFD	*cprm;

	/*	�w�i�f�[�^�pSAN �̍쐬								*/
	/*	Create SAN for Background Still Picture				*/
	ap->sandat = UsrLoadFile("azelbg.san", NULL);
	if ( (ap->sanwk=syMalloc(SAN_CalcWorkSize(NUM_TEX))) == NULL )
		for (;;);
	if ( (ap->san = SAN_Create(ap->sandat, NUM_TEX, ap->sanwk)) == NULL )
		for (;;);
	SAN_LoadTex(ap->san, 0, 0);

	/*	BGM �Đ�											*/
	/*	Play music											*/
	ap->adxt = ADXT_Create(2, ap->adxtwk, sizeof(ap->adxtwk));
	ADXT_SetOutVol(ap->adxt, -90);
	ADXT_StartFname(ap->adxt, "azel.adx");

	/*	����Đ��n���h���̐���								*/
	/*	Create SofdecF/X Player handle						*/
	cprm = &ap->cprm;
	memset(cprm, 0, sizeof(MWS_PLY_CPRM_SFD));
	cprm->compo_mode	= MWD_PLY_COMPO_ALPH256;
	cprm->ftype			= MWD_PLY_FTYPE_SFD;
	cprm->dtype			= MWD_PLY_DTYPE_FULL;
	cprm->max_bps		= 600*1024*8;
	cprm->max_width		= 256;
	cprm->max_height	= 256;
	cprm->nfrm_pool_wk	= 4;
	cprm->wksize		= mwPlyCalcWorkCprmSfd(cprm);
	cprm->work			= syMalloc(cprm->wksize);
	ap->ply = mwPlyCreateSofdec(cprm);
	if ( ap->ply == NULL )
		for (;;) ;

	mwPlySetAdjustY16(ap->ply, 0);
	mwPlySetBright(ap->ply, 255);
	mwPlySetBrightOfst(ap->ply, 0);
	mwPlySetDispPos(ap->ply, 0.0, 0.0);
	mwPlySetDispSize(ap->ply, 640.0, 480.0);
	mwPlySetDispZ(ap->ply, 1.0);
}

/*	�A�v���P�[�V������~����	*/
/*	Stop application		*/
void ApStop(AP ap)
{
	mwPlyStop(ap->ply);					/*	�Đ���~ 					*/
										/*	Stop to play middleware		*/
	mwPlyDestroy(ap->ply);				/*	�n���h������				*/
										/*	Destroy handle				*/
	ap->ply = NULL;
	syFree(ap->cprm.work);				/*	��Ɨ̈�̊J��				*/
										/*	Release work area			*/
	ap->cprm.work = NULL;

	ADXT_Destroy(ap->adxt);
	ap->adxt = NULL;

	SAN_Destroy(ap->san);
	syFree(ap->sanwk);
	syFree(ap->sandat);
	ap->sanwk = NULL;
	ap->sandat = NULL;
}

/*	�Đ��J�n			*/
/*	Play F/X movie		*/
void ApPlayFxmovie(MWPLY ply, char *fname)
{
	mwPlyStop(ply);
	if ( memcmp(fname+strlen(fname)-7, "ADD", 3) == 0 )
		mwPlySetCompoMode(ply, MWD_PLY_COMPO_ADD);
	else if ( memcmp(fname+strlen(fname)-7, "003", 3) == 0 )
		mwPlySetCompoMode(ply, MWD_PLY_COMPO_ALPH3);
	else if ( memcmp(fname+strlen(fname)-7, "256", 3) == 0 )
		mwPlySetCompoMode(ply, MWD_PLY_COMPO_ALPH256);
	else
		mwPlySetCompoMode(ply, MWD_PLY_COMPO_LUMI);
	mwPlyStartFname(ply, fname);
}

/*	����̍Đ�					*/
/*	Playing the animation file	*/
Sint32 ApExec(AP ap)
{
	MWPLY			ply=ap->ply;
	MWE_PLY_STAT	stat;
	PDS_PERIPHERAL*	per;

	per = pdGetPeripheral(PDD_PORT_A0);
	if ( per->press & PDD_DGT_ST )
		mwPlyPause(ply, ap->pause_flag=NOT_FLAG(ap->pause_flag));
	if ( per->press & PDD_DGT_TB )
		return FALSE;
	if ( per->press & PDD_DGT_TR )
		mwPlyStop(ply);

	if ( per->press & PDD_DGT_TA )
		ApPlayFxmovie(ply, "FFALL_LUMI.SFD");
	else if ( per->press & PDD_DGT_TX )
		ApPlayFxmovie(ply, "GEXP_LUMI.SFD");
	else if ( per->press & PDD_DGT_TY )
		ApPlayFxmovie(ply, "FIRE_LUMI.SFD");
	else if ( per->press & PDD_DGT_KL )
		ApPlayFxmovie(ply, "LBALL_ADD.SFD");
	else if ( per->press & PDD_DGT_KR )
		ApPlayFxmovie(ply, "RING_A256.SFD");
	else if ( per->press & PDD_DGT_KD )
		ApPlayFxmovie(ply, "SMK_LUMI.SFD");
	else if ( per->press & PDD_DGT_KU )
		ApPlayFxmovie(ply, "ARCH_LUMI.SFD");

	/*	Checking status												*/
    stat = mwPlyGetStat(ply);
	if ((stat == MWE_PLY_STAT_PLAYEND) || (stat == MWE_PLY_STAT_ERROR)) {
    	mwPlyStop(ply);
	}
	SAN_Draw(ap->san, 0);

	return TRUE;
}

/***
 *		���C������
 *		MAIN
 ***/

/*	GD�t�@�C���V�X�e���̃G���[�������ɋN������֐�			*/
/*	Callback function when an error occur in GD file system	*/
void ApGdErrFunc(void *obj, Sint32 errcode)
{
	AP ap=(AP)obj;

	if (errcode == GDD_ERR_TRAYOPEND || errcode == GDD_ERR_UNITATTENT)
		ap->term_flag = ON;			/*	�A�v���P�[�V�����̏I��		*/
									/*	Terminate application		*/
}

/*	���[�U��V-SYNC���荞�݂ɓo�^����֐�	*/
/*	Callback function when V-sync interrupt	*/
void ApVsyncFunc(void)
{
	UsrCheckDoorOpen();
}

void main(void)
{
	AP		ap=&ap_obj;
	void	*vtxbuf;
	Sint32	mode, frame, count, latency;
	Bool	ret;

#ifdef __GNUC__
	shinobi_workaround();
#endif

	/*	�~�h���E�F�A�̂��߂̃V�X�e�������� (sbInitSystem�̑O�ɒu��)	*/
	/*	Initialize system for middleware(call before sbInitSystem)	*/
	mwPlyPreInitSofdec();

	/*	�E���C�u�����ƃr�f�I�̏�����								*/
	/*	Initialize SHINOBI & Video Sysytem							*/
	vtxbuf = UsrInitVideo(&mode, &frame, &count, &latency);

	/*	GD�t�@�C���V�X�e���G���[�R�[���o�b�N�֐��̓o�^				*/
	/*	Entry callback function of GD file system error				*/
	gdFsEntryErrFuncAll((void *)ApGdErrFunc, ap);

	/*	�T�E���h�V�X�e���̏�����									*/
	/*	Initialize sound system										*/
	UsrInitSound();

	/*	V-Sync ���荞�ݏ����̓o�^									*/
	/*	Register V-Sync interrupt func								*/
	UsrSetVsyncFunc((void (*)(void))ApVsyncFunc);

	/*	�~�h���E�F�A���C�u����������								*/
	/*	Initialize middleware										*/
	ApInitMw(ap, mode, frame, count, latency, vtxbuf);

	/*	Frame Work	*/
	while ( ap->term_flag == OFF ) {
		ApStart(ap);
		while (1) {
			mwPlyExecTexSvr();			/*	Load Texture To V-RAM			*/
			UsrBeginDraw();
			mwPlyExecDrawSvr();		/*	Draw polygons 					*/
			ret = ApExec(ap);
			UsrEndDraw();
			if ( ret == FALSE || ap->term_flag == ON )
				break;

			UsrWaitVBlank();
		}
		ApStop(ap);
	}
	/*	�A�v���P�[�V�����I������	*/
	/*	Finalize application		*/
	ApFinishMw(ap);			/*	�~�h���E�F�A�̏I��					*/
							/*	Finalize Middleware					*/
	UsrFinishSound();		/*	�T�E���h�V�X�e���̏I������			*/
							/*	Finalize sound system				*/
	UsrFinishVideo();		/*	�E���C�u�����ƃr�f�I�̏I������		*/
							/*	Finalize SHINOBI & Video system		*/
	syBtExit();				/*	�V���v���v���C���փW�����v			*/
							/*	Jump to Simple player				*/
}

/* End of file */