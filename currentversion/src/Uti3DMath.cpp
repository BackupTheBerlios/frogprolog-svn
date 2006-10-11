//Uti3DMath.cpp
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



#include "Uti3DMath.h"

#include <math.h>
#include <stdio.h>

#include <iostream>

using namespace std;


//TODO: Im Falle von Multitasking klappt das mit der Globalen tempmatrix nicht
//Man muss fr jeden Thread eine machen
//CMatrix mMat;



//Summand + Summand = Summe
//Subtrahend - Minuend = Differenz
//Faktor * Faktor = Produkt
//Dividend : Divisor = Quotient

float absf(float x)
{
    if (x < 0) 
		return(-x);
	else
		return(x);
};



const CVector setVector(float x, float y, float z)
{
   CVector r;
   r.setVector(x, y, z);
   return r;
}

int maxf(float x, float y, float z) 
{
   int i = 0;
   float m = absf(x);
   if (absf(y) > m) { m = absf(y); i = 1; };
   if (absf(z) > m) { m = absf(z); i = 2; };
   return(i);
};


void Point_Add(float *sum, float* s1, float* s2, int count)
{
	for (int i = 0; i < count; i++) {
		sum[i] = s1[i] + s2[i];
	}
}

void Point_Sub(float *diff, float *sub, float *min, int count)
{
    for (int i = 0; i < count; i++) {
		diff[i] = sub[i] - min[i];
	}
}

void Point_Mul(float *p, float *f1, float *f2, int count)
{
    for (int i = 0; i < count; i++) {
		p[i] = f1[i] * f2[i];
	}
}

void Point_Div(float *quot, float *div, float *divisor, int count)
{
    for (int i = 0; i < count; i++) {
		quot[i] = div[i] / divisor[i];
	}
}

void Point_Add_Value(float *sum, float*sum1, float value, int count)
{
	for (int i = 0; i < count; i++) {
		sum[i] = sum1[i] + value;
	}
}

void Point_Sub_Value(float *diff, float*sub1, float min, int count)
{
	for (int i = 0; i < count; i++) {
		diff[i] = sub1[i] - min;
	}
}

void Value_Sub_Point(float *diff, float sub1, float* min, int count)
{
	for (int i = 0; i < count; i++) {
		diff[i] = sub1 - min[i];
	}
}

void Point_Mul_Value(float *pro, float*f1, float value, int count)
{
	for (int i = 0; i < count; i++) {
		pro[i] = f1[i] * value;
	}
}

void Point_Div_Value(float *quot, float*div, float divisor, int count)
{
	for (int i = 0; i < count; i++) {
		quot[i] = div[i] / divisor;
	}
}

void Value_Div_Point(float *quot, float div, float*divisor, int count)
{
	for (int i = 0; i < count; i++) {
		quot[i] = div / divisor[i];
	}
}


/*CVector::CVector(const S3DPoint & start, const S3DPoint & ende)
{
	x = (float)(ende.x - start.x);
	y = (float)(ende.y - start.y);
   z =(float)(ende.z - start.z);
}

CVector::CVector(const CVector &start, const CVector & ende)
{
x = (float)(ende.x - start.x);
	y = (float)(ende.y - start.y);
   z =(float)(ende.z - start.z);
};

CVector::CVector(TVector &v)
{
	x = v.x;
	y = v.y;
	z = v.z;

}
	
CVector::CVector(float _x, float _y, float _z)
{
	x = _x;
   y = _y;
	z = _z;
}*/

void CVector::Read(CStream & Stream)
{
	Stream.ReadFloat(x);
    Stream.ReadFloat(y);
	Stream.ReadFloat(z);
}
   
void CVector::Write(CStream & Stream)
{
Stream.WriteFloat(x);
    Stream.WriteFloat(y);
	Stream.WriteFloat(z);
}

/*CVector::~CVector(void)
{

}
*/
void CVector::Neg()
{
	x = -x;
	y = -y;
	z = -z;
}

void CVector::print()
{
  // wcout << UTEXT("Vektor X: ") << x << UTEXT(" Y: ") << y << UTEXT(" Z: ") << z;
}

