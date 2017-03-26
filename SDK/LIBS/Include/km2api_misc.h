/*++

  COPYRIGHT        (C) NEC        Corporation 1997 - 1999

  All rights reserved by NEC Corporation. This program must be
  used solely for the purpose for which it was furnished by NEC
  Corporation. No part of this program may be reproduced or
  disclosed to others, in any form, without the prior written
  permission of NEC Corporation.
  Use of copyright notice does not evidence publication of this
  program.

  Author     :		T.Hirata(NEC Software,Ltd.)
  Module Name:		km2api_misc.h

  Abstract:
	KAMUI = Kamui is abstruction model that is ultimate interface for PowerVR.
	'km2api_misc.h' define miscelaneous API which can not be classified.

  Environment:
	ANSI C Compiler.

  Notes:
	define Kamui's miscelaneous API proto-types which can not be classified. 
	fog , palette , pixel clipping etc..

  Revision History:

--*/

#if !defined(__kamui2_miscelaneous_api_h__)
#define __kamui2_miscelaneous_api_h__

/*++
kmSetWaitVsyncCount

proto type:

	KMSTATUS
	kmSetWaitVsyncCount( KMINT32 nCount );

Description:
		�t���[�����[�g��藦�ɂ��邽�߂ɁA�O��� Flip��A
		����Flip �\�ɂȂ�܂ł�V-Sync�����w�肵�܂��B

Arguments:
		IN	nCount		V-Sync ��҂񐔂��w�肵�܂��B�O��� Flip��A
						����Flip �\�ɂȂ�܂ł�V-Sync�����w�肵�܂��B

Result:
		KMSTATUS_SUCCESS			����
--*/
KMSTATUS KMAPI
kmSetWaitVsyncCount(
		IN	KMINT32 nCount 
		);


/*++
kmSetCullingRegister

proto type:

	KMSTATUS
	kmSetCullingRegister(
			KMFLOAT fCullVal
		);

Description:
		������ Polygon �ɑ΂���J�����O�̃X���b�V�����h�l��ݒ肵�܂��B

Arguments:
		IN	fCullVal	���ʃp�����[�^�̃f�^�~�i���g�l��ݒ肵�܂��B

Result:
		KMSTATUS_SUCCESS			Flip�R�}���h���s����
		KMSTATUS_CANT_FLIP_SURFACE 	Flip�R�}���h���s���s

--*/

KMSTATUS KMAPI
kmSetCullingRegister(
		IN	KMFLOAT fCullVal
	);


