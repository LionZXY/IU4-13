#ifndef IU4_DATABASE_READER_H
#define IU4_DATABASE_READER_H
extern const int START_BUFFER;

char *nextString(char *str, int *curIndex, const char separator);

long long nextLong(char *str, int *curIndex, const char separator);

int nextInt(char *str, int *curIndex, const char separator);

char *getLine();

int getUInt();

#endif //IU4_DATABASE_READER_H
