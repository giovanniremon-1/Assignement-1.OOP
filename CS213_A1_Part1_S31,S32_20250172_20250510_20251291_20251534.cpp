/*
FCAI – OOP Assignment 1 – 2026/2027
  Program Name: Image Processing Application
  Team Members:
    - Member 1: Geovanni Raymond    20250172    filters: 1, 5, 9, 13
    - Member 2: Mathieu Zaher       20250510    filters: 2, 6, 10, 14
    - Member 3: Karim Tarek        20251291    filters: 3, 7, 11, 15
    - Member 4: Retage Walid        20251534    filters: 4, 8, 12, 16
  Lab: S31,S32
*/

#include <string>
#include <cmath>
#include "Image_Class.h"
using namespace std;

string filenaming(const string& filename) {
    string s2;
    for (int i = 0; i < filename.length(); i++) {
        if (filename[i]=='.') {
            s2 +="-2.";
        }
        else {
            s2 += filename[i];
        }
    }
    return s2;
}

void Grayscale_Conversion(Image& ima, const string& filename) {
    int sum = 0;
    int average = 0;
    for (int i = 0; i < ima.width; i++) {
        for (int j = 0; j < ima.height; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += ima(i,j,k);
            }
            average = sum/3;
            for (int k = 0; k < 3; k++) {
                ima(i,j,k) = average;
            }
        }
    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Black_and_White(Image& ima, const string& filename) {
    int sum = 0;
    int average = 0;
    for (int i = 0; i < ima.width; i++) {
        for (int j = 0; j < ima.height; j++) {
            sum = 0;
            for (int k = 0; k < 3; k++) {
                sum += ima(i,j,k);
            }
            average = sum/3;
            if (average >= 127) {
                for (int k = 0; k < 3; k++) {
                    ima(i,j,k) = 255;
                }
            }
            else {
                for (int k = 0; k < 3; k++) {
                    ima(i,j,k) = 0;
                }
            }
        }
    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Invert_Image(Image &ima, const string& filename) {
    for ( int i = 0; i < ima.width; i++) {
        for ( int j = 0; j < ima.height; j++) {
            for ( int k = 0; k < ima.channels; k++) {
                ima(i,j,k) = 255 - ima (i,j,k);
            }
        }
    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Frame(Image& ima, const string& filename) {
    int frame = 20;
    for (int i = 0; i < ima.width; i++) {
        for (int j = 0; j < ima.height; j++) {
            if (i < frame || i >= ima.width - frame || j < frame || j >= ima.height - frame) {
                ima(i, j, 0) = 0;
                ima(i, j, 1) = 100;
                ima(i, j, 2) = 255;
            }
        }

    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Flip_Image(Image& ima, const string& filename) {
    string choosen;
    cout << "Horizontal or Vertical flipping: ";
    cin >> choosen;
    if (choosen == "horizontal") {
        int flipped_i = 0;
        Image ima2(ima.width,ima.height);
        for (int i = 0; i < ima.width; i++) {
            flipped_i = ima.width - i - 1;
            for (int j = 0; j < ima.height; j++) {
                ima2(flipped_i,j,0) = ima(i,j,0);
                ima2(flipped_i,j,1) = ima(i,j,1);
                ima2(flipped_i,j,2) = ima(i,j,2);
            }
        }
        string new_name = filenaming(filename);
        ima2.saveImage(new_name);
    }
    else if (choosen == "vertical") {
        int flipped_j = 0;
        Image ima2(ima.width,ima.height);
        for (int i = 0; i < ima.width; i++) {

            for (int j = 0; j < ima.height; j++) {
                flipped_j = ima.height - j - 1;
                ima2(i,flipped_j,0) = ima(i,j,0);
                ima2(i,flipped_j,1) = ima(i,j,1);
                ima2(i,flipped_j,2) = ima(i,j,2);
            }
        }
        string new_name = filenaming(filename);
        ima2.saveImage(new_name);
    }
}

void Rotate_Image(Image& ima, const string& filename) {
    int choice = 0 ;
    cout << "Enter rotation (90, 180, or 270): ";
    cin >> choice;
    if (choice == 90) {
        Image rotated(ima.height, ima.width);
        for (int i = 0; i < ima.width; i++) {
            for (int j = 0; j < ima.height; j++) {
                for (int k = 0; k < ima.channels; k++) {
                    rotated(ima.height - 1 - j, i,  k) = ima(i, j, k);
                }
            }
        }
        string new_name = filenaming(filename);
        rotated.saveImage(new_name);
    }
    else if (choice == 180) {
        Image rotated(ima.width, ima.height);
        for (int i = 0; i < ima.width; i++) {
            for (int j = 0; j < ima.height; j++) {
                for (int k = 0; k < ima.channels; k++) {
                    rotated(ima.width - 1 - i, ima.height - 1 - j, k) = ima(i, j, k);
                }
            }
        }
        string new_name = filenaming(filename);
        rotated.saveImage(new_name);
    }
    else if (choice == 270) {
        Image rotated(ima.height, ima.width);
        for (int i = 0; i < ima.width; i++) {
            for (int j = 0; j < ima.height; j++) {
                for (int k = 0; k < ima.channels; k++) {
                    rotated( j, ima.width - 1 - i, k) = ima(i, j, k);
                }
            }
        }
        string new_name = filenaming(filename);
        rotated.saveImage(new_name);
    }
    else {
        cout << "Invalid rotation!" << endl;
    }
}

void Darken_and_Lighten_Image(Image &ima, const string& filename) {
    string choosen;
    cout << "Darker or Lighter: ";
    cin >> choosen;
    for ( int i = 0; i <ima.width; i++) {

        for ( int j = 0; j <ima.height; j++) {

            for ( int k = 0; k <ima.channels; k++) {

                if (choosen == "darker") {
                    ima(i,j,k) = ima(i,j,k) * 0.5;
                }

                else if (choosen == "lighter") {
                    ima(i, j, k) = ima(i, j, k) + (255 - ima(i, j, k)) * 0.5;
                }
            }
        }
    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Resizing_Image(Image& ima, const string& filename) {
    int width, height;
    char x;
    cout << "Enter the new width and height (e.g., 800 x 600):";
    cin >> width >> x >> height;
    Image resized(width, height);
    float scale_width = (float)ima.width / width;
    float scale_height = (float)ima.height / height;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            int origin_width = round(i * scale_width); if (origin_width >= ima.width) origin_width = ima.width - 1;
            int origin_height = round(j * scale_height); if (origin_height >= ima.height) origin_height = ima.height - 1;
            for (int k = 0; k < 3; k++) {
                resized(i, j, k) = ima(origin_width, origin_height, k);
            }
        }
    }
    string new_name = filenaming(filename);
    resized.saveImage(new_name);
}

int main()
{
    while (true) {
        int x;
        cout << "1. Grayscale conversion. " << endl
        << "2. Black and White. " << endl
        << "3. Invert Image. " << endl
        << "4. Adding a Frame to the Picture. " << endl
        << "5. Flip image. " << endl
        << "6. Rotate Image. " << endl
        << "7. Darker or Lighter. " << endl
        << "8. Resizing Image. " << endl
        << "9. Exit." << endl
        << "Enter your choice:";
        cin >> x;
        if (x == 9)
        {
            return 0;
        }
        string filename;
        cout << "Enter your image filename (e.g.,filename.jpg):";
        cin >> filename;
        Image ima(filename);
        if (x == 1)
        {
            Grayscale_Conversion(ima, filename);
        }
        else if (x == 2)
        {
            Black_and_White(ima, filename);
        }
        else if (x == 3)
        {
            Invert_Image(ima, filename);
        }
        else if (x == 4)
        {
            Frame(ima, filename);
        }
        else if (x == 5)
        {
            Flip_Image(ima, filename);
        }
        else if (x == 6)
        {
            Rotate_Image(ima, filename);
        }
        else if (x == 7)
        {
            Darken_and_Lighten_Image(ima, filename);
        }
        else if (x == 8) {
            Resizing_Image(ima, filename);
        }
        cout << endl << "---Edited successfully---" << endl << endl;
    }
        return 0;
}