/*++
kmSetColorClampValue

proto type:

	KMSTATUS
	kmSetColorClampValue(
			KMPACKEDARGB MaxVal,
			KMPACKEDARGB MinVal 
		);

Description:
	�J���[�̃N�����v�l���w�肵�܂��B�J���[�N�����v�̓t�H�O�̑O�i�Ŋ|�����܂��B

Arguments:
	IN	MaxVal			Packed�� ARGB 32bit�J���[�ŁA�N�����v�̍ő�l���w�肵�܂��B
	IN	MinVal			Packed�� ARGB 32bit�J���[�ŁA�N�����v�̍ŏ��l���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetColorClampValue(
		IN	KMPACKEDARGB MaxVal,
		IN	KMPACKEDARGB MinVal 
	);

/*++
kmSetColorClampMax

proto type:
	KMSTATUS KMAPI
	kmSetColorClampMax(
			IN	KMPACKEDARGB Val
		);

Description:
	�J���[�̃N�����v�l���w�肵�܂��B�J���[�N�����v�̓t�H�O�̑O�i�Ŋ|�����܂��B

Arguments:
	IN	Val				Packed�� ARGB 32bit�J���[�ŁA�N�����v�̍ő�l���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetColorClampMax(
		IN	KMPACKEDARGB Val
	);

/*++
kmSetColorClampMin

proto type:
	KMSTATUS KMAPI
	kmSetColorClampMin(
			IN	KMPACKEDARGB Val
		);

Description:
	�J���[�̃N�����v�l���w�肵�܂��B�J���[�N�����v�̓t�H�O�̑O�i�Ŋ|�����܂��B

Arguments:
	IN	Val				Packed�� ARGB 32bit�J���[�ŁA�N�����v�̍ŏ��l���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetColorClampMin(
		IN	KMPACKEDARGB Val
	);


/*++
kmSetFogTableColor

proto type:

	KMSTATUS
	kmSetFogTableColor(
			IN	KMPACKEDARGB FogTableColor
		);

Description:
	Table ���g�p���� �t�H�O�J���[���w�肵�܂��B

Arguments:
	IN	FogTableColor		FogTable �Ɏg�p����Packed��32bit�J���[�ł��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetFogTableColor(
		IN	KMPACKEDARGB FogTableColor
	);

/*++
kmSetFogVertexColor

proto type:

	KMSTATUS 
	kmSetFogVertexColor(
			KMPACKEDARGB FogVertexColor
		);

Description:
	FogVertex �̃t�H�O�J���[���w�肵�܂��B

Arguments:
	IN	FogVertexColor		FogVertex�Ɏg�p����Packed��32bit�J���[�ł��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS  KMAPI
kmSetFogVertexColor(
		IN	KMPACKEDARGB FogVertexColor
	);

/*++
kmGenerateFogTable

proto type:

	KMSTATUS
	kmGenerateFogTable(
		OUT	PKMFLOAT	pFogTable,
		IN	KMFLOAT		fFrontBorder,
		IN	KMFLOAT		fBackBorder,
		IN	KMFLOAT		fFogDensity,
		OUT	KMFLOAT		*fHWFogDensity,
		IN	KMDWORD		dwFogType
		);

Description:
	�t�H�O�e�[�u���������������܂��B
	�t�H�O���L���ƂȂ��Ԃ̑O������ь㉏�̉��s���l��^����ƁA
	���̋�ԂɂȂ��炩�ȃt�H�O��������悤�ȃt�H�O�e�[�u���ƃt�H�O�W���𐶐����܂��B 

Arguments:
	OUT	PKMFLOAT	pFogTable
		���������t�H�O�e�[�u�����i�[���邽�߂́A
		128 �G���g���� KMFLOAT�`���̈ꎟ���z��ւ̃|�C���^�ł��B
	IN	KMFLOAT		fFrontBorder
		�t�H�O���L���ƂȂ��Ԃ̑O�����s���l���w�肵�܂��B
	IN	KMFLOAT		fBackBorder
		�t�H�O���L���ƂȂ��Ԃ̌㉏���s���l���w�肵�܂��B
	IN	KMFLOAT		fFogDensity
		�t�H�O�̔Z�x���w�肵�܂��B 
	OUT	KMFLOAT		*fHWFogDensity
		kmSetFogDensity ��PowerVR�n�[�h�E�F�A�ɐݒ肷��A
		�t�H�O�W���𕂓������ŕԂ��܂��B
	IN	KMDWORD		dwFogType
		�t�H�O�e�[�u���̃^�C�v���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��
	KMSTATUS_OUT_OF_RANGE	fBackBorder��0.0f�ȉ��ł���A
							�܂��� fBackBorder > fFrontBorder�ł���A
							�܂��� fFogDensity��0.0f��菬�����B 

--*/

KMSTATUS KMAPI
kmGenerateFogTable(
	OUT	PKMFLOAT	pFogTable,
	IN	KMFLOAT		fFrontBorder,
	IN	KMFLOAT		fBackBorder,
	IN	KMFLOAT		fFogDensity,
	OUT	KMFLOAT		*fHWFogDensity,
	IN	KMDWORD		dwFogType
	);

