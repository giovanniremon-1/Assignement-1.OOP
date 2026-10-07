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
#include <algorithm>
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
            int origin_width = i * scale_width; if (origin_width >= ima.width) origin_width = ima.width - 1;
            int origin_height = j * scale_height; if (origin_height >= ima.height) origin_height = ima.height - 1;
            for (int k = 0; k < 3; k++) {
                resized(i, j, k) = ima(origin_width, origin_height, k);
            }
        }
    }
    string new_name = filenaming(filename);
    resized.saveImage(new_name);
}

Image Resizing_Image(Image& ima, int& width, int& height) {
    Image resized(width, height);
    float scale_width = (float)ima.width / width;
    float scale_height = (float)ima.height / height;
    for (int i = 0; i < width; i++) {
        int origin_width = i * scale_width; if (origin_width >= ima.width) origin_width = ima.width - 1;
        for (int j = 0; j < height; j++) {
            int origin_height = j * scale_height; if (origin_height >= ima.height) origin_height = ima.height - 1;
            for (int k = 0; k < 3; k++) {
                resized(i, j, k) = ima(origin_width, origin_height, k);
            }
        }
    }
    return resized;
}

Image Merge(Image& merged, Image& ima, Image& second_ima) {
    for (int i = 0; i < ima.width; i++) {
        for (int j = 0; j < ima.height; j++) {
            for (int k = 0; k < ima.channels; k++) {
                merged(i, j, k) = (ima(i, j, k) + second_ima(i,j,k)) / 2;
            }
        }
    }
    return merged;
}

void Merge_Images(Image& ima, Image& second_ima, const string& filename) {
    if (ima.width == second_ima.width && ima.height == second_ima.height) {
        Image merged(ima.width, ima.height);
        merged = Merge(merged, ima, second_ima);
        string new_name = filenaming(filename);
        merged.saveImage(new_name);
    }
    else {
        cout << "Choose if you want to resize the two images or intersect them :";
        string choosen;
        cin >> choosen;
        if (choosen == "resize") {
            int width = max(ima.width, second_ima.width);
            int height = max(ima.height, second_ima.height);
            ima = Resizing_Image(ima, width, height);
            second_ima = Resizing_Image(second_ima, width, height);
            Image merged(width, height);
            merged = Merge(merged, ima, second_ima);
            string new_name = filenaming(filename);
            merged.saveImage(new_name);
        }
        else if (choosen == "intersect") {
            int width = min(ima.width, second_ima.width);
            int height = min(ima.height, second_ima.height);
            Image merged(width, height);
            Merge(merged, ima, second_ima);
            merged = Merge(merged, ima, second_ima);
            string new_name = filenaming(filename);
            merged.saveImage(new_name);
        }
    }
}

void Edge_Detection(Image& ima, const string& filename) {
    Image edge(ima.width, ima.height);
    int threshold = 30;

    for (int i = 1; i < ima.width - 1; i++)
    {
        for (int j = 1; j < ima.height - 1; j++)
        {
            int current =
                (ima(i,j,0) + ima(i,j,1) + ima(i,j,2)) / 3;

            int right =
                (ima(i+1,j,0) + ima(i+1,j,1) + ima(i+1,j,2)) / 3;

            int down =
                (ima(i,j+1,0) + ima(i,j+1,1) + ima(i,j+1,2)) / 3;

            int diffRight = abs(current - right);
            int diffDown = abs(current - down);

            if (diffRight > threshold || diffDown > threshold)
            {
                edge(i,j,0) = 0;
                edge(i,j,1) = 0;
                edge(i,j,2) = 0;
            }
            else
            {
                edge(i,j,0) = 255;
                edge(i,j,1) = 255;
                edge(i,j,2) = 255;
            }
        }
    }
    string new_name = filenaming(filename);
    edge.saveImage(new_name);
}

void Wano_Brightness(Image& ima, const string& filename) {
    int brightness = 50;
    for (int i = 0; i < ima.width; i++) {
        for (int j = 0; j < ima.height; j++) {
            for (int k = 0; k < ima.channels; k++) {
                int new_value = ima(i, j, k) + brightness;
                if (new_value > 255) new_value = 255;
                ima(i, j, k) = new_value;
            }
        }
    }
    string new_name = filenaming(filename);
    ima.saveImage(new_name);
}

void Skewing_Image(Image& ima, float& degree, const string& filename) {
    float radian = degree * M_PI / 180;
    float tangent = tan(radian);
    int max_shift = abs(ima.height * tangent);
    int new_width = ima.width + max_shift;
    Image skewed(new_width, ima.height);
    for (int i = 0; i < new_width; i++) {
        for (int j = 0; j < ima.height; j++) {
            for (int k = 0; k < ima.channels; k++) {
                skewed(i, j, k) = 255;
            }
        }
    }
    for (int i = 0; i < ima.height; i++) {
        int shift = (ima.height - 1 - i) * tangent;
        for (int j = 0; j < ima.width; j++) {
            int new_j = j + shift;
            if (new_j >= 0 && new_j < new_width) {
                for (int k = 0; k < ima.channels; k++) {
                    skewed(new_j, i, k) = ima( j, i, k);
                }
            }
        }
    }
    string new_name = filenaming(filename);
    skewed.saveImage(new_name);
}

int main()
{
    while (true) {
        int x;
        cout << "1. Grayscale conversion.                10. Detect Image edges." << endl
        << "2. Black and White.                     11. Crop Image." << endl
        << "3. Invert Image.                        12. Blur Image." << endl
        << "4. Adding a Frame to the Picture.       13. Brightness." << endl
        << "5. Flip Image.                          14. Old TV view." << endl
        << "6. Rotate Image.                        15. Purple Image." << endl
        << "7. Darker or Lighter.                   16. Infrared Image." << endl
        << "8. Resizing Image.                      17. Skewing Image." << endl
        << "9. Merge Images.                        18. Oil painting." << endl
        << "\t\t\t0. Exit." << endl
        << "Enter your choice:";
        cin >> x;
        cin.ignore();
        if (x == 0)
        {
            return 0;
        }
        string filename;
        cout << "Enter your image filename (e.g.,filename.jpg):";
        getline(cin, filename);
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
        else if (x == 9)
        {
            string second_filename;
            cout << "Enter your second file name :";
            cin >> second_filename;
            Image second_ima(second_filename);
            Merge_Images(ima, second_ima, filename);
        }
        else if (x == 10) {
            Edge_detection(ima, filename);
        }
        else if (x == 13) {
            Wano_Brightness(ima, filename);
        }
        else if (x == 17) {
            cout << "Enter the skewness degree :";
            float degree;
            cin >> degree;
            Skewing_Image(ima, degree, filename);
        }
        cout << endl << "---Edited successfully---" << endl << endl;
    }
        return 0;
}