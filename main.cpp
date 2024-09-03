#include <iostream>
#include <vector>
#include <string>
#include <dirent.h>
#include <unistd.h>
#include <cstdlib>

#define INTERVAL 600

std::vector<std::string> get_images_from_folder(const std::string& folder_path)
{
    std::vector<std::string> images;
    DIR* dir;
    struct dirent* entry;

    if((dir = opendir(folder_path.c_str())) != nullptr) {
        while((entry = readdir(dir)) != nullptr) {
            if(entry->d_type == DT_REG) {
                images.push_back(folder_path + "/" + entry->d_name);
            }
        }
        closedir(dir);
    } else {
        std::cerr << "Failed to open directory: " << folder_path << std::endl;
    }
    return images;
}

void set_wallpaper(const std::string& image_path, bool dark_mode){
    std::string command = dark_mode ?
                              "gsettings set org.gnome.desktop.background picture-uri-dark file://" + image_path :
                              "gsettings set org.gnome.desktop.background picture-uri file://" + image_path;
    system(command.c_str());
}

int main()
{
    std::string folder_path;
    std::string theme;
    bool dark_mode = false;

    std::cout << "Enter the path to the folder with images: ";
    std::getline(std::cin, folder_path);

    std::cout << "Enter your theme (light/dark): ";
    std::getline(std::cin, theme);

    if (theme == "dark") {
        dark_mode = true;
    }

    std::vector<std::string> images = get_images_from_folder(folder_path);

    if (images.empty()) {
        std::cerr << "No images found in the folder" << std::endl;
        return 1;
    }

    int current_index = 0;

    while (true) {
        set_wallpaper(images[current_index], dark_mode);
        current_index = (current_index + 1) % images.size();
        sleep(INTERVAL);
    }

    return 0;
}
