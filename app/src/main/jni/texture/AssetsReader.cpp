#include "AssetsReader.h"

AssetsReader::AssetsReader(AAssetManager *mgr) {
    this->mgr = mgr;
}

struct mypng {
    unsigned int pos;
    //текущая позиция в массиве
    unsigned int length;
    //длинна массива
    const char *data;//массив содержащий сжатую картинку
};


static void userReadData(png_structp png_ptr, png_bytep data, png_size_t length) {
    //получаем ссылку на структуру
    mypng *png = (mypng *) png_get_io_ptr(png_ptr);
    //смотрим чтобы не вылезти за края массива
    if (png->pos + length > png->length) length += png->pos - png->length;
    if (length > 0) {
        //копируем данные из массива
        memcpy(data, png->data + png->pos, length);
        //двигаем текущую позицию
        png->pos += length;
    }
}


static int reNpot(int w) {
    //поддерживает ли OpenGL текстуры размера не кратным двум
    //эту переменную конечно надо определять один раз при старте проги с помощью
    //String s = gl.glGetString(GL10.GL_EXTENSIONS);
    //NON_POWER_OF_TWO_SUPPORTED = s.contains("texture_2D_limited_npot") || s.contains("texture_npot") || s.contains("texture_non_power_of_two");
    bool NON_POWER_OF_TWO_SUPPORTED = true;
    if (NON_POWER_OF_TWO_SUPPORTED) {
        if (w % 2) w++;
    } else {
        if (w <= 4) w = 4;
        else if (w <= 8) w = 8;
        else if (w <= 16) w = 16;
        else if (w <= 32) w = 32;
        else if (w <= 64) w = 64;
        else if (w <= 128) w = 128;
        else if (w <= 256) w = 256;
        else if (w <= 512) w = 512;
        else if (w <= 1024) w = 1024;
        else if (w <= 2048) w = 2048;
        else if (w <= 4096) w = 4096;
    }
    return w;
}


Png AssetsReader::readPng(const std::string &fileName) {

    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_ptr = png_create_info_struct(png_ptr);

    AAsset *asset = AAssetManager_open(mgr, fileName.c_str(), AASSET_MODE_STREAMING);

    std::vector<char> data;

    char buf[BUFSIZ];
    int nb_read = 0;
    while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0) {
        data.insert(data.end(), &buf[0], &buf[nb_read]);

    }
    AAsset_close(asset);

    mypng png = {8, data.size(), data.data()};
    png_init_io(png_ptr, (FILE *) &png);
    png_set_read_fn(png_ptr, png_get_io_ptr(png_ptr), userReadData);


    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    //читаем данные о картинке
    png_uint_32 width, height;
    int bitDepth;
    int colorType;
    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bitDepth, &colorType, NULL, NULL, NULL);

    //определяем размер картинки подходящий для OpenGL
    png_uint_32 glWidth = reNpot(width);
    png_uint_32 glHeight = reNpot(height);

    //если картинка содержит прозрачность то на каждый пиксель 4 байта (RGBA), иначе 3 (RGB)
    int row = glWidth * (colorType == PNG_COLOR_TYPE_RGBA ? 4 : 3);
    char *dat = new char[row * glHeight];


    //в этом массиве содержатся указатели на начало каждой строки
    png_bytep *row_pointers = new png_bytep[height];
    for (int i = 0; i < height; ++i)
        row_pointers[i] = (png_bytep) (dat + i * row);

    //читаем картинку
    png_read_image(png_ptr, row_pointers);
    png_destroy_read_struct(&png_ptr, &info_ptr, 0);
    delete[] row_pointers;

    std::vector<char> tmp(&dat[0], &dat[row * glHeight]);

    return Png(tmp, glWidth, glHeight, bitDepth, colorType);
}


AssetsReader::~AssetsReader() {

}

std::string AssetsReader::readString(const std::string &fileName) const {
    AAsset *asset = AAssetManager_open(mgr, fileName.c_str(), AASSET_MODE_STREAMING);

    std::string data;

    char buf[BUFSIZ];
    int nb_read = 0;
    while ((nb_read = AAsset_read(asset, buf, BUFSIZ)) > 0) {
        data.insert(data.end(), &buf[0], &buf[nb_read]);

    }
    AAsset_close(asset);

    return data;
}
