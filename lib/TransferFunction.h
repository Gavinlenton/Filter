#ifndef TransferFunction_h
#define TransferFunction_h

#include "Polynomial.h"
#include <array>
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <complex>
#define _USE_MATH_DEFINES
#include <math.h>

template<typename T = double >
class TransferFunction {

public:
	typedef std::complex<T> Complex;

	TransferFunction() : numerator_({ { 1 } }), denominator_({ { 1 } }), samplingFrequency_(0.) { }

	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator) :
		numerator_(numerator), denominator_(denominator), samplingFrequency_(0.){
		normalize();
	}

	TransferFunction(const Polynomial<T>& numerator, const Polynomial<T>& denominator, double samplingFrequency) :
		numerator_(numerator), denominator_(denominator), samplingFrequency_(samplingFrequency) {
		normalize();
	}

	TransferFunction operator* (const TransferFunction<T>& tf) const;
	Complex a(unsigned i) const { return denominator_.getCoefficient(i); }
	Complex b(unsigned i) const { return numerator_.getCoefficient(i); }
	double getGainAt(double w) const;
	double getPhaseAt(double w) const;
	void getBode(std::vector<double>& xValues, std::vector<double>& gain, std::vector<double>& phase) const;
	double getSamplingFrequency() const { return samplingFrequency_; }
	void setSamplingFrequency(double samplingFrequency) { samplingFrequency_ = samplingFrequency; }

	size_t getNumeratorSize() { return numerator_.getSize(); }
	size_t getDenominatorSize() { return denominator_.getSize(); }

	template<typename U>
	friend std::ostream& operator<<(std::ostream& os, const TransferFunction<U>& tf);

private:
	Complex getResponseAt(double w) const;
	void normalize();
	double samplingFrequency_;
	Polynomial<T> numerator_, denominator_;

};

#include "TransferFunction.cpp"

#endif