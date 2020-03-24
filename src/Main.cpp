/*
 * Zepha, designed, developed, and created by Nicole Collings
 * This is my child, and I hope you like it.
 * Copyright 2018 - present Nicole Collings, All Rights Reserved.
 */

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wconversion"
#pragma ide diagnostic ignored "OCUnusedMacroInspection"

#define STB_IMAGE_IMPLEMENTATION
#define CUTE_FILES_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#pragma clang diagnostic pop

#include "StartGame.h"
#include "util/Any.h"

int main(int argc, char* argv[]) {
//    return StartGame(argc, argv);

    Any a(new std::string("whee"));
    Any b(new int(125));

    std::cout << *a.get<std::string>() << std::endl;
    std::cout << *b.get<int>() << std::endl;
}