#include <stdio.h>
#include "DHTInterface.h"



int main (void) {
  int key;
  
  valueType value, *temp;
  
  
  /* Initialization */
  DHTInitialize();
  printf("Initial network:\n\n");
  DHTPrint();
  
  
  /* Insertion */
  printf("Insert some values:\n\n");
  printf("Value: ");
  while (scanf("%d", &(value.Value)) != EOF) {
    value.NextValue = NULL;
    key = Hash(value);
    printf("|\n");
    printf("V\n");
    printf("Corresponding key: %d\n\n", key);
    DHTInsert(&Chord[0], key, value);
    printf("Current network:\n\n");
    DHTPrint();
    printf("Value: ");
  }
  printf("|\n");
  printf("V\n");
  printf("End of insertion.\n\n");
  
  
  /* Lookup*/
  printf("\nFind a group of existing values by giving its key (Lookup): ");
  scanf("%d", &key);
  printf("|\n");
  printf("V\n");
  value = DHTLookup(Chord[0], key);
  if (value.Value == ERROR) {
    printf("Not availiable corresponding value in network!");
  }
  else {
    printf("The corresponding value(s) is/are:");
    printf(" %d", value.Value);
    temp = value.NextValue;
    while (temp != NULL) {
      if (Hash(*temp) == key)
        printf(" %d", temp->Value);
      temp = temp->NextValue;
    }
  }
  printf("\n\n");
  
  
  /* Smart lookup*/
  printf("\nFind a group of existing values by giving its key (Smart Lookup): ");
  scanf("%d", &key);
  printf("|\n");
  printf("V\n");
  value = DHTSmartLookup(Chord[0], key);
  if (value.Value == ERROR) {
    printf("Not availiable corresponding value in network!");
  }
  else {
    printf("The corresponding value(s) is/are:");
    printf(" %d", value.Value);
    temp = value.NextValue;
    while (temp != NULL) {
      if (Hash(*temp) == key)
        printf(" %d", temp->Value);
      temp = temp->NextValue;
    }
  }
  printf("\n\n");
  
  
  return 0;
}
