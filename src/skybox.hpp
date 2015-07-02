#ifndef SKYBOX_HPP
#define SKYBOX_HPP

#include "algebra.hpp"

class Skybox
{
public:
	Skybox();
	~Skybox();

private:
	Point3D topfl, topfr, toprl, toprr, botfl, botfr, botrl, botrr;

}