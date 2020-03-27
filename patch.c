<?php
/******************************************************************************
            _ *------------------------------------------------------* _
        /o)|           Script   : Facebook SSL Pinning Patch            |(o\
        / / |          Author   : Ngoc Chanh at J2TeaM                  | \ \
        ( (_ |  _      FB       : https://fb.me/100002460766649      _  | _) )
        ((\ \)+-/o)*-----------------------------------------------*(o\-+(/ /))
        (\\\ \_/ /                                                   \ \_/ ///)
        \      /                                                     \      /
        \____/                                                       \____/
                    Copyright 2020 J2TeaM. All rights reserved
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <windows.h>


size_t replace(FILE *fi, FILE *fo, uint8_t *what, uint8_t *repl, size_t size){
    size_t i, index = 0, count = 0;
    int ch;
    while(EOF!=(ch=fgetc(fi))){
        if(ch == what[index]){
            if(++index == size){
                for(i = 0; i < size ; ++i){
                    fputc(repl[i], fo);
                }
                index = 0;
                ++count;
            }
        } else {
            for(i = 0; i < index ; ++i){
                fputc(what[i], fo);
            }
            index =0;
            fputc(ch, fo);
        }
    }
    for(i = 0; i < index ; ++i){
        fputc(what[i], fo);
    }

    return count;
}
/* ARM */
int main(void){
    FILE *file,*fileout;
    uint8_t what[] = {0x47, 0xB1, 0xDD, 0xE9, 0x09, 0x86, 0x38};
    uint8_t repl[] = {0x06, 0xE0, 0xDD, 0xE9, 0x09, 0x86, 0x38};
    uint8_t what1[] = {0xB1, 0x28, 0x46, 0xA9, 0xF0, 0xAE, 0xFB};
    uint8_t repl1[] = {0xB1, 0x28, 0x46, 0x00, 0xF0, 0x80, 0xF8};
    size_t count;
	if (access("libcoldstart.so", F_OK)) {
		printf("File libcoldstart.so not found!\n");
		MessageBox(NULL,"File libcoldstart.so not found!\nCopyright by J2TeaM\n","J2TeaM Patcher",MB_OK);
		exit(0);
	}
    file=fopen("libcoldstart.so","rb");
    fileout=fopen("libcoldstart.so.tmp","wb");
    count = replace(file, fileout, what, repl, sizeof(what));
    fclose(fileout);
    fclose(file);
    file=fopen("libcoldstart.so.tmp","rb");
    fileout=fopen("libcoldstart.so.patched","wb");
    count = replace(file, fileout, what1, repl1, sizeof(what1));
    fclose(fileout);
    fclose(file);
    remove("libcoldstart.so.tmp");
    printf("File libcoldstart.so has been patched success!\n");
    MessageBox(NULL,"File libcoldstart.so has been patched success!\nCopyright by J2TeaM\n","J2TeaM Patcher",MB_OK);
    exit(0);
}

/* x86
int main(void){
    FILE *file,*fileout;
    uint8_t what[] = {0x74, 0x3C, 0x8B, 0x7C, 0x24, 0x38};
    uint8_t repl[] = {0xEB, 0x19, 0x8B, 0x7C, 0x24, 0x38};
    uint8_t what1[] = {0x83, 0xC4, 0x10, 0x89, 0xC1, 0xB0};
    uint8_t repl1[] = {0x90, 0x90, 0x90, 0x90, 0x90, 0xB0};
    uint8_t what2[] = {0x75, 0x1A, 0x83, 0xEC, 0x0C, 0x57};
    uint8_t repl2[] = {0xEB, 0x1A, 0x83, 0xEC, 0x0C, 0x57};
    size_t count;
	if (access("libcoldstart.so", F_OK)) {
		printf("File libcoldstart.so not found!\n");
		MessageBox(NULL,"File libcoldstart.so not found!\nCopyright by J2TeaM\n","J2TeaM Patcher",MB_OK);
		exit(0);
	}
    file=fopen("libcoldstart.so","rb");
    fileout=fopen("libcoldstart.so.tmp.patch","wb");
    count = replace(file, fileout, what, repl, sizeof(what));
    fclose(fileout);
    fclose(file);
    file=fopen("libcoldstart.so.tmp.patch","rb");
    fileout=fopen("libcoldstart.so.tmp","wb");
    count = replace(file, fileout, what1, repl1, sizeof(what));
    fclose(fileout);
    fclose(file);
    remove("libcoldstart.so.tmp.patch");
    file=fopen("libcoldstart.so.tmp","rb");
    fileout=fopen("libcoldstart.so.patched","wb");
    count = replace(file, fileout, what2, repl2, sizeof(what1));
    fclose(fileout);
    fclose(file);
    remove("libcoldstart.so.tmp");
    printf("File libcoldstart.so has been patched success!\n");
    MessageBox(NULL,"File libcoldstart.so has been patched success!\nCopyright by J2TeaM\n","J2TeaM Patcher",MB_OK);
    exit(0);
} */