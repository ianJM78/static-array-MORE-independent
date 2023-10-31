#include <iostream>
#include <cstdlib> // Para generar números aleatorios
#include <ctime>   // Para inicializar la semilla aleatoria
#include <cstring>
#include <cctype>
#include <fstream>
#include <string>
using namespace std;

const int REGION_COUNT = 6;

struct file
{
    int  regionNumber;
    int rainAmount;
    int past_rainAmount;
};

struct precipitation
{
    int region;
    int times_it_rained;
    int totalRain;
    int totalPastRain;
};

class rainAnalyzer
{
private:
    file FILE_ARRAY[100];
    precipitation PRECIPITACION_ARRAY[REGION_COUNT];
public:
    rainAnalyzer();
    void set_fileVector(ifstream& value,int* FILE_array_size);
    void update_PRECIPITATION_array(int* FILE_array_size);
    file* get_FILE_array();
    precipitation* get_PRECIPITATION_array();
};

rainAnalyzer::rainAnalyzer()
{
    for (int i = 0; i < REGION_COUNT; i++)
    {
        PRECIPITACION_ARRAY[i].region = (i+1);   //! From 1 to REGION_COUNT.
        PRECIPITACION_ARRAY[i].times_it_rained = 0;
        PRECIPITACION_ARRAY[i].totalRain = 0;
        PRECIPITACION_ARRAY[i].totalPastRain = 0;
    }
}

void rainAnalyzer ::set_fileVector(ifstream& value,int* FILE_array_size)
{
    value >> FILE_ARRAY[*FILE_array_size].regionNumber >> FILE_ARRAY[*FILE_array_size].rainAmount >> FILE_ARRAY[*FILE_array_size].past_rainAmount;
}

void rainAnalyzer ::update_PRECIPITATION_array(int* FILE_array_size) 
{
    // for all elmenents is FILE array
    for (int i = 0; i < *FILE_array_size; i++)
    {
        // We get the value of the region at the "i" iteration
        int auxiliary = FILE_ARRAY[i].regionNumber;

        //* if its 1, we access the PRECIPITATION vector at the index equivalent to the region we are on currently itterating on the FILE array (region number - 1) and modify values to the required values in said vector
        PRECIPITACION_ARRAY[auxiliary - 1].totalRain += FILE_ARRAY[i].rainAmount;
        PRECIPITACION_ARRAY[auxiliary - 1].totalPastRain += FILE_ARRAY[i].past_rainAmount;
        PRECIPITACION_ARRAY[auxiliary - 1].times_it_rained++;
    }     
}


precipitation *rainAnalyzer::get_PRECIPITATION_array()
{
    return PRECIPITACION_ARRAY;
}

file *rainAnalyzer::get_FILE_array()
{
    return FILE_ARRAY;
}


//!    IMPORTANT

//!    GETTING THE DIRECCION OF THE ARRAYS FROM THE CLASS IS POINTLESS
//!    IT DEFEATS THE POINT OF THEM ONLY BEING ACCESIBLE BY METHODS


void create_file_with_Precipitation_array(struct precipitation PRECIPITATION_ARRAY[],string path)
{
    ofstream values(path);
    for (int i = 0; i < REGION_COUNT; i++)
    {
        values << PRECIPITATION_ARRAY[i].region << " | " << PRECIPITATION_ARRAY[i].totalRain << " | " << (PRECIPITATION_ARRAY[i].totalRain / PRECIPITATION_ARRAY[i].times_it_rained)
        << " | " << abs((PRECIPITATION_ARRAY[i].totalRain / PRECIPITATION_ARRAY[i].times_it_rained) - (PRECIPITATION_ARRAY[i].totalPastRain / PRECIPITATION_ARRAY[i].times_it_rained))
        << endl;
    }
    
}


void Smallest_to_largest(struct precipitation PRECIPITATION_ARRAY[],string path)
{
    for (int i = 1; i < REGION_COUNT; i++)
    {

        precipitation key = PRECIPITATION_ARRAY[i];

        int j = i - 1;

        while (j >= 0 && PRECIPITATION_ARRAY[j].totalRain > key.totalRain)
        {
            PRECIPITATION_ARRAY[j+1] = PRECIPITATION_ARRAY[j];
            j--;
        }
        

        PRECIPITATION_ARRAY[j+1] = key;
    }
    create_file_with_Precipitation_array(PRECIPITATION_ARRAY, path);

}
void largest_to_smallest(struct precipitation PRECIPITATION_ARRAY[],string path)
{
    for (int i = 1; i < REGION_COUNT; i++)
    {

        precipitation key = PRECIPITATION_ARRAY[i];

        int j = i - 1;

        while (j >= 0 && PRECIPITATION_ARRAY[j].totalRain < key.totalRain)
        {
            PRECIPITATION_ARRAY[j+1] = PRECIPITATION_ARRAY[j];
            j--;
        }
        

        PRECIPITATION_ARRAY[j+1] = key;
    }
    create_file_with_Precipitation_array(PRECIPITATION_ARRAY, path);
}

int main()
{
    int FILE_array_size = 0;
    string path = "C:/UNI/2 nd Parcial/texto.txt";
    string path_2 = "C:/UNI/2 nd Parcial/Small_Large.txt";
    string path_3 = "C:/UNI/2 nd Parcial/Large_Smalll.txt";

    rainAnalyzer RAIN;
    ifstream values(path);
    
    while (!values.eof())
    {
        RAIN.set_fileVector(values,&FILE_array_size);
        FILE_array_size++;
    }

    //? UPDATE Preceipitation array
    RAIN.update_PRECIPITATION_array(&FILE_array_size);

    //? GET File array and PRINT it

    file* FILE_ARRAY = RAIN.get_FILE_array();

    for (int i = 0; i < FILE_array_size; i++)
    {
        cout << FILE_ARRAY[i].regionNumber << " | " 
        << FILE_ARRAY[i].rainAmount << " | " 
        << FILE_ARRAY[i].past_rainAmount << endl;

    }
    

    //? GET Precipitation Array, SORT it and CREATE file
    precipitation* PRECIPITATION_ARRAY = RAIN.get_PRECIPITATION_array();

    Smallest_to_largest(PRECIPITATION_ARRAY,path_2);
    largest_to_smallest(PRECIPITATION_ARRAY,path_3);


    
    
}