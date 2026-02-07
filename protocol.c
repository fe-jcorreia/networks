#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HEADER_CONST 64

void insertHeader(char *str, size_t length)
{
  const char charset[] =
    "abcdefghijklmnopqrstuvwxyz"
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "0123456789";

  size_t charset_size = sizeof(charset) - 1;

  for (size_t i = 0; i < length; i++) {
    int key = rand() % charset_size;
    str[i] = charset[key];
  }
}

char *performConcatenate(char *str, int length) {
  int newLength = HEADER_CONST + length;
  char *t = (char *)realloc(str, newLength * sizeof(char));
  if (!t) {
    free(str);
    return NULL;
  }
  str = t;

  memmove(str + HEADER_CONST, str, length);
  insertHeader(str, HEADER_CONST);

  return str;
}

void *physical(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Physical Layer:\n");
  printf("%s\n", payload);
  printf("-----------------------------------------------------------------------------------------\n\n");
}

void *datalink(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Data Link Layer:\n");
  printf("%s\n", payload);

  physical(payload, length + HEADER_CONST);
}

void *network(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Network Layer:\n");
  printf("%s\n", payload);

  datalink(payload, length + HEADER_CONST);
}

void *transport(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Transport Layer:\n");
  printf("%s\n", payload);

  network(payload, length + HEADER_CONST);
}

void *session(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Session Layer:\n");
  printf("%s\n", payload);

  transport(payload, length + HEADER_CONST);
}

void *presentation(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Presentation Layer:\n");
  printf("%s\n", payload);

  session(payload, length + HEADER_CONST);
}

void *application(char *payload, int length) {
  payload = performConcatenate(payload, length);

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Application Layer:\n");
  printf("%s\n", payload);

  presentation(payload, length + HEADER_CONST);
}

int main (int argc, char *argv[]) {
  int length = strlen(argv[1]) + 1;
  char *payload = (char *) malloc(length * sizeof(char));
  strcpy(payload, argv[1]);
  payload[length] = '\0';

  printf("-----------------------------------------------------------------------------------------\n");
  printf("Payload message:\n");
  printf("%s\n", payload);
  
  application(payload, length);

  return 0;
}
