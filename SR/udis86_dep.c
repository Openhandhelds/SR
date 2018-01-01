/**
 *
 *  Copyright (C) 2016 Roman Pauer
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy of
 *  this software and associated documentation files (the "Software"), to deal in
 *  the Software without restriction, including without limitation the rights to
 *  use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
 *  of the Software, and to permit persons to whom the Software is furnished to do
 *  so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 */

#define DEFINE_VARIABLES
	#include "udis86_dep.h"
#undef DEFINE_VARIABLES

#if (OUTPUT_TYPE == OUT_ARM_LINUX)
    #define FLAGS_MODIF(f) (f)
#else
    #define FLAGS_MODIF(f) ((f) & ~(FL_CARRY_SUB_ORIGINAL | FL_CARRY_SUB_INVERTED))
#endif

#define SET_FLAGS(x, y, z) { \
	if ((x) >= MAX_MNEMONICS) return -1; \
	flags_needed[x] = FLAGS_MODIF(y); \
	flags_modified[x] = FLAGS_MODIF(z); }


int init_udis86_dep(void)
{
	int i;

	for (i = 0; i < MAX_MNEMONICS; i++)
	{
		flags_needed[i] = FL_UNKNOWN;
		flags_modified[i] = FL_UNKNOWN;
	}
	/* A */
	SET_FLAGS(UD_Iaam, FL_NONE, FL_COND);
	SET_FLAGS(UD_Iadc, FL_CARRY | FL_CARRY_SUB_INVERTED, FL_COND);
	SET_FLAGS(UD_Iadd, FL_NONE, FL_COND);
	SET_FLAGS(UD_Iand, FL_NONE, FL_COND);

	/* B */
	SET_FLAGS(UD_Ibsr, FL_NONE, FL_COND);
	SET_FLAGS(UD_Ibt, FL_NONE, FL_COND);

	/* C */
	SET_FLAGS(UD_Icall, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Icbw, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Icdq, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iclc, FL_NONE, FL_CARRY | FL_CARRY_SUB_INVERTED);
	SET_FLAGS(UD_Icld, FL_NONE, FL_DIRECTION);
	SET_FLAGS(UD_Icli, FL_NONE, FL_INTERRUPT);
	SET_FLAGS(UD_Icmc, FL_CARRY, FL_CARRY);
	SET_FLAGS(UD_Icmp, FL_NONE, FL_COND_SUB);
	SET_FLAGS(UD_Icmpsb, /* FL_DIRECTION */ FL_NONE, FL_COND_SUB);
	SET_FLAGS(UD_Icwd, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Icwde, FL_NONE, FL_NONE);

	/* D */
	SET_FLAGS(UD_Idec, FL_NONE, FL_PARITY | FL_ADJUST | FL_ZERO | FL_SIGN | FL_OVERFLOW);
	SET_FLAGS(UD_Idiv, FL_NONE, FL_COND);

	/* E */
	SET_FLAGS(UD_Ienter, FL_NONE, FL_NONE);

	/* F */
	SET_FLAGS(UD_Ifabs, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifadd, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifaddp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifchs, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifcomp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifcompp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifcos, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifdiv, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifdivp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifdivr, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifdivrp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifild, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifistp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifld, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifld1, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifldcw, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifldln2, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifldz, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifmul, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifmulp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifninit, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifnstcw, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifnstsw, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsin, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsqrt, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifst, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifstp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsub, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsubp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsubr, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifsubrp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifxch, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ifyl2x, FL_NONE, FL_NONE);

	/* I */
	SET_FLAGS(UD_Iidiv, FL_NONE, FL_COND);
	SET_FLAGS(UD_Iimul, FL_NONE, FL_COND);
	SET_FLAGS(UD_Iin, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iinc, FL_NONE, FL_PARITY | FL_ADJUST | FL_ZERO | FL_SIGN | FL_OVERFLOW);
	SET_FLAGS(UD_Iint, FL_NONE, FL_ALL);
	SET_FLAGS(UD_Iint1, FL_NONE, FL_ALL);
	SET_FLAGS(UD_Iint3, FL_NONE, FL_ALL);

	/* J */
	SET_FLAGS(UD_Ija, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijae, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijb, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijbe, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijc, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijecxz, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ijg, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijge, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijmp, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ijl, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijle, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijnb, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijnbe, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijnc, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Ijnl, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijnle, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Ijns, FL_SIGN, FL_NONE);
	SET_FLAGS(UD_Ijnz, FL_ZERO, FL_NONE);
	SET_FLAGS(UD_Ijs, FL_SIGN, FL_NONE);
	SET_FLAGS(UD_Ijz, FL_ZERO, FL_NONE);

	/* L */
	SET_FLAGS(UD_Ilahf, FL_AH | FL_WEAK, FL_NONE);
	SET_FLAGS(UD_Ilss, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilds, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilea, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iles, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilfs, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilgs, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ileave, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilodsb, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilodsd, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ilodsw, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iloop, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iloope, FL_ZERO, FL_NONE);
	SET_FLAGS(UD_Iloopnz, FL_ZERO, FL_NONE);
	SET_FLAGS(UD_Ilss, FL_NONE, FL_NONE);

	/* M */
	SET_FLAGS(UD_Imov, FL_NONE, FL_SPECIFIC);
	SET_FLAGS(UD_Imovsb, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Imovsd, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Imovsw, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Imovsx, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Imovzx, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Imul, FL_NONE, FL_COND);

	/* N */
	SET_FLAGS(UD_Ineg, FL_NONE, FL_COND_SUB);
	SET_FLAGS(UD_Inop, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Inot, FL_NONE, FL_NONE);

	/* O */
	SET_FLAGS(UD_Ior, FL_NONE, FL_COND);
	SET_FLAGS(UD_Iout, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ioutsb, /* FL_DIRECTION */ FL_NONE, FL_NONE);

	/* P */
	SET_FLAGS(UD_Ipop, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipopa, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipopad, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipopfd, FL_NONE, FL_ALL /* | FL_WEAK */);
	SET_FLAGS(UD_Ipush, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipusha, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipushad, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ipushfd, FL_ALL | FL_WEAK, FL_NONE);
	SET_FLAGS(UD_Ipushfw, FL_ALL | FL_WEAK, FL_NONE);

	/* R */
	SET_FLAGS(UD_Iret, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Iretf, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ircl, FL_CARRY | FL_CARRY_SUB_INVERTED, FL_CARRY | FL_CARRY_SUB_INVERTED | FL_OVERFLOW);
	SET_FLAGS(UD_Ircr, FL_CARRY | FL_CARRY_SUB_INVERTED, FL_CARRY | FL_CARRY_SUB_INVERTED | FL_OVERFLOW);
	SET_FLAGS(UD_Irol, FL_NONE, FL_CARRY | FL_CARRY_SUB_INVERTED | FL_OVERFLOW);
	SET_FLAGS(UD_Iror, FL_NONE, FL_CARRY | FL_CARRY_SUB_INVERTED | FL_OVERFLOW);

	/* S */
	SET_FLAGS(UD_Isahf, FL_NONE, FL_AH);
	SET_FLAGS(UD_Isal, FL_NONE, FL_COND);
	SET_FLAGS(UD_Isar, FL_NONE, FL_COND);
	SET_FLAGS(UD_Isbb, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_COND_SUB);
	SET_FLAGS(UD_Iscasb, /* FL_DIRECTION */ FL_NONE, FL_COND_SUB);
	SET_FLAGS(UD_Iseta, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Isetb, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Isetbe, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Isetg, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetge, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetl, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetle, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetnb, FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Isetnbe, FL_ZERO | FL_CARRY | FL_CARRY_SUB_ORIGINAL, FL_NONE);
	SET_FLAGS(UD_Isetnl, FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetnle, FL_ZERO | FL_SIGN | FL_OVERFLOW, FL_NONE);
	SET_FLAGS(UD_Isetnz, FL_ZERO, FL_NONE);
	SET_FLAGS(UD_Isetz, FL_ZERO, FL_NONE);
	SET_FLAGS(UD_Ishl, FL_NONE, FL_COND);
	SET_FLAGS(UD_Ishld, FL_NONE, FL_COND);
	SET_FLAGS(UD_Ishr, FL_NONE, FL_COND);
	SET_FLAGS(UD_Ishrd, FL_NONE, FL_COND);
	SET_FLAGS(UD_Istc, FL_NONE, FL_CARRY | FL_CARRY_SUB_INVERTED);
	SET_FLAGS(UD_Istd, FL_NONE, FL_DIRECTION);
	SET_FLAGS(UD_Isti, FL_NONE, FL_INTERRUPT);
	SET_FLAGS(UD_Istosb, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Istosd, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Istosw, /* FL_DIRECTION */ FL_NONE, FL_NONE);
	SET_FLAGS(UD_Isub, FL_NONE, FL_COND_SUB);

	/* T */
	SET_FLAGS(UD_Itest, FL_NONE, FL_COND);

	/* V */
	SET_FLAGS(UD_Iverr, FL_NONE, FL_ZERO);

	/* W */
	SET_FLAGS(UD_Iwait, FL_NONE, FL_NONE);

	/* X */
	SET_FLAGS(UD_Ixchg, FL_NONE, FL_NONE);
	SET_FLAGS(UD_Ixor, FL_NONE, FL_COND);

	return 0;
}