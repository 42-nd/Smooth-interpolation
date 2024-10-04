#include "Point.h"
#include "Cubic_interpolation_spline_1D.h"
#include "Smoothing_Spline_1D.h"
#include <iostream> 
#include <algorithm> 
#include <cmath>
#include <random>
#include <string>
#include <sstream>
#include <fstream>
# define M_PI 3.14159265358979323846

int points_size = 1363;

void save_to_file(const std::vector<double>& values_y,
    const std::vector<double>& interpolated,
    const std::vector<double>& smoothed0,
    const std::vector<double>& smoothed4,
    const std::vector<double>& smoothed8,
    const std::vector<double>& smoothed99,
    const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (size_t i = 0; i < points_size; ++i) {
            file << values_y[i] << " "
                << interpolated[i] << " "
                << smoothed0[i] << " "
                << smoothed4[i] << " "
                << smoothed8[i] << " "
                << smoothed99[i] << "\n";
        }
        file.close();
    }
    else {
        std::cout << "Unable to open file for writing: " << filename << std::endl;
    }
}

int main() {

    Com_Methods::Cubic_Interpolation_Spline_1D interpolation_spline;
    Com_Methods::Smoothing_Spline_1D smoothing_spline_0(0);
    Com_Methods::Smoothing_Spline_1D smoothing_spline_4(0.4);
    Com_Methods::Smoothing_Spline_1D smoothing_spline_8(0.8);
    Com_Methods::Smoothing_Spline_1D smoothing_spline_99(0.99);
    double mean = 1.02, stddev = 4.61,num_points = points_size;
    std::vector<double> values_y, interpolated, smoothed0, smoothed4, smoothed8, smoothed99;
    //std::vector<double> interpolated, smoothed0, smoothed4, smoothed8, smoothed99;
    //std::vector<double> values_y = { 0.532396358, -3.508040518, 1.19580284, 3.190684949, 3.138327355 };  // Заданные случайные величины
    std::vector<Com_Methods::Point> values_x;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<> dist(mean, stddev);
    for (int i = 0; i < num_points; ++i) {
        double x = i;  // Просто равномерное распределение по оси X
        double y = dist(gen);  // Нормальное распределение по оси Y
        values_y.push_back(y);
        values_x.push_back(Com_Methods::Point(x, 0,0));
    }


    double result_inter[3], result_smooth0[3], result_smooth4[3], result_smooth8[3], result_smooth99[3];
    interpolation_spline.Update_Spline(values_x, values_y);
    smoothing_spline_0.Update_Spline(values_x, values_y);
    smoothing_spline_4.Update_Spline(values_x, values_y);
    smoothing_spline_8.Update_Spline(values_x, values_y);
    smoothing_spline_99.Update_Spline(values_x, values_y);
    for (int i = 0; i < points_size; i++) {
        interpolation_spline.Get_Value(values_x[i], result_inter);
        smoothing_spline_0.Get_Value(values_x[i], result_smooth0);
        smoothing_spline_4.Get_Value(values_x[i], result_smooth4);
        smoothing_spline_8.Get_Value(values_x[i], result_smooth8);
        smoothing_spline_99.Get_Value(values_x[i], result_smooth99);
        interpolated.push_back(result_inter[0]);
        smoothed0.push_back(result_smooth0[0]);
        smoothed4.push_back(result_smooth4[0]);
        smoothed8.push_back(result_smooth8[0]);
        smoothed99.push_back(result_smooth99[0]);
        std::cout  << " Original Y: " << values_y[i] << " Interpolated: "
            << result_inter[0] << " Smoothed p = 0: " << result_smooth0[0] << " Smoothed p = 0.4: " << result_smooth4[0] << " Smoothed p = 0.8: " << result_smooth8[0] << " Smoothed p = 0.99: " << result_smooth99[0] << std::endl;
    }
    std::string filename = "spline_data.txt";
    save_to_file(values_y, interpolated, smoothed0, smoothed4, smoothed8, smoothed99, filename);
    // Optionally, run the Python script to plot the data
    std::string command = "python3 plot.py " + filename;
    system(command.c_str());
    return 0;
}