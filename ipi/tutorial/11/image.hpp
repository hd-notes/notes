#ifndef IMAGE_HPP
#define IMAGE_HPP

#include <cstdint>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

class Image {
    int                   width_;
    int                   height_;
    std::vector<uint16_t> data_;

	/*
	 * Für positive Indizes entspricht die periodische Randbedingung genau der Modulo Operation.
	 * Für negative Indizes muss der Wert erst ins Positive gebracht werden.
	 */
    uint16_t get_periodic_impl(int a, int boundary) const {
        return ((a % boundary) + boundary) % boundary;
    }

public:
    // Standardkonstruktor: initialisiere Bild mit Groesse (0,0)
    Image() : width_(0), height_(0) {}

    // Konstruktor: initialisiere Bild mit Groesse (width, height)
    // Alle Pixel sollen danach den Wert '0' haben.
    Image(unsigned int width, unsigned int height)
        : width_(width), height_(height), data_(width * height, uint16_t()) {}

    // Breite abfragen
    int width() const { return width_; }

    // Hoehe abfragen
    int height() const { return height_; }

    // Gesamtzahl der Pixel abfragen
    int size() const { return width_ * height_; }

    // Groesse der Bildes aendern
    void resize(unsigned int new_width, unsigned int new_height) {
        data_.resize(new_width * new_height, uint16_t());
        width_  = new_width;
        height_ = new_height;
    }

    uint16_t get_periodic(int x, int y) const {
		return data_[get_periodic_impl(x, width_) + get_periodic_impl(y, height_) * width_];
	}

    // lesender Zugriff auf des Pixel an Position (x,y)
    uint16_t operator()(int x, int y) const { return data_[x + y * width_]; }

    // Lese/Schreib-Zugriff auf des Pixel an Position (x,y)
    uint16_t & operator()(int x, int y) { return data_[x + y * width_]; }
};

// Gib 'true' zurueck, wenn die gegebenen Bilder gleich sind.
// Dies ist der Fall, wenn die Bildgroessen uebereinstimmen und
// alle Pixel die gleichen Werte haben.
// Diese Funktion ist nuetzlich zum Testen der Bildklasse.
bool operator==(Image const & im0, Image const & im1) {
    if(im0.width() != im1.width() || im0.height() != im1.height()) {
        return false;
    }

    for(int y = 0; y < im0.height(); ++y) {
        for(int x = 0; x < im0.width(); ++x) {
            if(im0(x, y) != im1(x, y)) { return false; }
        }
    }
    return true;
}

// Wandle die Pixelwerte zeilenweise in einen String.
// Für ein Bild der Groesse 4x3, das die Pixelwerte 0 und 1
// in Schachbrett-Anordnung enthaelt, soll z.B. der String
//         "0 1 0 1\n1 0 1 0\n0 1 0 1\n"
// zurueckgegeben werden (Pixelwerte sind durch Leerzeichen
// getrennt, am Ende jeder Zeile steht ein Enter-Zeichen '\n').
std::string to_string(Image const & im) {
    std::string res;
    for(int y = 0; y < im.height(); ++y) {
        for(int x = 0; x < im.width(); ++x) {
            res += std::to_string(im(x, y));
            if(x < im.width() - 1) res += ' ';
        }
        res += '\n';
    }
    return res;
}

// Gib das Bild im PGM-Format in das File 'filename' aus.
//
// Die Bilddatei kann mit allen Bildbetrachtern angezeigt
// werden, die das PGM-Format unterstuetzen (unter Windows
// z.B. 'IrfanView', unter Linux z.B. 'display' aus der
// imagemagick-Installation, ueberall 'gimp').
//
// Da das PGM-Format ein Textformat ist, kann man es zum
// Debuggen auch im Editor oeffnen und ueberpruefen.
void writePGM(Image const & img, std::string const & filename) {
    // Filestream erzeugen
    std::ofstream pgm(filename, std::ios::binary);

    // Fehlermeldung, wenn sich das File nicht oeffnen laesst.
    if(!pgm) {
        throw std::runtime_error("writePGM(): cannot open file '" + filename +
                                 "'.");
    }

    // Headerinformationen schreiben
    int max_pixelvalue = 255;
    pgm << "P2\n"
        << img.width() << " " << img.height() << "\n"
        << max_pixelvalue << "\n";

    // Bilddaten schreiben (verwendet Ihre Funktion 'to_string').
    pgm << to_string(img);
}

// Gib 'true' zurueck, wenn das File 'filename' das PGM-Format hat.
bool checkPGM(std::string const & filename) {
    std::ifstream pgm(filename);
    std::string   line;

    // Teste, ob das File geoeffnet werden kann und
    // mindestens eine Zeile hat.
    if(!std::getline(pgm, line)) { return false; }

    // Teste, dass die erste Zeile der String "P2" ist.
    return line == "P2";
}

// Lese das File 'filename' (im PGM-Format) ein und gib das resultierende
// Bild zurueck.
Image readPGM(std::string const & filename) {
    // Fehlermeldung, wenn sich das File nicht oeffnen laesst
    // oder kein PGM-File ist.
    if(!checkPGM(filename)) {
        throw std::runtime_error("readPGM(): File '" + filename +
                                 "' is not PGM.");
    }

    // Filestream erzeugen
    std::ifstream pgm(filename);
    std::string   line;

    // erste Zeile einlesen (enthaelt den String "P2")
    std::getline(pgm, line);

    // eventuelle Kommentarzeilen ueberspringen
    while(pgm.peek() == '#') { std::getline(pgm, line); }

    // Breite und Hoehe einlesen
    int width, height;
    pgm >> width >> height;

    // maximalen Grauwert einlesen und Fehlermeldung ausgeben, falls zu gross
    int max_value;
    pgm >> max_value;
    if(max_value > 255) {
        throw std::runtime_error("readPGM(): max value must be <= 255.");
    }

    // Ergebnisbild der gewuenschten Groesse erzeugen
    Image res(width, height);

    // Pixeldaten in einer zweifach geschachtelten Schleife ueber
    // die Zeilen und Spalten einlesen.

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) { pgm >> res(x, y); }
    }

    return res;
}

#endif // IMAGE_HPP
