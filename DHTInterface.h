#include "DHTTypes.h"



extern nodeType Chord[MAXNODENUMBER];


void DHTInitialize(void);
void DHTInsert(nodeType *, keyType, valueType);
valueType DHTLookup(nodeType, keyType);
valueType DHTSmartLookup(nodeType, keyType);
nodeType FindSuccessor(nodeType, keyType);
nodeType ClosestPrecedingNode(nodeType, keyType);
keyType Hash(valueType);
void DHTPrint(void);
