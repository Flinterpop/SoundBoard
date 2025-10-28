#pragma once

#include <vector>
#include <filesystem>



bool getFileNameNoExtension(const char* path, char* dest)
{
    char path_buffer[_MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    errno_t err;

    err = _splitpath_s(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    if (err != 0)
    {
        printf("Error splitting the path. Error code %d.\n", err);
        return true;
    }
    //printf("Path extracted with _splitpath_s:\n");
    //printf("   Drive: %s\n", drive);
    //printf("   Dir: %s\n", dir);
    //printf("   Filename: %s\n", fname);
    //printf("   Ext: %s\n", ext);

    strcpy(dest, fname);

    return false;
}


bool getFileNameExtension(const char* path, char* dest)
{
    char path_buffer[_MAX_PATH];
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    errno_t err;

    err = _splitpath_s(path, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    if (err != 0)
    {
        printf("Error splitting the path. Error code %d.\n", err);
        return true;
    }
    //printf("Path extracted with _splitpath_s:\n");
    //printf("   Drive: %s\n", drive);
    //printf("   Dir: %s\n", dir);
    //printf("   Filename: %s\n", fname);
    //printf("   Ext: %s\n", ext);

    strcpy(dest, ext);

    return false;
}

#include <iostream>   
#include <direct.h>   
using namespace std;


//check for crashes
std::vector<std::string> LoadFileNamesInFolder(char* folderName, char* fileType)
{
    std::vector<std::string> fileList;

    const size_t size = 1024;
    char CurDir[size];
    if (getcwd(CurDir, size) != NULL)
    {
        cout << "Current working directory: " << CurDir << endl;
    }
    else {
        // If _getcwd returns NULL, print an error message
        cerr << "Error getting current working directory" << endl;
        return fileList;
    }


    char bigBuf[200];
    sprintf(bigBuf, "%s\\%s\\", CurDir, folderName);
    printf("bigBuf: %s\r\n", bigBuf);


    //from https://www.geeksforgeeks.org/cpp-program-to-get-the-list-of-files-in-a-directory/
    // This structure would distinguish a file from a directory
    struct stat sb;
    // Looping until all the items of the directory are exhausted
    int count = 0;
    //for (const auto& entry : std::filesystem::directory_iterator(CurDir))
    for (const auto& entry : std::filesystem::recursive_directory_iterator(bigBuf))
        //for (const auto& entry : std::filesystem::recursive_directory_iterator("C:\\source\\git_Maps\\IM_MAPSDX11\\RunFolder\\MS2525C\\"))

    {
        // Converting the path to const char * in the subsequent lines
        std::filesystem::path outfilename = entry.path();
        std::string outfilename_str = outfilename.string();
        const char* path = outfilename_str.c_str();

        // Testing whether the path points to a non-directory or not If it does, displays path
        if (stat(path, &sb) == 0 && !(sb.st_mode & S_IFDIR))
        {
            char justTheExtension[40] = "";
            getFileNameExtension(path, justTheExtension);
            if (!strncmp(justTheExtension, fileType, 4))
            {
                printf("Filename: %s\n", path);
                fileList.push_back(path);
            }
            //if (fileList.size() > 40) break;
        }
    }
    return fileList;
}