/*++
kmConvertFogDensity

proto type:

	KMSTATUS
	kmConvertFogDensity(
		IN	KMFLOAT		fFogDensity,
		OUT	KMDWORD		*dwFogDensity
		);

Description:
	���������_������APowerVR�n�[�h�E�F�A���W�X�^�ɐݒ肷�邽�߂�
	2 �o�C�g�̃t�H�O�W�������߂܂��B

Arguments:
	IN	KMFLOAT		fFogDensity
		kmGenerateFogTable �Ő������ꂽ���������_���̃t�H�O�W�����w�肵�܂��B 
	OUT	KMDWORD		*dwFogDensity
		kmSetFogDensity �Ńn�[�h�E�F�A�ɐݒ肷��Ƃ��̂Q�o�C�g�l��Ԃ��܂��B 

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS KMAPI
kmConvertFogDensity(
	IN	KMFLOAT		fFogDensity,
	OUT	KMDWORD		*dwFogDensity
	);

/*++
kmSetFogTable

proto type:

	KMSTATUS
	kmSetFogTable(
			PKMFLOAT pfFogTable
		);

Description:
	FogTable��o�^���܂��B128 ��float�l�̊i�[���ꂽ�z��ւ̃|�C���^�������Ƃ��ēn���܂��B

Arguments:
	IN	pfFogTable	�t�H�O�e�[�u���l�z��ւ̃|�C���^�B128�̃p�����[�^���w�肵�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetFogTable(
		IN	PKMFLOAT pfFogTable
	);

/*++
kmSetFogDensity

proto type:

	KMSTATUS
	kmSetFogDensity(KMDWORD fogDensity)

Description:
	Fog �̌W����^����B

Arguments:
	IN	fogDensity			2 �o�C�g�� Fog �̌W�� 

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS	KMAPI
kmSetFogDensity(
		IN	KMDWORD fogDensity
	);

/*++
kmSetPaletteMode

proto type:

	KMSTATUS 
	kmSetPaletteMode(	
			KMPALETTEMODE Palettemode
		);

Description:
	�p���b�g�̃��[�h�w������܂��B
	�p���b�g�f�[�^��`�����ޑO�Ƀp���b�g���[�h��ݒ肷��K�v������܂��B

Arguments:
	IN	PaletteMode		�p���b�g�� BPP ���[�h
						KM_PALETTE_16BPP_ARGB1555	16BPP���[�h 
						KM_PALETTE_16BPP_RGB565		16BPP���[�h 
						KM_PALETTE_16BPP_ARGB4444	16BPP���[�h 
						KM_PALETTE_32BPP_ARGB8888	32BPP���[�h 

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS  KMAPI
kmSetPaletteMode(	
		IN	KMPALETTEMODE Palettemode
	);

/*++
kmSetPaletteData

proto type:
	KMSTATUS
	kmSetPaletteData(
			PKMPALETTEDATA pPaletteTable
		);

Description:
	�p���b�g�̐ݒ���s���܂��B

Arguments:
	IN	pPaletteTable	Palette�ݒ�p�z��̃|�C���^���w�肵�܂��B
						Palette�ݒ�p�z��̓��e�͈ȉ��̂悤�ɂȂ�܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetPaletteData(
		IN	PKMPALETTEDATA pPaletteTable
	);


/*++
kmSetPaletteBankData

proto type:
	KMSTATUS 
	kmSetPaletteBankData(
			IN KMINT32		PaletteEntry,
			IN KMINT32		DataSize,
			IN PKMPALETTEDATA	pPaletteTable
		);

Description:
	Palettize�e�N�X�`���Ŏg�p����� Palette �̈ꕔ�����A
	�w�肵���p���b�g�f�[�^�ŏ��������܂��B
	�p���b�g�̍\���ɂ��Ă�kmSetPaletteData���Q�Ɗ肢�܂��B

	�p���b�g���[�h��4bpp/8bpp�Ɋւ�炸 PaletteEntry�Ɏw��\�Ȓl�́A
	0����1023�̂����ꂩ�ł��B�o���N�̋��E�Ɋ֌W�Ȃ��A�C�ӂ̃G���g������
	�f�[�^���������ނ��Ƃ��ł��܂��B�p���b�g��PaletteEntry�Ԗڂ̃G���g������A
			PaletteEntry�@�{�@DataSize�Ԗڂ̃G���g��
	�܂łɁApPaletteTable�Ŏw�����̈�̐擪�̃f�[�^���珇�ɃZ�b�g���Ă����܂��B
	�p���b�g�ԍ� 1023 ���傫���p���b�g�ԍ��ɑΉ�����f�[�^�͖�������܂��B
	���Ȃ킿�ݒ肪�ȉ��Ɏ����悤�ȏꍇ�́A�p���b�g�ԍ�1023�܂łŒ�~���܂��B
			 PaletteEntry�@�{�@DataSize�@���@1024�@

Arguments:
	IN PaletteEntry
		�f�[�^���������ރp���b�g�̐擪�G���g���ԍ����w�肵�܂��B
		 0 ���� 1023 �̒��̂����ꂩ���w�肵�܂��B
		�w�肳�ꂽ�G���g���ԍ�����̃p���b�g�̓��e�����������܂��B

	IN DataSize
		�������ރf�[�^�̃T�C�Y(�G���g����)���w�肵�܂��B
		1 ����ő�1024 ���w��ł��܂��B

	IN pPaletteTable
		Palette�ݒ�p�z��̃|�C���^���w�肵�܂��B
		Palette�ݒ�p�z��̓��e�͈ȉ��̂悤�ɂȂ�܂��B

		KMPALETTEDATA		PaletteTable;

		���̃p���b�g�f�[�^�̗v�f����DataSize�ȏ�Ȃ���΂Ȃ�܂���B
		���ꂪDataSize�ȏ�Ȃ������ꍇ�̓���͕ۏ؂��܂���B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS  KMAPI
kmSetPaletteBankData(
		IN KMINT32			PaletteEntry,
		IN KMINT32			DataSize,
		IN PKMPALETTEDATA	pPaletteTable
	);

/*++
kmSetPaletteBank

proto type:
	KMSTATUS 
	kmSetPaletteBank(
		IN KMINT32				Bank,
		IN KMPALETTE_ENTRY_SIZE	DataSize,
		IN PKMDWORD				pPaletteData
		);

Description:
	Palettize�e�N�X�`���Ŏg�p�����I���`�b�v�p���b�g�́A
	�w�肳�ꂽ 1 �o���N��V���ȃf�[�^�ŏ��������܂��B 

	����������G���g���̐��́ABPP�̎w��ɂ�茈�肵�܂��B 
	DataSize�� KM_PALETTE_ENTRY_16���w�肳�ꂽ�Ƃ��́A�P�U�G���g�������������܂��B
	���̏ꍇ�́ApPaletteData�ɂ͂P�U�G���g�����̃f�[�^���K�v�ł��B 
	DataSize��KM_PALETTE_ENTRY_256���w�肳�ꂽ�Ƃ��́A�Q�T�U�G���g�������������܂��B
	���̏ꍇ�́ApPaletteData�ɂ͂Q�T�U�G���g�����̃f�[�^���K�v�ł��B 

	�p���b�g�̍\���ɂ��Ă� kmSetPaletteData ���Q�Ɗ肢�܂��B 

Arguments:
	IN KMINT32				Bank
		����������o���N�̔ԍ����w�肵�܂��B
		0 ���� 63 �܂ł̂����ꂩ���w��\�ł��B 
		8BPP�p���b�g�Ƃ��Ĉ����ꍇ�ɂ́A0�A16�A32�A48�̂����ꂩ���L���ł��B
		����ȊO�̒l���w�肳�ꂽ�ꍇ�́A�� 4 bit�� mask ���āA
		0,16,32,48�̂����ꂩ�ɕϊ����Ďg�p���܂��B 

	IN KMPALETTE_ENTRY_SIZE	DataSize
		����������p���b�g�f�[�^�̃T�C�Y���w�肵�܂��B
		�ȉ��̂����ꂩ���w��\�ł��B

		KM_PALETTE_ENTRY_16 	16�G���g�����̃f�[�^�����������܂��B 
								4 BPP�p���b�g�Ƃ��Ĉ����܂��B
		KM_PALETTE_ENTRY_256	256�G���g�����̃f�[�^�����������܂��B 
								8 BPP�p���b�g�Ƃ��Ĉ����܂��B


	IN PKMDWORD				pPaletteData
		Palette�ݒ�p�z��̃|�C���^���w�肵�܂��B
		���̃p���b�g�f�[�^�̗v�f�� ��DataSize �ȏ�Ȃ���΂Ȃ�܂���B
		���ꂪ DataSize �ȏ�Ȃ������ꍇ�̓���͕ۏ؂��܂���B 

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS  KMAPI
kmSetPaletteBank(
		IN KMINT32				Bank,
		IN KMPALETTE_ENTRY_SIZE	DataSize,
		IN PKMDWORD				pPaletteData
	);

/*++
kmSetBorderColor

proto type:
	KMSTATUS
	kmSetBorderColor(
			KMPACKEDARGB BorderColor
		);

Description:
	�{�[�_�[(�\����ʊO�̕���)�J���[�̐ݒ���s���܂��B

Arguments:
	IN	BorderColor		Packed��ARGB�J���[�ł��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetBorderColor(
		IN	KMPACKEDARGB BorderColor
	);

/*++
kmSetBackGroundRenderState

proto type:
	KMSTATUS
	kmSetBackGroundRenderState(
			PKMVERTEXCONTEXT	pVertexContext
		);

Description:
	kmProcessVertexRenderState �Őݒ肵�� KMVERTEXCONTEXT�\���̂̈ȉ��̃����o��
	Background Plane �̃����_�����O�p�����[�^�Ƃ��ăV�X�e���ɓo�^����B
	�{�֐��Ăяo���ȍ~�� kmSetBackGroundPlane() �Ŏw�肷�� �a�f�ʂ̐ݒ�́A
	�����ApVertexContext �Őݒ肵�� KMVERTEXCONTEXT �̒l���L���ɂȂ�B

	�Q�Ƃ��郁���o�F
				pVertexContext->GLOBALPARAMBUFFER
				pVertexContext->ISPPARAMBUFFER
				pVertexContext->TSPPARAMBUFFER
				pVertexContext->TexturePARAMBUFFER


Arguments:
	IN	pVertexContext
						Vertex Context �ւ̃|�C���^��^����B

Result:
	KMSTATUS_SUCCESS	�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetBackGroundRenderState(
		IN	PKMVERTEXCONTEXT	pVertexContext
	);

/*++
kmSetBackGroundPlane

proto type:
	KMSTATUS
	kmSetBackGroundPlane(
				PVOID			pVertex[3],
				KMVERTEXTYPE	VertexType,
				KMINT32			StructSize
			);

Description:
	�o�b�N�O���E���h���ʂ̐ݒ���s���܂��B
	���̑O�ɁAkmSetBackGroundRenderState ���Ăяo���K�v������܂��B

Arguments:
	IN	pVertex[3]		�o�b�N�O���E���h�v���[����̍��W���������_�f�[�^�\���̂ւ̃|�C���^
						�ڍׂ́A kmSetVertex �Q��

	IN	VertexType		���_�f�[�^�̃f�[�^�^�C�v�������B
						�ڍׂ� kmSetVertex �Q��
	IN	StructSize		���_�f�[�^�̃f�[�^�^�C�v�������B
						�ڍׂ� kmSetVertex �Q��

Result:
	KMSTATUS_SUCCESS			�ݒ萬��

--*/

