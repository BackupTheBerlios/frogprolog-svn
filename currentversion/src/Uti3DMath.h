//Uti3DMath 
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
#ifndef __UTI3DMATH__
#define __UTI3DMATH__

#include "Uti3DCore.h"

const int MAX_POINTS =20;
const float EPSILON =0.05f;

const int CP_FRONT =1;
const int CP_BACK =-1;
const int CP_ZERO =0;

//Datentypen  

const int TBGL[16] = {0, 4, 8, 12,
                                1, 5, 9, 13,
                                2, 6, 10, 14,
                                3, 7, 11, 15};

void Perform_OpenGL_matrix_inverse(float* _in,float* _out);

class C3DPoint;
struct CVector;
struct CPlane;

const double pi180 =0.0174532925199432957692369076848861; //pi/180

typedef struct S3DPoint
{
	U_SINGLE x, y, z;
	U_SINGLE nx, ny, nz;
	U_SINGLE u, v, r;
	int flags;
	U_UINT32 color;   
} T3DPoint;

struct S3DVERT
{
    U_SINGLE x, y, z;
	U_SINGLE u, v;
	U_SINGLE u2, v2;
	U_SINGLE s;
};

struct S3DUNLIT
{
    U_SINGLE x, y, z;
	U_SINGLE u, v, r;
	UINT color;
};

typedef struct S2DPoint
{
    U_SINGLE x, y;
} *P2DPoint;


struct S3DRect;

struct S2DRect
{
	S2DPoint p1;
	S2DPoint p2;
};

typedef struct SHitResult_typ
{
	S3DPoint Vector;
	CUtiOB** Ignore;
    int IgnoreCount;
	CUtiOB* object;
   CUtiOB* Parent;
    S3DPoint point;
	float distance;
	bool nobsp;
	bool NoJoints;
	bool SimpleTest;
} SHitResult, *PHitResult;

void GetRandomPointInRect(S3DPoint* p, S3DRect* r);

void Get3DRectClipPlanes(CPlane *planes, S3DRect* rect); 
void GetRectCenter(S3DRect* rect, S3DPoint *p);
void MoveRect(S3DRect* rect, S3DPoint* t);
int GetRectPoints(S3DRect* rectm, S3DPoint* points, int count, CVector* dir);
bool PointInRect(S3DRect* rect, S3DPoint *p);
bool PointInRect(S3DRect* rect, CVector *p);
bool PtInRect3D(S3DPoint *p,  S3DRect* rect2);
bool IntersectRect3D(S3DRect* rect1,  S3DRect* rect2);
bool IntersectRay(S3DPoint* vector, S3DRect* b, float &dis);
bool IntersectRayB(S3DPoint* vector, S3DRect* b, float &dis, bool &in);
bool IntersectNormRay(S3DPoint* vector, S3DRect* b, float &dis, CVector* normal);
void InitBounds(S3DRect &Bounds);

int maxf(float x, float y, float z);



void Add(S3DPoint* result, S3DPoint* sum1, S3DPoint* sum2);
void Add(S3DPoint* result, S3DPoint* sum1, CVector* sum2);
void Add(S3DPoint* result, CVector* sum1, S3DPoint* sum2);
void Add(S3DPoint* result, CVector* sum1, CVector* sum2);
void AddV(S3DPoint* result, S3DPoint* sum1, S3DPoint* sum2);
void AddV(S3DPoint* result, S3DPoint* sum1, CVector* sum2);
void AddV(S3DPoint* result, CVector* sum1, S3DPoint* sum2);
void AddV(S3DPoint* result, CVector* sum1, CVector* sum2);

void Set3DPoint(S3DPoint* p, float x, float y, float z, float nx=0, float ny=0, float nz=0, float tx=0, float ty=0, float tz = 0, UINT color = 0);
//S3DPoint Set3DPoint(float x, float y, float z, S3DPoint* p1);

