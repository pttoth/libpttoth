/** -----------------------------------------------------------------------------
  * FILE:    filesystem.h
  * AUTHOR:  pttoth
  * EMAIL:   peter.t.toth92@gmail.com
  * PURPOSE: Provides a platform-independent solution
  *             for handling files and directories.
  * CONCEPTS:
  *          - Need wchar_t as path types
  *             want to support ASCII -> Unicode conversion
  *             not backwards
  *          - Want to adjust upper/lowercase support
  *          - Can set up root directory to confine filesystem traversal
  *             can convert absolute and relative paths
  *          - Should be able to handle network-shared folders
  *          - Should(?) be able to identify symlinks?
  * -----------------------------------------------------------------------------
  */

#pragma once

#include <cstddef>
#include <string>
#include <vector>

namespace pttoth{

class FileSystem{

    std::string     _root_directory;
    std::string     _working_directory;

    //wchar_t

    //enable/disable Upper/lowercase support

public:
    enum class FileType{
        UNKNOWN = 0,
        FILE,
        DIRECTORY,
        SYMLINK_F,
        SYMLINK_D,
    };

    enum class ErrorCode{
        NO_ERROR = 0,
        INVALID_URL_SYNTAX,
        INVALID_PATH,
        PATH_OUTSIDE_ROOT_DIRECTORY,
        FILE_ALREADY_EXISTS,
        ACCESS_DENIED,

    };

    enum class Depth{
        NAME_ONLY = 0,
        FILES_ONLY,
        RECURSIVE
    };

    FileSystem();
    FileSystem(const FileSystem& other);
    FileSystem(FileSystem&& other);
    virtual ~FileSystem();
    FileSystem& operator=(const FileSystem &other);
    FileSystem& operator=(FileSystem &&other);
    bool operator==(const FileSystem &other)const;

    std::vector<std::string>    getCaseSensitivityConflicts(const std::string& path,
                                                            Depth alg_depth = Depth::NAME_ONLY) const;

    //should this be a standard functionality, or engine specific?
        //may enhance security with root-confinement (is a wrapper class better?)
    ErrorCode   setRootDir();   //sets working directory too if it would be outside
    void        getRootDir();

    std::string getRelativePath();
    std::string getAbsolutePath();

    std::string getWorkingDirectory() const;

    ErrorCode createDirectory();
    ErrorCode removeDirectory();
    ErrorCode navigateToDirectory(char* const path);

    std::vector<std::string>    getDirectoryContents() const;


};

}


