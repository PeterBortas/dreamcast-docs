; Tab width = 4

;----------------------------------------------------------------------------
; ** ���E�b�J�E���^ (LCD�\��, �^�C�}(T0)���荞��, �T�E���h�g�p�T���v��) **
;
; �E�v���O�����X�^�[�g����̎��Ԃ��J�E���g����(0�`99��59�b)
; �E1�����Ƃɉ���炷
;----------------------------------------------------------------------------
; 1.01 990208 SEGA Enterprises,LTD.
;----------------------------------------------------------------------------

chip	LC868700			; �`�b�v�̎�ނ��A�Z���u���Ɏw��
world	external			; �O���������p�v���O����

public	main				; ghead.asm ����Q�Ƃ����V���{��
public	int_T0H				; ghead.asm ����Q�Ƃ����V���{��

extern	_game_end			; �A�v���P�[�V�����I��


; **** �V�X�e���萔�̒�` ***************************************************

							; OCR(���U���䃌�W�X�^)�ݒ�l
osc_rc		equ 04dh		;	�V�X�e���N���b�N�ɓ���RC���U���w��
osc_xt		equ 0efh		;	�V�X�e���N���b�N�ɐ������U���w��


; *** �f�[�^�Z�O�����g ******************************************************

		dseg				; �f�[�^�Z�O�����g�J�n

r0:		ds		1			; �ԐڃA�h���b�V���O���W�X�^ r0
r1:		ds		1			; �ԐڃA�h���b�V���O���W�X�^ r1
r2:		ds		1			; �ԐڃA�h���b�V���O���W�X�^ r2
r3:		ds		1			; �ԐڃA�h���b�V���O���W�X�^ r3
		ds		12			; ���̑��̃��W�X�^

work1:	ds		1			; ��Ɨp(put2digit�Ŏg�p)

second:	ds		1			; �b�J�E���^
minute:	ds		1			; ���J�E���^


; *** �R�[�h�Z�O�����g ******************************************************

		cseg				; �R�[�h�Z�O�����g�J�n
		
; *-------------------------------------------------------------------------*
; * ���[�U�[�v���O����														*
; * �^�C�}(T0)���荞�݃T���v���u���E�b�J�E���^�v							*
; *-------------------------------------------------------------------------*
main:
		mov		#0, second	; ��������̃J�E���g�l�����Z�b�g����
		mov		#0, minute	;

		call	cls			; LCD�̏���
		call	T0Mode2Init	; �^�C�}T0�̏�����
		call	SndInit		; �����o�͂̏�����
		
loop0:
							; **** minute�̐��l��LCD�ɕ\������ ****
		mov		#0,c		;   �������W
		mov		#1,b		;   �������W
		ld		minute		;   �\���Ώې��l(��)
		call	put2digit	;   2�����l�\��
		
							; ****�u:�v��LCD�ɕ\������ ****
		mov		#2,c		;   �������W
		mov		#1,b		;   �������W
		mov		#10,acc		;   �L�����N�^�R�[�h
		call	putch		;   1�����\��
	
							; **** second�̐��l��LCD�ɕ\������ ****
		mov		#3,c		;   �������W
		mov		#1,b		;   �������W
		ld		second		;   �\���Ώې��l(�b)
		call	put2digit	;   2�����l�\��

							; ****�u.�v��LCD�ɕ\������ ****
		mov		#5,c		;  �������W
		mov		#1,b		;   �������W
		mov		#11,acc		;  �L�����N�^�R�[�h
		call	putch		;  1�����\��

							; **** 00�b�`01�b�܂Ńu�U�[��炷 ****
		ld		second		; second�l�̓ǂݍ���
		bnz		next3		; second != 0 �Ȃ�next3
		call	Snd2Start	; second == 0 �Ȃ特����
next3:						;
		ld		second		; second�l�̓ǂݍ���
		bnz		next4		; second != 1 �Ȃ�next4
		call	SndStop		; second == 1 �Ȃ特��~
next4:						;
		
		set1	pcon,0		; ���̊��荞�݂܂�HALT

							; ** [M](���[�h)�{�^���`�F�b�N **
		ld		P3
		bn		acc,6,finish ; [M]�{�^����������Ă�����A�v���I��

		jmp		loop0		; �J��Ԃ�

finish:						; ** �A�v���P�[�V�����I������ **
		jmp		_game_end	; �A�v���P�[�V�����I��


; *-------------------------------------------------------------------------*
; * �^�C�}/�J�E���^T0 �̏�����												*
; *   ���[�h2(16bit�J�E���^)�ŁA1�b���Ɋ��荞�݂�������						*
; *-------------------------------------------------------------------------*
T0Mode2Init:
		mov		#255,T0PRR	; �v���X�P�[���l�Z�b�g
							;   8bit�v���X�P�[���Ȃ̂�
							;   ���� = (256-255)*0.000183 = 0.000183
		mov		#high(65536-5464),T0HR ; �v���Z�b�g�l(H)�Z�b�g
		mov		#low(65536-5464),T0LR  ; �v���Z�b�g�l(L)�Z�b�g
							;   �v���X�P�[���ƃZ�b�g��
							;   0.000183 * 5464 = 0.999912 (��1sec)
							;   1�b���ɃI�[�o�[�t���[���N����
		mov		#0ffh,T0L	; �ŏ������ɃI�[�o�[�t���[����悤�ɂ���
		mov		#0ffh,T0H	;
		mov		#0e4h,T0CNT	; ���[�h2 (16bit�J�E���^)
							; T0H�I�[�o�[�t���[�Ŋ��荞�݂𔭐�������
							; T0����J�n
		
		; ���荞�݂�������Ă���K�v������ (mov #80h,IE)
	
		ret					; T0Mode2Init�I���


T0HStop:					; *** T0H�^�C�}��~ ***

		clr1	T0CNT,6		; T0L�J�E���g�����~
		clr1	T0CNT,7		; T0H�J�E���g�����~
		ret


; *-------------------------------------------------------------------------*
; * �^�C�}T0H���荞�݃n���h��												*
; *-------------------------------------------------------------------------*
int_T0H:					; *** T0H���荞�݃n���h�� ***
		push	acc

		inc		second		; �b�J�E���^��i�߂�
		ld		second		; �b�J�E���^��..
		bne		#60,tinx1	; 60�łȂ����tinx1��
		mov		#0,second	; 60�Ȃ�0�Ƀ��Z�b�g
		inc		minute		; ���J�E���^��i�߂�

		ld		minute		; ���J�E���^��..
		bne		#100,tinx1	; 100�łȂ����tinx1��
		mov		#0,minute	; 100�Ȃ�Ε��J�E���^��0�Ƀ��Z�b�g
tinx1:	
		pop		acc

		clr1	T0CNT,3		; �^�C�}���荞�ݗv���N���A
		clr1	T0CNT,1		;
		reti				; T0H���荞�݃n���h���I���


; *-------------------------------------------------------------------------*
; * �����o�͊֌W
; *-------------------------------------------------------------------------*
SndInit:					; *** �����o�̓n�[�h�̏����� ***
		clr1	P1,7		; �����o�̓|�[�g�Z�b�g
	
		ret
		
Snd1Start:					; *** ��342Hz �̔����J�n ***
		mov		#0f0h,T1LR	; ���� = 100h-0f0h = 16
		mov		#0f8h,T1LC	; L���x���� = 100h-0f8h = 8
		mov		#0D4h,T1CNT	; �����o�͊J�n
		
		ret

Snd2Start:					; *** ��781Hz �̔����J�n ***
		mov		#0f9h,T1LR	; ���� = 100h-0f9h = 7
		mov		#0fch,T1LC	; L���x���� = 100h-0fch = 4
		mov		#0D4h,T1CNT	; �����o�͊J�n
		
		ret

SndStop:					; *** ������~ ***
		mov		#0,T1CNT	; �����o�͒�~
		
		ret

		
; *-------------------------------------------------------------------------*
; * 2���̐��l��\������														*
; * ���� acc : ���l															*
; *        c : ���������ʒu												  	*
; *        b : ���������ʒu												  	*
; *-------------------------------------------------------------------------*
put2digit:
		push	b			; ���W�f�[�^��ޔ�
		push	c			;
		st		c			; 10�̈ʂ�1�̈ʂ̒l�����ꂼ��v�Z
		xor		a			; ( acc = acc/10, work1 = acc mod 10 )
		mov		#10,b		;
		div					;
		ld		b			;
		st		work1		; 1�̈ʂ̌v�Z���ʂ�work0�ɕۑ�
		ld		c			;
		pop		c			; ���W�l��(c.b)�ɕ��A
		pop		b			; 
		push	b			; �܂��ޔ�
		push	c			;
		call	putch		; 10�̈ʂ�\��
		ld		work1			; 1�̈ʂ̒l��ǂݍ���
		pop		c			; ���W�l��(c,b)�ɕ��A
		pop		b			; 
		inc		c			; �\�����W���E��
		call	putch		; 1�̈ʂ�\��

		ret					; put2digit�I���


; *-------------------------------------------------------------------------*
; * LCD�\���C���[�W����������												*
; *-------------------------------------------------------------------------*
cls:
		push	OCR			; OCR�l��ޔ�
		mov		#osc_rc,OCR ; �V�X�e���N���b�N���w��

		mov		#0,XBNK		; �\���pRAM�̃o���N�A�h���X���w��(BANK0)
		call	cls_s		; ���̃o���N���̃f�[�^���N���A

		mov		#1,XBNK		; �\���pRAM�̃o���N�A�h���X���w��(BANK1)
		call	cls_s		; ���̃o���N���̃f�[�^���N���A
		pop		OCR			; OCR�l�𕜋A
		
		ret					; cls�I���
		
cls_s:						; *** �\���pRAM 1BANK���̏��� ***
		mov		#80h,r2		; �ԐڃA�h���b�V���O���W�X�^��\���pRAM�̐擪��
		mov		#80h,b 		; ���[�v�J�E���^b�Ƀ��[�v�����Z�b�g
loop3:
		mov		#0,@r2		; �A�h���X���C���N�������g���Ȃ���0����������
		inc		r2			;
		dbnz	b,loop3		; b��0�ɂȂ�܂ŌJ��Ԃ�
		
		ret					; cls_s�I���
		

; *-------------------------------------------------------------------------*
; * �w��ʒu��1�L�����N�^�\������											*
; * ���� acc : �L�����N�^�R�[�h												*
; *        c : ���������ʒu												  	*
; *        b : ���������ʒu												  	*
; *-------------------------------------------------------------------------*
putch:
		push	XBNK
		push	acc
		call	locate		; ���W����\��RAM�̃A�h���X���v�Z
		pop		acc
		call	put_chara	; 1�L�����N�^�\������
		pop		XBNK
		
		ret					; putch�I���
		

locate:	; **** �\���ʒu�w�肩��\���pRAM�̃A�h���X���v�Z ****
		; ** ���� c: �����ʒu(0�`5) b: �����ʒu(0�`3)
		; ** �o�� r2: RAM�A�h���X XBNK: �\���pRAM�o���N

							; *** �\���pRAM�o���N�A�h���X�̔��f ***
		ld		b			; b>=2 �̂Ƃ� next1 ��
		sub		#2			;
		bn		PSW,7,next1	;
		
		mov		#00h,XBNK	; �\���pRAM�̃o���N�A�h���X���w��(BANK0)
		br		next2
next1:
		st		b
		mov		#01h,XBNK	; �\���pRAM�̃o���N�A�h���X���w��(BANK1)
next2:

							; *** �\���w��ʒu��RAM�A�h���X�v�Z ***
		ld		b			; b * 40h + c + 80h
		rol					;
		rol					;
		rol					;
		rol					;
		rol					;
		rol					;
		add		c			;
		add		#80h		;
		st		r2			; RAM�A�h���X��r2�Ɋi�[
				
		ret					; locate�I���


put_chara:
		push	PSW			; PSW�l��ޔ�
		set1	PSW,1		; �f�[�^RAM�o���N1��I��

							; *** �L�����N�^�f�[�^�A�h���X�̌v�Z ***
		rol					; (TRH,TRL) = acc*8 + fontdata
		rol					;
		rol					;	
		add		#low(fontdata)	;
		st		TRL				;
		mov		#0,acc			;
		addc	#high(fontdata)	;
		st		TRH			;

		push	OCR			; OCR�l��ޔ�
		mov		#osc_rc,OCR ; �V�X�e���N���b�N���w��

		mov		#0,b		; �L�����N�^�f�[�^�ǂݏo���p�I�t�Z�b�g�l
		mov		#4,c		; ���[�v�J�E���^
loop1:
		ld		b			; 1���C���ڂ̕\���f�[�^��ǂݏo��
		ldc					;
		inc		b			; �ǂݏo���f�[�^�̃I�t�Z�b�g�� +1
		st		@r2			; �\���f�[�^��\���pRAM�ɓ]��
		ld		r2			; �\���pRAM�A�h���X +6
		add		#6			;
		st		r2			;

		ld		b			; 2���C���ڂ̕\���f�[�^��ǂݏo��
		ldc					;
		inc		b			; �ǂݏo���f�[�^�̃I�t�Z�b�g�� +1
		st		@r2			; �\���f�[�^��\���pRAM�ɓ]��
		ld		r2			; �\���pRAM�A�h���X +10
		add		#10			;
		st		r2			;
		
		dec		c			; ���[�v�J�E���^�̃f�N�������g
		ld		c			; 
		bnz		loop1		; 8���C����(4��)�J��Ԃ�
		
		pop		OCR			; OCR�l�𕜋A
		pop		PSW			; PSW�l�𕜋A

		ret					; put_chara�I���


; *-------------------------------------------------------------------------*
; * �L�����N�^�̃r�b�g�C���[�W�f�[�^										*
; *-------------------------------------------------------------------------*
fontdata:
		db 07ch, 0e6h, 0c6h, 0c6h, 0c6h, 0ceh, 07ch, 000h	;0
		db 018h, 038h, 018h, 018h, 018h, 018h, 03ch, 000h	;1
		db 07ch, 0c6h, 0c6h, 00ch, 038h, 060h, 0feh, 000h	;2
		db 07ch, 0e6h, 006h, 01ch, 006h, 0e6h, 07ch, 000h	;3
		db 00ch, 01ch, 03ch, 06ch, 0cch, 0feh, 00ch, 000h	;4
		db 0feh, 0c0h, 0fch, 006h, 006h, 0c6h, 07ch, 000h	;5
		db 01ch, 030h, 060h, 0fch, 0c6h, 0c6h, 07ch, 000h	;6
		db 0feh, 0c6h, 004h, 00ch, 018h, 018h, 038h, 000h	;7
		db 07ch, 0c6h, 0c6h, 07ch, 0c6h, 0c6h, 07ch, 000h	;8
		db 07ch, 0c6h, 0c6h, 07eh, 006h, 00ch, 078h, 000h	;9
        
        db 000h, 030h, 030h, 000h, 000h, 030h, 030h, 000h	;:
        db 000h, 000h, 000h, 000h, 000h, 060h, 060h, 000h	;.
