#ifndef IMAGE_RGB_HPP
#define IMAGE_RGB_HPP

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>
#include <cstdint>
#include <cmath>

class RGBColor
{
    uint16_t red_, green_, blue_;

  public:

    RGBColor()
    : red_(0)
    , green_(0)
    , blue_(0)
    {}

    RGBColor(uint16_t red, uint16_t green, uint16_t blue)
    : red_(red)
    , green_(green)
    , blue_(blue)
    {}

    uint16_t red() const
    {
        return red_;
    }

    uint16_t green() const
    {
        return green_;
    }

    uint16_t blue() const
    {
        return blue_;
    }

    bool operator==(RGBColor const & other) const
    {
        return red_ == other.red_ && green_ == other.green_ && blue_ == other.blue_;
    }

    bool operator!=(RGBColor const & other) const
    {
        return red_ != other.red_ || green_ != other.green_ || blue_ != other.blue_;
    }
};

RGBColor hsv_to_rgb(double H, double S, double V)
{
    double h = std::floor(H / 60.0),
           f = H / 60.0 - h;
    uint16_t p = uint16_t(255.0*V*(1.0 - S)),
             q = uint16_t(255.0*V*(1.0 - S*f)),
             t = uint16_t(255.0*V*(1.0 - S*(1.0 - f))),
             v = uint16_t(255.0*V);

    if(h == 0.0 || h == 6.0)
    {
        return RGBColor(v, t, p);
    }
    if(h == 1.0)
    {
        return RGBColor(q, v, p);
    }
    if(h == 2.0)
    {
        return RGBColor(p, v, t);
    }
    if(h == 3.0)
    {
        return RGBColor(p, q, v);
    }
    if(h == 4.0)
    {
        return RGBColor(t, p, v);
    }
    // (h == 5.0)
    return RGBColor(v, p, q);
}

template <typename PixelType>
class Image
{
    int width_;
    int height_;
    std::vector<PixelType> data_;

public:

        // Standardkonstruktor: initialisiere Bild mit Groesse (0,0)
    Image()
    : width_(0)
    , height_(0)
    {}

        // Konstruktor: initialisiere Bild mit Groesse (width, height)
        // Alle Pixel sollen danach den Wert '0' haben.
    Image(unsigned int width, unsigned int height)
    : width_(width)
    , height_(height)
    , data_(width*height, PixelType())
    {}

        // Breite abfragen
    int width() const
    {
        return width_;
    }

        // Hoehe abfragen
    int height() const
    {
        return height_;
    }

        // Gesamtzahl der Pixel abfragen
    int size() const
    {
        return width_*height_;
    }

        // Groesse der Bildes aendern
    void resize(unsigned int new_width, unsigned int new_height)
    {
        data_.resize(new_width*new_height, PixelType());
        width_  = new_width;
        height_ = new_height;
    }

        // lesender Zugriff auf des Pixel an Position (x,y)
    PixelType operator()(int x, int y) const
    {
        return data_[x + y*width_];
    }

        // Lese/Schreib-Zugriff auf des Pixel an Position (x,y)
    PixelType & operator()(int x, int y)
    {
        return data_[x + y*width_];
    }
};

    // Gib 'true' zurueck, wenn die gegebenen Bilder gleich sind.
    // Dies ist der Fall, wenn die Bildgroessen uebereinstimmen und
    // alle Pixel die gleichen Werte haben.
    // Diese Funktion ist nuetzlich zum Testen der Bildklasse.
template <typename PixelType>
bool operator==(Image<PixelType> const & im0, Image<PixelType> const & im1)
{
    if(im0.width() != im1.width() || im0.height() != im1.height())
    {
        return false;
    }

    for(int y=0; y<im0.height(); ++y)
    {
        for(int x=0; x<im0.width(); ++x)
        {
            if(im0(x,y) != im1(x,y))
            {
                return false;
            }
        }
    }
    return true;
}

    // Wandle die Pixelwerte zeilenweise in einen String.
