#ifndef MACROS_H
#define MACROS_H

#define CLI


#ifdef CLI

#define READ(description,size,type,variable) readcli(description,size,type,variable);


#endif

#ifdef GUI

#define READ(description,size,type,variable) readcli(description,size,type,variable);


#endif

#endif
