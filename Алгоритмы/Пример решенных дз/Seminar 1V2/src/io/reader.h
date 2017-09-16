/**
 * @file reader.h
 * @author LionZXY
 * @project Seminar
 * @date 08.09.17
 * @email nikita@kulikof.ru
 **/
#ifndef SEMINAR_READER_H
#define SEMINAR_READER_H

struct ArrayList {
    int bufferSize;
    int realSize;
    int *array;
} typedef ArrayList;

int getInt(int *out);
int getIntArray(ArrayList *outList);
char *copyString(char *str);

#endif //SEMINAR_READER_H