void Set3DPoint(float x, float y, float z, S3DPoint*p);
void Point_Add(float *sum, float* s1, float* s2, int count);
void Point_Sub(float *diff, float *sub, float *min, int count);
void Point_Mul(float *p, float *f1, float *f2, int count);
void Point_Div(float *quot, float *div, float *divisor, int count);
void Point_Add_Value(float *sum, float*sum1, float value, int count);
void Point_Sub_Value(float *diff, float*sub1, float min, int count);
void Value_Sub_Point(float *diff, float sub1, float* min, int count);
void Point_Mul_Value(float *pro, float*f1, float value, int count);
void Point_Div_Value(float *quot, float*div, float divisor, int count);
void Value_Div_Point(float *quot, float div, float*divisor, int count);
bool IntersectLinePlaneV(float d, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);

float absf(float x);

/*typedef struct SVector 
{
   float x, y, z;
} TVector, *PVector;
*/
typedef struct CVector
{
public:
	float x;
    float y;
	float z;
	/*CVector()
    {
      x = y = z = 0;
    }*/
	void fromTo(const S3DPoint & start, const S3DPoint & ende)
	{
        x = ende.x-start.x;
		y = ende.y-start.y;
		z = ende.z-start.z;
	};
	void fromTo(const CVector & start, const CVector & ende)
	{
        x = ende.x-start.x;
		y = ende.y-start.y;
		z = ende.z-start.z;
	};
	/*CVector(float _x, float _y, float _z);
	CVector(const S3DPoint & start, const S3DPoint & ende);
	CVector(const CVector &start, const CVector & ende);
	CVector(TVector &v);*/
	//~CVector();
	void setVector(float _x, float _y, float _z);
	float length();
	void scalVector(float value);
	float Normalize();
	float DistanceTo(CVector*v );
	void addVector(float _x, float _y, float _z);
	void subVector(float _x, float _y, float _z);
	void Neg();
	void print();
	const CVector getVector(){ return *this;};
	CVector operator+(const CVector & b);
	CVector operator+(const S3DPoint & b);
    CVector operator-(const CVector & b);
	CVector operator-(const S3DPoint & b);
	CVector operator-();
	CVector &operator+=(const CVector &s);
	CVector &operator+=(const S3DPoint &s);
	CVector &operator-=(const CVector &s);
	CVector &operator-=(const S3DPoint &s);	
	//S3DPoint& operator= (const CVector &a);
	CVector& operator= (const S3DPoint &a);
	
	
	float operator*(const CVector & b);
	float operator*(const S3DPoint &b);
	CVector operator^(const CVector &b);
	//float dotProduct(const CVector & b);
	//float dotProduct(const C3DPoint & b);
	//float dotProduct(const S3DPoint & b);
	inline float dotProduct(const CVector & b)
    {
	    return x*b.x + y*b.y + z*b.z;
	}
   /* inline float dotProduct(const C3DPoint & b)
    {
	   return x*b.x + y*b.y + z*b.z;
    }*/

    inline float dotProduct(const S3DPoint & b)
    {
	    return x*b.x + y*b.y + z*b.z;
    }
	CVector operator*(float n);
	friend CVector operator*(float n, CVector & b)
	{
   	    return b *n;
	}
	void ReflectVector(CVector* Norm);
	void ToPoint(S3DPoint *p) const {p->x = x; p->y = y; p->z = z;};
	int GetMajorAxis();
	CVector GetMajorNormal();
	void CalcRightUpVector(CVector* right, CVector* up);
	void CrossProduct(CVector* p1, CVector *res);
	void Read(CStream & Stream);
   void Write(CStream & Stream);
} SVector, TVector, *PVector;



const CVector setVector(float x, float y, float z);

struct S3DRect
{
	CVector p1;
	CVector p2;
};

struct TBounds
{
    TVector p1;
	TVector p2;
};


class C3DPoint
{
public:
	float x;
	float y;
	float z;
	C3DPoint();
	C3DPoint(float _x, float _y, float _z);
	virtual ~C3DPoint();
	void print();
};



class CMatrix
{
public:
	static void inverse(CMatrix &in, CMatrix &out);
	