KMSTATUS KMAPI
kmSetBackGroundPlane(
			IN	PVOID			pVertex[3],
			IN	KMVERTEXTYPE	VertexType,
			IN	KMINT32			StructSize
		);

/*++
kmSetBackGround

proto type:
	KMSTATUS
	kmSetBackGroundPlane(
				IN	PKMSTRIPHEAD	pStripHead,
				IN	KMVERTEXTYPE	VertexType,
				IN	PVOID			pVertex1,
				IN	PVOID			pVertex2,
				IN	PVOID			pVertex3
			);

Description:
	�o�b�N�O���E���h���ʂ̐ݒ���s���܂��B

Arguments:
	IN	pStripHead		�L���� KMSTRIPHEAD �\���̂ւ̃|�C���^��n���܂��B
	IN	VertexType		background �ʂŎg�p���钸�_�f�[�^�̃f�[�^�^�C�v�������B
	IN	pVertex1 / 		�o�b�N�O���E���h�v���[����̍��W���������_�f�[�^�\���̂ւ̃|�C���^
		pVertex2 /		(0-16)
		pVertex3

Result:
	KMSTATUS_SUCCESS			�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetBackGround(
		IN	PKMSTRIPHEAD	pStripHead,
		IN	KMVERTEXTYPE	VertexType,
		IN	PVOID			pVertex1,
		IN	PVOID			pVertex2,
		IN	PVOID			pVertex3
	);

/*++
kmSetAutoSortMode

proto type:
	KMSTATUS
	kmSetAutoSortMode(
			KMBOOLEAN fEnable
		);

Description:
	�������ʂ̃I�[�g�\�[�g���[�h��ON/OFF�𐧌䂵�܂��B

	-> �}���`�p�X�Ή��̂��߂ɁA���̊֐��͖����ɂ��܂����B
	   kmSetSystemConfiguration ���g�p���āA
	   �e�p�X���� AutoSort �̗L�����w�肵�Ă��������B

Arguments:
	IN	bEnable		Auto Sort mode �̗L�����t���O
				TRUE	�������ʂ̃\�[�g�ɃI�[�g�\�[�g���[�h��ݒ肵�܂��B
				FALSE	�]���^�Ɠ����\�t�g�E�F�A�ɂ��\�[�e�B���O���G�~�����[�V�������܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetAutoSortMode(
		IN	KMBOOLEAN fEnable
	);

/*++
kmSetPixelClipping

proto type:
	KMSTATUS
	kmSetPixelClipping(
				KMINT32	Xmin,
				KMINT32	Ymin,
				KMINT32	Xmax,
				KMINT32	Ymax
			);

Description:
	 Frame Buffer �ւ̃����_�����O�̏o�͂ɑ΂���A�s�N�Z���P�ʂ̃N���b�s���O��ݒ肵�܂��B

Arguments:
	IN	Xmin, Ymin, Xmax, Ymax
				�s�N�Z���P�ʂ̃N���b�s���O�̈�̍���A�E�����W���w�肵�܂��B
				(Xmin,Ymin)-(Xmax,Ymax)�́A��ʃT�C�Y��菬�����Ȃ���΂����܂���B
				�܂��A��ʃ��[�h��24bpp�̎��́A�N���b�s���O�̈�̍��W�͋����łȂ���΂����܂���
				(���Ȃ킿 2�s�N�Z���P�ʂł����N���b�s���O�̈��ݒ�ł��܂���)�B
				�����łȂ������ꍇ�ɂ́A(Xmin,Ymin)�ɑ΂��Ă͎w���� 1 �傫���l�A
										(Xmax,Ymax)�ɑ΂��Ă͎w���� 1 �������l���ݒ肳��܂��B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��
	KMSTATUS_INVALID_PARAMETER	�p�����[�^���s��

--*/

