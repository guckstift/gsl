#ifndef basetypes_H
#define basetypes_H

typedef signed long gint;
typedef unsigned long guint;
typedef double gfloat;
typedef unsigned char gchar;
typedef unsigned char gbool;

#define gfalse ((gbool)0)
#define gtrue ((gbool)1)

typedef signed char gint8;
typedef unsigned char guint8;
typedef signed short gint16;
typedef unsigned short guint16;
typedef signed int gint32;
typedef unsigned int guint32;
typedef signed long gint64;
typedef unsigned long guint64;

#define MAX_UINT ((guint)-1)

#define Base_HEAD \
	guint refcount; \
	struct Base* type;

typedef struct Base {
	Base_HEAD
} Base;

#define VarBase_HEAD \
	Base_HEAD \
	guint length;

typedef struct VarBase {
	VarBase_HEAD
} VarBase;

#endif
