#ifndef INIT_ADD_H
#define INIT_ADD_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

void init();
bool checkFileExists(const std::string& filename);
std::string hashContentOfFile(const std::string& content);
void writeTheBlob(const std::string& hash, const std::string& content);
void stageFile(const std::string& filename, const std::string& hash);

#endif