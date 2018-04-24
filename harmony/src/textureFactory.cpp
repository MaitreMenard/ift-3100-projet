#include "textureFactory.h"


TextureFactory::TextureFactory()
{
    ofPixels emptyPixels = initPixels();
    textures.push_back(new Texture("None", emptyPixels));

    ofPixels cloudPixels = initPixels();
    cloudPixels = setCloud(cloudPixels, 5.f);
    textures.push_back(new Texture("Cloud", cloudPixels));

    ofPixels marblePixels = initPixels();
    marblePixels = setMarble(marblePixels, 5.f, 5.f, 1.f, 16.f);
    textures.push_back(new Texture("Marble", marblePixels));

    ofPixels noisePixels = initPixels();
    noisePixels = setNoise(noisePixels);
    textures.push_back(new Texture("Noise", noisePixels));

    ofPixels turbulencePixels = initPixels();
    turbulencePixels = setTurbulence(turbulencePixels, 5.f);
    textures.push_back(new Texture("Turbulence", turbulencePixels));

    ofPixels zoomPixels = initPixels();
    zoomPixels = setZoom(zoomPixels, 5.f);
    textures.push_back(new Texture("Zoom", zoomPixels));
}

ofPixels TextureFactory::initPixels()
{
    ofPixels pixels = ofPixels();
    pixels.allocate(256, 256, OF_PIXELS_RGB);
    pixels.setColor(0, 0, ofColor(255, 255, 255));
    return pixels;
}

ofPixels& TextureFactory::setNoise(ofPixels& image)
{
    int temp;
    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            temp = int(255 * ofRandom(1.0));
            image.setColor(x, y, ofColor(temp, temp, temp));
        }
    }

    return image;
}

ofPixels& TextureFactory::setZoom(ofPixels& image, float zoom)
{
    ofPixels cimage = ofPixels();
    cimage.allocate(image.getWidth(), image.getHeight(), OF_PIXELS_RGB);
    setNoise(image);
    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            int color = int(255 * linearInterpolation(image, x / zoom, y / zoom));
            cimage.setColor(x, y, ofColor(color, color, color));
        }
    }

    return cimage;
}

float TextureFactory::linearInterpolation(const ofPixels& image, float x, float y)
{
    int width = int(image.getWidth()), height = int(image.getHeight());
    float fractX = x - int(x), fractY = y - int(y);
    int x1 = (int(x) + width) % width, y1 = (int(y) + height) % height;
    int x2 = (x1 + width - 1) % width, y2 = (y1 + height - 1) % height;
    float value = 0.f;
    value += fractX * fractY * image.getColor(x1, y1).getBrightness() / 255.f;
    value += (1 - fractX) * fractY * image.getColor(x2, y1).getBrightness() / 255.f;
    value += fractX * (1 - fractY) * image.getColor(x1, y2).getBrightness() / 255.f;
    value += (1 - fractX) * (1 - fractY) * image.getColor(x2, y2).getBrightness() / 255.f;
    return value;
}

ofPixels& TextureFactory::setTurbulence(ofPixels& image, float size)
{
    ofPixels cimage = ofPixels();
    cimage.allocate(image.getWidth(), image.getHeight(), OF_PIXELS_RGB);
    setNoise(image);
    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            int color = int(turbulence(image, x, y, size));
            cimage.setColor(x, y, ofColor(color, color, color));
        }
    }

    return cimage;
}

float TextureFactory::turbulence(const ofPixels &image, float x, float y, float size)
{
    float value = 0.f, initSize = size;
    while (size >= 1)
    {
        value += linearInterpolation(image, x / size, y / size) * size;
        size /= 2.0;
    }
    return 128.f * value / initSize;
}

ofPixels& TextureFactory::setCloud(ofPixels& image, float size)
{
    ofPixels cimage = ofPixels();
    cimage.allocate(image.getWidth(), image.getHeight(), OF_PIXELS_RGB);
    setNoise(cimage);
    cimage = setTurbulence(cimage, size);
    ofColor color;
    for (int x = 0; x < image.getWidth(); x++)
    {
        for (int y = 0; y < image.getHeight(); y++)
        {
            color = convertHslToHsb(169, 255, 192 + cimage.getColor(x, y).r / 4);
            cimage.setColor(x, y, color);
        }
    }

    return cimage;
}

ofColor TextureFactory::convertHslToHsb(int pH, int pS, int pL)
{
    float h = pH / 255.f, s = pS / 255.f, l = pL / 255.f, hh, ss, bb;
    ofColor color;
    hh = h;
    bb = (2 * l + s*(1 - abs(2 * l - 1))) / 2;
    ss = 2 * (bb - l) / bb;
    color.setHsb(int(hh * 255), int(ss * 255), int(bb * 255));
    return color;
}

ofPixels& TextureFactory::setMarble(ofPixels& image, float xPeriod, float yPeriod, float TurbPower, float TurbSize)
{
    setNoise(image);
    ofPixels cimage = ofPixels();
    cimage.allocate(image.getWidth(), image.getHeight(), OF_PIXELS_RGB);
    for (int x = 0; x < cimage.getWidth(); x++)
    {
        for (int y = 0; y < cimage.getHeight(); y++)
        {
            float xyValue = x * xPeriod / cimage.getWidth() + y * yPeriod / cimage.getHeight() + TurbPower * turbulence(image, x, y, TurbSize) / 255.f;
            float sineValue = 255 * fabs(sin(xyValue * PI));
            cimage.setColor(x, y, ofColor(sineValue, sineValue, sineValue));
        }
    }

    return cimage;
}

ofPixels& TextureFactory::setWood(ofPixels& image, float numberRings, float TurbPower, float TurbSize)
{
    ofPixels cimage = ofPixels();
    cimage.allocate(image.getWidth(), image.getHeight(), OF_PIXELS_RGB);
    setNoise(image);
    for (int x = 0; x < cimage.getWidth(); x++)
        for (int y = 0; y < cimage.getHeight(); y++)
        {
            float xValue = (x - cimage.getWidth() / 2) / float(cimage.getWidth());
            float yValue = (y - cimage.getHeight() / 2) / float(cimage.getHeight());
            float distValue = sqrt(pow(xValue, 2) + pow(yValue, 2)) + TurbPower * turbulence(image, x, y, TurbSize) / 255.f;
            float sineValue = 127.f * fabs(sin(2 * numberRings * distValue * PI));
            cimage.setColor(x, y, ofColor(80 + sineValue, 30 + sineValue, 30));
        }

    return cimage;
}

TextureFactory::~TextureFactory()
{
    for (Texture* texture : textures)
    {
        delete texture;
    }
    textures.clear();
}

std::vector<Texture*> TextureFactory::getAllTextures()
{
    return textures;
}

Texture* TextureFactory::getEmptyTexture()
{
    return textures[0];
}