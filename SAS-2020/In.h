#pragma once

#define IN_MAX_LEN_TEXT 1024*1024 
#define IN_CODE_ENDL '|'


#define IN_CODE_TABLE {\
	/* NON SOH	  STX	 ETX	EOT	   ENQ	  ACK	 BEL	BS	   Tab	  LF	 VT     FF     CR	  SO	 SI	  */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::T, IN::F, IN::F, IN::I, IN::F, IN::F, \
	/* DLE DC1	  DC2	 DC3	DC4	   NAK	  SYN	 ETB	CAN	   EM	  SUB	 ESC    FS     GS	  RS	 US	  */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	/* " " !	  "	     #	    $	   %	  &	     '	    (	   )	  *	     +      ,      -	  .    	 /	  */\
	IN::T, IN::T, IN::T, IN::F, IN::F, IN::F, IN::S, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::S, IN::F, IN::F, \
	/* 0   1	  2	     3	    4	   5	  6	     7	    8	   9	  :	     ;      <      =	  > 	 ?	  */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::S, IN::S, IN::F, \
	/* @   A      B      C      D      E      F      G      H      I      J      K      L      M      N      O    */\
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	/* P   Q      R      S      T      U      V      W      X        Y    Z      [      \      ]      ^      _    */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::S, IN::S, IN::F, IN::F, \
	/* `   a      b      c      d      e      f      g      h      i      j      k      l      m      n      o    */\
	IN::F, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	/* p   q      r      s      t      u      v      w      x      y      z      {      |      }      ~      DEL  */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::S, IN::F, IN::S, IN::S, IN::F, \
																													\
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	/* �   �      �      �      �      �      �      �             �      �      �      �      �      �      �    */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	/*     �      �      �      �      �      �      �      �      �      �      �      �             �      �    */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, IN::F, \
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, \
	/* �   �      �      �      �      �      �      �      �      �      �      �      �      �      �      �    */\
	IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T, IN::T  \
					  }


namespace In
{
	struct IN
	{
		enum { T = 1024, F = 2048, I = 4096, S = 5120 }; // � - ���������� ������, F - ������������,I - ������������, ����� �������� S- ���� ������� - ������ ����� � �����.
		int size;   //������ ��������� ����
		int lines;	//���������� �����
		int ignor;	//���������� ����������������� ��������
		char* text;	//�������� ���
		int code[256] = IN_CODE_TABLE;		//������� ��������  T,F,I ����� ��������
	};

	IN getin(wchar_t infile[]);
	void FileOut(wchar_t outfile[], IN in);
	int words(char* text);
};