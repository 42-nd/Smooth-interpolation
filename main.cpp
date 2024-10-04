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

void save_to_file(const std::vector<double>& values_y,
    const std::vector<double>& interpolated,
    const std::vector<double>& smoothed0,
    const std::vector<double>& smoothed4,
    const std::vector<double>& smoothed8,
    const std::vector<double>& smoothed99,
    const std::string& filename) {
    std::ofstream file(filename);

    if (file.is_open()) {
        for (size_t i = 0; i < 5; ++i) {
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
    double mean = 1.02, stddev = 4.61,num_points = 1363;
    std::vector<double> values_y, interpolated, smoothed0, smoothed4, smoothed8, smoothed99;
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
    for (int i = 0; i < 5; i++) {
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
    //for (int i = 0; i < num_points; ++i) {
    //    std::cout << values_x[i].x() << " " << values_x[i].y() << std::endl; 
    //}
    //std::string filename = "samples.txt";
    //save_to_file(values_x, filename);
    //std::string command = "python3 plot.py " + filename;
    //system(command.c_str());

    //double a = 0;
    //double b = 1;
    //int parts = 10; // количество частей
    //double sparse = 1; 

    //std::vector<Com_Methods::Point> grid_h = grid_generator(a, b, parts, sparse);

    //std::cout << "Grid: h = 0.1" << std::endl;
    //std::cout << "X|f(x)" << std::endl;
    //std::vector<double> values;
    //for (const auto& point : grid_h) {
    //    std::cout << point.x() << " " << pow(point.x(),4) - 2  << std::endl;
    //    values.push_back(pow(point.x(), 4) - 2);
    //}
    //std::cout << "                                        " << std::endl;

    //
    //spline.Update_Spline(grid_h, values);
    //std::vector<Com_Methods::Point> intermediate_points_h = generate_intermediate_points(grid_h, 1);

    //std::vector<double> errors_f;
    //std::vector<double> errors_f_prime;
    //std::vector<double> errors_f_double_prime;
    //double max_error_f = -1 , max_error_f_prime = -1, max_error_f_double_prime = -1;
    //double result[3];
    //for (const auto& point : intermediate_points_h) {
    //    spline.Get_Value(point, result);
    //    double x = point.x();
    //    double f_x = pow(x, 4) - 2;
    //    double f_prime_x = 4 * pow(x, 3);
    //    double f_double_prime_x = 12 * pow(x, 2);
    //    errors_f.push_back(fabs(f_x - result[0]));
    //    errors_f_prime.push_back(fabs(f_prime_x - result[1]));
    //    errors_f_double_prime.push_back(fabs(f_double_prime_x - result[2]));
    //    max_error_f = std::max(max_error_f, fabs(f_x - result[0]));
    //    max_error_f_prime = std::max(max_error_f_prime, fabs(f_prime_x - result[1]));
    //    max_error_f_double_prime = std::max(max_error_f_double_prime, fabs(f_double_prime_x - result[2]));
    //    std::cout << "x = " << x << ", f(x) = " << f_x << ", f'(x) = " << f_prime_x << ", f''(x) = " << f_double_prime_x << ", s(x) = " << result[0] << ", s'(x) = " << result[1] << ", s''(x) = " << result[2] << std::endl;
    //}
    //std::cout << "                                        " << std::endl;
    //std::cout << "Errors:" << std::endl;
    //std::cout << "|f - s|       |f' - s'|    |f'' - s''|" << std::endl;
    //for (int i = 0; i < errors_f.size(); i++) {
    //    std::cout << errors_f[i] << " | " << errors_f_prime[i] << " | " << errors_f_double_prime[i] << std::endl;
    //}
    //std::cout << "Max:" << std::endl;
    //std::cout << max_error_f << " | " << max_error_f_prime << " | " << max_error_f_double_prime << std::endl;

    //std::cout << "-----------------------------------------------" << std::endl;


    //values.clear();
    //errors_f.clear();
    //errors_f_prime.clear();
    //errors_f_double_prime.clear();
    //max_error_f = -1;
    //max_error_f_prime = -1;
    //max_error_f_double_prime = -1;

    //std::vector<Com_Methods::Point> grid_h2 = grid_generator(a, b, parts * 2, sparse);

    //std::cout << "Grid: h = 0.05" << std::endl;
    //std::cout << "X|f(x)" << std::endl;
    //for (const auto& point : grid_h2) {
    //    std::cout << point.x() << " " << pow(point.x(), 4) - 2 << std::endl;
    //    values.push_back(pow(point.x(), 4) - 2);
    //}
    //std::cout << "                                        " << std::endl;

    //Com_Methods::Cubic_Interpolation_Spline_1D spline_h2;
    //spline_h2.Update_Spline(grid_h2, values);
    ////std::vector<Com_Methods::Point> intermediate_points_h2 = generate_intermediate_points(grid_h2, 1);

    //for (const auto& point : intermediate_points_h) {
    //    spline_h2.Get_Value(point, result);
    //    double x = point.x();
    //    double f_x = pow(x, 4) - 2;
    //    double f_prime_x = 4 * pow(x, 3);
    //    double f_double_prime_x = 12 * pow(x, 2);
    //    errors_f.push_back(fabs(f_x - result[0]));
    //    errors_f_prime.push_back(fabs(f_prime_x - result[1]));
    //    errors_f_double_prime.push_back(fabs(f_double_prime_x - result[2]));
    //    max_error_f = std::max(max_error_f, fabs(f_x - result[0]));
    //    max_error_f_prime = std::max(max_error_f_prime, fabs(f_prime_x - result[1]));
    //    max_error_f_double_prime = std::max(max_error_f_double_prime, fabs(f_double_prime_x - result[2]));
    //    std::cout << "x = " << x << ", f(x) = " << f_x << ", f'(x) = " << f_prime_x << ", f''(x) = " << f_double_prime_x << ", s(x) = " << result[0] << ", s'(x) = " << result[1] << ", s''(x) = " << result[2] << std::endl;
    //}
    //std::cout << "                                        " << std::endl;
    //std::cout << "Errors:" << std::endl;
    //std::cout << "|f - s|       |f' - s'|    |f'' - s''|" << std::endl;
    //for (int i = 0; i < errors_f.size(); i++) {
    //    std::cout << errors_f[i] << " | " << errors_f_prime[i] << " | " << errors_f_double_prime[i] << std::endl;
    //}
    //std::cout << "Max:" << std::endl;
    //std::cout << max_error_f << " | " << max_error_f_prime << " | " << max_error_f_double_prime << std::endl;

    //std::cout << "-----------------------------------------------" << std::endl;


    //values.clear();
    //errors_f.clear();
    //errors_f_prime.clear();
    //errors_f_double_prime.clear();
    //max_error_f = -1;
    //max_error_f_prime = -1;
    //max_error_f_double_prime = -1;

    //std::vector<Com_Methods::Point> grid_h4 = grid_generator(a, b, parts * 4, sparse);

    //std::cout << "Grid: h = 0.025" << std::endl;
    //std::cout << "X|f(x)" << std::endl;
    //for (const auto& point : grid_h4) {
    //    std::cout << point.x() << " " << pow(point.x(), 4) - 2 << std::endl;
    //    values.push_back(pow(point.x(), 4) - 2);
    //}
    //std::cout << "                                        " << std::endl;

    //Com_Methods::Cubic_Interpolation_Spline_1D spline_h4;
    //spline_h4.Update_Spline(grid_h4, values);
    ////std::vector<Com_Methods::Point> intermediate_points_h4 = generate_intermediate_points(grid_h4, 1);

    //for (const auto& point : intermediate_points_h) {
    //    spline_h4.Get_Value(point, result);
    //    double x = point.x();
    //    double f_x = pow(x, 4) - 2;
    //    double f_prime_x = 4 * pow(x, 3);
    //    double f_double_prime_x = 12 * pow(x, 2);
    //    errors_f.push_back(fabs(f_x - result[0]));
    //    errors_f_prime.push_back(fabs(f_prime_x - result[1]));
    //    errors_f_double_prime.push_back(fabs(f_double_prime_x - result[2]));
    //    max_error_f = std::max(max_error_f, fabs(f_x - result[0]));
    //    max_error_f_prime = std::max(max_error_f_prime, fabs(f_prime_x - result[1]));
    //    max_error_f_double_prime = std::max(max_error_f_double_prime, fabs(f_double_prime_x - result[2]));
    //    std::cout << "x = " << x << ", f(x) = " << f_x << ", f'(x) = " << f_prime_x << ", f''(x) = " << f_double_prime_x << ", s(x) = " << result[0] << ", s'(x) = " << result[1] << ", s''(x) = " << result[2] << std::endl;
    //}
    //std::cout << "                                        " << std::endl;
    //std::cout << "Errors:" << std::endl;
    //std::cout << "|f - s|       |f' - s'|    |f'' - s''|" << std::endl;
    //for (int i = 0; i < errors_f.size(); i++) {
    //    std::cout << errors_f[i] << " | " << errors_f_prime[i] << " | " << errors_f_double_prime[i] << std::endl;
    //}
    //std::cout << "Max:" << std::endl;
    //std::cout << max_error_f << " | " << max_error_f_prime << " | " << max_error_f_double_prime << std::endl;
    //std::cout << "-----------------------------------------------" << std::endl;

    return 0;
}