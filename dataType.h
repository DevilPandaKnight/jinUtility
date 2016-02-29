//
//  dataType.h
//  temp
//
//  Created by Jin on 9/20/13.
//  Copyright (c) 2013 Jin. All rights reserved.
//
#ifndef __DATATYPE_H_
#define __DATATYPE_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum{
	intType,
	doubleType,
	floatType,
	charType,
	longType,
	stringType,
    longlongType,
    longdoubleType,
    vectorType,
	memoryType,
    linklistType,
    stackType,
    boolType,
	nullType,
	vector2DType,
	vector3DType,
	complexType
}dataType;

#ifdef __cplusplus
};
#endif

#endif