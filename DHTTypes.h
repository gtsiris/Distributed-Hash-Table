#define MAXNODENUMBER 5
#define ERROR 0xF0000000


typedef struct valueTag {
  int Value;
  struct valueTag *NextValue;
} valueType;

typedef int keyType;

typedef struct nodeTag {
  int NodeID;
  valueType *Info;
  struct nodeTag *FingerTable[MAXNODENUMBER];
} nodeType;
