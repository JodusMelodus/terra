#include "types.h"

struct TextureMap CreateTextureMap(const char *path)
{
    int width, height, channels;
    unsigned char *textureData = stbi_load(path, &width, &height, &channels, 0);
    if (!textureData)
    {
        perror("CreateTextureMap: Failed to read texture");
        exit(1);
    }

    return (struct TextureMap){
        .width = width,
        .height = height,
        .channels = channels,
        .textureData = textureData};
}

void FreeTextureMap(struct TextureMap *textureMap)
{
    stbi_image_free(textureMap->textureData);
}
