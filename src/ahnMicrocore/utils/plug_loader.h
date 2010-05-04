#ifndef PLUG_LOADER_H
#define PLUG_LOADER_H

void load_mod( const char* mod_name );
void scan_mod( const char* dir_name, bool Recursive = false );
extern void get_mod(void* mod_ptr);

#endif
