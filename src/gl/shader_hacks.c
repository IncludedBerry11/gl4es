#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "string_utils.h"

typedef struct hack_s {
    char* sign;
    int   n;
    char* next[5];
} hack_t;

static const hack_t gl4es_hacks[] = {
// for OpenMW
// fog.glsl
{"#ifdef ADDITIVE_BLENDING",
1, {"#if defined(ADDITIVE_BLENDING)"}},
// end of fog.glsl
}
// for OpenMW
// fog.glsl
static const char* gl4es_sign_1[] = {
"#ifdef ADDITIVE_BLENDING",
};
static const char* gl4es_hacks_1[] = {
"#ifdef ADDITIVE_BLENDING",
"#if defined(ADDITIVE_BLENDING)",
};

// For Psychonauts
static const char* gl4es_sign_2[] = {
"vec4 ps_t3 = gl_TexCoord[3];",
"vec4 ps_t2 = gl_TexCoord[2];",
"vec4 ps_t1 = gl_TexCoord[1];",
"vec4 ps_t0 = gl_TexCoord[0];",
};

static const char* gl4es_sign_2_main = 
"void main()\n"
"{\n";


static const char* gl4es_hacks_2_1[] = {
"vec4 ps_t3;",
"vec4 ps_t2;",
"vec4 ps_t1;",
"vec4 ps_t0;",
};

static const char* gl4es_hacks_2_2[] = {
"\tps_t3 = gl_TexCoord[3];",
"\tps_t2 = gl_TexCoord[2];",
"\tps_t1 = gl_TexCoord[1];",
"\tps_t0 = gl_TexCoord[0];",
};

static char* ShaderHacks_1(char* shader, char* Tmp, int* tmpsize)
{
    // check for all signature first
    for (int i=0; i<sizeof(gl4es_sign_1)/sizeof(gl4es_sign_1[0]); i++)
        if(!strstr(Tmp, gl4es_sign_1[i]))
            return Tmp;
    // Do the replace
    for (int i=0; i<sizeof(gl4es_hacks_1)/sizeof(gl4es_hacks_1[0]); i+=2)
        if(strstr(Tmp, gl4es_hacks_1[i])) {
            if(Tmp==shader) {Tmp = (char*)malloc(*tmpsize); strcpy(Tmp, shader);}   // hacking!
            Tmp = gl4es_inplace_replace_simple(Tmp, tmpsize, gl4es_hacks_1[i], gl4es_hacks_1[i+1]);
        }
    return Tmp;
}

static char* ShaderHacks_2_1(char* shader, char* Tmp, int* tmpsize, int i)
{
    char* p = strstr(Tmp, gl4es_sign_2[i]);
    if(!p) return Tmp;  // not found
    char* m = strstr(Tmp, gl4es_sign_2_main);
    if(!m) return Tmp;  // main signature not found
    if((uintptr_t)p > (uintptr_t)m) return Tmp; // main is before, aborting...
    // ok, instance found, insert main line...
    if(Tmp==shader) {Tmp = (char*)malloc(*tmpsize); strcpy(Tmp, shader); m = strstr(Tmp, gl4es_sign_2_main);}   // hacking!
    m += strlen(gl4es_sign_2_main);
    Tmp = gl4es_inplace_insert(m, gl4es_hacks_2_2[i], Tmp, tmpsize);
    Tmp = gl4es_inplace_replace_simple(Tmp, tmpsize, gl4es_sign_2[i], gl4es_hacks_2_1[i]);
    return Tmp;
}

static char* ShaderHacks_2(char* shader, char* Tmp, int* tmpsize)
{
    // check for each signature
    for (int i=0; i<sizeof(gl4es_sign_2)/sizeof(gl4es_sign_2[0]); i++)
        Tmp = ShaderHacks_2_1(shader, Tmp, tmpsize, i);
    return Tmp;
}

char* ShaderHacks(char* shader)
{

    char* Tmp = shader;
    int tmpsize = strlen(Tmp)+10;
    // specific hacks
    Tmp = ShaderHacks_1(shader, Tmp, &tmpsize);
    Tmp = ShaderHacks_2(shader, Tmp, &tmpsize);
    // generic
    for (int i=0; i<sizeof(gl4es_hacks)/sizeof(gl4es_hacks[0]); ++i) {
        char* f = gl4es_hacks[i].sign;
        int n = gl4es_hacks[i].n;
        if(strstr(Tmp, f)) {
            if(Tmp==shader) {Tmp = (char*)malloc(tmpsize); strcpy(Tmp, shader);}   // hacking!
            for (int j=0; j<n; j+=2) {
                if(j) f = gl4es_hacks[i].next[j-1];
                Tmp = gl4es_inplace_replace_simple(Tmp, &tmpsize, f, gl4es_hacks[i].next[j]);
            }
        }
    }

    return shader;

}
