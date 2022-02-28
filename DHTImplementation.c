#include <stdio.h>
#include <stdlib.h>
#include "DHTInterface.h"



static int maxID = -1;
nodeType Chord[MAXNODENUMBER];


void DHTInitialize(void) {
  int i, j, k, ID = 1, exp;
  
  /* Initialize Chord */
  for (i = 0; i < MAXNODENUMBER; i++, ID += 7) {
    Chord[i].NodeID = ID;  /* Arbitrary IP addressing to represent every connected computer */
    if (Chord[i].NodeID > maxID)  /* Find maximum ID */
      maxID = Chord[i].NodeID;
    Chord[i].Info = NULL;  /* Not availiable info */
  }
  
  /* Construct each finger table */
  for (i = 0; i < MAXNODENUMBER; i++) {
    for (j = 0, exp = 1; j < MAXNODENUMBER; j++, exp *= 2) {
      for (k = 0; k < MAXNODENUMBER; k++) { 
        if (Chord[k].NodeID >= (Chord[i].NodeID + exp) % maxID) {
          Chord[i].FingerTable[j] = &Chord[k];
          break;
        }
      }
      if (Chord[i].FingerTable[j]->NodeID == Chord[i].NodeID) {
        Chord[i].FingerTable[j] = NULL;
        break;
      }
    }
  }
}


void DHTInsert(nodeType *nodeptr, keyType key, valueType value) {
  valueType *new_value, *temp;
  new_value = malloc(sizeof(valueType));
  new_value->Value = value.Value;
  new_value->NextValue = NULL;
  while (nodeptr->NodeID < key) {
    nodeptr = nodeptr->FingerTable[0];
  }
  if (nodeptr->Info == NULL) {
    nodeptr->Info = new_value;
    return;
  }
  temp = nodeptr->Info;
  while (temp->NextValue != NULL)
    temp = temp->NextValue;
  temp->NextValue = new_value;
}


valueType DHTLookup(nodeType node, keyType key) {
  valueType *temp;
  if (key == 0 || key > maxID) {  /* Not availiable corresponding value */
    temp = malloc(sizeof(valueType));
    temp->Value = ERROR;
    return *temp;
  }
  while (node.NodeID < key) {
    node = *node.FingerTable[0];
  }
  temp = node.Info;
  if (temp == NULL) {  /* Not availiable corresponding value */
    temp = malloc(sizeof(valueType));
    temp->Value = ERROR;
    return *temp;
  }
  while (Hash(*temp) != key) {
    if (temp->NextValue == NULL) {
      temp = malloc(sizeof(valueType));
      temp->Value = ERROR;
      return *temp;
    }
    temp = temp->NextValue;
  }
  return *temp;
}


valueType DHTSmartLookup(nodeType node, keyType key) {
  int i;
  valueType *temp;
  if (key == 0 || key > maxID) {  /* Not availiable corresponding value */
    temp = malloc(sizeof(valueType));
    temp->Value = ERROR;
    return *temp;
  }
  if (node.NodeID != key)
    node = FindSuccessor(node, key);
  temp = node.Info;
  if (temp == NULL) {  /* Not availiable corresponding value */
    temp = malloc(sizeof(valueType));
    temp->Value = ERROR;
    return *temp;
  }
  while (Hash(*temp) != key) {
    if (temp->NextValue == NULL) {
      temp = malloc(sizeof(valueType));
      temp->Value = ERROR;
      return *temp;
    }
    temp = temp->NextValue;
  }
  return *temp;
}


nodeType FindSuccessor(nodeType node, keyType key) {
  if (key > node.NodeID && key <= node.FingerTable[0]->NodeID)
    return *node.FingerTable[0];
  else {
    node = ClosestPrecedingNode(node, key);
    return FindSuccessor(node, key);
  }
}


nodeType ClosestPrecedingNode(nodeType node, keyType key) {
  int i;
  for (i = 0; i < MAXNODENUMBER; i++)
    if (node.FingerTable[i]->NodeID > node.NodeID && node.FingerTable[i]->NodeID < key)
      return *node.FingerTable[i];
  return node;
}


keyType Hash(valueType value) {
  return value.Value % maxID;
}


void DHTPrint(void) {
  int i;
  valueType *temp;
  for (i = 0; i < MAXNODENUMBER; i++) {
    printf("Node[%d]:", i+1);
    temp = Chord[i].Info;
    while (temp != NULL) {
      printf(" %d", temp->Value);
      temp = temp->NextValue;
    }
    printf("\n");
  }
  printf("\n");
}