   float m[4][4];
   CMatrix()
   {
      m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	   m[1][0] = m[2][0] = m[3][0] = 0;
	   m[0][1] = m[2][1] = m[3][1] = 0;
	   m[0][2] = m[1][2] = m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
   }
	//~CMatrix();
	//void LoadIdentity();
	inline void LoadIdentity()
   {
	   m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1;
	   m[1][0] = m[2][0] = m[3][0] = 0;
	   m[0][1] = m[2][1] = m[3][1] = 0;
	   m[0][2] = m[1][2] = m[3][2] = 0;
	   m[0][3] = m[1][3] = m[2][3] = 0;
    }
	void SetXRotation(float value);
	void SetYRotation(float value);
	void SetZRotation(float value);
	void SetTranslate(float _x, float _y, float _z);
	void SetScaling(float _x, float _y, float _z);
	void Rotate(float _x, float _y, float _z);
	void RotateInv(float _x, float _y, float _z);
	void Translation(float _x, float _y, float _z);
	void Scaling(float _x, float _y, float _z);
	void multipyMatrix(const CMatrix & b);
	void print();
	C3DPoint Transform(const C3DPoint & b);
	//void Transform(S3DPoint *p);
	//void Transform(CVector *p);
	//void TransformP(CVector *p);
   inline void Transform(CVector *p)
   {
      float x, y, z;
      x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2];
      y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2];
      z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2];
      p->x = x;
      p->y = y;
      p->z = z;
   }

   inline void TransformP(CVector *p)
   {
      float x, y, z;
      x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2] + m[0][3];
      y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2] + m[1][3];
      z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2] + m[2][3];
  
      p->x = x;
      p->y = y;
      p->z = z;
   }

   inline void Transform(S3DPoint *p)
   {
      float x, y, z;
      x = p->x * m[0][0] + p->y * m[0][1] + p->z * m[0][2] + m[0][3];
      y = p->x * m[1][0] + p->y * m[1][1] + p->z * m[1][2] + m[1][3];
      z = p->x * m[2][0] + p->y * m[2][1] + p->z * m[2][2] + m[2][3];
      p->x = x;
      p->y = y;
      p->z = z;
    }
	void TransformNorm(S3DPoint *p);
	void TransformAll(S3DPoint *p);
	void Transpose(CMatrix* target);
	CMatrix operator*(const CMatrix & b);
	inline void SetMatrix(const CMatrix* m)
    {
		*this = *m;/*
	   for (int i = 0; i<4; i++) {
		//for (int j = 0; j<4; j++) {
           this->m[i][0] = m->m[i][0];
		   this->m[i][1] = m->m[i][1];
		   this->m[i][2] = m->m[i][2];
		   this->m[i][3] = m->m[i][3];
		//}
	   };*/
    }
};

typedef float TUtiMatrix[16]; 

struct SClipResult {
   LPVOID oldpoly;
   UINT count;
   S3DPoint points[20];
};

#define BSP_FRONT 1
#define BSP_BACK -1
#define BSP_CUT 2
#define BSP_SAME 0

struct uvector
{
    float x,y,z;
};

struct CVertex
{
public:
    int Flags;
	float weight;
    CVector pos;
	CVector normal;
};

struct CPlane
{
public:
	int ClassifyPolygon(S3DPoint* list, int count); //Gibt BSP_FRONT, BSP_BACK, BSP_CUT, BSP_SAME zurck
	int ClassifyPolygon(UINT* list, CVertex* v, int count); //Gibt BSP_FRONT, BSP_BACK, BSP_CUT, BSP_SAME zurck
   void cliptoplane(S3DPoint *in, int countin, S3DPoint *out, int &countout);
	void cliptoplane(CVector *in, int countin, CVector *out, int &countout);
	int getPlanePos(C3DPoint & p);
	int getPlanePos(S3DPoint & p);
	int getPlanePos(CVector &p);
	static bool IntersectTriangle(S3DPoint* p1, S3DPoint* p2, S3DPoint* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec);
	static bool IntersectTriangle(S3DUNLIT* p1, S3DUNLIT* p2, S3DUNLIT* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec);
	static bool IntersectTriangleWithV(S3DPoint* p1, S3DPoint* p2, S3DPoint* p3, CPlane *p, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec);
	static bool IntersectTriangleWithV(CVector* p1, CVector* p2, CVector* p3, CPlane *p, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec);
    static bool IntersectTriangle(CVector* p1, CVector* p2, CVector* p3, CUtiOB* obj, CUtiOB* parent, PHitResult HitRec);
	CVector cvVector;
	float d;
	//CPlane();
	