void CVector::setVector(float _x, float _y, float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

float CVector::length()
{
	return((float)sqrt(x*x+y*y+z*z));
}

void CVector::scalVector(float value)
{
	x = x*value;
	y = y*value;
	z = z*value;
}
	
float CVector::Normalize()
{
   float length = (float)sqrt(x*x+y*y+z*z);
   if (length == 0) return(0);
   x = x / length;
   y = y / length;
   z = z / length;
   return(length);
}

float CVector::DistanceTo(CVector*v )
{
   float kx = x-v->x;
   float ky = y-v->y;
   float kz = z-v->z;
return (float)sqrt(kx*kx+ky*ky+kz*kz);
}
	
void CVector::addVector(float _x, float _y, float _z)
{
	x = x + _x;
	y = y + _y;
	z = z + _z;
}
	
void CVector::subVector(float _x, float _y, float _z)
{
	x = x - _x;
	y = y - _y;
	z = z - _z;
}

CVector CVector::operator+(const CVector & b)
{
	float sx,sy,sz;
	sx = x + b.x;
	sy = y + b.y;
	sz = z + b.z;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}

CVector CVector::operator+(const S3DPoint & b)
{
	float sx,sy,sz;
	sx = x + b.x;
	sy = y + b.y;
	sz = z + b.z;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}

CVector CVector::operator-(const CVector & b)
{
	float sx,sy,sz;
	sx = x - b.x;
	sy = y - b.y;
	sz = z - b.z;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}

CVector CVector::operator-(const S3DPoint & b)
{
	float sx,sy,sz;
	sx = x - b.x;
	sy = y - b.y;
	sz = z - b.z;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}


CVector CVector::operator-()
{
	float sx,sy,sz;
	sx = -x;
	sy = -y;
	sz = -z;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}  

CVector& CVector::operator= (const S3DPoint &a)
{

	x = a.x;
	y = a.y;
	z = a.z; 
	return(*this);
};
/*CVector& CVector::operator= (const SVector &a)
{
	CVector r;
	x = a.x;
	y = a.y;
	z = a.z; 
	return(*this);
};
*/
CEntity& CEntity::operator= (const SEntity &a)
{
    CEntity r;
	Group = a.Group;
	Position.x = a.Position.x;
	Position.y = a.Position.y;
	Position.z = a.Position.z;
	Rotation.x = a.Rotation.x;
	Rotation.y = a.Rotation.y;
	Rotation.z = a.Rotation.z;
	valid = a.valid;
	return(*this);
}

/*S3DPoint& CVector::operator= (const CVector &a)
{
	S3DPoint r;
	r.x = a.x;
	r.y = a.y;
	r.z = a.z; 
	return(r);
}; */

CVector &CVector::operator+=(const CVector &s)
{
	x += s.x;
	y += s.y;
	z += s.z;
	return(*this);
};
CVector &CVector::operator+=(const S3DPoint &s)
{
	x += s.x;
	y += s.y;
	z += s.z;
	return(*this);
};

CVector &CVector::operator-=(const CVector &s)
{
	
	x -= s.x;
	y -= s.y;
	z -= s.z;
	return(*this);
};

CVector &CVector::operator-=(const S3DPoint &s)
{
	x -= s.x;
	y -= s.y;
	z -= s.z;
	return(*this);
};


float CVector::operator*(const CVector & b)
{
  
   return x*b.x+y*b.y+z*b.z;
} 

void CVector::ReflectVector(CVector* Norm)
{
    CVector n1;
	float proj = (*this*-1)*(*Norm);
	n1 = (*Norm)*proj;

	CVector f = 2*n1+ *this;
	*this = f;
}

int CVector::GetMajorAxis()
{
   return(maxf(x, y, z));
}

CVector CVector::GetMajorNormal()
{
	CVector result;
	switch(GetMajorAxis()) {
	case 0: result.setVector(1, 0, 0); break;
	case 1: result.setVector(0, 1, 0); break;
	case 2: result.setVector(0, 0, 1); break;
	};
	return result;
}

void CVector::CrossProduct(CVector* p1, CVector *res)
{
  
	res->x = y*p1->z-z*p1->y;
   res->y = z*p1->x-x*p1->z;
   res->z = x*p1->y-y*p1->x;

}

void CVector::CalcRightUpVector(CVector* right, CVector* up)
{
	CVector maj(GetMajorNormal());

	int major = GetMajorAxis();
	if (x == 1 || y == 1 || z == 1 || x == -1 || y == -1 || z == -1) {
		if ((major == 0 && x > 0) || major == 1) {
			right->setVector(0, 0, -1);
		} else if (major == 0) {
		  right->setVector(0, 0, 1);
		} else {
		  right->setVector(z, 0, 0);
		};

	} else
	   CrossProduct(&maj, right);
	
	
	CrossProduct(right, up);
}



CVector CVector::operator*(float n)
{
	float sx,sy,sz;
	sx = x * n;
	sy = y * n;
	sz = z * n;
	CVector sum;
	sum.x = sx;
	sum.y = sy;
	sum.z = sz;
	return sum;
}

float CVector::operator*(const S3DPoint &b)
{
   return x*b.x+y*b.y+z*b.z;
};

CVector CVector::operator^(const CVector &b)
{
	CVector cvVector;
	cvVector.x = y*b.z-z*b.y;
   cvVector.y = z*b.x-x*b.z;
   cvVector.z = x*b.y-y*b.x;
   return(cvVector);
};

C3DPoint::C3DPoint()
{
	x = 0; 
	y = 0; 
	z = 0;
}

void C3DPoint::print()
{
//   wcout << UTEXT("Punkt X: ") << x << UTEXT(" Y: ") << y << UTEXT(" Z: ") << z;
}

C3DPoint::C3DPoint(float _x, float _y, float _z)
{
	x = _x; y = _y; z = _z;
}

C3DPoint::~C3DPoint() {}

/*CMatrix::CMatrix()
{
	LoadIdentity();
}*/

//CMatrix::~CMatrix() {}

/*void CMatrix::LoadIdentity()
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	m[1][0] = m[2][0] = m[3][0] = 0;
	m[0][1] = m[2][1] = m[3][1] = 0;
	m[0][2] = m[1][2] = m[3][2] = 0;
	m[0][3] = m[1][3] = m[2][3] = 0;
}*/

void CMatrix::SetXRotation(float value)
{
	//LoadIdentity();
	m[0][0] = m[3][3] = 1;
	   m[1][0] = m[2][0] = m[3][0] = 0;
	   m[0][1] =  m[3][1] = 0;
	   m[0][2] =  m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
	float c = (float)cos(value*pi180);
	float s = (float)sin(value*pi180);
	m[1][1] = c;
	m[2][1] = s;
	m[1][2] = -s;
	m[2][2] = c;
}

void CMatrix::SetYRotation(float value)
{
	 m[1][1] =  m[3][3] = 1;
	   m[1][0] =  m[3][0] = 0;
	   m[0][1] = m[2][1] = m[3][1] = 0;
	    m[1][2] = m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
	float c =(float) cos(value*pi180);
	float s = (float)sin(value*pi180);
	m[0][0] = c;
	m[2][0] = -s;
	m[0][2] = s;
	m[2][2] = c;
}

void CMatrix::SetZRotation(float value)
{
	  m[2][2] = m[3][3] = 1;
	   m[2][0] = m[3][0] = 0;
	    m[2][1] = m[3][1] = 0;
	   m[0][2] = m[1][2] = m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
	float c = (float)cos(value*pi180);
	float s = (float)sin(value*pi180);
	m[0][0] = c;
	m[1][0] = s;
	m[0][1] = -s;
	m[1][1] = c;
}

void CMatrix::SetTranslate(float _x, float _y, float _z)
{
	m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	   m[1][0] = m[2][0] = m[3][0] = 0;
	   m[0][1] = m[2][1] = m[3][1] = 0;
	   m[0][2] = m[1][2] = m[3][2] = 0;
	   
	m[0][3] = _x;
	m[1][3] = _y;
	m[2][3] = _z;
}

void CMatrix::SetScaling(float _x, float _y, float _z)
{
	 m[3][3] = 1;
	   m[1][0] = m[2][0] = m[3][0] = 0;
	   m[0][1] = m[2][1] = m[3][1] = 0;
	   m[0][2] = m[1][2] = m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
	m[0][0] = _x;
	m[1][1] = _y;
	m[2][2] = _z;
}

void CMatrix::Rotate(float _x, float _y, float _z)
{
    CMatrix mMat;

	if (_y != 0) { 
	   mMat.SetYRotation(_y);
	   multipyMatrix(mMat);
	}

	if (_x != 0) { 
	   mMat.SetXRotation(_x);
      multipyMatrix(mMat);
	}

	if (_z != 0) { 
	   mMat.SetZRotation(_z);
   	multipyMatrix(mMat);
	}
}

void CMatrix::RotateInv(float _x, float _y, float _z)
{
    CMatrix mMat;
if (_z != 0) { 
	   mMat.SetZRotation(-_z);
   	multipyMatrix(mMat);
	}
	
	if (_x != 0) { 
	   mMat.SetXRotation(-_x);
      multipyMatrix(mMat);
	}
if (_y != 0) { 
	   mMat.SetYRotation(-_y);
	   multipyMatrix(mMat);
	}

	
}

void CMatrix::Translation(float _x, float _y, float _z)
{
   
   if ((_x != 0) || (_y != 0) || (_z != 0)) {
	   CMatrix mMat;
      mMat.SetTranslate(_x, _y, _z);
		multipyMatrix(mMat);
	}
}

void CMatrix::Scaling(float _x, float _y, float _z)
{
   
   if ((_x != 1) || (_y != 1) || (_z != 1)) {
	  CMatrix mMat;
      mMat.SetScaling(_x, _y, _z);
		multipyMatrix(mMat);
	}
}

CMatrix CMatrix::operator*(const CMatrix & b)
{
   CMatrix mMat;
   int i, j, k;

   float sum; 
   for (i=0; i<4; i++) {
      for (j=0; j<4; j++) {
         sum = 0;
			for (k=0; k<4; k++) {
            sum += m[i][k] * b.m[k][j];
			}
			mMat.m[i][j] = sum;
		}
   } 
   return mMat;
}

void CMatrix::print()
{
//	int i, j;

//   cout << UTEXT("\n");
  /* for (i=0; i<4; i++) {
      for (j=0; j<4; j++) {
         wcout << m[j][i] << UTEXT("   | ");
		}
		wcout << UTEXT("\n");
	}*/
   
}

C3DPoint CMatrix::Transform(const C3DPoint & b)
{
	C3DPoint r;
	r.x = b.x * m[0][0] + b.y * m[1][0] + b.z * m[2][0] + m[0][3];
	r.y = b.x * m[0][1] + b.y * m[1][1] + b.z * m[2][1] + m[1][3];
	r.z = b.x * m[0][2] + b.y * m[1][2] + b.z * m[2][2] + m[2][3];
   return r;
}


void CMatrix::TransformNorm(S3DPoint *p)
{
   float x, y, z;
   x = p->nx * m[0][0] + p->ny * m[0][1] + p->nz * m[0][2];
   y = p->nx * m[1][0] + p->ny * m[1][1] + p->nz * m[1][2];
   z = p->nx * m[2][0] + p->ny * m[2][1] + p->nz * m[2][2];
   p->nx = x;
   p->ny = y;
   p->nz = z;
}

void CMatrix::TransformAll(S3DPoint *p)
{
   float x, y, z;
   x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2] + m[0][3];
   y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2] + m[1][3];
   z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2] + m[2][3];
   p->x = x;
   p->y = y;
   p->z = z;
   x = p->nx * m[0][0] + p->ny * m[0][1] + p->nz * m[0][2];
   y = p->nx * m[1][0] + p->ny * m[1][1] + p->nz * m[1][2];
   z = p->nx * m[2][0] + p->ny * m[2][1] + p->nz * m[2][2];
   p->nx = x;
   p->ny = y;
   p->nz = z;
}

void CMatrix::Transpose(CMatrix* target)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			target->m[j][i] = m[i][j];
		}
	};
}

