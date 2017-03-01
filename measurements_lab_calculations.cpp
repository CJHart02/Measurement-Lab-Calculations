#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

const long double pi = 3.14159265358979323846264338328;

double cylVol(double inD, double outD, double length);
double rulCylVolUncert(double inD, double outD, double vol);
double calCylVolUncert(double inD, double outD, double vol);
double boxVol(double length, double width, double height);
double rulBoxVolUncert(double length, double width, double height, double vol);
double calBoxVolUncert(double length, double width, double height, double vol);
double density(double mass, double vol);
double rulDensityUncert(double mass, double vol, double density);
double calDensityUncert(double mass, double vol, double density);
double sigma(double rulVol, double calVol, double rulUncert, double calUncert);

int main()
{
    double sfbRulL, sfbRulW, sfbRulH, sfbMass, sfbRulVol, sfbRulVolUncert, sfbRulDensity, sfbRulDensUncert, sfbSig;
    double sfbCalL, sfbCalW, sfbCalH, sfbCalVol, sfbCalVolUncert, sfbCalDensity, sfbCalDensUncert;
    double lsbRulL, lsbRulW, lsbRulH, lsbMass, lsbRulVol, lsbRulVolUncert, lsbRulDensity, lsbRulDensUncert, lsbSig;
    double lsbCalL, lsbCalW, lsbCalH, lsbCalVol, lsbCalVolUncert, lsbCalDensity, lsbCalDensUncert;
    double cylRulInD, cylRulOutD, cylRulL, cylMass, cylRulVol, cylRulVolUncert, cylRulDensity, cylRulDensUncert, cylSig;
    double cylCalInD, cylCalOutD, cylCalL, cylCalVol, cylCalVolUncert, cylCalDensity, cylCalDensUncert;

    cout << endl << "LSB Ruler Dimensions in cm (L, W, H): ";
    cin >> lsbRulL >> lsbRulW >> lsbRulH;

    cout << endl << "LSB Caliper Dimensions in cm (L, W, H): ";
    cin >> lsbCalL >> lsbCalW >> lsbCalH;

    cout << endl << "LSB Mass in g: ";
    cin >> lsbMass;

    cout << endl << "SFB Ruler Dimensions in cm (L, W, H): ";
    cin >> sfbRulL >> sfbRulW >> sfbRulH;

    cout << endl << "SFB Caliper Dimensions in cm (L, W, H): ";
    cin >> sfbCalL >> sfbCalW >> sfbCalH;

    cout << endl << "SFB Mass in g: ";
    cin >> sfbMass;

    cout << endl << "CYL Ruler Dimensions in cm (L, Out D, In D): ";
    cin >> cylRulL >> cylRulOutD >> cylRulInD;

    cout << endl << "CYL Caliper Dimensions in cm (L, Out D, In D): ";
    cin >> cylCalL >> cylCalOutD >> cylCalInD;

    cout << endl << "CYL Mass in g: ";
    cin >> cylMass;

    lsbRulVol = boxVol(lsbRulL, lsbRulW, lsbRulH);
    lsbRulVolUncert = rulBoxVolUncert(lsbRulL, lsbRulW, lsbRulH, lsbRulVol);
    lsbCalVol = boxVol(lsbCalL, lsbCalW, lsbCalH);
    lsbCalVolUncert = calBoxVolUncert(lsbCalL, lsbCalW, lsbCalH, lsbCalVol);
    lsbRulDensity = density(lsbMass, lsbRulVol);
    lsbRulDensUncert = rulDensityUncert(lsbMass, lsbRulVol, lsbRulDensity);
    lsbSig = sigma(lsbRulVol, lsbCalVol, lsbRulVolUncert, lsbCalVolUncert);

    sfbRulVol = boxVol(sfbRulL, sfbRulW, sfbRulH);


    cylRulVol = cylVol(cylRulInD, cylRulOutD, cylRulL);

    sfbCalVol = cylVol(cylCalInD, cylCalOutD, cylCalL);

    cout << "LSB Ruler Volume: " << setprecision(2) << lsbRulVol << " +/- " << lsbRulVolUncert << " cm3." << endl;
    cout << "LSB Caliper Volume: " << setprecision(3) << lsbCalVol << " +/- " << lsbCalVolUncert << " cm3." << endl;
    cout << "LSB Ruler Density: " << setprecision(2) << lsbRulDensity << " +/- " << lsbRulDensUncert << " g/cm3." << endl;
    cout << "LSB Number of Sigma: " << setprecision(3) << lsbSig << endl;

    cout << "SFB Ruler Volume: " << setprecision(2) << sfbRulVol << " +/- " << sfbRulVolUncert << " cm3." << endl;
    cout << "SFB Caliper Volume: " << setprecision(3) << sfbCalVol << " +/- " << sfbCalVolUncert << " cm3." << endl;
    cout << "SFB Ruler Density: " << setprecision(2) << sfbRulDensity << " +/- " << sfbRulDensUncert << " g/cm3." << endl;
    cout << "SFB Number of Sigma: " << setprecision(3) << sfbSig << endl;

    cout << "CYL Ruler Volume: " << setprecision(2) << cylRulVol << " +/- " << cylRulVolUncert << " cm3." << endl;
    cout << "CYL Caliper Volume: " << setprecision(3) << cylCalVol << " +/- " << cylCalVolUncert << " cm3." << endl;
    cout << "CYL Ruler Density: " << setprecision(2) << cylRulDensity << " +/- " << cylRulDensUncert << " g/cm3." << endl;
    cout << "CYL Number of Sigma: " << setprecision(3) << cylSig << endl;


    return 0;
}

