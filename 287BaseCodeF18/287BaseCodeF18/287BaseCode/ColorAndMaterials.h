#pragma once
#include <vector>
#include "Defs.h"

typedef glm::vec3 color;

const color black(0, 0, 0);
const color red(1, 0, 0);
const color green(0, 1, 0);
const color blue(0, 0, 1);
const color magenta(1, 0, 1);
const color yellow(1, 1, 0);
const color cyan(0, 1, 1);
const color white(1, 1, 1);
const color gray(0.5f, 0.5f, 0.5f);
const color lightGray(0.8f, 0.8f, 0.8f);
const color darkGray(0.3f, 0.3f, 0.3f);

color brighten(const color &C);
color darken(const color &D);
float brightness(const color &C);

const color DEFAULT_COLOR = magenta;

/**
 * @struct	Material
 * @brief	Represents all the material information.
 */

struct Material {
	color ambient;		//!< ambient material property
	color diffuse;		//!< diffuse material property
	color specular;		//!< specular material property
	float shininess;	//!< shininess material property
	float alpha;		//!< alpha value of object. 1 if opaque.
	Material(const color &amb,
		const color &diff,
		const color &spec, float shininess);
	Material(const std::vector<float> &C);
	Material(const color &oneColor=black);

	friend Material operator *(float w, const Material &mat);
	Material operator *(float w) const;
	Material &operator +=(const Material &mat);
	Material operator +(const Material &mat) const;
	Material operator -(const Material &mat) const;
	static Material makeTransparent(float alpha, const color &C);
};

// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
const Material brass(std::vector<float>{0.329412f, 0.223529f, 0.027451f,
	0.780392f, 0.568627f, 0.113725f,
	0.992157f, 0.941176f, 0.807843f,
	27.8974f});
const Material bronze(std::vector<float>{0.2125f, 0.1275f, 0.054f,
	0.714f, 0.4284f, 0.18144f,
	0.393548f, 0.271906f, 0.166721f,
	25.6f});
const Material polishedBronze(std::vector<float>{0.25f, 0.148f, 0.06475f,
	0.4f, 0.2368f, 0.1036f,
	0.774597f, 0.458561f, 0.200621f,
	76.8f});
const Material chrome(std::vector<float>{0.25f, 0.25f, 0.25f,
	0.4f, 0.4f, 0.4f,
	0.774597f, 0.774597f, 0.774597f,
	76.8f});
const Material copper(std::vector<float>{0.19125f, 0.0735f, 0.0225f,
	0.7038f, 0.27048f, 0.0828f,
	0.256777f, 0.137622f, 0.086014f,
	12.8f});
const Material polishedCopper(std::vector<float>{0.2295f, 0.08825f, 0.0275f,
	0.5508f, 0.2118f, 0.066f,
	0.580594f, 0.223257f, 0.0695701f,
	51.2f});
const Material gold(std::vector<float>{0.24725f, 0.1995f, 0.0745f,
	0.75164f, 0.60648f, 0.22648f,
	0.628281f, 0.555802f, 0.366065f,
	51.2f});
const Material polishedGold(std::vector<float>{0.24725f, 0.2245f, 0.0645f,
	0.34615f, 0.3143f, 0.0903f,
	0.797357f, 0.723991f, 0.208006f,
	83.2f});
const Material tin(std::vector<float>{0.105882f, 0.058824f, 0.113725f,
	0.427451f, 0.470588f, 0.541176f,
	0.333333f, 0.333333f, 0.521569f,
	9.84615f});
const Material silver(std::vector<float>{0.19225f, 0.19225f, 0.19225f,
	0.50754f, 0.50754f, 0.50754f,
	0.508273f, 0.508273f, 0.508273f,
	51.2f});
const Material polishedSilver(std::vector<float>{0.23125f, 0.23125f, 0.23125f,
	0.2775f, 0.2775f, 0.2775f,
	0.773911f, 0.773911f, 0.773911f,
	89.6f});
const Material blackPlastic(std::vector<float>{0.0f, 0.0f, 0.0f,
	0.01f, 0.01f, 0.01f,
	0.50f, 0.50f, 0.50f,
	32.0f});