void Perform_OpenGL_matrix_inverse(float* _in,float* _out)
{
	float scale;
   scale = _in[TBGL[0*4 + 0]] * _in[TBGL[0*4 + 0]] +
            _in[TBGL[0*4 + 1]] * _in[TBGL[0*4 + 1]] +
            _in[TBGL[0*4 + 2]] * _in[TBGL[0*4 + 2]];
   scale = 1/scale;
   _out[TBGL[0 * 4 + 0]] = scale * _in[TBGL[0*4 + 0]];
   _out[TBGL[1 * 4 + 0]] = scale * _in[TBGL[0*4 + 1]];
   _out[TBGL[2 * 4 + 0]] = scale * _in[TBGL[0*4 + 2]];
   _out[TBGL[0 * 4 + 1]] = scale * _in[TBGL[1*4 + 0]];
   _out[TBGL[1 * 4 + 1]] = scale * _in[TBGL[1*4 + 1]];
   _out[TBGL[2 * 4 + 1]] = scale * _in[TBGL[1*4 + 2]];
   _out[TBGL[0 * 4 + 2]] = scale * _in[TBGL[2*4 + 0]];
   _out[TBGL[1 * 4 + 2]] = scale * _in[TBGL[2*4 + 1]];
   _out[TBGL[2 * 4 + 2]] = scale * _in[TBGL[2*4 + 2]];

   _out[TBGL[0*4 + 3]]   = -(_out[TBGL[0*4 + 0]] * _in[TBGL[0*4 + 3]] +
                        _out[TBGL[0*4 + 1]] * _in[TBGL[1*4 + 3]] +
                        _out[TBGL[0*4 + 2]] * _in[TBGL[2*4 + 3]]);
   _out[TBGL[1*4 + 3]]   = -(_out[TBGL[1*4 + 0]] * _in[TBGL[0*4 + 3]] +
                        _out[TBGL[1*4 + 1]] * _in[TBGL[1*4 + 3]] +
                        _out[TBGL[1*4 + 2]] * _in[TBGL[2*4 + 3]]);
   _out[TBGL[2*4 + 3]]   = -(_out[TBGL[2*4 + 0]] * _in[TBGL[0*4 + 3]] +
                        _out[TBGL[2*4 + 1]] * _in[TBGL[1*4 + 3]] +
                        _out[TBGL[2*4 + 2]] * _in[TBGL[2*4 + 3]]);
   _out[TBGL[3*4 + 0]] = 0;
   _out[TBGL[3*4 + 1]] = 0;
   _out[TBGL[3*4 + 2]] = 0;
   _out[TBGL[3*4 + 3]] = 1;
}

void CMatrix::multipyMatrix(const CMatrix & b)
{
 //  CMatrix mMat;
   float km[4][4];
   int i, j;

  
   for (i=0; i<4; i++) {
      for (j=0; j<4; j++) {
         /*sum = 0;
			for (k=0; k<4; k++) {
            sum += m[i][k] * b.m[k][j];
			}
			km[i][j] = sum;*/
		  km[i][j] = m[i][0] * b.m[0][j]+m[i][1] * b.m[1][j]+m[i][2] * b.m[2][j]+m[i][3] * b.m[3][j];

		}
   } 

	//Kopieren
   memcpy(m, km, 64);
/*   for (i=0; i<4; i++) {
      for (j=0; j<4; j++) {
         m[i][j] =km[i][j];
		}
	}*/
}
bool CPlane::IntersectTriangle(S3DPoint* p1, S3DPoint* p2, S3DPoint* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec)
{
   CPlane p;
   p.GetNormal(p1, p2, p3);
   S3DPoint res;
   float dis;
   if (!IntersectLinePlaneV(p.d, &p.cvVector, &HitRec->Vector, &res, &dis)) return(false);
   if ((dis > 0) && (dis < HitRec->distance)) {
	   /*S3DPoint pl[3];
	   pl[0] = *p1;
	   pl[1] = *p2;
	   pl[2] = *p3;*/
	   S3DPoint pl[3];
	   pl[0].x = p1->x;
	   pl[0].y = p1->y;
	   pl[0].z = p1->z;

	   pl[1].x = p2->x;
	   pl[1].y = p2->y;
	   pl[1].z = p2->z;

	   pl[2].x = p3->x;
	   pl[2].y = p3->y;
	   pl[2].z = p3->z;
       bool r = false;
	   switch (p.cvVector.GetMajorAxis()) {
	   case 0: {
		   r = Has2DPointX(pl, 3, &res);
			   }; break;
		case 1: {
		   r = Has2DPointY(pl, 3, &res);
			   }; break;
		case 2: {
		   r = Has2DPointZ(pl, 3, &res);
			   }; break;
	   };	  
	   if (r) {
    	  HitRec->distance = dis;
	      HitRec->point.x = res.x;
		   HitRec->point.y = res.y;
		   HitRec->point.z = res.z;
		   HitRec->point.nx = p.cvVector.x;
		   HitRec->point.ny = p.cvVector.y;
		   HitRec->point.nz= p.cvVector.z;
		   HitRec->object = obj;
         HitRec->Parent = parent;
		   return(true);
	  }; 
	  return(false);
   };	
   return(false);
};
bool CPlane::IntersectTriangle(CVector* p1, CVector* p2, CVector* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec)
{
   CPlane p;
   p.GetNormal(p1, p2, p3);

   S3DPoint res;
   float dis;
   if (!IntersectLinePlaneV(p.d, &p.cvVector, &HitRec->Vector, &res, &dis)) return(false);
   if ((dis > 0) && (dis < HitRec->distance)) {
	   /*S3DPoint pl[3];
	   pl[0] = *p1;
	   pl[1] = *p2;
	   pl[2] = *p3;*/
	   S3DPoint pl[3];
	   pl[0].x = p1->x;
	   pl[0].y = p1->y;
	   pl[0].z = p1->z;

	   pl[1].x = p2->x;
	   pl[1].y = p2->y;
	   pl[1].z = p2->z;

	   pl[2].x = p3->x;
	   pl[2].y = p3->y;
	   pl[2].z = p3->z;
       bool r = false;
	   switch (p.cvVector.GetMajorAxis()) {
	   case 0: {
		   r = Has2DPointX(pl, 3, &res);
			   }; break;
		case 1: {
		   r = Has2DPointY(pl, 3, &res);
			   }; break;
		case 2: {
		   r = Has2DPointZ(pl, 3, &res);
			   }; break;
	   };	  
	   if (r) {
    	  HitRec->distance = dis;
	      HitRec->point.x = res.x;
		   HitRec->point.y = res.y;
		   HitRec->point.z = res.z;
		   HitRec->point.nx = p.cvVector.x;
		   HitRec->point.ny = p.cvVector.y;
		   HitRec->point.nz= p.cvVector.z;
		   HitRec->object = obj;
         HitRec->Parent = parent;
		   return(true);
	  }; 
	  return(false);
   };	
   return(false);
};
bool CPlane::IntersectTriangleWithV(S3DPoint* p1, S3DPoint* p2, S3DPoint* p3, CPlane *p, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec)
{
   S3DPoint res;
   float dis;
   if (!IntersectLinePlaneV(p->d, &p->cvVector, &HitRec->Vector, &res, &dis)) return(false);
   if ((dis > 0) && (dis < HitRec->distance)) {
	   /*S3DPoint pl[3];
	   pl[0] = *p1;
	   pl[1] = *p2;
	   pl[2] = *p3;*/
	   S3DPoint pl[3];
	   pl[0].x = p1->x;
	   pl[0].y = p1->y;
	   pl[0].z = p1->z;

	   pl[1].x = p2->x;
	   pl[1].y = p2->y;
	   pl[1].z = p2->z;

	   pl[2].x = p3->x;
	   pl[2].y = p3->y;
	   pl[2].z = p3->z;
       bool r = false;
	   switch (p->cvVector.GetMajorAxis()) {
	   case 0: {
		   r = Has2DPointX(pl, 3, &res);
			   }; break;
		case 1: {
		   r = Has2DPointY(pl, 3, &res);
			   }; break;
		case 2: {
		   r = Has2DPointZ(pl, 3, &res);
			   }; break;
	   };	  
	   if (r) {
    	  HitRec->distance = dis;
	      HitRec->point.x = res.x;
		   HitRec->point.y = res.y;
		   HitRec->point.z = res.z;
		   HitRec->point.nx = p->cvVector.x;
		   HitRec->point.ny = p->cvVector.y;
		   HitRec->point.nz= p->cvVector.z;
		   HitRec->object = obj;
         HitRec->Parent = parent;
		   return(true);
	  }; 
	  return(false);
   };	
   return(false);
};