double cylVol(double inD, double outD, double length)
{
    double inVol, outVol, vol;

    /*inVol = ((pi/4) * (inD * inD)) * length;
    outVol = ((pi/4) * (outD * outD)) * length;
    */

    vol = (((pi/4) * (outD * outD)) * length) - (((pi/4) * (inD * inD)) * length);

    return vol;

}

double boxVol(double length, double width, double height)
{
    double vol;
    vol = length * width * height;
    return vol;
}

double density(double mass, double vol)
{
    double density;
    density = mass / vol;
    return density;
}

double rulCylVolUncert(double inD, double outD, double length, double vol)
{
    double uncert;
    double in = inD;
    double out = outD;
    double l = length;
    double volume = vol;

    uncert = (2*(0.05/inD) + 2*(0.05/outD) + 2*(0.05/length)) * vol;

    return uncert;
}
double calCylVolUncert(double inD, double outD, double length, double vol)
{
    double uncert;
    /*double in = inD;
    double out = outD;
    double l = length;
    double volume = vol;*/


    uncert = (2*(0.003/inD) + 2*(0.003/outD) + 2*(0.003/length)) * vol;

    return uncert;
}

double rulBoxVolUncert(double length, double width, double height, double vol)
{
    double uncert;
    double l = length;
    double w = width;
    double h = height;
    double volume = vol;

    uncert = (0.05/length + 0.05/width + 0.05/height) * vol;

    return uncert;
}

double calBoxVolUncert(double length, double width, double height, double vol)
{
    double uncert;

    uncert = (0.003/length + 0.003/width + 0.003/height) * vol;

    return uncert;
}

double rulDensityUncert(double mass, double vol, double density)
{
    double uncert;

    uncert = (0.05/mass + 0.05/vol) * density;

    return uncert;
}

double calDensityUncert(double mass, double vol, double density)
{
    double uncert;

    uncert = (0.003/mass + 0.003/vol) * density;

    return uncert;
}

double sigma(double rulVol, double calVol, double rulUncert, double calUncert)
{
    double sigma;

    sigma = abs(rulVol - calVol)/(rulUncert + calUncert);

    return sigma;

}



