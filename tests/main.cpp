#include "Polynomial.h"
#include "Filter.h"
#include "TransferFunction.h"
#include "Designer.h"

#include <array>
#include <iostream>
#include <fstream>
#include <vector>
using std::vector;
#include <fstream>
#include <cstdlib>
#include <algorithm>
#define _USE_MATH_DEFINES
#include <math.h>
#include <complex>

using std::cout;
using std::endl;

int main() {

	typedef std::complex<double> Complex;
	cout << "--------------------------" << endl;
	cout << "|        TEST #1         |" << endl;
	cout << "|       Polynomial       |" << endl;
	cout << "--------------------------" << endl;

	Polynomial<double> p1{ 1, 2 };
	Polynomial<double> p2{ 1, -2, 0 };
	Polynomial<double> p3{ 0, 2, 3, 4 };
	Polynomial<double> p4{ 5 };

	cout << "p1 =" << p1;
	cout << "p2 =" << p2;
	cout << "p3 =" << p3;
	cout << "p4 =" << p4;
	cout << endl;
	cout << "Scalar Multiplication" << endl;
	cout << "p1 * 2 = " << multiply<double>(p1, { 2 }) << endl;
	cout << "p2 * 3 = " << multiply<double>(p2, { 3 }) << endl;
	cout << "p3 * 4 = " << multiply<double>(p3, { 4 }) << endl;
	cout << "p4 * 5 = " << multiply<double>(p4, { 5 }) << endl;
	cout << endl;
	cout << "Complex Multiplication" << endl;
	cout << "p1 * (2 + 2i) = " << multiply<double>(p1, { Complex(2, 2) }) << endl;
	cout << "p2 * (3 - 3i) = " << multiply<double>(p2, { Complex(3, -3) }) << endl;
	cout << "p3 * (4 + 4i) = " << multiply<double>(p3, { Complex(4, 4) }) << endl;
	cout << "p4 * (5 - 5i) = " << multiply<double>(p4, { Complex(5, -5) }) << endl;
	cout << endl;
	cout << "Polynomial Multiplication" << endl;
	cout << "p1 * p1 = " << p1*p1 << endl;
	cout << "p2 * p1 = " << p2*p1 << endl;
	cout << "p3 * p1 = " << p3*p1 << endl;
	cout << "p4 * p1 = " << p4*p1 << endl;
	cout << endl;
	cout << "Polynomial Addition" << endl;
	cout << "p1 + p1 = " << add<double>(p1, p1) << endl;
	cout << "p2 + p1 = " << add<double>(p2, p1) << endl;
	cout << "p3 + p1 = " << add<double>(p3, p1) << endl;
	cout << "p4 + p1 = " << add<double>(p4, p1) << endl;

	
	
	/*
	std::cout << "p1 = " << p1;
	std::cout << "p1(3) = " << p1.solveFor(-1) << std::endl;


	//step response
	std::vector<double> zeroes(1, 0.0);
	std::vector<double> ones(1000, 1.0);
	std::vector<double> step(zeroes);
	step.insert(step.end(), ones.begin(), ones.end());

	TransferFunction<double> tfDesigned(Designer::butter2ndOrder<double>(6, 1000.));

	std::cout << "Designed filter\n";
	std::cout << tfDesigned.getSamplingFrequency() << std::endl;
	Filter<double> filter(tfDesigned);
	
	Filter<double> filter4th(Designer::butter<double>(4, 6, 1000));

	//std::cout << filter;
	//std::cout << filter4th;
//	std::cout << filterDouble;

	/*
	std::ofstream oF("output.csv");
	for (double val : step)
		oF << val << "," << std::abs(filter.filter(val)) << "," << std::abs(filter4th.filter(val)) << std::endl;
	oF.close();
	
	std::ofstream oFBode("bode_gain.csv");
	std::vector<double> xValues, gain, phase;
	tfDesigned.getBode(xValues, gain, phase);
	for (unsigned i{ 0 }; i < xValues.size(); ++i)
		oFBode << xValues.at(i) << "," << gain.at(i) << "," << phase.at(i) << std::endl;
	oFBode.close();
	/*
	std::ofstream oFBodePhase("bode_phase.csv");
	for (unsigned i{ 1 }; i < 1000; ++i)
		oFBodePhase << M_PI / 1000 * i << "," << tfDesigned.getPhaseAt(M_PI / 1000 * i) << std::endl;
	oFBodePhase.close();

	/*
	
	//test filtfilt
	vector<double> firstPass(filter.pass(step));
	std::reverse(firstPass.begin(), firstPass.end());
	vector<double> secondPass(filter.pass(firstPass));
	std::reverse(secondPass.begin(), secondPass.end());

	std::reverse(firstPass.begin(), firstPass.end());

	std::ofstream oF2("filtfilt.csv");
	for (unsigned i{ 0 }; i < step.size(); ++i)
		oF2 << step.at(i) << "," << firstPass.at(i) << "," << secondPass.at(i) << std::endl;
	oF2.close();


	/*
	
	//test linear phase fir filter 
	std::vector<double> firB( { 
		 0.00127199776427371,
		 0.00175973248875467,
		-0.000474050123699974,
		-0.00507655778150986,
		-0.00730622779100510,
		-0.00139834985893385,
		 0.0118182305510141,
		 0.0208600394665444,
		 0.0108509633977398,
		-0.0201948738097724,
		-0.0503421398292688,
		-0.0426075899832280,
		 0.0273002961309331,
		 0.144919701151270,
		 0.257048286517307,
		 0.303233271924363,
		 0.257048286517307,
		 0.144919701151270,
		 0.0273002961309331,
		-0.0426075899832280,
		-0.0503421398292688,
		-0.0201948738097724,
		 0.0108509633977398,
		 0.0208600394665444,
		 0.0118182305510141,
		-0.00139834985893385,
		-0.00730622779100510,
		-0.00507655778150986,
		-0.000474050123699974,
		 0.00175973248875467,
		 0.00127199776427371
	} );

	Polynomial<> n(firB), d{ 1 };

	TransferFunction<> tfFir(n, d);
	Filter<> firFilter(tfFir);
	vector<double> resultFir(firFilter.pass(step));

	std::ofstream oF3("comparison.csv");
	for (unsigned i{ 0 }; i < step.size(); ++i)
		oF3 << step.at(i) << "," << firstPass.at(i) << "," << secondPass.at(i) << ", " << resultFir.at(i) << std::endl;
	oF3.close();

	
	*/
	//	TransferFunction<double> h1(p1, p2);

	//std::cout << add(p, Polynomial<double>(std::vector<double>{ 1, 2, 3, 4 }));
	
	std::exit(EXIT_SUCCESS);
}