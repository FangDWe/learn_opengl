#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include"src/stb_image.h"
#include<string>

unsigned char* load(std::string path, int *width, int *height, int *nrComponents){
    int a = 1;
    unsigned char *data = stbi_load(path.c_str(), width, height, nrComponents, 0);
    return data;
}