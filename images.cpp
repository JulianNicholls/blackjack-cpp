#include <filesystem>

#include "raylib.h"

#include "images.h"

namespace CPPRaylib
{

ImageLoader::ImageLoader(std::string_view dir)
    : images_{}
{
    for (auto const &dir_entry : std::filesystem::directory_iterator(dir))
    {
        const std::string ext{dir_entry.path().extension()};

        if (ext != ".png" && ext != ".jpg")
            continue;

        const std::string imagename{dir_entry.path().stem()};
        const char *filename = dir_entry.path().c_str();

        images_.emplace(imagename, LoadTexture(filename));
    }
}

ImageLoader::~ImageLoader()
{
    for (auto [key, tex] : images_)
    {
        ::UnloadTexture(tex);
    }
}

const Texture2D &ImageLoader::at(std::string_view name) const
{
    return images_.at(std::string(name));
}

const Texture2D &ImageLoader::operator[](std::string_view name)
{
    return images_[std::string(name)];
}

}