std::string to_string(Image<RGBColor> const & im)
{
    std::string res;
    for(int y=0; y<im.height(); ++y)
    {
        for(int x=0; x<im.width(); ++x)
        {
            res += std::to_string(im(x,y).red()) + ' ' +
                   std::to_string(im(x,y).green()) + ' ' +
                   std::to_string(im(x,y).blue()) + ' ';
            if(x < im.width()-1)
                res += ' ';
        }
        res += '\n';
    }
    return res;
}

    // Gib das Bild im PPM-Format in das File 'filename' aus.
    // Der Filename muss auf ".ppm" enden.
    //
    // Die Bilddatei kann mit allen Bildbetrachtern angezeigt
    // werden, die das PPM-Format unterstuetzen (unter Windows
    // z.B. 'IrfanView', unter Linux z.B. 'display' aus der
    // imagemagick-Installation, ueberall 'gimp').
    //
    // Da das PPM-Format ein Textformat ist, kann man es zum
    // Debuggen auch im Editor oeffnen und ueberpruefen.
void writePPM(Image<RGBColor> const & img, std::string const & filename)
{
    // Filestream erzeugen
    std::ofstream ppm(filename, std::ios::binary);

    // Fehlermeldung, wenn sich das File nicht oeffnen laesst.
    if (!ppm)
    {
        throw std::runtime_error("writePPM(): cannot open file '" + filename + "'.");
    }

    // Headerinformationen schreiben
    int max_pixelvalue = 255;
    ppm << "P3\n"
        << img.width() << " " << img.height() << "\n"
        << max_pixelvalue << "\n";

    // Bilddaten schreiben (verwendet Ihre Funktion 'to_string').
    ppm << to_string(img);
}

    // Gib 'true' zurueck, wenn das File 'filename' das PPM-Format hat.
bool checkPPM(std::string const & filename)
{
    std::ifstream ppm(filename);
    std::string line;

    // Teste, ob das File geoeffnet werden kann und
    // mindestens eine Zeile hat.
    if (!std::getline(ppm, line))
    {
        return false;
    }

    // Teste, dass die erste Zeile der String "P3" ist.
    return line == "P3";
}

    // Lese das File 'filename' (im PPM-Format) ein und gib das resultierende
    // Bild zurueck.
Image<RGBColor> readPPM(std::string const & filename)
{
    // Fehlermeldung, wenn sich das File nicht oeffnen laesst
    // oder kein PPM-File ist.
    if (!checkPPM(filename))
    {
        throw std::runtime_error("readPPM(): File '" + filename + "' is not PPM.");
    }

    // Filestream erzeugen
    std::ifstream ppm(filename);
    std::string line;

    // erste Zeile einlesen (enthaelt den String "P3")
    std::getline(ppm, line);

    // eventuelle Kommentarzeilen ueberspringen
    while (ppm.peek() == '#')
    {
        std::getline(ppm, line);
    }

    // Breite und Hoehe einlesen
    int width, height;
    ppm >> width >> height;

    // maximalen Grauwert einlesen und Fehlermeldung ausgeben, falls zu gross
    int max_value;
    ppm >> max_value;
    if (max_value > 255)
    {
        throw std::runtime_error("readPPM(): max value must be <= 255.");
    }

    // Ergebnisbild der gewuenschten Groesse erzeugen
    Image<RGBColor> res(width, height);

    // Pixeldaten in einer zweifach geschachtelten Schleife ueber
    // die Zeilen und Spalten einlesen.

    for(int y=0; y<height; ++y)
    {
        for(int x=0; x<width; ++x)
        {
            uint16_t red, green, blue;
            ppm >> red >> green >> blue;
            res(x,y) = RGBColor(red, green, blue);
        }
    }

    return res;
}

#endif // IMAGE_RGB_HPP