bool CPlane::IntersectTriangleWithV(CVector* p1, CVector* p2, CVector* p3, CPlane *p, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec)
{
   S3DPoint res;
   float dis;
   //p->GetNormal(p1, p2, p3);
   

   if (!IntersectLinePlaneV(p->d, &p->cvVector, &HitRec->Vector, &res, &dis)) return(false);
   if ((dis > 0) && (dis < HitRec->distance)) {
	   /*S3DPoint pl[3];
	   pl[0] = *p1;
	   pl[1] = *p2;
	   pl[2] = *p3;*/
	   S3DPoint pl[3];
      pl[0].x = p1->x;
	   pl[0].y = p1->y;
	   pl[0].z = p1->z; 

	   pl[1].x = p2->x;
	   pl[1].y = p2->y;
	   pl[1].z = p2->z;

	   pl[2].x = p3->x;
	   pl[2].y = p3->y;
	   pl[2].z = p3->z;
      // bool r = Has2DPointX(pl, 3, &res) || Has2DPointY(pl, 3, &res) || Has2DPointZ(pl, 3, &res);
	   bool r = false;
      switch (p->cvVector.GetMajorAxis()) {
	   case 0: {
		   r = Has2DPointX(pl, 3, &res);
			   }; break;
		case 1: {
		   r = Has2DPointY(pl, 3, &res);
			   }; break;
		case 2: {
		   r = Has2DPointZ(pl, 3, &res);
			   }; break;
	   };	  
	   if (r) {
    	  HitRec->distance = dis;
	      HitRec->point.x = res.x;
		   HitRec->point.y = res.y;
		   HitRec->point.z = res.z;
		   HitRec->point.nx = p->cvVector.x;
		   HitRec->point.ny = p->cvVector.y;
		   HitRec->point.nz= p->cvVector.z;
		   HitRec->object = obj;
         HitRec->Parent = parent;
		   return(true);
	  }; 
	  return(false);
   };	
   return(false);
};

bool CPlane::IntersectTriangle(S3DUNLIT* p1, S3DUNLIT* p2, S3DUNLIT* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec)
{
   CPlane p;
   p.GetNormal(p1, p2, p3);
   S3DPoint res;
   float dis;
   if (!IntersectLinePlaneV(p.d, &p.cvVector, &HitRec->Vector, &res, &dis)) return(false);
   if ((dis > 0) && (dis < HitRec->distance)) {
	   S3DPoint pl[3];
	   pl[0].x = p1->x;
	   pl[0].y = p1->y;
	   pl[0].z = p1->z;

	   pl[1].x = p2->x;
	   pl[1].y = p2->y;
	   pl[1].z = p2->z;

	   pl[2].x = p3->x;
	   pl[2].y = p3->y;
	   pl[2].z = p3->z;


	   //pl[1] = *p2;
	  // pl[2] = *p3;
	  bool r = false;
	   switch (p.cvVector.GetMajorAxis()) {
	   case 0: {
		   r = Has2DPointX(pl, 3, &res);
			   }; break;
		case 1: {
		   r = Has2DPointY(pl, 3, &res);
			   }; break;
		case 2: {
		   r = Has2DPointZ(pl, 3, &res);
			   }; break;
	   };	  
	   if (r) {
    	   HitRec->distance = dis;
	      HitRec->point.x = res.x;
		   HitRec->point.y = res.y;
		   HitRec->point.z = res.z;
		   HitRec->point.nx = p.cvVector.x;
		   HitRec->point.ny = p.cvVector.y;
		   HitRec->point.nz= p.cvVector.z;
		   HitRec->object = obj;
         HitRec->Parent = parent;
		   return(true);
	  };
	  return(false);
   };	
   return(false);
};

/*CPlane::CPlane()
{
	d = 0;
}
	
CPlane::~CPlane()
{}*/

bool CPlane::IntersectLine(CVector* Start, CVector* Dir, float &dis)
{
   float N = cvVector.x*Dir->x+cvVector.y*Dir->y+cvVector.z*Dir->z;
   if (N==0) return false;
   dis = (d-cvVector.x*Start->x-cvVector.y*Start->y-cvVector.z*Start->z)/N;
   return true;
}


	





/*int CPlane::getPlanePos(C3DPoint & p)
{
   float distance = PlaneDistance(p);
   if (distance < -EPSILON) return (CP_BACK);
   if (distance > EPSILON) return (CP_FRONT);
   return (CP_ZERO);
}*/							

int CPlane::getPlanePos(S3DPoint & p)
{
   float distance = PlaneDistance(p);
   if (distance < -EPSILON) return (CP_BACK);
   if (distance > EPSILON) return (CP_FRONT);
   return (CP_ZERO);
}

int CPlane::getPlanePos(CVector &p)
{
   float distance = PlaneDistance(p);
   if (distance < -EPSILON) return (CP_BACK);
   if (distance > EPSILON) return (CP_FRONT);
   return (CP_ZERO);
}


int CPlane::getBoundingPos(S3DPoint *p, int count)
{
	if (count <= 0) return(0);
   bool res = PlaneDistance(p[0])> 0;
   for (int i = 1; i < count; i++) {
	   bool b1 = PlaneDistance(p[i]) > 0;
	   if (b1 != res) return(0);
   };
   if (res) return(1); else return(-1);
};


void clippoint3d(S3DPoint *in, S3DPoint *innext, S3DPoint *out,float scale)
{
    out->x = in->x + (innext->x - in->x) * scale;
    out->y = in->y + (innext->y - in->y) * scale;
	out->z = in->z + (innext->z - in->z) * scale;
	out->nx = in->nx + (innext->nx - in->nx) * scale;
	out->ny = in->ny + (innext->ny - in->ny) * scale;
    out->nz = in->nz + (innext->nz - in->nz) * scale;
    out->u = in->u + (innext->u - in->u) * scale;
	out->v = in->v + (innext->v - in->v) * scale;
	out->r = in->r + (innext->r - in->r) * scale;
}

void clippoint(CVector *in, CVector *innext, CVector *out,float scale)
{
    out->x = in->x + (innext->x - in->x) * scale;
    out->y = in->y + (innext->y - in->y) * scale;
	out->z = in->z + (innext->z - in->z) * scale;
}

/* int other_side(float a, float b)
{
	if ((a > 0 && b <= 0) || (a < 0 && b >= 0))
		return 1;
	else
		return 0;
}*/

#define other_side(a, b) ((a > 0 && b <= 0) || (a < 0 && b >= 0))

void CPlane::cliptoplane(S3DPoint *in, int countin, S3DPoint *out, int &countout)
{
	int i;
	float scale;
    float indot[60];
    countout = 0;

	for (i = 0; i < countin; i++) 
	{
		//indot[i] = cvVector.dotProduct(in[i]);
		indot[i] = cvVector.x*in[i].x+cvVector.y*in[i].y+cvVector.z*in[i].z;
	}
    

	for (i = 0; i < countin-1; i++) 
	{
		if (indot[i] >= d)
			out[countout++] = in[i];
		if (other_side(indot[i] - d, indot[i+1] - d))
		{
			scale = (indot[i]-d) / ((indot[i]-d)-(indot[i+1]-d));
			clippoint3d(&in[i], &in[i+1], &out[countout], scale);
			countout++;
		}
	}

	if (indot[countin-1] >= d)
		out[countout++] = in[countin-1];

	if (other_side(indot[0] - d, indot[countin-1] - d))
	{
		scale = (indot[0]-d) / ((indot[0]-d)-(indot[countin-1]-d));
		clippoint3d(&in[0], &in[countin-1], &out[countout], scale);
		countout++;
	}

}

void CPlane::cliptoplane(CVector *in, int countin, CVector *out, int &countout)
{
	int i;
	float scale;
    float indot[60];
	utiassert(countin < 60);
    countout = 0;

	//for (i = 0; i < countin; i++) 
	//{
	//	indot[i] = cvVector.dotProduct(in[i]);
	//}
    for (i = 0; i < countin; i++) 
	{
		//indot[i] = cvVector.dotProduct(in[i]);
		indot[i] = cvVector.x*in[i].x+cvVector.y*in[i].y+cvVector.z*in[i].z;
	}

	for (i = 0; i < countin-1; i++) 
	{
		if (indot[i] >= d)
			out[countout++] = in[i];
		if (other_side(indot[i] - d, indot[i+1] - d))
		{
			scale = (indot[i]-d) / ((indot[i]-d)-(indot[i+1]-d));
			clippoint(&in[i], &in[i+1], &out[countout], scale);
			countout++;
		}
	}

	if (indot[countin-1] >= d)
		out[countout++] = in[countin-1];

	if (other_side(indot[0] - d, indot[countin-1] - d))
	{
		scale = (indot[0]-d) / ((indot[0]-d)-(indot[countin-1]-d));
		clippoint(&in[0], &in[countin-1], &out[countout], scale);
		countout++;
	}

}