KMSTATUS KMAPI
kmSetPixelClipping(
		IN	KMINT32	Xmin,
		IN	KMINT32	Ymin,
		IN	KMINT32	Xmax,
		IN	KMINT32	Ymax
	);

/*++
kmSetRegionClipping

proto type:
	KMSTATUS
	kmSetRegionClipping(
				KMINT32	Xmin,
				KMINT32	Ymin,
				KMINT32	Xmax,
				KMINT32	Ymax
			);

Description:
	 Frame Buffer �ւ̃����_�����O�̏o�͂ɑ΂���A���[�W�����P�ʂ̃N���b�s���O��ݒ肵�܂��B

Arguments:
	IN	Xmin, Ymin, Xmax, Ymax
				���[�W�����P�ʂ̃N���b�s���O�̈�̍���A�E�����W���w�肵�܂��B
				(Xmin,Ymin)-(Xmax,Ymax)�́A��ʃT�C�Y��菬�����Ȃ���΂����܂���B

Result:
	KMSTATUS_SUCCESS		�ݒ萬��
	KMSTATUS_INVALID_PARAMETER	�p�����[�^���s��

--*/

KMSTATUS KMAPI
kmSetRegionClipping(
		IN	KMINT32	Xmin,
		IN	KMINT32	Ymin,
		IN	KMINT32	Xmax,
		IN	KMINT32	Ymax
	);

