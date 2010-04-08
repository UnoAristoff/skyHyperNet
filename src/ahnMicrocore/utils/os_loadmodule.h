#ifndef OS_LOADMODULE_H
#define OS_LOADMODULE_H

//////////// Cross-Platform Module Loader ///////////
//// � ���� ������ ���� �� ���������, ����� ����� ������ SDL ������ ��� CLe266 :(((

void *os_LoadObject(const char *ModuleName);

void *os_LoadFunction(void *handle, const char *name);

void os_UnloadObject(void *handle);

#endif