const Material cyanPlastic(std::vector<float>{0.0f, 0.1f, 0.06f,
	0.0f, 0.50980392f, 0.50980392f,
	0.50196078f, 0.50196078f, 0.50196078f,
	32.0f});
const Material greenPlastic(std::vector<float>{0.0f, 0.0f, 0.0f,
	0.1f, 0.35f, 0.1f,
	0.45f, 0.55f, 0.45f,
	32.0f});
const Material redPlastic(std::vector<float>{0.0f, 0.0f, 0.0f,
	0.5f, 0.0f, 0.0f,
	0.7f, 0.6f, 0.6f,
	32.0f});
const Material whitePlastic(std::vector<float>{0.0f, 0.0f, 0.0f,
	0.55f, 0.55f, 0.55f,
	0.70f, 0.70f, 0.70f,
	32.0f});
const Material yellowPlastic(std::vector<float>{0.0f, 0.0f, 0.0f,
	0.5f, 0.5f, 0.0f,
	0.60f, 0.60f, 0.50f,
	32.0f});
const Material blackRubber(std::vector<float>{0.02f, 0.02f, 0.02f,
	0.01f, 0.01f, 0.01f,
	0.4f, 0.4f, 0.4f,
	10.0f});
const Material cyanRubber(std::vector<float>{0.0f, 0.05f, 0.05f,
	0.4f, 0.5f, 0.5f,
	0.04f, 0.7f, 0.7f,
	10.0f});
const Material greenRubber(std::vector<float>{0.0f, 0.05f, 0.0f,
	0.4f, 0.5f, 0.4f,
	0.04f, 0.7f, 0.04f,
	10.0f});
const Material redRubber(std::vector<float>{0.05f, 0.0f, 0.0f,
	0.5f, 0.4f, 0.4f,
	0.7f, 0.04f, 0.04f,
	10.0f});
const Material whiteRubber(std::vector<float>{0.05f, 0.05f, 0.05f,
	0.5f, 0.5f, 0.5f,
	0.7f, 0.7f, 0.7f,
	10.0f});
const Material yellowRubber(std::vector<float>{0.05f, 0.05f, 0.0f,
	0.5f, 0.5f, 0.4f,
	0.7f, 0.7f, 0.04f,
	10.0f});
const Material pewter(std::vector<float>{0.105882f, 0.058824f, 0.113725f,
	0.427451f, 0.470588f, 0.541176f,
	0.333333f, 0.333333f, 0.521569f,
	9.846150f});

// Translucent materials - this code base does not support material alpha values
const Material emerald(std::vector<float>{0.0215f, 0.1745f, 0.0215f,
	0.07568f, 0.61424f, 0.07568f,
	0.633f, 0.727811f, 0.633f,
	76.8f});
const Material jade(std::vector<float>{0.135f, 0.2225f, 0.1575f,
	0.54f, 0.89f, 0.63f,
	0.316228f, 0.316228f, 0.316228f,
	12.8f});
const Material obsidian(std::vector<float>{0.05375f, 0.05f, 0.06625f,
	0.18275f, 0.17f, 0.22525f,
	0.332741f, 0.328634f, 0.346435f,
	38.4f});
const Material perl(std::vector<float>{0.25f, 0.20725f, 0.20725f,
	1.0f, 0.829f, 0.829f,
	0.296648f, 0.296648f, 0.296648f,
	11.264f});
const Material ruby(std::vector<float>{0.1745f, 0.01175f, 0.01175f,
	0.61424f, 0.04136f, 0.04136f,
	0.727811f, 0.626959f, 0.626959f,
	76.8f});
const Material turquoise(std::vector<float>{0.1f, 0.18725f, 0.1745f,
	0.396f, 0.74151f, 0.69102f,
	0.297254f, 0.30829f, 0.306678f,
	12.8f});

const Material testMaterial(std::vector<float>{0.4f, 0.5f, 0.6f, 0.9f, 1.0f, 0.9f, 0.9f, 0.8f, 0.7f, 1.0f});