void CPlane::GetNormal(S3DPoint *p)
{
   float ax = p[0].x-p[1].x;
   float ay = p[0].y-p[1].y;
   float az = p[0].z-p[1].z;
   float bx = p[2].x-p[1].x;
   float by = p[2].y-p[1].y;
   float bz = p[2].z-p[1].z;
   cvVector.x = ay*bz-az*by;
   cvVector.y = az*bx-ax*bz;
   cvVector.z = ax*by-ay*bx;
   cvVector.Normalize();
   d = 0;
   d = PlaneDistance(p[0]);
}

void CPlane::GetNormal(S3DPoint *p1, S3DPoint *p2, S3DPoint *p3)
{
   float ax = p1->x-p2->x;
   float ay = p1->y-p2->y;
   float az = p1->z-p2->z;
   float bx = p3->x-p2->x;
   float by = p3->y-p2->y;
   float bz = p3->z-p2->z;
   cvVector.x = ay*bz-az*by;
   cvVector.y = az*bx-ax*bz;
   cvVector.z = ax*by-ay*bx;
   cvVector.Normalize();
   d = 0;
   d = PlaneDistance(*p1);
}
void CPlane::GetNormal(CVector *p1, CVector *p2, CVector *p3)
{
   float ax = p1->x-p2->x;
   float ay = p1->y-p2->y;
   float az = p1->z-p2->z;
   float bx = p3->x-p2->x;
   float by = p3->y-p2->y;
   float bz = p3->z-p2->z;
   cvVector.x = ay*bz-az*by;
   cvVector.y = az*bx-ax*bz;
   cvVector.z = ax*by-ay*bx;
   cvVector.Normalize();
   d = 0;
   d = PlaneDistance(*p1);
}

void CPlane::GetNormal(S3DUNLIT *p1, S3DUNLIT *p2, S3DUNLIT *p3)
{
   float ax = p1->x-p2->x;
   float ay = p1->y-p2->y;
   float az = p1->z-p2->z;
   float bx = p3->x-p2->x;
   float by = p3->y-p2->y;
   float bz = p3->z-p2->z;
   cvVector.x = ay*bz-az*by;
   cvVector.y = az*bx-ax*bz;
   cvVector.z = ax*by-ay*bx;
   cvVector.Normalize();
   d = p1->x*cvVector.x+p1->y*cvVector.y+p1->z*cvVector.z;
  // d = PlaneDistance(*p1);
}

const S3DPoint CPlane::GetNormal(S3DPoint p1, S3DPoint p2, S3DPoint p3, S3DPoint *res)
{
   S3DPoint result;
   if (res) {
	   result = *res;
   } else {
	   zeromem(&result,sizeof(S3DPoint));
   }
   float ax = p1.x-p2.x;
   float ay = p1.y-p2.y;
   float az = p1.z-p2.z;
   float bx = p3.x-p2.x;
   float by = p3.y-p2.y;
   float bz = p3.z-p2.z;
   CVector v;
   v.x = ay*bz-az*by;
   v.y = az*bx-ax*bz;
   v.z = ax*by-ay*bx;
   v.Normalize();
   result.nx = v.x;
   result.ny = v.y;
result.nz = v.z;
return result;
}


void CMatrix::inverse(CMatrix &in, CMatrix &out)
{
   /*float scale;
   scale = in.m[0][0] * in.m[0][0] +
            in.m[0][1] * in.m[0][1] +
            in.m[0][2] * in.m[0][2];
   scale = 1/scale;
   out.m[0][0] = scale * in.m[0][0];
   out.m[1][0] = scale * in.m[0][1];
   out.m[2][0] = scale * in.m[0][2];
   out.m[0][1] = scale * in.m[1][0];
   out.m[1][1] = scale * in.m[1][1];
   out.m[2][1] = scale * in.m[1][2];
   out.m[0][2] = scale * in.m[2][0];
   out.m[1][2] = scale * in.m[2][1];
   out.m[2][2] = scale * in.m[2][2];

   out.m[0][3]   = -(out.m[0][0] * in.m[0][3] +
                        out.m[0][1] * in.m[1][3] +
                        out.m[0][2] * in.m[2][3]);
   out.m[1][3]   = -(out.m[1][0] * in.m[0][3] +
                        out.m[1][1] * in.m[1][3] +
                        out.m[1][2] * in.m[2][3]);
   out.m[2][3]   = -(out.m[2][0] * in.m[0][3] +
                         out.m[2][1] * in.m[1][3] +
                         out.m[2][2] * in.m[2][3]);
   out.m[3][0] = 0;
   out.m[3][1] = 0;
   out.m[3][2] = 0;
   out.m[3][3] = 1;
   */
  
 
   float  d00, d01, d02, d03,
  d10, d11, d12, d13,
  d20, d21, d22, d23,
  d30, d31, d32, d33,
  m00, m01, m02, m03,
  m10, m11, m12, m13,
  m20, m21, m22, m23,
  m30, m31, m32, m33, D;
  
  m00 = in.m[0][0];  m01 = in.m[0][1];  m02 = in.m[0][2];  m03 = in.m[0][3];
  m10 = in.m[1][0];  m11 = in.m[1][1];  m12 = in.m[1][2];  m13 = in.m[1][3];
  m20 = in.m[2][0];  m21 = in.m[2][1];  m22 = in.m[2][2];  m23 = in.m[2][3];
  m30 = in.m[3][0];  m31 = in.m[3][1];  m32 = in.m[3][2];  m33 = in.m[3][3];

  d00 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m31*m22*m13 - m32*m23*m11 - m33*m21*m12;
  d01 = m10*m22*m33 + m12*m23*m30 + m13*m20*m32 - m30*m22*m13 - m32*m23*m10 - m33*m20*m12;
  d02 = m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m30*m21*m13 - m31*m23*m10 - m33*m20*m11;
  d03 = m10*m21*m32 + m11*m22*m30 + m12*m20*m31 - m30*m21*m12 - m31*m22*m10 - m32*m20*m11;

  d10 = m01*m22*m33 + m02*m23*m31 + m03*m21*m32 - m31*m22*m03 - m32*m23*m01 - m33*m21*m02;
  d11 = m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m30*m22*m03 - m32*m23*m00 - m33*m20*m02;
  d12 = m00*m21*m33 + m01*m23*m30 + m03*m20*m31 - m30*m21*m03 - m31*m23*m00 - m33*m20*m01;
  d13 = m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m30*m21*m02 - m31*m22*m00 - m32*m20*m01;

  d20 = m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m31*m12*m03 - m32*m13*m01 - m33*m11*m02;
  d21 = m00*m12*m33 + m02*m13*m30 + m03*m10*m32 - m30*m12*m03 - m32*m13*m00 - m33*m10*m02;
  d22 = m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m30*m11*m03 - m31*m13*m00 - m33*m10*m01;
  d23 = m00*m11*m32 + m01*m12*m30 + m02*m10*m31 - m30*m11*m02 - m31*m12*m00 - m32*m10*m01;

  d30 = m01*m12*m23 + m02*m13*m21 + m03*m11*m22 - m21*m12*m03 - m22*m13*m01 - m23*m11*m02;
  d31 = m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m20*m12*m03 - m22*m13*m00 - m23*m10*m02;
  d32 = m00*m11*m23 + m01*m13*m20 + m03*m10*m21 - m20*m11*m03 - m21*m13*m00 - m23*m10*m01;
  d33 = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m20*m11*m02 - m21*m12*m00 - m22*m10*m01;

  D = m00*d00 - m01*d01 + m02*d02 - m03*d03;



  out.m[0][0] =  d00/D; out.m[0][1] = -d10/D;  out.m[0][2] =  d20/D; out.m[0][3] = -d30/D;
  out.m[1][0] = -d01/D; out.m[1][1] =  d11/D;  out.m[1][2] = -d21/D; out.m[1][3] =  d31/D;
  out.m[2][0] =  d02/D; out.m[2][1] = -d12/D;  out.m[2][2] =  d22/D; out.m[2][3] = -d32/D;
  out.m[3][0] = -d03/D; out.m[3][1] =  d13/D;  out.m[3][2] = -d23/D; out.m[3][3] =  d33/D;
}