/*++
kmSetGlobalClipping

proto type:
	KMSTATUS
	kmSetGlobalClipping(
				KMINT32 nWidth, 
				KMINT32 nHeight
			);
Description:
	�O���[�o���N���b�s���O�̈���w�肵�܂��B0,0�I���W����Width�AHeight�Ŏw�肳�ꂽ
	�̈�ȊO�̂Ƃ���ɂ̓����_�����O����܂���B

Arguments:
	IN	nWidth, nHeight				�^�C���T�C�Y�́A32x32�ł��B
									���Ƃ���128x64�̗̈���w�肵�����ꍇ�ɂ� 
									Width = 4,Height= 2�Ƃ��܂��B

Result:
	KMSTATUS_SUCCESS					�ݒ萬��
	KMSTATUS_INVALID_PARAMETER			�ݒ莸�s

--*/

KMSTATUS KMAPI
kmSetGlobalClipping(
		IN	KMINT32 nWidth, 
		IN	KMINT32 nHeight
	);

/*++
kmSetStrideWidth

proto type:
	KMSTATUS
	kmSetStrideWidth(
			KMINT32 nWidth
		);

Description:
	�X�g���C�h�e�N�X�`���̃X�g���C�h�T�C�Y���w�肵�܂��B�X�g���C�h�T�C�Y�́A
	32 �̔{���łȂ���΂Ȃ�Ȃ��B

Arguments:
	IN	nWidth		�X�g���C�h�T�C�Y����͂���B
					�X�g���C�h�T�C�Y�� 32�̔{���łȂ���΂Ȃ�Ȃ��B

Result:
	KMSTATUS_SUCCESS			�ݒ萬��
	KMSTATUS_INVALID_PARAMETER	�p�����[�^���s��

--*/

KMSTATUS KMAPI
kmSetStrideWidth(
		KMINT32 nWidth
	);

/*++
kmResetRenderer

proto type:

	KMSTATUS
	kmResetRenderer( VOID );

Description:
	�����_�����O�p�C�v���C���̃\�t�g�E�F�A���Z�b�g���s���B

	�g�p����ꍇ�F
		�EStripBuffer�g�p���ɃX�g���b�v���̃f�[�^��`������Ȃ�����
		  �ꍇ�̋������Z�b�g����B

Arguments:
	NONE

Result:

	KMSTATUS_SUCCESS				����

--*/

KMSTATUS KMAPI
kmResetRenderer( VOID );