	void GetNormal(S3DUNLIT *p1, S3DUNLIT *p2, S3DUNLIT *p3);
	//float PlaneDistance(C3DPoint & p);
	//float PlaneDistance(S3DPoint & p);
	//float PlaneDistance(CVector & p);
	/*inline float CPlane::PlaneDistance(C3DPoint & p)
    {
       return(cvVector.dotProduct(p)-d);
    }*/

    inline float PlaneDistance(S3DPoint & p)
    {
       return(cvVector.dotProduct(p)-d);
	}
	inline float PlaneDistance(CVector &p)
{
   return(cvVector.dotProduct(p)-d);
}
	bool IntersectLine(CVector* Start, CVector* Dir, float &dis);
	int getBoundingPos(S3DPoint *p, int count);
	void GetNormal(S3DPoint *p);
	void GetNormal(S3DPoint *p1, S3DPoint *p2, S3DPoint *p3);
   void GetNormal(CVector *p1, CVector *p2,CVector *p3);

	static const S3DPoint GetNormal(S3DPoint p1, S3DPoint p2, S3DPoint p3, S3DPoint *res);
};

struct SEntity
{
	SEntity(){valid = false;};
    SVector Position;
	SVector Rotation;
	UINT Group;
	bool valid;
	UINT Parent;
	int index;
	bool added;
};

class CEntity : public CUtiOB
{
private:

public:
	CEntity(){valid = false;Position.setVector(0, 0, 0);Rotation.setVector(0, 0, 0);};
	CVector Position;
	CVector Rotation;
	UINT Group;
	bool valid;
	CEntity& operator= (const SEntity &a);
};





bool IntersectLinePlane(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneX(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneY(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneZ(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneNX(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneNY(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool IntersectLinePlaneNZ(S3DPoint *polypoint, CVector *v, S3DPoint *line, S3DPoint *result, float *dis);
bool Has2DPointZ(S3DPoint *points, int npol, S3DPoint *point);
bool Has2DPointY(S3DPoint *points, int npol, S3DPoint *point);
bool Has2DPointX(S3DPoint *points, int npol, S3DPoint *point);
float SearchRoundedAreaWidthZ(S3DPoint *points, int npol);
float SearchRoundedAreaWidthY(S3DPoint *points, int npol);
float SearchRoundedAreaWidthX(S3DPoint *points, int npol);

void operator += (S3DPoint &a, const S3DPoint &b);
void operator += (S3DPoint &a, const CVector &b);
void operator *= ( S3DPoint &a, const float b );
S3DPoint operator * (const S3DPoint &a, const float b);
S3DPoint operator - ( const S3DPoint &a, const S3DPoint &b );
S3DPoint operator - ( const S3DPoint &a, const CVector &b )	;
S3DPoint operator + ( const S3DPoint &a, const S3DPoint &b );
S3DPoint operator + ( const S3DPoint &a, const CVector &b );
S3DPoint operator ^ ( const S3DPoint &a, const S3DPoint &b );
S3DPoint operator ^ ( const S3DPoint &a, const CVector &b );
float operator * ( const S3DPoint &a, const S3DPoint &b );
float operator * ( const S3DPoint &a, const CVector &b );	


float Interpolatef(float a, float b, float value);
float InterpolateCosinef(float a, float b, float x);
float Normalize(float*v);
float Length(float*v);
int ClassifyPoints(S3DPoint* points, int count, CPlane*plane);
float Interpolate(float a, float b, float x);
float InterpolateRectangle(float aa, float ba, float ab, float bb, float x, float y);
inline void AdvanceRect3D(S3DRect &Bounds, S3DPoint &p)
{
    if (Bounds.p1.x > p.x) Bounds.p1.x = p.x;
		      if (Bounds.p2.x < p.x) Bounds.p2.x = p.x;

		      if (Bounds.p1.y > p.y) Bounds.p1.y = p.y;
		      if (Bounds.p2.y < p.y) Bounds.p2.y = p.y;

		      if (Bounds.p1.z > p.z) Bounds.p1.z = p.z;
		      if (Bounds.p2.z < p.z) Bounds.p2.z = p.z;
};
#define UTI_INLINE_DOT(a, b) ((a).x*(b).x+(a).y*(b).y+(a).z*(b).z)
#define UTI_INLINE_INIT(a) a.x = a.y = a.z = 0;
#endif