void Get3DRectClipPlanes(CPlane *planes, S3DRect* rect)
{
   
   planes[0].cvVector.setVector(0, 1, 0);
   planes[0].d = 0;
   planes[0].d = planes[0].PlaneDistance(rect->p1);
   planes[1].cvVector.setVector(1, 0, 0);
   planes[1].d = 0;
   planes[1].d = planes[1].PlaneDistance(rect->p1);
   planes[2].cvVector.setVector(0, 0, 1);
   planes[2].d = 0;
   planes[2].d = planes[2].PlaneDistance(rect->p1);
   planes[3].cvVector.setVector(0, -1, 0);
   planes[3].d = 0;
   planes[3].d = planes[3].PlaneDistance(rect->p2);
   planes[4].cvVector.setVector(-1, 0, 0);
   planes[4].d = 0;
   planes[4].d = planes[4].PlaneDistance(rect->p2);
   planes[5].cvVector.setVector(0, 0, -1);
   planes[5].d = 0;
   planes[5].d = planes[5].PlaneDistance(rect->p2);

}

void GetRectCenter(S3DRect* rect, S3DPoint *p)
{
   p->x = rect->p1.x + (rect->p2.x - rect->p1.x) / 2;
   p->y = rect->p1.y + (rect->p2.y - rect->p1.y) / 2;
   p->z = rect->p1.z + (rect->p2.z - rect->p1.z) / 2;
}

bool PointInRect(S3DRect* rect, S3DPoint *p)
{
   if ((rect->p1.x <= p->x) && (rect->p2.x >= p->x) &&
	   (rect->p1.y <= p->y) && (rect->p2.y >= p->y) &&
	   (rect->p1.z <= p->z) && (rect->p2.z >= p->z)) {

	   return(true);
   };
   return(false);
}

bool PointInRect(S3DRect* rect, CVector *p)
{
   if ((rect->p1.x <= p->x) && (rect->p2.x >= p->x) &&
	   (rect->p1.y <= p->y) && (rect->p2.y >= p->y) &&
	   (rect->p1.z <= p->z) && (rect->p2.z >= p->z)) {

	   return(true);
   };
   return(false);
}

#define MAXFLOAT 1E+10

bool IntersectRay(S3DPoint* vector, S3DRect* b, float &dis)
{
	dis = 0;
	bool in = false;
	if (PointInRect(b, vector)) {
		in = true;
		//return(true);
	};
	dis = MAXFLOAT;
	float t1, t2;
	float minx, maxx, miny, maxy, minz, maxz;
	if (fabs(vector->nx) < 0.0001) {
		if (b->p1.x < vector->x && b->p2.x > vector->x) {
			minx = -MAXFLOAT;
			maxx = MAXFLOAT;
		} else {
			return(false);
		};
	} else {
		t1 = (b->p1.x - vector->x) / vector->nx;
		t2 = (b->p2.x - vector->x) / vector->nx;
		if (t1 < t2)
		{
			minx = t1;
			maxx = t2;
		} else {
			minx = t2;
			maxx = t1;
		};
		//if (maxx < 0) ;
			//return(0);
	}
	 
	if (fabs(vector->ny) < 0.0001) {
		if (b->p1.y < vector->y && b->p2.y > vector->y) {
			miny = -MAXFLOAT;
			maxy = MAXFLOAT;
		} else {
			return(false);
			miny = -MAXFLOAT;
			maxy = MAXFLOAT;
		};
	} else {
		t1 = (b->p1.y - vector->y) / vector->ny;
		t2 = (b->p2.y - vector->y) / vector->ny;
		if (t1 < t2)
		{
			miny = t1;
			maxy = t2;
		} else {
			miny = t2;
			maxy = t1;
		};
		//if (maxy < 0)	   ;
			//return(false);
	}
	if (fabs(vector->nz) < 0.0001) {
		if (b->p1.z < vector->z && b->p2.z > vector->z) {
			minz = -MAXFLOAT;
			maxz = MAXFLOAT;
		} else {
			return(false);
			minz = -MAXFLOAT;
			maxz = MAXFLOAT;
		};
	} else {
		t1 = (b->p1.z - vector->z) / vector->nz;
		t2 = (b->p2.z - vector->z) / vector->nz;
		if (t1 < t2)
		{
			minz = t1;
			maxz = t2;
		} else {
			minz = t2;
			maxz = t1;
		};
		//if (maxz < 0)  ;
			//return(false);
	}

	float t_min = max(minx, max(miny, minz));
	float t_max = min(maxx, min(maxy, maxz));
	if (t_min <= t_max) {
		if (in) {
			dis = t_max;
		} else {
		    dis = t_min;
		}
	   return(true);
	};
	return(false);
};

bool IntersectRayB(S3DPoint* vector, S3DRect* b, float &dis, bool &in)
{
	dis = 0;
    in = false;
	if (PointInRect(b, vector)) {
		in = true;
		//return(true);
	};
	dis = MAXFLOAT;
	float t1, t2;
	float minx, maxx, miny, maxy, minz, maxz;
	if (fabs(vector->nx) < 0.0001) {
		if (b->p1.x < vector->x && b->p2.x > vector->x) {
			minx = -MAXFLOAT;
			maxx = MAXFLOAT;
		} else {
			return(0);
		};
	} else {
		t1 = (b->p1.x - vector->x) / vector->nx;
		t2 = (b->p2.x - vector->x) / vector->nx;
		if (t1 < t2)
		{
			minx = t1;
			maxx = t2;
		} else {
			minx = t2;
			maxx = t1;
		};
		//if (maxx < 0) ;
			//return(0);
	}
	 
	if (fabs(vector->ny) < 0.0001) {
		if (b->p1.y < vector->y && b->p2.y > vector->y) {
			miny = -MAXFLOAT;
			maxy = MAXFLOAT;
		} else {
			//return(false);
		};
	} else {
		t1 = (b->p1.y - vector->y) / vector->ny;
		t2 = (b->p2.y - vector->y) / vector->ny;
		if (t1 < t2)
		{
			miny = t1;
			maxy = t2;
		} else {
			miny = t2;
			maxy = t1;
		};
		//if (maxy < 0)	   ;
			//return(false);
	}
	if (fabs(vector->nz) < 0.0001) {
		if (b->p1.z < vector->z && b->p2.z > vector->z) {
			minz = -MAXFLOAT;
			maxz = MAXFLOAT;
		} else {
			//return(false);
		};
	} else {
		t1 = (b->p1.z - vector->z) / vector->nz;
		t2 = (b->p2.z - vector->z) / vector->nz;
		if (t1 < t2)
		{
			minz = t1;
			maxz = t2;
		} else {
			minz = t2;
			maxz = t1;
		};
		//if (maxz < 0)  ;
			//return(false);
	}

	float t_min = max(minx, max(miny, minz));
	float t_max = min(maxx, min(maxy, maxz));
	if (t_min <= t_max) {
		if (in) {
			dis = t_max;
		} else {
		    dis = t_min;
		}
	   return(true);
	};
	return(false);
};

