//
// Created by ptriller on 06.07.16.
//

#include "ppeg.h"
#include "netutil.h"

using namespace codec;

namespace {

    typedef std::uint8_t (*calc_op)(const RGBPixel &);

    inline std::uint8_t convert_y(const RGBPixel &pixel) {
        return (std::uint8_t)
                (16.f
                 + (float) pixel.red * 0.183f
                 + (float) pixel.green * 0.614f
                 + (float) pixel.blue * 0.062f);
    }

    inline std::uint8_t convert_cb(const RGBPixel &pixel) {
        return (std::uint8_t)
                (128.f
                 + (float) pixel.red * -0.101f
                 + (float) pixel.green * -0.339f
                 + (float) pixel.blue * 0.439f);
    }

    inline std::uint8_t convert_cr(const RGBPixel &pixel) {
        return (std::uint8_t)
                (16.f
                 + (float) pixel.red * 0.439f
                 + (float) pixel.green * -0.399f
                 + (float) pixel.blue * -0.040f);
    }


    template<calc_op calc>
    inline void map_bitmap(const RGBImage &image, ppeg::ComponentBitmap &ybitmap) {
        for (uint32_t y = 0; y < image.height(); ++y)
            for (uint32_t x = 0; x < image.height(); ++x) {
                const RGBPixel &pixel = image.get(x, y);
                ybitmap.data()[y * image.width() + x] = calc(pixel);
            }
    }

    // http://www.equasys.de/colorconversion.html
    ppeg::ComponentImage rgb_to_ycbcr(const RGBImage &image) {
        ppeg::ComponentImage result(image.width(), image.height(), 3);
        map_bitmap<convert_y>(image, result[0].initialize(image.width(), image.height()));
        map_bitmap<convert_cb>(image, result[1].initialize(image.width(), image.height()));
        map_bitmap<convert_cr>(image, result[2].initialize(image.width(), image.height()));
        result.validate();
        return result;
    }

    RGBImage ycbcr_to_rgb(const ppeg::ComponentImage &image) {
        RGBImage result(image.width(), image.heigth());

        return result;
    }
}

std::vector<std::uint8_t> ppeg::convert_to_ppeg(const RGBImage &image) {
    ppeg::ComponentImage compImage = rgb_to_ycbcr(image);
    int size = 3 * sizeof(std::uint32_t);
    for (size_t i = 0; i < 3; ++i)
        size += 2 * sizeof(std::uint32_t) + compImage[i].width() * compImage[i].height();
    std::vector<std::uint8_t> result(size);
    auto it = result.begin();
    write_iterator(it, compImage.width());
    write_iterator(it, compImage.heigth());
    write_iterator(it, 3);
    for (size_t i = 0; i < 3; ++i) {
        write_iterator(it, compImage[i].width());
        write_iterator(it, compImage[i].height());
        it = std::copy(compImage[i].data().begin(), compImage[i].data().end(), it);
    }
    return result;
}


RGBImage ppeg::convert_to_rgbimage(const std::vector<std::uint8_t> &data) {
    std::size_t size = 3 * sizeof(std::uint32_t);
    if (data.size() < size) throw std::range_error("binary data too big");
    auto it = data.begin();
    std::uint32_t width = read_iterator<std::uint32_t>(it);
    std::uint32_t height = read_iterator<std::uint32_t>(it);
    std::uint32_t depth = read_iterator<std::uint32_t>(it);
    if (depth != 3) throw std::range_error("I need 3 components");
    ComponentImage result(width, height, 3);
    for (size_t i = 0; i < 3; ++i) {
        size += 2 * sizeof(std::uint32_t);
        if (data.size() < size) throw std::range_error("binary data too big");
        std::uint32_t bwidth = read_iterator<std::uint32_t>(it);
        std::uint32_t bheight = read_iterator<std::uint32_t>(it);
        result[i].initialize(bwidth, bheight);
        size += result[i].data().size();
        if (data.size() < size) throw std::range_error("binary data too big");
        it = std::copy(it, it + result[i].data().size(), result[i].data().begin());
    }
    return ycbcr_to_rgb(result);
}