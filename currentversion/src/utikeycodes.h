/***************************************************************************
 *   Copyright (C) 2006 by Michael Staud   *
 *   michael.staud@uni-ulm.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef DONOTDECLARE
#ifndef __UTIKEYCODES__
#define __UTIKEYCODES__



#define UTIKEYMAP(a, b) const int UTI_ ## a = b;
#endif
UTIKEYMAP(BackSpace,0xFF08)
UTIKEYMAP(Tab,0xFF09)
UTIKEYMAP(Linefeed,0xFF0A)
UTIKEYMAP(Clear,0xFF0B)
UTIKEYMAP(Return,0xFF0D)
UTIKEYMAP(Pause,0xFF13)
UTIKEYMAP(Scroll_Lock,0xFF14)
UTIKEYMAP(Escape,0xFF1B)
UTIKEYMAP(Delete,0xFFFF)

UTIKEYMAP(KP_Space,0xFF80)
UTIKEYMAP(KP_Tab,0xFF89)
UTIKEYMAP(KP_Enter,0xFF8D)
UTIKEYMAP(KP_F1,0xFF91)
UTIKEYMAP(KP_F2,0xFF92)
UTIKEYMAP(KP_F3,0xFF93)
UTIKEYMAP(KP_F4,0xFF94)
UTIKEYMAP(KP_Home,0xFF95)
UTIKEYMAP(KP_Left,0xFF96)
UTIKEYMAP(KP_Up,0xFF97)
UTIKEYMAP(KP_Right,0xFF98)
UTIKEYMAP(KP_Down,0xFF99)
UTIKEYMAP(KP_Prior,0xFF9A)
UTIKEYMAP(KP_Page_Up,0xFF9A)
UTIKEYMAP(KP_Next,0xFF9B)
UTIKEYMAP(KP_Page_Down,0xFF9B)
UTIKEYMAP(KP_End,0xFF9C)
UTIKEYMAP(KP_Begin,0xFF9D)
UTIKEYMAP(KP_Insert,0xFF9E)
UTIKEYMAP(KP_Delete,0xFF9F)
UTIKEYMAP(KP_Equal,0xFFBD)
UTIKEYMAP(KP_Multiply,0xFFAA)
UTIKEYMAP(KP_Add,0xFFAB)
UTIKEYMAP(KP_Separator,0xFFAC)
UTIKEYMAP(KP_Subtract,0xFFAD)
UTIKEYMAP(KP_Decimal,0xFFAE)
UTIKEYMAP(KP_Divide,0xFFAF)

UTIKEYMAP(KP_0,0xFFB0)
UTIKEYMAP(KP_1,0xFFB1)
UTIKEYMAP(KP_2,0xFFB2)
UTIKEYMAP(KP_3,0xFFB3)
UTIKEYMAP(KP_4,0xFFB4)
UTIKEYMAP(KP_5,0xFFB5)
UTIKEYMAP(KP_6,0xFFB6)
UTIKEYMAP(KP_7,0xFFB7)
UTIKEYMAP(KP_8,0xFFB8)
UTIKEYMAP(KP_9,0xFFB9)

UTIKEYMAP(F1,0xFFBE)
UTIKEYMAP(F2,0xFFBF)
UTIKEYMAP(F3,0xFFC0)
UTIKEYMAP(F4,0xFFC1)
UTIKEYMAP(F5,0xFFC2)
UTIKEYMAP(F6,0xFFC3)
UTIKEYMAP(F7,0xFFC4)
UTIKEYMAP(F8,0xFFC5)
UTIKEYMAP(F9,0xFFC6)
UTIKEYMAP(F10,0xFFC7)
UTIKEYMAP(F11,0xFFC8)
UTIKEYMAP(F12,0xFFC9)


UTIKEYMAP(A,0x041)
UTIKEYMAP(B,0x042)
UTIKEYMAP(C,0x043)
UTIKEYMAP(D,0x044)
UTIKEYMAP(E,0x045)
UTIKEYMAP(F,0x046)
UTIKEYMAP(G,0x047)
UTIKEYMAP(H,0x048)
UTIKEYMAP(I,0x049)
UTIKEYMAP(J,0x04a)
UTIKEYMAP(K,0x04b)
UTIKEYMAP(L,0x04c)
UTIKEYMAP(M,0x04d)
UTIKEYMAP(N,0x04e)
UTIKEYMAP(O,0x04f)
UTIKEYMAP(P,0x050)
UTIKEYMAP(Q,0x051)
UTIKEYMAP(R,0x052)
UTIKEYMAP(S,0x053)
UTIKEYMAP(T,0x054)
UTIKEYMAP(U,0x055)
UTIKEYMAP(V,0x056)
UTIKEYMAP(W,0x057)
UTIKEYMAP(X,0x058)
UTIKEYMAP(Y,0x059)
UTIKEYMAP(Z,0x05a)
UTIKEYMAP(bracketleft,0x05b)
UTIKEYMAP(backslash,0x05c)
UTIKEYMAP(bracketright,0x05d)
UTIKEYMAP(asciicircum,0x05e)
UTIKEYMAP(underscore,0x05f)
UTIKEYMAP(grave,0x060)
UTIKEYMAP(a,0x061)
UTIKEYMAP(b,0x062)
UTIKEYMAP(c, 0x063)
UTIKEYMAP(d,0x064)
UTIKEYMAP(e,0x065)
UTIKEYMAP(f,0x066)
UTIKEYMAP(g,0x067)
UTIKEYMAP(h,0x068)
UTIKEYMAP(i,0x069)
UTIKEYMAP(j,0x06a)
UTIKEYMAP(k,0x06b)
UTIKEYMAP(l,0x06c)
UTIKEYMAP(m,0x06d)
UTIKEYMAP(n,0x06e)
UTIKEYMAP(o,0x06f)
UTIKEYMAP(p,0x070)
UTIKEYMAP(q,0x071)
UTIKEYMAP(r,0x072)
UTIKEYMAP(s,0x073)
UTIKEYMAP(t,0x074)
UTIKEYMAP(u,0x075)
UTIKEYMAP(v,0x076)
UTIKEYMAP(w,0x077)
UTIKEYMAP(x,0x078)
UTIKEYMAP(y,0x079)
UTIKEYMAP(z,0x07aE)


UTIKEYMAP(Shift_L,0xFFE1)
UTIKEYMAP(Shift_R,0xFFE2)
UTIKEYMAP(Control_L,0xFFE3)
UTIKEYMAP(Control_R,0xFFE4)
UTIKEYMAP(Caps_Lock,0xFFE5)
UTIKEYMAP(Shift_Lock,0xFFE6)

UTIKEYMAP(Alt_L,0xFFE9)
UTIKEYMAP(Alt_R,0xFFEA)

UTIKEYMAP(space,0x020)
UTIKEYMAP(exclam,0x0219)
UTIKEYMAP(quotedbl,0x022)
UTIKEYMAP(numbersign,0x023)
UTIKEYMAP(dollar,0x024)
UTIKEYMAP(percent, 0x025)
UTIKEYMAP(ampersand ,0x026)
UTIKEYMAP(apostrophe,0x027)
UTIKEYMAP(parenleft,0x028)
UTIKEYMAP(parenright,0x029)
UTIKEYMAP(asterisk,0x02a)
UTIKEYMAP(plus,0x02b)
UTIKEYMAP(comma,0x02c)
UTIKEYMAP(minus,0x02d)
UTIKEYMAP(period,0x02e)
UTIKEYMAP(slash,0x02f)
UTIKEYMAP(0,0x030)
UTIKEYMAP(1,0x031)
UTIKEYMAP(2,0x032)
UTIKEYMAP(3,0x033)
UTIKEYMAP(4,0x034)
UTIKEYMAP(5,0x035)
UTIKEYMAP(6,0x036)
UTIKEYMAP(7,0x037)
UTIKEYMAP(8,0x038)
UTIKEYMAP(9,0x039)
UTIKEYMAP(colon,0x03a)
UTIKEYMAP(semicolon,0x03b)
UTIKEYMAP(less,0x03c)
UTIKEYMAP(equal,0x03d)
UTIKEYMAP(greater,0x03e)
UTIKEYMAP(question,0x03f)

#ifndef DONOTDECLARE
#undef UTIKEYMAP

#endif

#endif