bool IntersectNormRay(S3DPoint* vector, S3DRect* b, float &dis, CVector* normal)
{
	dis = 0;
	float x, y, z;
	bool in = false;
	if (PointInRect(b, vector)) {
		in = true;
		//return(true);
	};
	dis = MAXFLOAT;
	float t1, t2;
	float minx, maxx, miny, maxy, minz, maxz;
	if (fabs(vector->nx) < 0.0001) {
		if (b->p1.x < vector->x && b->p2.x > vector->x) {
			minx = -MAXFLOAT;
			maxx = MAXFLOAT;
		} else {
			return(0);
		};
	} else {
		t1 = (b->p1.x - vector->x) / vector->nx;
		t2 = (b->p2.x - vector->x) / vector->nx;
		if (t1 < t2)
		{
			minx = t1;
			maxx = t2;
			x = -1;
		} else {
			minx = t2;
			maxx = t1;
			x = 1;
		};
		//if (maxx < 0) ;
			//return(0);
	}
	 
	if (fabs(vector->ny) < 0.0001) {
		if (b->p1.y < vector->y && b->p2.y > vector->y) {
			miny = -MAXFLOAT;
			maxy = MAXFLOAT;
		} else {
			//return(false);
		};
	} else {
		t1 = (b->p1.y - vector->y) / vector->ny;
		t2 = (b->p2.y - vector->y) / vector->ny;
		if (t1 < t2)
		{
			miny = t1;
			maxy = t2;
			y = -1;
		} else {
			miny = t2;
			maxy = t1;
			y = 1;
		};
		//if (maxy < 0)	   ;
			//return(false);
	}
	if (fabs(vector->nz) < 0.0001) {
		if (b->p1.z < vector->z && b->p2.z > vector->z) {
			minz = -MAXFLOAT;
			maxz = MAXFLOAT;
		} else {
			//return(false);
		};
	} else {
		t1 = (b->p1.z - vector->z) / vector->nz;
		t2 = (b->p2.z - vector->z) / vector->nz;
		if (t1 < t2)
		{
			minz = t1;
			maxz = t2;
			z = -1;
		} else {
			minz = t2;
			maxz = t1;
			z = 1;
		};
	//	if (maxz < 0)  ;
			//return(false);
	}

	float t_min = max(minx, max(miny, minz));
	float t_max = min(maxx, min(maxy, maxz));
	if (t_min <= t_max) {
		if (in) {
			dis = t_max;
			if (t_max == maxx) {
				normal->setVector(x, 0, 0);
				return(true);
			}
			if (t_max == maxy) {
				normal->setVector(0, y, 0);
				return(true);
			}
			if (t_max == maxz) {
				normal->setVector(0, 0, z);
				return(true);
			}
		} else {
		    dis = t_min;
			if (t_min == minx) {
				normal->setVector(-x, 0, 0);
				return(true);
			}
			if (t_min == miny) {
				normal->setVector(0, -y, 0);
				return(true);
			}
			if (t_min == minz) {
				normal->setVector(0, 0, -z);
				return(true);
			}

		}
	   return(true);
	};
	return(false);
};


void MoveRect(S3DRect* rect, S3DPoint* t)
{
   Point_Add(&rect->p1.x, &rect->p1.x, &t->x, 3);
   Point_Add(&rect->p2.x, &rect->p2.x, &t->x, 3);
};

int GetRectPoints(S3DRect* rectm, S3DPoint* points, int count, CVector* dir)
{
	if (!dir) {
	points[0].x = rectm->p1.x;
	points[0].y = rectm->p1.y;
   points[0].z = rectm->p1.z;

	points[1].x = rectm->p2.x;
	points[1].y = rectm->p1.y;
	points[1].z = rectm->p1.z;
	
	points[2].x = rectm->p2.x;
	points[2].y = rectm->p2.y;
	points[2].z = rectm->p1.z;
	
	points[3].x = rectm->p1.x;
	points[3].y = rectm->p2.y;
	points[3].z = rectm->p1.z;

	//points[4] = rectm->p2;
   points[4].x = rectm->p2.x;
   points[4].y = rectm->p2.y;
   points[4].z = rectm->p2.z;


	points[5].x = rectm->p2.x;
	points[5].y = rectm->p1.y;
	points[5].z = rectm->p2.z;
	
	points[6].x = rectm->p1.x;
	points[6].y = rectm->p1.y;
	points[6].z = rectm->p2.z;
	
	points[7].x = rectm->p1.x;
	points[7].y = rectm->p2.y;
	points[7].z = rectm->p2.z; 
	return count;
	};
return 0;
};

int ClassifyPoints(S3DPoint* points, int count, CPlane*plane)
{
	if (count == 0) return CP_BACK;
   int side = plane->getPlanePos(points[0]);
   if (side == CP_ZERO) return CP_ZERO;
   int s2;
   for (int i = 1; i < count; i++) {
	   s2 = plane->getPlanePos(points[i]);
	   if (side != s2) {
		   return CP_ZERO;
	   }
   };
   return side;
};



void InitBounds(S3DRect &Bounds)
{
     Bounds.p1.x = 10000000000.0f;
		Bounds.p1.y = 10000000000.0f;
		Bounds.p1.z = 10000000000.0f;
		Bounds.p2.x = -10000000000.0f;
		Bounds.p2.y = -10000000000.0f;
		Bounds.p2.z = -10000000000.0f;
};

bool IntersectRect3D(S3DRect* rect1,  S3DRect* rect2)
{
	
   if (((rect1->p2.x < rect2->p1.x) || (rect2->p2.x < rect1->p1.x)) ||
	   ((rect1->p2.y < rect2->p1.y) || (rect2->p2.y < rect1->p1.y)) ||
	   ((rect1->p2.z < rect2->p1.z) || (rect2->p2.z < rect1->p1.z))) {
	  return(false);
   };
   return(true);

}

bool PtInRect3D(S3DPoint *p,  S3DRect* rect2)
{
	
   if (rect2->p1.x <= p->x && rect2->p1.y <= p->y && rect2->p1.z <= p->z ||
	   rect2->p2.x >= p->x && rect2->p2.y >= p->y && rect2->p2.z >= p->z)
   return(true);
   return(false);

}

float Length(float*v)
{
   return(sqrt(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]));
}

float Normalize(float*v)
{
    float r = Length(v);
	v[0] /= r;
	v[1] /= r;
	v[2] /= r;
	return r;
}

void Set3DPoint(float x, float y, float z, S3DPoint*p)
{
    p->x = x;
	p->y = y;
	p->z = z;
}

void Set3DPoint(S3DPoint* p, float x, float y, float z, float nx, float ny, float nz, float tx, float ty, float tz, UINT color)
{
   p->x = x;
   p->y = y;
   p->z = z;
   p->nx = nx;
   p->ny = ny;
   p->nz = nz;
   p->u = tx;
   p->v = ty;
   p->r = tz;
   p->color = color;
   p->flags = 0;
}

/*S3DPoint Set3DPoint(float x, float y, float z, S3DPoint* p1)
{
	S3DPoint p;
	if (p1) {
		p = *p1;

	} else {
		zeromem(p, sizeof p);
	}
   p.x = x;
   p.y = y;
   p.z = z;
   return p;
   
}*/

bool IntersectLineSphere(S3DPoint* line, float radius, CVector* sphere, CVector* res)
{
	/*CVector pov;
	CVector pop;
	pov = *sphere-*line;
	pop = *line;

	CVector lvector(line->nx, line->ny, line->nz);
	float v = pov * lvector;
	float povdot = pov* pov;

	float disc = radius*radius-(povdot-v*v);
	if (disc < 0) return(false);
	float d= sqrt(disc);
	res=pop+(v-d)*lvector;*/
	return(true);
};