/*++
kmSetUserClipLevelAdjust

proto type:

	KMSTATUS
	kmSetUserClipLevelAdjust( KMADJUSTTYPE	Adjust,
				  PKMINT32	pLine
				 );

Description:
	���������̉�ʕ\�����[�h��ݒ肵�܂��B
	������g�p���邱�Ƃɂ��A���������̃��[�U�[�N���b�s���O�̈�̋��E���A
	��ʂ̂قڒ����ɗ���悤�ɂ��邱�Ƃ��ł��܂��B�ΐ�Q�[���Ȃǂŉ�ʂ�
	�㉺ 2 �������Ďg�p����ꍇ�ɐݒ肵�܂��B

	�_�Ђŉ�ʂ��㉺ 2 �ɕ����������ꍇ�́A���̊֐���KM_LEVEL_ADJUST_HALF���w�肵����ŁA
	���[�U�[�N���b�v�̈�̂x���W�����L�̂悤�ɐݒ肵�Ă��������B����ƁA���̃N���b�v�̈��
	���������̋��E���ɗ͉�ʂ̒����ƂȂ�悤�A�\���̈�𒲐����܂��B

		��ʂ̏c�����̉𑜓x	���[�U�[�N���b�v�̈�̂x���W
			240						0 �` 119�@�Ɓ@120 �` 239
			480						0 �` 255�@�Ɓ@256 �` 479

	�Ȃ��A���̏ꍇ�A��ʂ̏㕔�����C�����͕\�����Ȃ��Ȃ�܂��B�\������
	�Ȃ��Ȃ郉�C�����́ApLine���瓾�邱�Ƃ��ł��܂��B

Arguments:
	IN	Adjust	���������̉�ʕ\�����[�h���w�肵�܂��B
			�ȉ��̂����ꂩ���w��ł��܂��B
			KMADJUSTTYPE
			KM_LEVEL_ADJUST_NORMAL		�ʏ�\���p�̕\�����[�h�w�肵�܂��B
			KM_LEVEL_ADJUST_HALF		2�����\���p�̕\�����[�h���w�肵�܂��B


	OUT	pLine
			Adjust��KM_LEVEL_ADJUST_HALF���w�肵���ꍇ�A�_�Ђ͂����ɉ�ʂ̏㉺������
			�V�t�g�ʂ��s�N�Z�����ŕԂ��܂��B��ʂ̍ŏ㕔����A�����Ŏw�肳�ꂽ���C������
			�\������Ȃ��Ȃ�܂��B���_�o�^���ɂ͊e���_�̂x���W�l�ɁA���̒l�����Z���Ă��������B
			pLine �� NULL ���w�肵�Ă����܂��܂��񂪁A���̏ꍇ�A���[�U�͒��_�̂x���W�ɉ��Z���ׂ�
			���C�������擾���邱�Ƃ��ł��܂���B

			Adjust��KM_LEVEL_ADJUST_NORMAL���w�肵���ꍇ�́ApLine���w���̈�̓��e�͕ύX���܂���B


Result:

	KMSTATUS_SUCCESS				����

--*/
KMSTATUS KMAPI
kmSetUserClipLevelAdjust(
		IN	KMADJUSTTYPE	Adjust,
		OUT	PKMINT32	pLine
	);

/*++
kmGetGunTriggerPos

proto type:
	KMSTATUS KMAPI
	kmGetGunTriggerPos(
			PKMDWORD pHPos,
			PKMDWORD pVPos
		);

Description:
	Gun Peripheral �̃g���K�������ꂽ�ʒu��Ԃ��܂��B

Arguments:
	OUT	pHPos	H-Blank Out ����̐����ʒu
    OUT	pVPos	V-Blank Out ����̐����ʒu

Result:
	KMSTATUS_SUCCESS		����

--*/

KMSTATUS KMAPI
kmGetGunTriggerPos(
		OUT	PKMDWORD pHPos,
		OUT	PKMDWORD pVPos
	);

/*++
kmUseAnotherModifier

proto type:
	KMSTATUS
	kmUseAnotherModifier(
			KMLISTTYPE kmModifierListType
			);

Description:
	kmModifierListType �Ŏw�肵�� Modifier �𑼕��� 
	Modifier �Ƃ��Ă��g�p����B

	-> �}���`�p�X�Ή��̂��߂ɁA���̊֐��͖����ɂ��܂����B
	   kmSetSystemConfiguration ���g�p���āA�e�p�X���� 
		�����̃��X�g���g�p�@�\�̗L�����w�肵�Ă��������B

Arguments:
	IN	kmModifierListType		KM_OPAQUE_MODIFIER	Opaque Modifier �� Trans Modifier  �Ƃ��Ďg�p����B
								KM_TRANS_MODIFIER	Trans Modifier  �� Opaque Modifier �Ƃ��Ďg�p����B

Result:
	KMSTATUS_SUCCESS				�ݒ萬��
	KMSTATUS_INVALID_LIST_TYPE		�ݒ莸�s

--*/