bool IntersectLinePlane(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = line->nx*v->x+
	              line->ny*v->y+
				  line->nz*v->z;
   if (bottom == 0) return(false);
   float top = (polypoint->x-line->x)*v->x+
	           (polypoint->y-line->y)*v->y+
			   (polypoint->z-line->z)*v->z;
   float mul = top/bottom;

   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneV(float d, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = line->nx*v->x+
	              line->ny*v->y+
				  line->nz*v->z;
   if (bottom == 0) return(false);
   float top = d-v->x*line->x-v->y*line->y-v->z*line->z;//(polypoint->x-line->x)*v->x+
	           //(polypoint->y-line->y)*v->y+
			   //(polypoint->z-line->z)*v->z;

   //top := V[3]-V[0]*Line.X-V[1]*Line.Y-V[2]*Line.Z;
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneZ(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = line->nz;
   if (bottom == 0) return(false);
   float top = polypoint->z-line->z;
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneX(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = line->nx;
   if (bottom == 0) return(false);
   float top = (polypoint->x-line->x);
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneY(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = line->ny;
   if (bottom == 0) return(false);
   float top = (polypoint->y-line->y);
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneNZ(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = -line->nz;
   if (bottom == 0) return(false);
   float top = -(polypoint->z-line->z);
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneNX(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = -line->nx;
   if (bottom == 0) return(false);
   float top = -(polypoint->x-line->x);
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

bool IntersectLinePlaneNY(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis)
{ 
   float bottom = -line->ny;
   if ((bottom > -0.01) && (bottom < 0.01)) return(false);
   float top = -(polypoint->y-line->y);
   float mul = top/bottom;
   
   result->x = line->x + mul * line->nx;
   result->y = line->y + mul * line->ny;
   result->z = line->z + mul * line->nz;
   *dis = mul;
   return(true);
}

float SearchRoundedAreaWidthZ(S3DPoint *points, int npol)
{
    float xmin = (float)1E+20;
	float ymin = (float)1E+20;
    float xmax = (float)-1E+20;
	float ymax = (float)-1E+20;

	for (int i = 0; i < npol; i++) {
		if (points[i].x > xmax) xmax = points[i].x;
		if (points[i].y > ymax) ymax = points[i].y;
		if (points[i].x < xmin) xmin = points[i].x;
		if (points[i].y < ymin) ymin = points[i].y;
	};
	float w = xmin-xmax;
	float h = ymin-ymax;
	return(w*h);
};

float SearchRoundedAreaWidthY(S3DPoint *points, int npol)
{
    float xmin = (float)1E+20;
	float zmin = (float)1E+20;
    float xmax = (float)-1E+20;
	float zmax = (float)-1E+20;

	for (int i = 0; i < npol; i++) {
		if (points[i].x > xmax) xmax = points[i].x;
		if (points[i].z > zmax) zmax = points[i].z;
		if (points[i].x < xmin) xmin = points[i].x;
		if (points[i].z < zmin) zmin = points[i].z;
	};
	float w = xmin-xmax;
	float h = zmin-zmax;
	return(w*h);
};

float SearchRoundedAreaWidthX(S3DPoint *points, int npol)
{
    float ymin = (float)1E+20;
	float zmin = (float)1E+20;
    float ymax = (float)-1E+20;
	float zmax = (float)-1E+20;

	for (int i = 0; i < npol; i++) {
		if (points[i].y > ymax) ymax = points[i].y;
		if (points[i].z > zmax) zmax = points[i].z;
		if (points[i].y < ymin) ymin = points[i].y;
		if (points[i].z < zmin) zmin = points[i].z;
	};
	float w = ymin-ymax;
	float h = zmin-zmax;
	return(w*h);
};

bool Has2DPointZ(S3DPoint *points, int npol, S3DPoint *point)
{
    bool r = false;
	int j = npol-1;
	int i;
	for (i = 0; i < npol; i++) {
		if ((((points[i].y <= point->y) && (point->y < points[j].y)) || 
			((points[j].y <= point->y) && (point->y < points[i].y))) &&
			(point->x < (points[j].x - points[i].x) * (point->y - points[i].y) /
			(points[j].y - points[i].y) + points[i].x)) {
			r = !r;
		};
		j = i;
	}
	return(r);
}

bool Has2DPointY(S3DPoint *points, int npol, S3DPoint *point)
{
    bool r = false;
	int j = npol-1;
	int i;
	for (i = 0; i < npol; i++) {
		if ((((points[i].z <= point->z) && (point->z < points[j].z)) || 
			((points[j].z <= point->z) && (point->z < points[i].z))) &&
			(point->x < (points[j].x - points[i].x) * (point->z - points[i].z) /
			(points[j].z - points[i].z) + points[i].x)) {
			r = !r;
		};
		j = i;
	}
	return(r);
}

bool Has2DPointX(S3DPoint *points, int npol, S3DPoint *point)
{
    bool r = false;
	int j = npol-1;
	int i;
	for (i = 0; i < npol; i++) {
		if ((((points[i].z <= point->z) && (point->z < points[j].z)) || 
			((points[j].z <= point->z) && (point->z < points[i].z))) &&
			(point->y < (points[j].y - points[i].y) * (point->z - points[i].z) /
			(points[j].z - points[i].z) + points[i].y)) {
			r = !r;
		};
		j = i;
	}
	return(r);
}

void Add(S3DPoint* result, S3DPoint* sum1, S3DPoint* sum2)
{
   result->x = sum1->x + sum2->x;
   result->y = sum1->y + sum2->y;
   result->z = sum1->z + sum2->z;
}

void Add(S3DPoint* result, S3DPoint* sum1, CVector* sum2)
{
   result->x = sum1->x + sum2->x;
   result->y = sum1->y + sum2->y;
   result->z = sum1->z + sum2->z;
}

void Add(S3DPoint* result, CVector* sum1, S3DPoint* sum2)
{
   result->x = sum1->x + sum2->x;
   result->y = sum1->y + sum2->y;
   result->z = sum1->z + sum2->z;
}

void Add(S3DPoint* result, CVector* sum1, CVector* sum2)
{
   result->x = sum1->x + sum2->x;
   result->y = sum1->y + sum2->y;
   result->z = sum1->z + sum2->z;
}

void AddV(S3DPoint* result, S3DPoint* sum1, S3DPoint* sum2)
{
   result->nx = sum1->x + sum2->x;
   result->ny = sum1->y + sum2->y;
   result->nz = sum1->z + sum2->z;
}

void AddV(S3DPoint* result, S3DPoint* sum1, CVector* sum2)
{
   result->nx = sum1->x + sum2->x;
   result->ny = sum1->y + sum2->y;
   result->nz = sum1->z + sum2->z;
}

void AddV(S3DPoint* result, CVector* sum1, S3DPoint* sum2)
{
   result->nx = sum1->x + sum2->x;
   result->ny = sum1->y + sum2->y;
   result->nz = sum1->z + sum2->z;
}

void AddV(S3DPoint* result, CVector* sum1, CVector* sum2)
{
   result->nx = sum1->x + sum2->x;
   result->ny = sum1->y + sum2->y;
   result->nz = sum1->z + sum2->z;
}

int CPlane::ClassifyPolygon(S3DPoint* list, int count)
{
   
   int side = getPlanePos(list[0]);
   for (int i = 1; i < count; i++) {
	   if (side != getPlanePos(list[i])) {
          return(BSP_CUT);
	   };
   };
   return(side);
}

int CPlane::ClassifyPolygon(UINT* list, CVertex* v, int count)
{
   int side = getPlanePos(v[list[0]].pos);
   for (int i = 1; i < count; i++) {
	   if (side != getPlanePos(v[list[i]].pos)) {
          return(BSP_CUT);
	   };
   };
   return(side);

}

void operator += (S3DPoint &a, const S3DPoint &b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}

void operator += (S3DPoint &a, const CVector &b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
}

void operator *= ( S3DPoint &a, const float b )
{
	a.x *= b;
	a.y *= b;
	a.z *= b;
}

S3DPoint operator * (const S3DPoint &a, const float b)
{
	S3DPoint result;

	result.x = a.x * b;
	result.y = a.y * b;
	result.z = a.z * b;
	return result;
}

S3DPoint operator - ( const S3DPoint &a, const S3DPoint &b )
{
	S3DPoint result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}

S3DPoint operator - ( const S3DPoint &a, const CVector &b )
{
	S3DPoint result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;

	return result;
}

S3DPoint	operator + ( const S3DPoint &a, const S3DPoint &b )
{
	S3DPoint result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}

S3DPoint	operator + ( const S3DPoint &a, const CVector &b )
{
	S3DPoint result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;

	return result;
}


S3DPoint operator ^ ( const S3DPoint &a, const S3DPoint &b )
{
	S3DPoint result;

	result.x = a.y * b.z - b.y * a.z;
	result.y = a.z * b.x - b.z * a.x;
	result.z = a.x * b.y - b.x * a.y;

	return result;
}

S3DPoint operator ^ ( const S3DPoint &a, const CVector &b )
{
	S3DPoint result;

	result.x = a.y * b.z - b.y * a.z;
	result.y = a.z * b.x - b.z * a.x;
	result.z = a.x * b.y - b.x * a.y;

	return result;
}


float	operator * ( const S3DPoint &a, const S3DPoint &b )
{
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}

float	operator * ( const S3DPoint &a, const CVector &b )
{
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}



void GetRandomPointInRect(S3DPoint* p, S3DRect* r)
{
   p->x = r->p1.x + (r->p2.x-r->p1.x) * urandom();
   p->y = r->p1.y + (r->p2.y-r->p1.y) * urandom();
   p->z = r->p1.z + (r->p2.z-r->p1.z) * urandom();
}

float Interpolatef(float a, float b, float value)
{
   return(a+(b-a)*value);
}

float InterpolateCosinef(float a, float b, float x)
{
   float value = (1.0f - (float)cos(x*PI))*0.5f;
   return(a*(1-value)+b*value);
};
float Interpolate(float a, float b, float x)
{
   return a + (b-a)*x;
};

float InterpolateRectangle(float aa, float ba, float ab, float bb, float x, float y)
{
   float a = Interpolate(aa, ba, x);
   float b = Interpolate(ab, bb, x);
   return Interpolate(a, b, y);
};