KMSTATUS KMAPI
kmUseAnotherModifier(
		IN	KMLISTTYPE kmModifier
			);

/*++
kmSetCheapShadowMode

proto type:
	KMSTATUS
	kmSetCheapShadowMode(
			KMINT32 nIntensity
			);

Description:
	�`�[�v(�Ȉ�)�V���h�E���[�h��I�����܂��BCheapShadowMode�Ƃ́A����Polygon�� Modifier Volume �ɂ������������ꍇ�A
   ���̕����̋P�x�������邱�Ƃɂ��e��\������@�\�ł��B���̊֐��Œl���ݒ肳�ꂽ��́A���ׂĂ�ModifierVolume�̐ݒ��
   �`�[�v�V���h�E���[�h�ɐݒ肳��܂��B�V�[������ 2 �p�����[�^Polygon�Ƃ̋����͂ł��܂���B
   CheapShadowMode���I��������ɂ͈����ɕ��̐������Ă��̊֐����Ăяo���Ă��������B

Arguments:
	IN	nIntensity		���f�B�t�@�C�A�{�����[�����ɓ�����Polygon�̋P�x��ݒ肵�܂��B0����255�̒l���g�p�ł��܂��B
						���ۂɂ͂����256�Ŋ������l��Polygon�̃x�[�X�J���[�ƃI�t�Z�b�g�J���[�ɏ�Z����܂��B�]���āA
						128���w�肷���128/256 = 0.5����Z����邱�ƂɂȂ�܂��B�܂��A���̒l����͂����ꍇ�A
						���̃V�[������ CheapShadowMode �̐ݒ���I�����A�ʏ�� 2 �p�����[�^Polygon���L���ƂȂ�܂��B

Result:
	KMSTATUS_SUCCESS					�ݒ萬��
	KMSTATUS_INVALID_PARAMETER			�p�����[�^���s��

--*/

KMSTATUS KMAPI
kmSetCheapShadowMode(
		IN	KMINT32 nIntensity
			);


/*++
kmQueryFinishLastTextureDMA

proto type:
	KMSTATUS
	kmQueryFinishLastTextureDMA(KMVOID);

Description:
	�O���LoadTexture�ɂ��DMA���I���������ǂ������`�F�b�N���܂��B
	kmSetSystemConfiguration��flag��KM_CONFIGFLAG_NOWAIT_FINISH_TEXTUREDMA��
	�ꍇ�ɂ̂ݗL���ł��B����ȊO�̏ꍇ�ɂ́A���KMSTATUS_SUCCESS��Ԃ��܂��B

Arguments:
	�Ȃ�

Result:
	KMSTATUS_SUCCESS				�O���DMA�͏I�����Ă���
	KMSTATUS_NOT_FINISH_DMA			�O���DMA�͏I�����Ă��Ȃ�

--*/
KMSTATUS KMAPI
kmQueryFinishLastTextureDMA(KMVOID);


/*++
kmGetSystemMetrics

proto type:
	KMSTATUS
	kmGetSystemMetrics(
		PKMSYSTEMMETRICS pSysMetrics
		);

Description:

Arguments:
	IN	OUT	pSysMetrics				

Result:
	KMSTATUS_SUCCESS				

--*/
KMSTATUS KMAPI
kmGetSystemMetrics(
		IN OUT PKMSYSTEMMETRICS pSysMetrics
		);

/*++
kmSetPunchThroughThreshold

proto type:
	KMSTATUS KMAPI
	kmSetPunchThroughThreshold(
			IN	KMDWORD dwThreshold
		);

Description:
		Punch Through List �� �� ��臒l��ݒ肵�܂��B

			0 < �� < dwThreshold 	= 0
			dwThreshold  < �� < 255	= 0xff

Arguments:
	IN	dwThreshold		Punch Through List �� �� 臒l
						�͈� �F 0 - 255

Result:
	KMSTATUS_SUCCESS				�ݒ萬��

--*/
KMSTATUS KMAPI
kmSetPunchThroughThreshold(
		IN	KMDWORD dwThreshold
	);

#endif